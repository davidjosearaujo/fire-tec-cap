#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 0, 100};  // Board address
byte gw[] = {192, 168, 0, 1};
byte netmask[] = {255, 255, 255, 0};
bool nl = false;
int i = 0;

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
    Serial.print((char)client.read());
  }
}
