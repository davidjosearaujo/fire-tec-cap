/*
 Main Program for arduino MKR zero 
 
 Description: 
 
 by: Miguel Coelho and David Araújo
*/

#include "Arduino.h"
#include "client\ClientSCK.h"
#include <SPI.h>
#include <Ethernet.h>
#include "SAVE_WAV\SAVE_WAV.h"
#include "structures.h"

//########[ Pressupostos ]###############
IPAddress ip(192, 168, 0, 21);   // IP address
byte mac[] = {0xA8, 0x61, 0x0A, 0xAE, 0x8A, 0x0A}; //mac do arduino
byte server[] = {192, 168, 0, 23}; // server ip
int port = 8080; //Porto para comunicar com o server
#define LED 2
//##############################################



/* Data variables
 * Fixed size for parameters with:
 *  - Radio station name;
 *  - Program identification,
 *  - Frequency list.
 */ 
Parameter params[3];
int index1 = 0;
// Variables for real-time parsing
String xml = "";
//####################################

//Functions
void receive_msg();
void Ethernet_Status();
void report2server();

//global variables
char retorno[] = "";
String protocol, St1;
int FlagLED=0;

ClientSCK::ClientSCK() {
}

EthernetClient client;  // create an object EthernetClient for use in this sketch

void ClientSCK::init()
{ 
  WAV.init(); 
  Ethernet.begin(mac, ip); // initialize Ethernet device
  pinMode(LED, OUTPUT);
  Ethernet_Status(); // Verifica o estado da ethernet

  Serial.print(" Ethernet Cilent ip:  "); Serial.println(Ethernet.localIP());
}

void ClientSCK::connect_server()
{
  Ethernet_Status(); // Verifica o estado da ethernet
  Serial.print("Searching...");
  while ( !client.connected())    //Connectar via timer?
  {
    client.connect(server, port);
  }
  WAV.DeleteWav();
  digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  if (client.connected()) //acho que posso eliminar isto daqui??????
  { 
    Serial.println("Connected");
    delay(100);
    receive_msg();
    client.stop();
  }
  digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
}

void receive_param(){
  while (client.available()){
    char c = client.read();

    if (xml != "" || c == '<')
      xml.concat(c);

    String tag = xml.substring(xml.lastIndexOf('<')+1, xml.lastIndexOf('>'));

    // Retrieve parameter values
    if (tag == "/valueName"){
      params[index1].valueName = xml.substring(xml.indexOf('>')+1, xml.lastIndexOf('<'));
      xml = "";
    }else if (tag == "/value"){
      params[index1].value = xml.substring(xml.indexOf('>')+1, xml.lastIndexOf('<'));
      index1++;
      break;
    }
  }
}

void receive_audio(){
  String audiobyte = "";
  
  while (client.available()){
    char c = client.read();

    // Write audio file
    if(c == '<'){
      WAV.CLOSE();
      break;
    }else{  // Read two characters that form the hex value and convert them to a byte
      audiobyte.concat(c);
      if(audiobyte.length() == 2){
        byte hexvalue = strtol(audiobyte.c_str(), NULL, 16);
        WAV.SAVE(hexvalue);
        audiobyte = "";
      }
    }
  }
}

void receive_msg()
{
  //report
  St1="";
  if(client.read()=='?')
  {
    report2server();
    return;
  }

  while (client.available())
  {
    char c = client.read();

    if (xml != "" || c == '<')
      xml.concat(c);
    
    if (xml.indexOf('<') < xml.indexOf('>')){
      String tag = xml.substring(xml.lastIndexOf('<')+1, xml.lastIndexOf('>'));
      xml="";
      // Detect tags of interest: <parameter>, </parameter> and <derefUri>
      if (tag == "parameter"){
        receive_param();
      } else if (tag == "derefUri"){
        WAV.CreateWav();
        receive_audio();
        break;
      }
    }
  }
}

char* ClientSCK:: return_PS()
{
  ReturnPS[(params[0].value).length() + 1];
  (params[0].value).toCharArray(ReturnPS, (params[0].value).length() + 1);

  return ReturnPS;
}

char* ClientSCK:: return_PI()
{
  ReturnPI[(params[1].value).length() + 1];
  (params[1].value).toCharArray(ReturnPI, (params[1].value).length() + 1);

  return ReturnPI;
}

char* ClientSCK:: return_AF()
{ 
  ReturnAF[(params[2].value).length() + 1];
  (params[2].value).toCharArray(ReturnAF, (params[2].value).length() + 1);

  return ReturnAF;
}


String ClientSCK::return_receive()
{
  return St1;
}

void ClientSCK::Receive_report(char char3[])
{
  protocol = String(char3); 
  Serial.println(protocol); 
}

void report2server()
{
  St1="Request";
  char inputAF[protocol.length() + 1];
  protocol.toCharArray(inputAF, protocol.length() + 1);

  char sendBuf[strlen(inputAF) + 5];
  sprintf(sendBuf, "%s", inputAF );
  client.write(sendBuf);
  client.stop();                      //Verificar esta questão
}


void Ethernet_Status()
{
  while((Ethernet.linkStatus() == LinkOFF)  || (Ethernet.hardwareStatus() == EthernetNoHardware) )
  {
    if (FlagLED==0) //#Debug
    {
      Serial.println("Ethernet shield was not found");
      Serial.println("   OR");
      Serial.println("Ethernet cable is not connected");
      FlagLED=1;
    }
    //### LED Blink ######
    digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a second
    digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
    delay(500);                      // wait for a second
    //########################
  }
  digitalWrite(LED, LOW); //Forçar o LED a Low
}

ClientSCK clients =  ClientSCK();
