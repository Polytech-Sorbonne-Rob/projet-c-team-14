#define LED_PIN (13)
#define MOTOR0_PIN (3)
#define MOTOR1_PIN (5)


#define CLOCKWISE (-1)
#define ANTI_CLOCKWISE (1)

#define UPWARD (-1)
#define DOWNWARD (1)


void setup() {
  Serial.begin(9600); // Enable Serial connection with a rate of 9600 bauds
}


void rotateMotor(int pin, int ms, int direction) {
  const int out_anticlockwise = 235; // +4.8V
  const int out_clockwise =  20; // -4.8V

  if (direction == CLOCKWISE) {
    analogWrite(pin, out_clockwise);
  } else if (direction == ANTI_CLOCKWISE) {
    analogWrite(pin, out_anticlockwise);
  }
  
  delay(ms);
  analogWrite(pin, 0); // Stop movement
}

void loop() {

  while (Serial.available() > 0) {
    int val0 = Serial.parseInt(SKIP_ALL);
    int val1 = Serial.parseInt(SKIP_ALL);
    
    // Clamp value: prevents events in which motor would rotate for a long time
    // if the entered value is too big
    val0 = max(min(val0, 2000), -2000); 
    val1 = max(min(val1, 2000), -2000);
    
    // Vertical rotation
    if (val0 > 0) {
      rotateMotor(MOTOR0_PIN, abs(val0), UPWARD);
    } else if (val0 < 0) {
      rotateMotor(MOTOR0_PIN, abs(val0), DOWNWARD);
    }

    // Horizontal rotation
    if (val1 > 0) {
      rotateMotor(MOTOR1_PIN, abs(val1), CLOCKWISE);
    } else if (val1 < 0) {
      rotateMotor(MOTOR1_PIN, abs(val1), ANTI_CLOCKWISE);
    }
  }
}
