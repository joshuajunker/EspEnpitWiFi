#ifndef EspEnPitWiFi_h 
#define EspEnPitWiFi_h 
#include "Arduino.h"

String receiveDataFromToTime(String first_Char,String last_Char,int LTIME);
String receiveData(String last_Char);
void ReadAndWrite();
//int wait = -1; 

class ATcommand {
  public:
  int wait = -1; 
  boolean Display_ON = true;
  boolean Display_OFF = false;
  void debug(String LAT_command,unsigned int LTIME);
  void command(String LAT_command,unsigned int LTIME);
  String getString(String LAT_command,unsigned int LTIME); 
  void ATcommand::WiFi(String LAT_SSID,String LAT_Password,boolean Lscreen);
  void ATcommand::TCP(unsigned int Llink_ID,String LIPaddress,unsigned int Lport,boolean Lscreen,unsigned int LTIME);
  private:
  //int wait = -1; 
};

#endif