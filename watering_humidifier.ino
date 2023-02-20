// C++ code
//
#include "AsyncMqttClient"
#include "ESPAsyncTCP"
#include "Arduino ESP8266 Core"
#include "ESP8266MQTTMesh"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Servo.h>
#include "index.h"

ESP8266MQTTMesh mesh = ESP8266MQTTMesh::Builder(networks, mqtt_server, mqtt_port).build();
//.setVersion(firmware_ver, firmware_id).setMeshPassword(password).setMqttAuth(username, password).build();

wifi_conn_networks[]

const char mqtt.by //server
int mqtt_port 1883 //спросить про цифирку !!!
const char grn_house //username
const char hOnEy3 //password (username)
const char sUpEr_bEArs //пароль для подключения

setMeshSSid(ssid)
const char *ssid //по умолчанию 'esp8266_mqtt_mesh'

setMeshPort(port)
int port 1884 //спросить про порт !!!

setTopic(in_topic, ou_topic)
const char user/grn_house //in_topic
const char *out_topic //по умолчанию esp8266-out/
//setMeshSSL(cert, cert_len, key, key_len, fingerprint)

publish(topic, payload, msgCmd)
publish_node(topic, payload, msgCmd)

///

int getCommand();
Watering userWatering;

void sendMessage();
void receivedCallback(uint32_t from, String&msg){
  Serial.printf("startHere:Received from user/grn_house msg=%s\n", from, msg.c_str());
  wateringTimeout = msg;
}

///

#include <Arduino.h>
#include "DHT.h"

#define sensorPin A0
#define DHTPIN 2
#define DHTTYPE DHT22

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

#define MESH_ON '0'
#define MESH_OFF '1'
#define CMD_WAIT '2'
#define S_CMD_WAIT '3'
#define S_HUMIDITY_ERROR '4'
#define S_HUMIDITY_OK '5'
#define WATERING_ON '6'
#define WATERING_OK '7'
#define AUTO_OFF '8'
#define AUTO_ON '9'
#define WATER_ON_AUTO_OFF '10'
#define WATER_OFF_AUTO_OFF '11'
#define W_H_ON '12'
#define HUMID_ON_AUTO_OFF '13'
#define HUMID_OFF_AUTO_OFF '14'
#define A_CMD_WAIT '15'
#define A_HUMIDIFIER_OK '16'
#define A_HUMIDIFIER_ERROR '17'
#define HUMIDIFIER_ON '18'
#define HUMIDIFIER_OFF '19'
#define WATER_LEVEL_OK '20'
#define WATER_LEVEL_ERROR '21'
#define W_H_WARN '22'


int state = NO_CONNECTION_ST;
int wateringTimeout = 10*1000;
int humidifierTimeout = 20*1000;
bool conState = false;
bool auto = true;

void setup() {
  Serial.begin(9600);
  dht.begin();
}
int getCommand(){
  int cmd = Serial.read();
  return cmd;
}

bool meshConnect(){
  conState = true;
}

void s_humidity_errorSt_handler(int cmd){
  if (auto){
    state = WATERING_ON_ST;
  }
}

void a_humidity_errorSt_handler(int cmd){
  if (auto){
    state = HUMIDIFIER_ON_ST;
  }
}

void a_water_level_okSt_handler(int cmd){
  state = HUMIDIFIER_ON_ST;
}

void s_water_level_okSt_handler(int cmd){
  state = WATERING_ON_ST;
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
    case A_DATA_GET_ST:{
      a_data_getSt_handler();
      break;
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

void s_data_getSt_handler()
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

void a_data_getSt_handler() {

float h = dht.readHumidity();

Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %");
}
}

uint32_t watering_stime;

void s_ch_water_level_handler(){

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

void a_ch_water_level_handler(){

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
  int cmd = getCommand();
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
       s_ch_water_level_handler();
       watering_onSt_handler(cmd);
       break;
     }
     case HUMIDIFIER_ON_ST:{
       a_ch_water_level_handler();
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
     case S_HUMIDITY_ERROR_ST:{
       s_humidity_errorSt_handler(cmd);
       break;
     }
     case A_WATER_LEVEL_OK_ST:{
       a_water_level_okSt_handler(cmd);
       break;
     }
     case WATER_LEVEL_ERROR_ST:{
       water_level_errorSt_handler(cmd);
       break;
     }
     case S_WATER_OK_ST:{
       s_water_okSt_handler(cmd);
       break;
     }

}
