#include "ClientSCK.h"

//definir classes
int p=12;
ClientSCK clients(p);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(2400); // For testing
  clients.init();
}

void loop() 
{
  clients.conect_server();
  
  if ( clients.return_receive().length()!=0)
  {
    Serial.println(clients.return_receive());
  }
}
