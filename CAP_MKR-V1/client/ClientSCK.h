#ifndef ClientSCK_h
#define ClientSCK_h
#include "Arduino.h"

class ClientSCK{
  public:
    ClientSCK();
    void init();
    void conect_server();
    String return_receive();
    void Receive_report(char*);
    char* return_PI();
    char* return_PS();
    char* return_AF();

    char ReturnAF[130];
    char ReturnPS[15];
    char ReturnPI[7];

  private:
};
extern ClientSCK clients;

#endif
