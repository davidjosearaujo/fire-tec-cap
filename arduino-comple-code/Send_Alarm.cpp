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
  Serial1.setTimeout(500);

  pinMode(pinSW, OUTPUT);
  digitalWrite(pinSW, LOW);
}

void Send_Alarm::sending(char PS[] , char PI_[], char AF[], int SWs )
{
  //------[SEND TO RDS_ENCODER]------
  Send_RDS();
  //Serial1.println(AF); Serial1.println(PS);Serial1.println(PI_);//Only send rds
  report[0] = checks.check_RDS(PS); report[1] = checks.check_RDS(PI_); report[2] = checks.check_RDS(AF); //Send and Reiceive RDS
  //------------------------------
  startsa=millis(); //PROFILING
  digitalWrite(SWs, HIGH); //activating the Switch
  send_Wav("ALARM.wav", 2);
  digitalWrite(SWs, LOW); //deactivating the Switch
  endsa=millis(); //PROFILING
  //Serial.println("SW OFF");//####[Debug]#####
  //Serial.print(report[0]); Serial.print(report[1]); Serial.println(report[2]);//####[Debug]#####
}

void Send_RDS() //Enviar cenas defaults para o RDS encoder
{
  Serial1.println(F("ECHO=0"));
  Serial1.println(F("PTY=31"));  //PTY=30=> Alarm Test PTY=31=> Alarm 
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

int Send_Alarm::Time_profsa() //PROFILING
{
  return  endsa-startsa;
}
