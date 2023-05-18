/*
 Main Program for arduino MKR zero 
 
 Description: 
 
 by: Miguel Coelho
*/

#include "Arduino.h"
#include "SAVE_WAV\SAVE_WAV.h"
#include <SPI.h>
#include <SD.h>

File myFile;

SAVE_WAV::SAVE_WAV() {
}

void SAVE_WAV::init()
{ 
  if (!SD.begin())  // see if the card is present and can be initialized:
  { 
    Serial.println("SD fail");
    return;   // don't do anything more if not
  }
}

void SAVE_WAV::DeleteWav()
{
  if (SD.exists("ALARM.wav"))
  {
    SD.remove("ALARM.wav");
    Serial.println("Remover Ficheiro");
    return;
  }
}
void SAVE_WAV::CreateWav()
{
  myFile = SD.open("ALARM.wav", FILE_WRITE);
  if (!myFile)
  {
    Serial.println("Erro ao criar");
    return;
  }
}


void SAVE_WAV::SAVE(byte c)
{
  myFile.write(c);
}

void SAVE_WAV::CLOSE()
{
  myFile.close();
  Serial.println("Close");
}


SAVE_WAV  WAV =  SAVE_WAV();
