#include "Arduino.h"
#include "Report_RDS\Report_RDS.h"

Report_RDS::Report_RDS()
{
}

// ***** Receber do RDS encoder ***** //
char Report_RDS::check_RDS(char Comand[]) //verifica de os comandos RDS foram bem programados
{ 
  //Serial1.println(F("ECHO=0"));// para ver se funciona à primeira
  Serial1.readString();  
  //Serial.println(Comand);
  Serial1.println(Comand);
  
  const int BUFFER_SIZE = 7;
  char buf[BUFFER_SIZE];
  Serial1.readBytes(buf, BUFFER_SIZE);
  //Serial.println(rlen);  
  return buf[(BUFFER_SIZE-5)]; 
}

Report_RDS checks = Report_RDS();
