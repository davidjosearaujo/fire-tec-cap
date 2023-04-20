#ifndef SAVE_WAV_h
#define SAVE_WAV_h

#include "Arduino.h"

class SAVE_WAV{
  public:
   SAVE_WAV();
   void init();
   void DeleteWav();
   void CreateWav();
   void SAVE(byte);
   void CLOSE();
  float DurationWav();
  private:
};

extern  SAVE_WAV  WAV;
#endif
