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

    if (xml != "" || c == '<' || param || audio)
      xml.concat(c);

    Serial.println("xml: " + xml);
    
    if (xml.indexOf('<') < xml.indexOf('>')){
      String t = xml.substring(1, xml.indexOf('>'));

      Serial.println("tag: " + t);
      
      char tag[t.length()+1];
      t.toCharArray(tag, t.length()+1);

      if (tag == "parameter"){
        param = true;
      } else if (tag == "resource"){
        audio = true;
      }else if (tag == "/parameter"){
        param = false;
      }else if (tag == "/resource"){
        audio = false;
      }
      
      int opn = xml.lastIndexOf('>');
      int cls = xml.lastIndexOf('<');
      if (opn < cls && (param || audio)){
          if (tag == "valueName"){
            //Serial.println("ValueName: " + xml.substring(opn,cls));
            xml = "";
          }else if (tag == "value"){
            //Serial.println("Value: " + xml.substring(opn,cls));
            xml = "";
          }else if (tag == "derefUri"){
            //Serial.println("audio: " + xml.substring(opn,cls));
            xml = "";
          }
      }

      Serial.println(!param && !audio);
      if (!param && !audio)
        xml = "";
    }

    
  }
}
