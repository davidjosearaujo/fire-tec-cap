#ifndef ClientSCK_h
#define ClientSCK_h

class ClientSCK{
  public:
   ClientSCK(int);
   void init();
    void conect_server();
   String return_receive();
  private:
  int pin;
};

#endif
