#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
const int bufferPin = 4;

int toneFrequency = 0;
long duration;
int distance;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(bufferPin, OUTPUT); // Establecer bufferPin como salida
  Serial.begin(9600);
  myServo.attach(5);
}

void loop() {
  for (int i = 15; i <= 165; i++) {  
    myServo.write(i);
    delay(30);
    delay(200); // Esperar 200 ms para que el servo se mueva a la posición
    distance = calculateDistance();
    Serial.println(distance);
    buffersound();
  }
  for (int i = 165; i > 15; i--) {  
    myServo.write(i);
    delay(30);
    delay(200); // Esperar 200 ms para que el servo se mueva a la posición
    distance = calculateDistance();
    Serial.println(distance);
    buffersound();
  }
}

int calculateDistance() {   
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2; // Calcular la distancia en centímetros
  return distance;
}

void buffersound() {
 if (distance >= 36 ) {
    toneFrequency = 1000;
  } else if (distance >= 26 && distance <= 35) {
    toneFrequency = 1500;
  } else if (distance >= 11 && distance <= 25) {
    toneFrequency = 2000;
  } else {
    toneFrequency = 2500;
  }
  tone(bufferPin, toneFrequency);
}
