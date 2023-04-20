/*
 Main Program for arduino MKR zero 
 
 Description: -> simple communication and send alarm
 
 by: Miguel Coelho V1.0 
*/

#include "client\ClientSCK.h"
#include "SendAlrm\Send_Alarm.h"
#include "SAVE_WAV\SAVE_WAV.h"
#include "Arduino.h"

#define SW_pin 1

//------[define classes]------
Send_Alarm  Send_Alarm(SW_pin);
//------------------------

void setup()
{
  Serial.begin(2400);
  while (!Serial); 
  clients.init();
  Send_Alarm.init();
}

void loop()
{
  clients.conect_server();

  if (clients.return_receive() == "Request")
  {
    return;
  }

  Send_Alarm.sending(&(clients.return_PS()[0]), &(clients.return_PI()[0]), &(clients.return_AF()[0]),SW_pin);
  
  clients.Receive_report(Send_Alarm.Result_Report());
}
