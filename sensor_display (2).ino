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

#define WAITING_ST 0
#define MORE_A_SENS_ST 1
#define SETTINGS_ST 2
#define SET_SETTINGS_ST 3
#define HUMIDITY_ON_ST 4
#define WND_LEAF_ON_ST 5
#define CONDITION_ON_ST 6

#define SETTINGS '0'
#define SET_SETTINGS '1'
#define HOME '2'
#define HUMIDITY_ON '3'
#define HUMIDITY_OFF '4'
#define MORE_A_SENS '5'
#define WND_LEAF_ON '6'
#define WND_LEAF_OFF '7'
#define CONDITION_ON '8'


int state = WAITING_ST;
bool auto = true;
int wateringTimeout = 10*1000;
int humidifierTimeout = 20*1000;
int ANGLE = 0;
int ANGLE_S = 45;
int TOK = 1,5; //ток, текущий в системе

uint32_t watering_stime;
uint32_t humidifier_stime;
Servo myservo1;

int getCommand(){
  int cmd = Serial.read();
  return cmd;
}

void waitingSt_handler(int cmd){
  switch(cmd){
    case NO_CMD:{
      break;
    }
    case SETTINGS:{
      settingsSt_handler(cmd):
      break;
    }
    case HUMIDITY_ON:{
      humidity_onSt_handler(cmd);
      break;
    }
    case MORE_A_SENS:{
      more_a_sensSt_handler(cmd);
      break;
    }
    case WND_LEAF_ON:{
      wnd_leaf_onSt_handler(cmd);
      break;      
    }
    case CONDITION_ON:{
      condition_onSt_handler(cmd);
      break;
    }  
    }
}

void more_a_sensSt_handler(int cmd){
  //переход на экран ПОДРОБНЕЕ О ДАТЧИКАХ 
}

void s_ch_water_level_handler(){

 bool waterLevel = checkWaterLevel();
 if (waterLevel){
  watering_stime = millis();
  return '1'
 }
 else{
  return '0'
 }
}

void a_ch_water_level_handler(){

 bool waterLevel = checkWaterLevel();
 if (waterLevel){
  humidifier_stime = millis();
  return '1' 
 }
 else{
  retutn '0'
 }
}

void settingsSt_handler(int cmd){
  //переход на экран НАСТРОЙКИ
}

void humidity_onSt_handler(int cmd){
  if (auto){
    if (s_ch_water_level_handler()){
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
          state = CONDITION_ON_ST;}
          }
        }
    if (a_ch_water_level_handler()){
      uint32_t time_now = millis();
      humidifier_turn_on();
 
      if (abs(time_now - humidifier_stime) >= humidifierTimeout){
        humidifier_turn_off();
        state = WAITING_ST;}
      else{
        bool waterLevel = checkWaterLevel();
        if (!waterLevel){
          humidifier_turn_off();
          state = CONDITION_ON_ST;
          }
        }
      }
    }
}

void set_settingsSt_handler(int cmd){
  //запись нормальных условий и их амплитуду
}

void wnd_overloadSt_handler(int cmd){
  int tok =; //надо узнать функцию !!!
  if (tok > TOK){
    int ANGLE = ANGLE_S;    
  }
}

void wnd_leaf_onSt_handler(int cmd){
  if (auto){
    int angle_1 =; //выставляют угол для открытия
    if (ANGLE == 45){
      if (angle_1 > 45){
        int angle = 45;
      }
      else{
        int angle = angle_1;
       }
      }
    else{
      int angle = angle_1;
    }
    myservo1.write(angle); //если перегрузка
    }
    myservo1.write(30);
    delay(500);
  
    myservo1.write(45);
    delay(500);
  
    myservo1.write(90);
    delay(500);

    myservo1.write(120);
    delay(500);

    myservo1.write(0);
    delay(500);
    //код для сервака с условием угла angle
  }
  }
  else{
    int angle_1 =; //выставляют угол для открытия
    if (ANGLE == 45){
      if (angle_1 > 45){
        int angle = 45;
      }
      else{
        int angle = angle_1;
        }
      }
    else{
      int angle = angle_1;
    }
  myservo1.write(angle);
  }
  //код для сервака с условием угла angle
  }
}

void condition_onSt_handler(int cmd){
  //вывод предупреждения о поломке датчика/механизма
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  myservo1.attach(2);
}

void loop() {
  int cmd = getCommand();
  switch(state){
    case WAITING_ST:{
      waitingSt_handler(cmd);
      break;      
    }
    case MORE_A_SENS_ST:{
      more_a_sensSt_handler(cmd);
      break;
    }
    case SETTINGS_ST:{
      settingsSt_handler(cmd);
      break;
    }
    case SET_SETTINGS_ST:{
      set_settingsSt_handler(cmd);
      break;
    }
    case HUMIDITY_ON_ST:{
      humidity_onSt_handler(cmd);
      break;
    }
    case WND_LEAF_ON_ST:{
      wnd_leaf_onSt_handler(cmd);
      break;
    }
    case CONDITION_ON_ST:{
      condition_onSt_handler(cmd);
    }
  }
}
