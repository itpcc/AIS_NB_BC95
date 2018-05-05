#include "AIS_NB_BC95.h"

AIS_NB_BC95 AISnb;
bool debug = true;

void getCEREGStatus(unsigned char status){
  switch(status){
    case 0: 
      Serial.println(F("0: Disable network registration unsolicited result code."));
    break;

    case 1: 
      Serial.println(F("1: Enable network registration unsolicited result code."));
    break;

    case 2: 
      Serial.println(F("2: Enable network registration and location information unsolicited result code."));
    break;

    case 3: 
      Serial.println(F("3: Enable network registration, location information and EMM cause value information unsolicited result code."));
    break;

    case 4: 
      Serial.println(F("4: For a UE that requests PSM, enable network registration and location information unsolicited result code."));
    break;

    case 5: 
      Serial.println(F("5: For a UE that requests PSM, enable network registration, location information and EMM cause value information unsolicited result code."));
    break;

    default: 
      Serial.println(F("Unknow"));
    break;
  }
}

void getEPSStatus(unsigned char EPS_status){
  switch(EPS_status){
    case 0:
      Serial.println(F("0: Not registered, MT is not currently searching an operator to register to."));
    break;

    case 1:
      Serial.println(F("1: Registered, home network."));
    break;

    case 2:
      Serial.println(F("2: Not registered, but MT is currently trying to attach or searching an operator to register to."));
    break;

    case 3:
      Serial.println(F("3: Registration denied."));
    break;

    case 5:
      Serial.println(F("5: Registered, roaming."));
    break;

    case 8:
      Serial.println(F("8: Attached for emergency bearer services only."));
    break;
    default: 
      Serial.println(F("Unknow"));
    break;
  }
}

void debugEPS(){
  AIS_NB_BC95_CEREG result;
  result = AISnb.getEPSNetworkStatus();
  Serial.println(F("# EPS Network status-->  "));
  Serial.print(F("    Result: ")); getCEREGStatus(result.status);
  Serial.print(F("    EPS   : ")); getEPSStatus(result.EPS_status);
  Serial.print(F("    Tracking Area Code: 0x")); Serial.println(result.TAC, HEX);
  Serial.print(F("    E-UTRAN cell ID   : 0x")); Serial.println(result.ECI, HEX);
  Serial.print(F("    access technology : 0x")); Serial.println(result.AcT, DEC);
  Serial.print(F("Operator MNC+MMC Code : ")); Serial.println(AISnb.getPLMN());
}

void setup(){ 
  AISnb.debug = true;
  
  Serial.begin(9600);
  AISnb.setupDeviceWithoutAttachNB();
  delay(1000);
}
void loop(){
  debugEPS();
  delay(1000);
  Serial.println(F("----------------------------------------------------"));
}