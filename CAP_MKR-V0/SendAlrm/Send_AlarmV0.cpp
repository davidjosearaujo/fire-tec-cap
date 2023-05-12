/*
 Send alarm program
 
 Description: code responsible for programming the RDS encoder, playing the audio file,
    activating and deactivating the Switch and obtaining a report on the RDS programming  
 
 by: Miguel Coelho V0.0
*/

#include "Arduino.h"
#include "SendAlrm\Send_Alarm.h"


//Functions
void Send_WAV();
void Send_RDS();

//global variables
char result_check[]="----- ";

Send_Alarm::Send_Alarm(int pinoSW)
{
  pinSW = pinoSW;
}

void Send_Alarm::init()
{
  Serial1.begin(2400);
  pinMode(pinSW, OUTPUT);
  digitalWrite(pinSW, LOW);
}

void Send_Alarm::sending(char PS[] , char PI_[], char AF[])
{
  //------[SEND TO RDS_ENCODER]------
  Send_RDS();
  Serial1.println(PS);
  Serial1.println(PI_);
  Serial1.println(AF);
  //------------------------------~

  Serial.println("PIN IN ON!!");
  digitalWrite(pinSW, HIGH); //activating the Switch
  //SEND_WAV();
  digitalWrite(pinSW, LOW); //deactivating the Switch
  Serial.println("PIN IN OFF!!");
}

void Send_RDS() //Enviar cenas defaults para o RDS encoder
{
  Serial1.println("ECHO=0");
  Serial1.println("PTY=31");  //PTY=30=> Alarm Test // PTY=31=> Alarm 
  Serial1.println(F("RT1=Incendio na proximidade.Circule com cuidado")); //aloca na memoria Flash
}

void Send_WAV()
{
  result_check[4] = (byte)'-';
}

