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
  clients.connect_server();

  if (clients.return_receive() == "Request")
  {
    return;
  }

   unsigned long start_sending_time = millis();//PROFILING
  Send_Alarm.sending(&(clients.return_PS()[0]), &(clients.return_PI()[0]), &(clients.return_AF()[0]),SW_pin);
    unsigned long end_sending_time = millis();//PROFILING

  clients.Receive_report(Send_Alarm.Result_Report());

    unsigned long end_all_time = millis();//PROFILING

  Serial.println("######[ Profiling Report]######");
  Serial.print("  Total duration of the write wav file:  ");   Serial.print((clients.Time_wav())/1000.0);                   Serial.println(" seconds");
  Serial.print("  Total duration of the clientSCK code:  ");   Serial.print((clients.Time_prof())/1000.0);                 Serial.println(" seconds");
  Serial.print("  Total duration of the split all RDS comands:  ");   Serial.print((clients.Time_prof()-clients.Time_wav())/1000.0); Serial.println(" seconds");
  Serial.print("  Alert speech time duration :  ");                Serial.print((Send_Alarm.Time_profsa())/1000.0);            Serial.println(" seconds");
  Serial.print("  Total duration of the Send_Alarm code:  ");  Serial.print((end_sending_time-start_sending_time)/1000.0); Serial.println(" seconds");
  Serial.print("  Average time duration of sending and receiving all RDS commands:  "); Serial.print(((end_sending_time-start_sending_time)-(Send_Alarm.Time_profsa()))/1000.0);   Serial.println(" seconds");
  Serial.print("  Total duration of all code:  ");             Serial.print((end_all_time-clients.Time_start())/1000.0);   Serial.println(" seconds");
  Serial.println("####################################");
}
