//C++ code
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

#define DHTPIN 2
#define DHTTYPE DHT22

#define NO_CONNECTION_ST 0
#define WAITING_ST 1
#define DATA_GET_ST 2
#define WND_ON_ST 3
#define WND_ON_DATA_GET_ST 4
#define AUTO_OFF_ST 5
#define WND_ON_AUTO_OFF_ST 6
#define WND_OVERLOAD_ST 7

#define MESH_ON '0'
#define MESH_OFF '1'
#define DATA_GET '2'
#define TEMP_OK '3'
#define TEMP_ERROR '4'
#define WND_LEAF_OFF '5'
#define WND_LEAF_ON '6'
#define AUTO_OFF '7'
#define AUTO_ON '8'
#define WND_LEAF_OVERLOAD '9'
#define WND_LEAF_WARN '10'


int state = NO_CONNECTION_ST;
int ANGLE = 0;
int ANGLE_S = 45;
int TOK = 1,5; //ток, текущий в системе
bool conState = false;
bool auto = true;
int timeout = 5*60*1000;

DHT dht(DHTPIN, DHTTYPE);
Servo myservo1;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  myservo1.attach(2);

}

int getCommand(){
  int cmd = Serial.read();
  return cmd;
}

bool meshConnect(){
  conState = true;
}

void wnd_overloadSt_handler(int cmd){
  int tok =; //надо узнать функцию !!!
  if (tok > TOK){
    int ANGLE = ANGLE_S;    
  }
}

void wnd_on_auto_offSt_handler(int cmd){
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

void auto_offSt_handler(){
  bool auto = false;
}

void wnd_onSt_handler(int cmd){
  int temp = wnd_on_data_getSt_handler();
  uint32_t time = millis();
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

void data_getSt_handler(){
  float t = dht.readTemperature();
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
}

void wnd_on_data_getSt_handler(){
  float t = dht.readTemperature();
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
  return t;
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
    case DATA_GET_ST:{
      data_getSt_handler();
      break;
    }
    case WND_ON_ST:{
      wnd_onSt_handler(cmd);
      break;
    }
    case WND_OVERLOAD_ST:{
      wnd_overloadSt_handler(cmd);
      break;      
    }
  }  
}

void loop(){
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
    case DATA_GET_ST:{
      data_getSt_handler(cmd);
      break;
    }
     case WND_ON_ST:{
       wnd_onSt_handler(cmd);
       break;
     }
     case AUTO_OFF_ST:{
       auto = false;
       break;
     }
     case WND_ON_DATA_GET_ST:{
       wnd_on_data_getSt_handler(cmd);
       break;
     }
     case WND_ON_AUTO_OFF_ST:{
       wnd_on_auto_offSt_handler(cmd);
       break;       
     }
     case WND_OVERLOAD_ST:{
       wnd_overloadSt_handler(cmd);
       break;
     }

}
}
