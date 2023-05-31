#ifndef ClientSCK_h
#define ClientSCK_h
#include "Arduino.h"

class ClientSCK{
  public:
    ClientSCK();
    void init();
    void connect_server();
    String return_receive();
    void Receive_report(char*);
    char* return_PI();
    char* return_PS();
    char* return_AF();

    char ReturnAF[130];
    char ReturnPS[15];
    char ReturnPI[7];

    int Time_prof();
    int Time_start();
    int Time_wav();

    unsigned long startc, endc,startRDS;

  private:

};
extern ClientSCK clients;

#endif
