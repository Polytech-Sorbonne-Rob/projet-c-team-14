#include <Servo.h> 

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


Servo myservo1;  // create servo object to control a servo 
Servo myservo2;                // a maximum of eight servo objects can be created 
int pos1 = 0; 
int pos2 = 90;    // variable to store the servo position 
int idx = 1;

void setup() 
{ 
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  myservo1.attach(5);  // attaches the servo on pin 6 to the servo object 
  myservo2.attach(6);
} 


void loop() 
{ 
  // print the string when a newline arrives:
  if (stringComplete) {
    String mytext = "";
    mytext = mytext + "pos1:" + pos1 + " pos2:" + pos2;
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos1' 
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos2' 
    delay(15);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  //                       // waits 15ms for the servo to reach the position  
} 


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if(inChar == ' '){
      pos1=inputString.toInt();
      inputString="";
    }
    if (inChar == '\n' ) {
      pos2=inputString.toInt();
      inputString="";
      stringComplete = true;
    } 
  }
}
