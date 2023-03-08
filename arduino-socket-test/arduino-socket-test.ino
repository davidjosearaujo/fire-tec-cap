#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 1, 100};  // Board address
byte gw[] = {192, 168, 1, 1};
byte netmask[] = {255, 255, 255, 0};
String xml = "";

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
    xml += c;

    int l = xml.lastIndexOf('>');
    int f = xml.lastIndexOf('<')+1;
    if (l > f){
      String al = xml.substring(f,l);  
      if (al == "/identifier"){
        Serial.println(xml);  
      }
    }
  }
}
