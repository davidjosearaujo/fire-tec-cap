/*
 Send alarm program
 
 Description: code responsible for programming the RDS encoder, playing the audio file,
    activating and deactivating the Switch and obtaining a report on the RDS programming  
 
 by: Miguel Coelho V1.0
*/

#include "Arduino.h"
#include <SD.h>
#include <AudioZero.h>
#include "SendAlrm\Send_Alarm.h"
#include "Report_RDS\Report_RDS.h"

#define Duration_TIME                     1000

//Functions
void Send_WAV();
void Send_RDS();
void send_Wav(const char*, int);

//global variables
char report[]="---- ";

Send_Alarm::Send_Alarm(int pinoSW)
{
  pinSW = pinoSW;
}

void Send_Alarm::init()
{
  Serial1.begin(2400);
  checks.init();
  
  if (!SD.begin()) 
  {
    Serial.println(" failed!");
    while(true);
  }
  pinMode(pinSW, OUTPUT);
  digitalWrite(pinSW, LOW);
}

void Send_Alarm::sending(char PS[] , char PI_[], char AF[], int SWs )
{
  //------[SEND TO RDS_ENCODER]------
  Send_RDS();
  //Serial.println(PS); Debug
  report[0] = checks.check_RDS(PS);
  report[1] = checks.check_RDS(PI_);
  report[2] = checks.check_RDS(AF);
  //------------------------------~
  Serial.println("SW PIN IN ON!!");//####[Debug]#####
  digitalWrite(SWs, HIGH); //activating the Switch
  send_Wav("ALARM.wav", 1);
  digitalWrite(SWs, LOW); //deactivating the Switch
  Serial.println("SW PIN IN OFF!!");//####[Debug]#####
  Serial.print(report[0]); Serial.print(report[1]); Serial.println(report[2]);//####[Debug]#####
}

void Send_RDS() //Enviar cenas defaults para o RDS encoder
{
  Serial1.println("ECHO=0");
  Serial1.println("PTY=31");  //PTY=30=> Alarm Test // PTY=31=> Alarm 
  Serial1.println(F("RT1=Incendio na proximidade.Circule com cuidado")); //aloca na memoria Flash
}

void send_Wav(const char* filename,int times)
{
  int millis1,millis2;
  AudioZero.begin(44100);
  for(int i=0;i<times;i++)
  {
    File AlarmFile = SD.open(filename);
    if (!AlarmFile) 
    {
      Serial.println("error opening alarm audio");
      break;
    }
    millis1=millis();  
    AudioZero.play(AlarmFile);
  }

  AudioZero.end();

  millis2=millis(); 
  if((millis2-millis1)>=Duration_TIME)
  {
    report[3] = (byte)'+';
  }
  else
  {
    report[3] = (byte)'-';
  }
}

char* Send_Alarm::Result_Report()
{
  return report;
}

