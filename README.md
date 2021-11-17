   **SAY NO TO RAPE !**
   
*An effort from high schooler to minimize rape, harassment and provide the protection to all the victims from misfortune events.*

**Project Introduction:**
Antirape Watch is a wearable technology with motto of providing the security especially for women from misfortune events and make them confident when they step out from their home. The project consists of two components: Watch and Server Box.

 **Watch :** This is similar to the normal watch that are available in market with additional security features such as sending rescue message, tracking live location, generating 3 micro ampere electric shock. It is rechargeable and works more than 8 hours once it is fully charged.

**Server Box:** This is extra step taken to ensure the rescue message gets notified to the rescue team (cops, family members, and volunteers) even if they missed their phone messages. The server consists of LCD display panel where the rescue message is displayed in bold text, and alerting systems which includes buffers and continuously blinking bulbs. The server Box contains the power cable which can work with AC source and  even with battery.

**LCD panel displaying rescue message**

![image](https://user-images.githubusercontent.com/35656849/141984349-a4469b38-23c7-42d5-addf-5513143755c8.png)


**Function:**

 When a victim feels unsafe, she/he needs to press a button present in the watch. When the victim presses the button, a message is generated saying "I am in danger. Please rescue me. My Location is ..... ." And also the location of victim is stated in the message and the message is delivered to local authorities and their family members .
![image](https://user-images.githubusercontent.com/35656849/141984534-8acd53f8-9ca6-451d-8a42-a62e640447aa.png)


**Working mechanism:**

There will be two systems watch and server. The watch consists of arduino, GSM module ,GPS sensor ,transmitter. When a button is pressed, the signals get triggered and GPS sensor generates the location in the form of latitude and longitude. The values of latitude and longitude are stored in two different variables. The sample message is created saying "I am in danger. Please rescue me ." The link is also created using latitude and longitude variables that redirect to Google maps url. Then the message is sent to the local authorities phone number which will be set by the programmer during watch construction.

In addition there will be a local server which can be kept to local police station. The server consists of receiver ,LCD display panel and a buffer. The LCD panel will also display the same message with location of victim. The beeping sound will be produced in the server to make sure that police should be ready to rescue the victim .

Transmission of signal between watch and server will be in the form of electromagnetic waves that travels serially.

The message can be sent to the police personal number of station number anywhere in the world but the transmission between watch and the server should be within the range of 1 km in omni-direction.

The watch is rechargeable. The charger is given to victim. The watch works well more than 8 hours once it is fully charged.The server box can work on both AC as well as DC.
![image](https://user-images.githubusercontent.com/35656849/134703432-3509239e-83d7-4616-b5bb-1c2278a23e03.png)



**Instruments Used:**

1 arduino nano in watch and 1 arduino Mega in server box.

Transmitter and receiver

GSM module to send messages to mobile number.

GPS module to locate victim location.

LCD panel to display messages

Buffer to produce beeping sound
                                     
                                     
**Circuit Connection:**

![image](https://user-images.githubusercontent.com/35656849/134703662-1cf6a169-5360-4128-a70e-aa8872521724.png)

**Video**

![Anti-Rape Watch Demo](https://drive.google.com/file/d/16oUzJ25ZZx_akrpArYxueoXifferAxby/view?usp=sharing)


