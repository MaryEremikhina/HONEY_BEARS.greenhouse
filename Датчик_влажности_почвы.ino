// C++ code
//
#define sensorPin A0
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Влажность почвы:");
  Serial.println(readSensor());
  
  delay(300000);
}

int readSensor()
{
  int soil = analogRead(sensorPin);
  return soil;
}
