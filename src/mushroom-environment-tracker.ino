/*
 * Project Mushroom Environment Tracker (MET)
 * Description: Mushroom growth alerting system
 * Author: Branden Byers
 * Date: 2018
 */

#include "SparkFunBME280.h"
#include "uCommand.h"

#define RADIO Cellular

BME280 mySensor;

unsigned int sampleNumber = 0; // For counting number of CSV rows

STARTUP(cellular_sms_received_handler_set(smsRecvFlag, NULL, NULL));
STARTUP(cellular_credentials_set("wireless.twilio.com", "", "", NULL));

String messageText = "default";
String phoneReturn = "default";
String moduleID = "MET";
uCommand uCmd;

int smsSent = 0;
int smsLimit = 4;

int smsAvailableFlag = 0;
//------SETUP-------
void setup() {
    int atResult;
    Serial.println("Entering sms setup");
    uCmd.setDebug(false);

    atResult = uCmd.setSMSMode(1);
    if(atResult == RESP_OK) {
        errorAlerter("Text mode setup okay");
    }
    else {
        errorAlerter("Did not set up text mode");
    }
    pinMode(D7, OUTPUT);
}

void setup() {
  // Sensor setup
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x77;
  mySensor.settings.runMode = 3;  // 3, Normal mode
  mySensor.settings.tStandby = 0; // 0, 0.5ms
  mySensor.settings.filter = 0;   // 0, filter off
  mySensor.settings.tempOverSample = 1;
  mySensor.settings.pressOverSample = 1;
  mySensor.settings.humidOverSample = 1;
  Serial.begin(57600);
  Serial.print("Starting BME280... result of .begin(): 0x");
  delay(10); // BME280 requires 2ms to start up.
  // Load sensor settings
  Serial.println(mySensor.begin(), HEX);

  // SMS setup
  int atResult;
  Serial.println("Entering sms setup");
  uCmd.setDebug(false);

  atResult = uCmd.setSMSMode(1);
  if(atResult == RESP_OK) {
      errorAlerter("Text mode setup success");
  }
  else {
      errorAlerter("Text mode failed to set up");
  }
  pinMode(D7, OUTPUT);
}

void loop() {
  Serial.print(sampleNumber);
  Serial.print(",");
  Serial.print(mySensor.readTempC(), 2);
  Serial.print(",");
  Serial.print(mySensor.readTempF(), 3);
  Serial.print(",");
  Serial.print(mySensor.readFloatPressure(), 0);
  Serial.print(",");
  Serial.print(mySensor.readFloatAltitudeMeters(), 3);
  Serial.print(",");
  Serial.print(mySensor.readFloatAltitudeFeet(), 3);
  Serial.print(",");
  Serial.print(mySensor.readFloatHumidity(), 0);
  Serial.println();

  sampleNumber++;

  delay(60000);
}

void errorAlerter(String errorMessage) {
    Serial.println("ErrorAlerter", errorMessage, 60, PRIVATE);
}

int sendSMS(const char* msg, const char* telNr) {
  if (smsSent <= smsLimit) {
    smsLimit = smsLimit + 1;
    int  ret;

    if (!RADIO.ready()) {
      RADIO.on();
      RADIO.connect();
      if (!waitFor(RADIO.ready, 5000)) {
            return -1;
          }
      }

      ret = Cellular.command("AT+CMGF=1\r\n");
      ret = Cellular.command("AT+CMGS=\"%s%s\",145\r\n", (telNr[0] != '+') ? "+" : "", telNr);
      ret = Cellular.command("%s\x1a", msg);

      switch (ret) {
        case WAIT:
          errorAlerter("SMS Waiting");
        case RESP_OK:
          break;
        default:
          errorAlerter("Message not sent");
          break;
      }

      return ret;
  }
  return 0;
}
