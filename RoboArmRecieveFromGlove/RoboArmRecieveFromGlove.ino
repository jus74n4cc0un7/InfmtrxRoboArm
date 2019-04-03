#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// 
 Servo myservo;
char c = ' ';
String data = "";
int angz, angx, angy;
void setup() 
{
  myservo.attach(8);
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
 BTserial.setTimeout(50);
    // HC-05 default serial speed for AT mode is 38400
    BTserial.begin(9600);  
    myservo.write(0);

}
 
void loop()
{
  
  // Pass data to servos
  if (data.startsWith("#")) {// Make sure data comes from glove
    myservo.write(angz);
  }

  
  
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {
      data = BTserial.readString();
      angx = data.substring(1,4).toInt();
      angy = data.substring(4,7).toInt();
      angz = data.substring(7,10).toInt();
      Serial.println(data); 
      
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        BTserial.write(Serial.read());  
    }
 
}
