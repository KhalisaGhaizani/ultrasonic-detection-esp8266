#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "name"; //change it to your wifi name | ubah ke nama wifi kalian
const char* password = "pass"; //change it to its password | ubah ke passwordnya
const char* ip = "192.168.1.00"; //change it tou your computer's ip address | ubah ke ip address laptop kalian
const int triggerPin = 12; //change it according to your trigger pin | ubah sesuai dengan trigger pinnya
const int echoPin = 14; //change it according to your echo pin | ubah sesuai dengan echo pinnya
const int maxDistance = 40; //max distance that it will detect something | jarak maksimal sensor mendeteksi sesuatu (cm)
const int soundDuration = 230; //the duration of your sound | durasi suara yang ingin dimainkan (ms)

void setup() 
{
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
  delay(10);

  wifiConnect();
}

void loop() 
{
  unsigned int distance = calcDistance();
  if (distance > 0 && distance < maxDistance) 
  {
    sendRequestLaptop();
  }
  delay(soundDuration); 
}


unsigned int calcDistance() 
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  unsigned long pulse = pulseIn(echoPin, HIGH);
  unsigned int distance = pulse * 0.034 / 2;

  return distance;
}

void sendRequestLaptop() 
{
  WiFiClient client;
  if (client.connect(ip, 80)) 
  {  
    client.print("GET /play_sound HTTP/1.1\r\n"
                 "Host: ");
    client.print(ip);
    client.print("\r\nConnection: close\r\n\r\n");
    delay(10);
    client.stop();
  }
}

void wifiConnect() 
{
  WiFi.begin(ssid, password);
}
