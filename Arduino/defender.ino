#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 6;
const int echoPin = 7;
const int buzzer = 9;
const float a = 0.2;


float EWMF;
float previousTemp;
long duration;
float distance;
float freq;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Distance:");

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  previousTemp = duration * 0.034 / 2;

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 57;

  if ( distance > 300 ) return;

  EWMF = (1 - a) * previousTemp + a * distance;

  if ( abs ( previousTemp - EWMF ) < 0.1 ) return;

  Serial.println(EWMF);

  previousTemp = EWMF;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(EWMF);
  lcd.print(" cm");

  if (EWMF < 6.00) {

    tone(buzzer, 300);
    delay(3000);
    noTone(buzzer);

    return;

  }
}