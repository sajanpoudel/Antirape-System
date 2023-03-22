#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#include "alert_logic.h"

// Pins and timings used by the server box
const int GSM_RX_PIN = 12;   // SIM900A TX goes here
const int GSM_TX_PIN = 13;   // SIM900A RX goes here
const int ALERT_LIGHT_PIN = 6; // bulb or buffer that blinks during an alert
const long SERIAL_BAUD = 9600;
const long GSM_BAUD = 9600;
const int BLINK_COUNT = 100;   // number of on/off cycles per alert
const int BLINK_DELAY_MS = 250; // length of the on and of the off phase
const int SMS_GAP_MS = 2000;   // pause between two SMS so the module can finish
const char ALERT_SIGNAL = 'a'; // byte sent by the watch when the button is pressed

SoftwareSerial mySerial(GSM_RX_PIN, GSM_TX_PIN);
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
String textForSMS; // text of the rescue message
RH_ASK driver; // 433 MHz receiver for the watch signal
char i;
char b;
char msg;
char call;

// Registered numbers
const int CONTACT_COUNT = 5;
String contacts[CONTACT_COUNT] = {
  "+9779811111111",
  "+97798222222222",
  "+97798333333333",
  "+9779810366707",
  "+9779817448555"
};

// Starts the serial ports, the LCD and the radio receiver.
void setup()
{
  pinMode(ALERT_LIGHT_PIN, OUTPUT);

  lcd.begin(16, 2);
  Serial.begin(SERIAL_BAUD);
  mySerial.begin(SERIAL_BAUD);

  // The module defaults to 19200 baud, a SIM900A needs 9600.
  Serial.println(" logging time completed!");
  if (!driver.init())
    Serial.println("init failed");

  for (int n = 0; n < CONTACT_COUNT; n++)
  {
    if (!isValidPhoneNumber(contacts[n].c_str()))
    {
      Serial.print("check the registered number ");
      Serial.println(n + 1);
    }
  }
}

// Waits for the watch signal and starts the alert when it arrives.
void loop()
{
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  // recv() does not block, so loop() keeps running when nothing arrives
  if (driver.recv(buf, &buflen))
  {
    char i;
    for (i = 0; i < buflen; i++)
    {
      b = buf[i];
      Serial.println(b);
      if (b == ALERT_SIGNAL)
      {
        // readdata();
        send1();
        sendcall();
        output();
      }
    }
  }
}

// Texts the rescue message to every registered number.
void send1()
{
  textForSMS = "\nPLEASE RESCUE ME , I AM IN PROBLEM . '\n' MY CURRENT LOCATION IS : https://goo.gl/maps/search/query?=lat,lon";

  for (int n = 0; n < CONTACT_COUNT; n++)
  {
    sendsms(textForSMS, contacts[n]);
    Serial.println(textForSMS);
    Serial.print("message");
    Serial.print(n + 1);
    Serial.println(" sent.");
    delay(SMS_GAP_MS);
  }
}

// Sends one SMS through the GSM module using AT commands.
void sendsms(String message, String number)
{
  char command[48];
  if (!buildSmsCommand(number.c_str(), command, sizeof(command)))
  {
    Serial.println("number too long, message skipped");
    return;
  }
  String mnumber = command;
  mySerial.print("AT+CMGF=1\r");
  delay(1000);
  mySerial.println(mnumber); // recipient's mobile number, in international format

  delay(1000);
  mySerial.println(message); // message to send
  delay(1000);
  mySerial.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(1000);
  mySerial.println();
  delay(100); // give module time to send SMS
  // SIM900power();
}

// Blinks the alert light BLINK_COUNT times.
void blinkAlertLight()
{
  for (i = 0; i < BLINK_COUNT; i++)
  {
    digitalWrite(ALERT_LIGHT_PIN, HIGH);
    delay(BLINK_DELAY_MS);
    digitalWrite(ALERT_LIGHT_PIN, LOW);
    delay(BLINK_DELAY_MS);
  }
}

// Shows the warning on the LCD and blinks the light.
void output()
{
  lcd.setCursor(0, 0);      // row 0, column 0
  lcd.print("WOMAN IS    "); // 16x2 LCD module
  lcd.setCursor(2, 1);      // row 1, column 2
  lcd.print("     IN DANGER");
  blinkAlertLight();
}

// Dials the last registered number through the GSM module.
void sendcall()
{
  mySerial.println("ATD" + contacts[callIndex(CONTACT_COUNT)] + ";"); // call the last registered number
  Serial.println("Calling  ");            // print response over serial port
  delay(1000);
  Serial.println("called");
}
