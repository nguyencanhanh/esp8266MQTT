#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D4, D5);
const char *ssid = "OPPO Reno4";
const char *password = "11111111";
const char *mqtt_server = "192.168.0.223";  
const int mqtt_port = 1883;
const char *mqtt_user = "esp8266";
const char *mqtt_password = "Esp8266wifi";
const char *mqtt_topic = "dulieu";
int ledState = LOW; 
unsigned long previousMillis = 0; 
const long interval = 1000;
const int ledPin = 2;
String message;
String myTopic;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, 1);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if (message == "BLINK"){
     unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPin, ledState);
    }
  }
  client.loop();
}

void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // Convert payload to string
  message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
  if (message == "OFF") {
    digitalWrite(2, 1);
  } else if (message == "ON") {
    digitalWrite(2, 0);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("esp8266", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
      const char* topic1 = "den";
      if (digitalRead(2) == 0)
        client.publish(topic1, "0");
      else
        client.publish(topic1, "1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
