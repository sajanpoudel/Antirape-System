#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#include "alert_logic.h"
#include "contacts.h"

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
const unsigned long ALERT_COOLDOWN_MS = 120000; // ignore button presses for two minutes after an alert

SoftwareSerial mySerial(GSM_RX_PIN, GSM_TX_PIN);
const int LCD_COLUMNS = 16;
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
String textForSMS; // text of the rescue message
const char LOCATION_LINK[] = "https://goo.gl/maps/search/query?=lat,lon"; // replace with the link of the place the watch is used
RH_ASK driver; // 433 MHz receiver for the watch signal
bool hasAlerted = false;
unsigned long lastAlertAt = 0;


// Starts the serial ports, the LCD and the radio receiver.
void setup()
{
  pinMode(ALERT_LIGHT_PIN, OUTPUT);

  lcd.begin(LCD_COLUMNS, 2);
  showReady();
  Serial.begin(SERIAL_BAUD);
  mySerial.begin(SERIAL_BAUD);

  // The module defaults to 19200 baud, a SIM900A needs 9600.
  Serial.println(" logging time completed!");
  if (!driver.init())
    Serial.println("init failed");

  for (int n = 0; n < CONTACT_COUNT; n++)
  {
    if (!isValidPhoneNumber(CONTACT_NUMBERS[n]))
    {
      Serial.print("check the registered number ");
      Serial.println(n + 1);
    }
  }
}

// Writes two lines on the display, each one padded or cut to the 16 columns.
void showLines(const char* top, const char* bottom)
{
  char line[LCD_COLUMNS + 1];
  fitLcdLine(top, LCD_COLUMNS, line);
  lcd.setCursor(0, 0);
  lcd.print(line);
  fitLcdLine(bottom, LCD_COLUMNS, line);
  lcd.setCursor(0, 1);
  lcd.print(line);
}

// Shows that the box is switched on and waiting for the watch.
void showReady()
{
  showLines("SYSTEM READY", "AWAITING WATCH");
}

// Waits for the watch signal and starts the alert when it arrives.
void loop()
{
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  // recv() does not block, so loop() keeps running when nothing arrives
  if (driver.recv(buf, &buflen))
  {
    for (uint8_t k = 0; k < buflen; k++)
    {
      char received = buf[k];
      Serial.println(received);
      if (received == ALERT_SIGNAL && canStartAlert(hasAlerted, millis(), lastAlertAt, ALERT_COOLDOWN_MS))
      {
        send1();
        sendcall();
        output();
        showReady();
        hasAlerted = true;
        lastAlertAt = millis();
      }
    }
  }
}

// Texts the rescue message to every registered number.
void send1()
{
  char message[200];
  buildAlertMessage(LOCATION_LINK, message, sizeof(message));
  textForSMS = message;

  for (int n = 0; n < CONTACT_COUNT; n++)
  {
    sendsms(textForSMS, String(CONTACT_NUMBERS[n]));
    Serial.println(textForSMS);
    Serial.print("message");
    Serial.print(n + 1);
    Serial.println(" sent.");
    delay(SMS_GAP_MS);
  }
}

// Collects what the GSM module answers within timeoutMs.
String readGsmResponse(unsigned long timeoutMs)
{
  String response = "";
  unsigned long start = millis();
  while (millis() - start < timeoutMs)
  {
    while (mySerial.available())
    {
      response += (char)mySerial.read();
    }
  }
  return response;
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
  if (!responseIsOk(readGsmResponse(1000).c_str()))
  {
    Serial.println("the GSM module did not accept text mode");
  }
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
  for (int i = 0; i < BLINK_COUNT; i++)
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
  showLines("WOMAN IS", "  IN DANGER");
  blinkAlertLight();
}

// Dials the last registered number through the GSM module.
void sendcall()
{
  mySerial.println("ATD" + String(CONTACT_NUMBERS[callIndex(CONTACT_COUNT)]) + ";"); // call the last registered number
  Serial.println("Calling  ");            // print response over serial port
  delay(1000);
  Serial.println("called");
}
