#include <LiquidCrystal_I2C.h>

int sensorPin = A0;
int sensorValue = 0; // Variable for storing values derived from soil moisture sensors
const int buzzer = 8;

/* Create object named lcd of the class LiquidCrystal */
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Project Arduino");
  lcd.setCursor(0,1);
  lcd.print("Soil Moisture");
  delay(2000);
  lcd.clear();
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Begin serial communication at a baud rate of 9600
}

void loop() {
  // Get a reading from the Moisture sensor:
  sensorValue = analogRead(sensorPin);
  
  /*------Display Moisture Sensor Value in Serial Monitor------*/
  Serial.print("Moisture Sensor Value:");
  Serial.println(sensorValue);

  /*------Display the Moisture Percentage------*/
  float moisturePercentage;
  moisturePercentage = (100-((sensorValue/1023.00)*100));
  Serial.print("Moisture Percentage = ");
  Serial.print(moisturePercentage);
  Serial.print("%\n");
 
  /*------Display the plant need------*/
  if(sensorValue < 614) {
    Serial.println("I am thirsty, please give me water");
    tone(buzzer, 1000);
    delay(3000);
    noTone(buzzer);
    delay(1000);
  } else if(sensorValue > 614 && sensorValue < 819) {
    Serial.println("I feel so comfortable");
  }
  if(sensorValue > 819){
    Serial.println("Too much water, I might get hurt");
  }
 
  Serial.print("\n");
  
  /*------Display Moisture Sensor Value in LCD------*/
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soil Moisture");
    
  lcd.setCursor(0,1);
  lcd.print(sensorValue);
  lcd.setCursor(6,1);
  lcd.print("&");
  lcd.setCursor(8,1);
  lcd.print(moisturePercentage);
  lcd.print(" %");
  delay(500);
}
