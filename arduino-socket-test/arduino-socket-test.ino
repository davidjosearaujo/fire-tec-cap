#include <SHA224.h>
#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

#include "SAVE_WAV.h"
#include "structures.h"

// Connection
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 1, 100};  // Board address
byte gw[] = {192, 168, 1, 1};
byte netmask[] = {255, 255, 255, 0};

// Variables for real-time parsing
String xml = "";

/* Data variables
 * Fixed size for parameters with:
 *  - Radio station name;
 *  - Program identification,
 *  - Frequency list.
 */ 
Parameter params[3];
int index1 = 0;

EthernetServer server = EthernetServer(50005);
EthernetClient client;

void setup()
{
  Serial.begin(9600);

  // initialize the ethernet device
  Ethernet.begin(mac, ip, gw, netmask);
  Serial.println(Ethernet.localIP());

  WAV.init();

  // start listening for clients
  server.begin();
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

void loop()
{
  // if an incoming client connects, there will be bytes available to read:
  client = server.available();
  while (client.available())
  {
    char c = client.read();

    if (xml != "" || c == '<')
      xml.concat(c);
    
    if (xml.indexOf('<') < xml.indexOf('>')){
      String tag = xml.substring(xml.lastIndexOf('<')+1, xml.lastIndexOf('>'));
      xml = "";
      
      // Detect tags of interest: <parameter>, </parameter> and <derefUri>
      if (tag == "parameter"){
        receive_param();
      } else if (tag == "derefUri"){
        WAV.DeleteWav();
        WAV.CreateWav();
        receive_audio();
        break;
      }
    }
  }
}
