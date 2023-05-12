#ifndef Send_Alarm_h
#define Send_Alarm_h

class Send_Alarm{
  public:
   Send_Alarm(int);
   void init();
   void sending(char*,char*,char*,int);
   char* Result_Report();

  private:
    int pinSW;
};

#endif
