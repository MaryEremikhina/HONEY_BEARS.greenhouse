// C++ code
//
#include <Arduino.h>
#define sensorPin A0
#include "DHT.h"

#define NO_CONNECTION_ST 0
#define WAITING_ST 1
#define S_DATA_GET_ST 2
#define S_HUMIDITY_ERROR_ST 3
#define AUTO_OFF_ST 4
#define WATERING_ON_ST 5
#define HUMIDIFIER_ON_ST 6
#define A_DATA_GET_ST 7
#define A_HUMIDITY_ERROR_ST 8
#define A_WATER_LEVEL_OK_ST 9
#define A_WATER_LEVEL_ERROR_ST 10
#define S_WATER_OK_ST 11

#define DHTPIN 2
#define DHTTYPE DHT22

int state = NO_CONNECTION_ST;
int wateringTimeout = 10*1000;
int humidifierTimeout = 20*1000;
bool conState = false;
bool auto = true

void setup() {
  Serial.begin(9600);
  dht.begin();

}

bool meshConnect(){
  conState = true;
}

void no_connectionSt_handler()
{
  meshConnect();
  if (conState){
    state = WAITING_ST;
  }
}

void waitingSt_handler(int cmd){
  switch(cmd){
    case NO_CMD:{
      break;
    }
    case AUTO_OFF:{
      auto = false;
       break;
    }
    case S_DATA_GET_ST:{
      s_data_getSt_handler();
      break
    }
    case HUMIDIFIER_ON_ST:{
      humidifier_onSt_handler(cmd);
      break;
    }
    case WATERING_ON_ST:{
      watering_onSt_handler(cmd);
      break;
    }
  }
}

void s_data_get()
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

DHT dht(DHTPIN, DHTTYPE);

void a_data_get() {

float h = dht.readHumidity();

Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %");
}
}

uint32_t watering_stime;

void ch_water_level_handler(){

 bool waterLevel = checkWaterLevel();
 if (waterLevel){
  watering_stime = millis();
  state = WATERING_ON_ST; 
 }
 else{
  state = WATER_LEVEL_ERROR_ST;
 }
}

void watering_onSt_handler(int cmd){
 uint32_t time_now = millis();
 pump_turn_on();
 
 if (abs(time_now - watering_stime) >= wateringTimeout){
  pump_turn_off();
  state = WAITING_ST;
 }
 else{
  bool waterLevel = checkWaterLevel();
  if (!waterLevel){
   pump_turn_off();
   state = WATER_LEVEL_ERROR_ST;
  }
 }

uint32_t humidifier_stime;

void ch_water_level_handler(){

 bool waterLevel = checkWaterLevel();
 if (waterLevel){
  humidifier_stime = millis();
  state = HUMIDIFIER_ON_ST; 
 }
 else{
  state = WATER_LEVEL_ERROR_ST;
 }
}

void humidifier_onSt_handler(int cmd){
 uint32_t time_now = millis();
 humidifier_turn_on();
 
 if (abs(time_now - humidifier_stime) >= humidifierTimeout){
  humidifier_turn_off();
  state = WAITING_ST;
 }
 else{
  bool waterLevel = checkWaterLevel();
  if (!waterLevel){
   humidifier_turn_off();
   state = WATER_LEVEL_ERROR_ST;
  }
 }
 
}
void loop() {
  switch(state){
    case NO_CONNECTION_ST:{
      no_connectionSt_handler();
      break;
    }
    case WAITING_ST:{
      waitingSt_handler(cmd);
      break;
    }
    case S_DATA_GET_ST:{
      s_data_getSt_handler(cmd);
      break;
    }
     case S_HUMIDITY_ERROR_ST:{
       s_humidity_errorSt_handler(cmd);
       break;
     }
     case AUTO_OFF_ST:{
       auto = false;
       break;
     }
     case WATERING_ON_ST:{
       ch_water_level_handler();
       watering_onSt_handler(cmd);
       break;
     }
     case HUMIDIFIER_ON_ST:{
       ch_water_level_handler();
       humidifier_onSt_handler(cmd);
       break;       
     }
     case A_DATA_GET_ST:{
       a_data_getSt_handler(cmd);
       break;
     }
     case A_HUMIDITY_ERROR_ST:{
       a_humidity_errorSt_handler(cmd);
       break;
     }
     case A_WATER_LEVEL_OK_ST:{
       a_water_level_okSt_handler(cmd);
       break;
     }
     case A_WATER_LEVEL_ERROR_ST:{
       a_water_level_errorSt_handler(cmd);
       break;
     }
     case S_WATER_OK_ST:{
       s_water_okSt_handler(cmd);
       break;
     }

}
