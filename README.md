A watch is given to the victim which he should wear every time. When a victim feels unsafe, he needs to press a button present in the watch. Then the victim presses the button , a message is generated saying "I am in danger. Please rescue me . My Location is ....." And also the location of victim is stated in the message and the message is delivered to local authorities and their family members .

![image](https://user-images.githubusercontent.com/35656849/134703203-8261bfd3-e7c7-4e7f-8abb-aef5b50113ab.png)


    

                                                          Working mechanism:
There will be two systems watch and server. The watch consists of arduino, GSM module ,GPS sensor ,transmitter. When a button is pressed, the signals get triggered and GPS sensor generates the location in the form of latitude and longitude. The values of latitude and longitude are stored in two different variables. The sample message is created saying "I am in danger. Please rescue me ." The link is also created using latitude and longitude variables that redirect to Google maps url. Then the message is sent to the local authorities phone number which will be set by the programmer during watch construction.

In addition there will be a local server which can be kept to local police station. The server consists of receiver ,LCD display panel and a buffer. The LCD panel will also display the same message with location of victim. The beeping sound will be produced in the server to make sure that police should be ready to rescue the victim .

Transmission of signal between watch and server will be in the form of electromagnetic waves that travels serially.

The message can be sent to the police personal number of station number anywhere in the world but the transmission between watch and the server should be within the range of 1 km in omni-direction.



The watch is rechargeable. The charger is given to victim. The watch works well more than 8 hours once it is fully charged.The server box can work on both AC as well as DC.
![image](https://user-images.githubusercontent.com/35656849/134703432-3509239e-83d7-4616-b5bb-1c2278a23e03.png)



                                      Instruments Used:
1 arduino nano in watch and 1 arduino Mega in server box.

Transmitter and receiver

GSM module to send messages to mobile number.

GPS module to locate victim location.

LCD panel to display messages

Buffer to produce beeping sound
                                     
                                     
                                      Circuit Connection:

![image](https://user-images.githubusercontent.com/35656849/134703662-1cf6a169-5360-4128-a70e-aa8872521724.png)

                              Video

<iframe width="560" height="315" src="https://www.youtube.com/embed/ZIGlyxaKdog?start=324" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


