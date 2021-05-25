#include <AFMotor.h>

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
int ThermistorPin = A0;
int Vo;
double R1 = 10000; // value of R1 on board
double logR2, R2, T;
double c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coefficients for thermistor

AF_DCMotor leftm(1);
AF_DCMotor rightm(3);

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
   //Set initial speed of the motor & stop
   leftm.setSpeed(255);
   leftm.run(RELEASE);
   rightm.setSpeed(255);
   rightm.run(RELEASE);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
   pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
   Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
   Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
   Serial.println("with Arduino UNO R3");
}
void loop() {
   int thresh = 40;
   Serial.println(temp());
   if (temp() <= thresh) {
      f: if (dist() > 10) {
         forward();
      }
      else {
         stopmot();
         while (dist() < 10)
            left();
         goto f;
      }
   }
   else {
      stopmot();
      while (temp() > thresh)
         left();
   }
}
void stopmot() {
   leftm.run(RELEASE);
   rightm.run(RELEASE);
}
void forward() {
   leftm.run(FORWARD);
   rightm.run(FORWARD);
   leftm.setSpeed(255);
   rightm.setSpeed(253);
}
void left() {
   leftm.run(BACKWARD);
   leftm.setSpeed(255);
   rightm.setSpeed(252);
}
double temp() {
   Vo = analogRead(ThermistorPin);
   R2 = R1 * (1023.0 / (float) Vo - 1.0); //calculate resistance on thermistor
   logR2 = log(R2);
   T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); // temperature in Kelvin
   T = T - 273.15; //convert Kelvin to Celsius
   // T = (T * 9.0)/ 5.0 + 32.0; //convert Celcius to Farenheit
   return T;
}
int dist() {
   // Clears the trigPin condition
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   // Reads the echoPin, returns the sound wave travel time in microseconds
   duration = pulseIn(echoPin, HIGH);
   // Calculating the distance
   distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
   // Displays the distance on the Serial Monitor
   return distance;
}
