#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "nama wifi"; //ubah ke nama wifi kalian
const char* password = "password"; //ubah ke password dari wifi tersebut
const char* ip = "192.168.1.00"; //ubah ke ip adrress laptop kalian
const int triggerPin = 12; //ubah sesuai pin trigger kalian
const int echoPin = 14; //ubah sesuai pin trigger kalian
const int jarakMax = 40; //jarak maksimal sensor mendeteksi suatu benda
const int lamaSuara = 230; //waktu yang dibutuhkan untuk memainkan suara kalian (ms)

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
  unsigned int jarak = hitungJarak();
  if (jarak > 0 && jarak < jarakMax) 
  {
    sendRequestLaptop();
  }
  delay(lamaSuara); 
}


unsigned int hitungJarak() 
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  unsigned long pulse = pulseIn(echoPin, HIGH);
  unsigned int jarak = pulse * 0.034 / 2;

  return jarak;
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
