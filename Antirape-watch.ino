#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h> 
#include <LiquidCrystal.h>
SoftwareSerial mySerial(12,13);
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
String textForSMS;
RH_ASK driver;
char i;
int light = 6;
char b;
char msg;
char call;

String f1001 = "+9779811111111"; 
String f1002 = "+97798222222222"; //Registered Numbers 
String f1003 = "+97798333333333";
String f1004 = "+9779810366707";
String f1005 = "+9779817448555";

void setup()
{
    pinMode(light , OUTPUT);
 
   lcd.begin(16, 2);
  Serial.begin(9600);
  mySerial.begin(9600); 
   
 // original 19200. while enter 9600 for sim900A
 Serial.println(" logging time completed!");
 if (!driver.init())
         Serial.println("init failed");
 
}
void loop()
{

    uint8_t buf[1];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
char i; 
for (i = 0; i < buflen; i++)
    {
b=buf[i];
Serial.println(b);
  if ( b == 'a') // 
  {
   // readdata();
send1();
sendcall();
output();


  }
}
    }
}

void send1()
{
         textForSMS =  "\nPLEASE RESCUE ME , I AM IN PROBLEM . '\n' MY CURRENT LOCATION IS : https://goo.gl/maps/search/query?=lat,lon";  
  //sendSMS(textForSMS);
  sendsms(textForSMS, f1001); // you can use a variable of the type String
  Serial.println(textForSMS);
  Serial.println("message1 sent."); 
delay(2000);
 
  sendsms(textForSMS, f1002); // you can also write any message that you want to send.
  Serial.println(textForSMS);
  Serial.println("message2 sent."); 
delay(2000);
 
  sendsms(textForSMS, f1003); // you can also write any message that you want to send.
  Serial.println(textForSMS);
  Serial.println("message3 sent."); 
delay(2000);

 sendsms(textForSMS, f1004); // you can also write any message that you want to send.
  Serial.println(textForSMS);
  Serial.println("message4 sent."); 
delay(2000);


 sendsms(textForSMS, f1005); // you can also write any message that you want to send.
  Serial.println(textForSMS);
  Serial.println("message5 sent."); 
delay(2000);

//sendsms(textForSMS, f1006); // you can also write any message that you want to send.
 // Serial.println(textForSMS);
 // Serial.println("message5 sent."); 
//delay(3000);
}
void sendsms(String message, String number)
{
String mnumber = "AT + CMGS = \""+number+"\""; 
   mySerial.print("AT+CMGF=1\r");                   
  delay(1000);
mySerial.println(mnumber);  // recipient's mobile number, in international format
 
  delay(1000);
 mySerial.println(message);                         // message to send
  delay(1000);
mySerial.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
mySerial.println();
  delay(100);                                     // give module time to send SMS
 // SIM900power();  
}
 void output()
      {
       
 lcd.setCursor(0,0);           //sets the cursor at row 0 column 0
  lcd.print("WOMAN IS    "); // prints 16x2 LCD MODULE
  lcd.setCursor(2,1);           //sets the cursor at row 1 column 2
  lcd.print("     IN DANGER");  
         for(i=0;i<100;i++)
         {
          digitalWrite(light , HIGH);
       delay(250);
        digitalWrite(light , LOW);
        delay(250);
        
         }
      }
    void sendcall()
{
  mySerial.println("ATD+9779817448555;"); //Calling Numbers
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
  Serial.println("called");
  
}
