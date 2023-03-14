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

/* Data variables
 * Fixed size for parameters with:
 *  - Radio statio name;
 *  - Program identificaion,
 *  - Frequency list.
 */ 
Parameter params[3];
int index = 0;

Audio first_audio;
Audio *temp;

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
        params[index].valueName = xmli.substring(xmli.lastIndexOf('>'),xmli.lastIndexOf('<'));
        Serial.println(params[index].valueName);
      }else if (param && tag == "/value"){
        String xmli = xml.substring(0, xml.length()-1);
        params[index].value = xmli.substring(xmli.lastIndexOf('>'),xmli.lastIndexOf('<'));
        Serial.println(params[index].value);
        index++;
      }

      if (tag == "/derefUri"){
          String xmli = xml.substring(0, xml.length()-1);
          // TODO - Add audio to chunks in a linked list
          Serial.println(xmli.substring(xmli.lastIndexOf('>'),xmli.lastIndexOf('<')));
      }
      
      if (!param && !audio)
        xml = "";
    }
  }
}
