#include "Arduino.h"
#include "ClientSCK.h"

#include <Ethernet.h>

//pressupostos
byte mac[] = {0xA8, 0x61, 0x0A, 0xAE, 0x8A, 0x0A};
byte server[] = {192, 168, 0, 23}; // server ip
int port=8080;
IPAddress ip(192, 168, 0, 21);   // IP address

//global variables
static boolean clientActive = false;
char incomingByte;
String retorno;

String receive_msg();

ClientSCK::ClientSCK(int pino)
{
  pin=pino;
}

EthernetClient client;  // create an object EthernetClient for use in this sketch
 
void ClientSCK::init()
{
  Serial.begin(2400);
  Serial.print("Starting Ethernet...");
  
  Ethernet.begin(mac, ip);  // initialize Ethernet device
 
  Serial.println("SUCCESS");
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  delay(1000);
}

void ClientSCK::conect_server()
{  retorno=""; //reset;
  String string1;
  Serial.print("Searching for server...");
  if(client.connected())
  {
    Serial.println("Connected to the server.");
    receive_msg();
  }
  else
  {
  client.connect(server, port);
  Serial.println("Failed to connect to the server.");
  }
}

String receive_msg()
{ 
  char c;
  String line;
  while(client.available()) 
  {
  //-------alternativa 1-------
  //c = client.read();
  //string1.concat(c);
      
  //-------alternativa 2-------
    line = client.readStringUntil('\0');
  //Serial.println(line);
  }
  retorno=line;
   //Serial.println(string1); //da alternativa 1
}

String ClientSCK::return_receive()
{
    return retorno;
}
