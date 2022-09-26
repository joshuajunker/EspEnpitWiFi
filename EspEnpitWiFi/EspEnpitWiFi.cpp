
#include "EspEnpitWiFi.h"
#include "Arduino.h"
//int wait = -1;
void ATcommand::debug(String LAT_command,unsigned int LTIME){
  Serial1.print(LAT_command);
  Serial1.print("\r\n");

  String findOK;//OKとERRORを探す
  char printAT;
  uint32_t Time = millis();
  
  while(true){
    if(Serial1.available()){
      printAT = Serial1.read();
      Serial.write(printAT);
      findOK += String(printAT);
    }else{
      if(findOK.indexOf("OK\r\n") > 0){
      break;
    }else if(findOK.indexOf("ERROR\r\n") > 0){
      break;
    }
    }

    if(Time + LTIME <= millis()){
        break;
      }
  }
}

void ATcommand::command(String LAT_command,unsigned int LTIME){
  Serial1.print(LAT_command);
  Serial1.print("\r\n");

  String findOK;//OKとERRORを探す
  char printAT;
  uint32_t Time = millis();
  
  while(true){
    if(Serial1.available()){
      printAT = Serial1.read();
      findOK += String(printAT);
    }else{
      if(findOK.indexOf("OK\r\n") > 0){
      break;
    }else if(findOK.indexOf("ERROR\r\n") > 0){
      break;
    }
    }

    if(Time + LTIME <= millis()){
        break;
      }
  }
}

String ATcommand::getString(String LAT_command,unsigned int LTIME){
  Serial1.print(LAT_command);
  Serial1.print("\r\n");

  String findOK;//OKとERRORを探す
  char printAT;
  uint32_t Time = millis();
  
  while(true){
    if(Serial1.available()){
      printAT = Serial1.read();
      findOK += String(printAT);
    }else{
      if(findOK.indexOf("OK\r\n") > 0){
      break;
    }else if(findOK.indexOf("ERROR\r\n") > 0){
      break;
    }
    }

    if(Time + LTIME <= millis()){
        break;
      }
  }
  return findOK;
}

void ATcommand::WiFi(String LAT_SSID,String LAT_Password,boolean Lscreen){
  while(true){
    String LWiFi = "AT+CWJAP=\"" + LAT_SSID + "\",\"" + LAT_Password + "\"";

    Serial1.print(LWiFi);
    Serial1.print("\r\n");

    String findOK;//OKとERRORを探す
    char printAT;//ATのレスポンス
    boolean CONNECTtrue = false;

    while(true){
      if(Serial1.available()){
        printAT = Serial1.read();
        if(Lscreen == true){
          Serial.write(printAT);
        }
        findOK += String(printAT);
      }else{
        if(findOK.indexOf("OK") > 0){
          CONNECTtrue = true;
          break;
        }else if(findOK.indexOf("CWJAP:1") > 0){
          Serial.println(" : connection timeout.");
          delay(800);
          break;
        }else if(findOK.indexOf("CWJAP:2") > 0){
          Serial.println(" : wrong password.");
          delay(800);
          break;
        }else if(findOK.indexOf("CWJAP:3") > 0){
          Serial.println(" : cannot find the target AP.");
          delay(800);
          break;
        }else if(findOK.indexOf("CWJAP:4") > 0){
          Serial.println(" : connection failed. ");
          delay(800);
          break;
        }
      }
    }
    if(CONNECTtrue == true){
    break;
   }
  }
}

void ATcommand::TCP(unsigned int Llink_ID,String LIPaddress,unsigned int Lport,boolean Lscreen,unsigned int LTIME){
  
  String LTCP = "AT+CIPSTART=" + String(Llink_ID) + ",\"TCP\",\"" + LIPaddress + "\"," + String(Lport) + ",1000";

  Serial1.print(LTCP);
  Serial1.print("\r\n");
  
  String findOK;//OKとERRORを探す
  char printAT;//ATのレスポンス
  uint32_t Time = millis();

  while(true){
    if (Serial1.available()){
      printAT = Serial1.read();
      if(Lscreen == true){
        Serial.write(printAT);
      }
      findOK += String(printAT);
    }else{
      if(findOK.indexOf("OK") > 0){
        break;
      }else if(findOK.indexOf("ERROR") > 0){
        break;
      }
    }

    if(Time + LTIME <= millis()){
        break;
      }
  }
}

String receiveDataFromToTime(String first_Char,String last_Char,int LTIME){
  String findChar;//OKとERRORを探す
  char printChar;//ATのレスポンス
  uint32_t Time = millis();

  while(true){
    if(Serial1.available()){
      printChar = Serial1.read();
      findChar += String(printChar);
    }else{
      if(findChar.indexOf(last_Char) > 0){
        findChar = findChar.substring(findChar.indexOf(first_Char), findChar.indexOf(last_Char)+1);
        break;
      }
    }
    if(LTIME == -1){
      
    }else{
      if(Time + LTIME <= millis()){
        break;
      }
    }
  }
  return findChar;
}

void ReadAndWrite(){
  if (Serial1.available())
    Serial.write(Serial1.read());
  if (Serial.available())
    Serial1.write(Serial.read());
}

String receiveData(String last_Char){
  String findChar;//OKとERRORを探す
  char printChar;//ATのレスポンス

  while(true){
    if(Serial1.available()){
      printChar = Serial1.read();
      findChar += String(printChar);
    }else{
      if(findChar.indexOf(last_Char) > 0){
        break;
      }
    }
  }
  return findChar;
}


