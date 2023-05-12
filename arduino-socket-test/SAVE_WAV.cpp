#include "Arduino.h"
#include "SAVE_WAV.h"
#include <SPI.h>
#include <SD.h>


#define SD_ChipSelectPin  4

File myFile;
float duration = 3.0;

SAVE_WAV::SAVE_WAV() {
}

void SAVE_WAV::init()
{
  //Serial.print("Start SD");
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");
    return;   // don't do anything more if not
  }
}
void SAVE_WAV::DeleteWav()
{
  if (SD.exists("ALARM.mp3"))
  {
    SD.remove("ALARM.mp3");
    //Serial.println("Remover ALARM.wav...");
  }
  return;
}
void SAVE_WAV::CreateWav()
{
  myFile = SD.open("ALARM.mp3", FILE_WRITE);
  if (!myFile)
  {
    //Serial.println("Erro ao criar");
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

  File file = SD.open("ALARM.mp3");
  if (file)
  {

    file.seek(44);
    // Read the number of samples
    unsigned long numSamples = (file.size() - 44) / 2;
    duration = (float)numSamples / (float)(16000.0);
    file.close();
    Serial.println("Audio file written successfully!");
    //Serial.print("duration:  "); Serial.println(duration);
  }
  //ler os primeiros 44 bytes, que são o cabeçalho do arquivo .wav
  //byte header[44];
  //file.read(header, 44);

  // extrair o número de amostras e a taxa de amostragem
  //unsigned int sampleCount = (header[43] << 24) | (header[42] << 16) | (header[41] << 8) | header[40];
  //unsigned int sampleRate = (header[27] << 24) | (header[26] << 16) | (header[25] << 8) | header[24];
  //Serial.print("duration:     "); Serial.println(duration);

  //Serial.println("Dados escritos em: ALARM.wav");
}


float SAVE_WAV::DurationWav()
{
  return duration;
}

SAVE_WAV  WAV =  SAVE_WAV();
