#include <WiFi.h>
#include <PicoMQTT.h>
#include <WiFiManager.h>

#define LED 18
#define RELAY 13
#define SWITCH 33
#define WIFI_BUTTON 4

String Wifissid;
PicoMQTT::Server mqtt;

int push_count;
int commandMsg = 2;
int lampState = LOW;
int wifi_timeout = 90; // seconds
int currentSwitchState = 0;
unsigned long start_time;

// DEVICE ID
const char* topic_d2u = "opin/SmartLamp_u5on8/d2u";
const char* topic_u2d = "opin/SmartLamp_u5on8/u2d";
const char* device_ssid = "OPIN-SmartLamp-u5on8";

void connect_mqtt() {
  Serial.println("\nStart MQTT Broker");
  const char* mqtt_server = WiFi.localIP().toString().c_str();

  // Subscribe to a topic pattern and attach a callback
  mqtt.subscribe(topic_u2d, [](const char * topic, const char * payload) {
    Serial.printf("Received message in topic '%s': %s\n", topic, payload);
    commandMsg = atoi(payload);
  });

  // Start the broker
  mqtt.begin();

  delay(100);
  Serial.println("MQTT Broker ready");
}

void connect_wifi() {
  Serial.println("\n Connecting...");
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  wm.setConnectTimeout(5);
  wm.setConfigPortalTimeout(wifi_timeout);
  wm.startConfigPortal(device_ssid);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }else if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void reset_wifi() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  WiFi.disconnect();
  wm.resetSettings();
}

void reconnect_wifi(String ssid, String pass) {
  delay(100);
  Serial.println("Reconnecting...");
  WiFi.disconnect();
  WiFi.begin(ssid, pass);

  unsigned long start_timeout = millis();
  while (WiFi.status() != WL_CONNECTED){
    if (millis() - start_timeout >= 3000){
      break;
    }
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  Serial.println("\n Starting up");
  digitalWrite(RELAY, HIGH);
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(WIFI_BUTTON, INPUT_PULLUP);
}

void loop() {
  // WIFI and MQTT Connection
  push_count = 0;
  if (digitalRead(WIFI_BUTTON) == LOW) {
    start_time = millis();
    while (true) {
      if (millis() - start_time >= 100 && digitalRead(WIFI_BUTTON) == HIGH) {
        push_count = 1;
        break;
      }
      if (millis() - start_time >= 2000 && digitalRead(WIFI_BUTTON) == LOW) {
        push_count = 2;
        break;
      }
    }
  }

  if (push_count == 1) {
    connect_wifi();
  } else if (push_count == 2) {
    reset_wifi();
    connect_wifi();
  }

  if (WiFi.status() != WL_CONNECTED){
    WiFiManager wm;
    reconnect_wifi(wm.getWiFiSSID(), WiFi.psk());
  } else {
    mqtt.loop();
    digitalWrite(LED, HIGH);
  }

  // Main Program
  int switchState = digitalRead(SWITCH);
  if (switchState == 0 && commandMsg == 2 && currentSwitchState == 1) {
    currentSwitchState = 0;
    lampState = HIGH;
    Serial.println("Switch ON");
    String json_data =  String("{") +
                        String("\"from_switch\": 1") + String(",")  +
                        String("\"state\": 1")  +
                        String("}");
    mqtt.publish(topic_d2u, json_data.c_str());
  }
  else if (switchState == 1 && commandMsg == 2 && currentSwitchState == 0) {
    currentSwitchState = 1;
    lampState = LOW;
    Serial.println("Switch OFF");
    String json_data =  String("{") +
                        String("\"from_switch\": 1") + String(",")  +
                        String("\"state\": 0")  +
                        String("}");
    mqtt.publish(topic_d2u, json_data.c_str());
  }
  if (commandMsg == 0) {
    lampState = LOW;
    Serial.println("User: Turn OFF");
  }
  else if (commandMsg == 1) {
    lampState = HIGH;
    Serial.println("User: Turn ON");
  }
  if (lampState == HIGH) {
    digitalWrite(RELAY, LOW);
  }
  else {
    digitalWrite(RELAY, HIGH);
  }
  commandMsg = 2;
  delay(10);
}
