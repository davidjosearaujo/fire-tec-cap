/*
 Main Program for arduino MKR zero 
 
 Description: 
 
 by: Miguel Coelho
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
//##############################################



/* Data variables
 * Fixed size for parameters with:
 *  - Radio statio name;
 *  - Program identificaion,
 *  - Frequency list.
 */ 
Parameter params[3];
//####################################

//Functions
void receive_msg();
void Ethernet_Status();

//global variables
char retorno[] = "";
String protocol;
int FlagLED=0;

ClientSCK::ClientSCK() {
}

EthernetClient client;  // create an object EthernetClient for use in this sketch

void ClientSCK::init()
{ 
  WAV.init(); 
  Ethernet.begin(mac, ip); // initialize Ethernet device

  Serial.print(" Ethernet Cilent ip:  "); Serial.println(Ethernet.localIP());
}

void ClientSCK::conect_server()
{
  Serial.print("Searching...");
  while ( !client.connected())    //Connectar via timer?
  {
    client.connect(server, port);
  }
  WAV.DeleteWav();
  if (client.connected()) //acho que posso eliminar isto daqui??????
  { 
    Serial.println("Connected");
    delay(100);
    receive_msg();
    client.stop();
  }
}

void receive_msg()
{
  // Variables for real-time parsing
  String xml = "";
  bool param = false;
  bool audio = false;
  String audiobyte = "";
  int index1 = 0;
  
  while (client.available())
  {
    char c = client.read();

    if ((xml != "" || c == '<') && !audio)
      xml.concat(c);
    
    if (xml.indexOf('<') < xml.indexOf('>')){
      String tag = xml.substring(xml.lastIndexOf('<')+1, xml.lastIndexOf('>'));

      // Detect tags of interest: <parameter>, </parameter> and <derefUri>
      if (tag == "parameter" && !param){
        param = true;
      } else if (tag == "derefUri" && !audio){
        //WAV.DeleteWav();
        WAV.CreateWav();
        audio = true;
      }else if (tag == "/parameter" && param){
        param = false;
      }

      // Retrieve parameter values
      if (param && tag == "/valueName"){
        String xmli = xml.substring(0, xml.length()-1);
        params[index1].valueName = xmli.substring(xmli.lastIndexOf('>'),xmli.lastIndexOf('<'));
        //Serial.println(params[index1].valueName);
      }else if (param && tag == "/value"){
        String xmli = xml.substring(0, xml.length()-1);
        params[index1].value = xmli.substring((xmli.lastIndexOf('>')+1),xmli.lastIndexOf('<'));
        //Serial.println(params[index1].value);
        index1++;
      }

      // Write audio file
      if (audio && c != '>'){
        if(c == '<'){
          WAV.CLOSE();
          audio = false;
        }else{
          // Read two characters that form the hexvalue and convert them to a byte
          audiobyte.concat(c);
          if(audiobyte.length() == 2){
            byte hexvalue = strtol(audiobyte.c_str(), NULL, 16);
            //Serial.print(hexvalue);
            WAV.SAVE(hexvalue);
            audiobyte = "";
          }
        }
      }
      
      if (!param && !audio)
        xml = "";
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

ClientSCK clients =  ClientSCK();
