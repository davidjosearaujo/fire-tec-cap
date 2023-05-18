#include "Arduino.h"
#include "Report_RDS\Report_RDS.h"

Report_RDS::Report_RDS()
{
}

void Report_RDS::init()
{
  Serial1.begin(2400);
  Serial.begin(2400);
  while (!Serial); 
  Serial.println("report");
}

// ***** Receber do RDS encoder ***** //
char Report_RDS::check_RDS(char Comand[]) //verifica de os comandos RDS foram bem programados
{ 
  //Serial1.readString();  
  const int BUFFER_SIZE = 50;
  char buf[BUFFER_SIZE];
  //Serial.println(Comand);
  Serial1.println(Comand);
  int rlen = Serial1.readBytes(buf, BUFFER_SIZE);
  //Serial.println(buf[(rlen-5)]);
  return buf[(rlen-5)]; 
}

Report_RDS checks = Report_RDS();
