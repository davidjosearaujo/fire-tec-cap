#include <Ethernet.h>
#include <SPI.h>

#include "structures.h"

// Connection
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 1, 100};  // Board address
byte gw[] = {192, 168, 1, 1};
byte netmask[] = {255, 255, 255, 0};

// Variables for real-time parsing
String xml = "";
bool param = false;
bool audio = false;

// Data variables
Frequency freqs[10];

EthernetServer server = EthernetServer(50005);
void setup()
{
  Serial.begin(9600);

  // initialize the ethernet device
  Ethernet.begin(mac, ip, gw, netmask);
  Serial.println(Ethernet.localIP());
  
  // start listening for clients
  server.begin();
}

void loop()
{
  // if an incoming client connects, there will be bytes available to read:
  EthernetClient client = server.available();
  if (client) {
    char c = client.read();

    if (xml != "" || c == '<')
      xml.concat(c);
    
    if (xml.indexOf('<') < xml.indexOf('>')){
      String tag = xml.substring(xml.lastIndexOf('<')+1, xml.lastIndexOf('>'));

      if (tag == "parameter"){
        param = true;
      } else if (tag == "derefUri"){
        audio = true;
      }else if (tag == "/parameter"){
        param = false;
      }else if (tag == "/derefUri"){
        audio = false;
      }

      if (param && tag == "/valueName"){
        String xmli = xml.substring(0, xml.length()-1);
        Serial.println(xmli.substring(xmli.lastIndexOf('>'),xmli.lastIndexOf('<')));
      }else if (param && tag == "/value"){
        String xmli = xml.substring(0, xml.length()-1);
        Serial.println(xmli.substring(xmli.lastIndexOf('>'),xmli.lastIndexOf('<')));
      }
      
      if (!param && !audio)
        xml = "";
    }
  }
}
