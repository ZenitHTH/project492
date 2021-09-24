#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Setup.h"
#include "Data.h"
#include "Board.h"
#include "Pin.h"
#include "PinCheck.h"
#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>


#define DEVICE_COL  4
#define DEVICE_ROW  4 
#define NUM_LEDS    16
#define LED_PIN     2

#define mqtt_server       "m24.cloudmqtt.com"
#define mqtt_port         15342
#define mqtt_user         "qyuzvafp"
#define mqtt_pass         "0ynj_3e3rzJ6"
#define topic             "toys/test"

WiFiManager wm;
WiFiClient espClient;
PubSubClient client(espClient);
RPR0521RS rpr0521rs[DEVICE_ROW][DEVICE_COL];
PinCheck pincheck;
WiFiUDP Udp;

static const char ntpServerName[] = "time.navy.mi.th";
unsigned int localport = 123;
static const int timeZone = 7;
const uint8_t tcaAddr[2] = {0x71,0x70};
pin **p;

time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
void WiFi_Setup();
void Reconnect();
char* f2char(double);
char* int2char(int);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Wire.begin();
  WiFi_Setup();
  Udp.begin(123);
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
  //FastLED.addLeds<WS2812B,LED_PIN,GRB>(leds,NUM_LEDS);
  //FastLED.setBrightness(50);
  p = MatchSensor(tcaAddr,DEVICE_ROW,DEVICE_COL);
  SetupSensor(p,rpr0521rs);
}

void loop()
{
  Board board;
  char* msg;
  if(!client.connected())
  {
    Reconnect();
  }
  client.loop();
  delay(2000);
  board = GetValue(p,rpr0521rs);

  pincheck.Insert(board);
  pincheck.CheckDiffrent();
  msg = pincheck.PublishData(now());
  if(msg != "ERR") client.publish("toys/test",msg,true);
  board.PrintStatus();
  delay(500);
}

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets


// send an NTP request to the time server at the given address
time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}


void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}


void WiFi_Setup()
{
    wm.setTimeout(300);

    if(!wm.autoConnect("AutoConnect_ESP32"))
    {
        Serial.println("Connecting Failed");
        delay(3000);
        ESP.restart();
    }

    client.setServer(mqtt_server,mqtt_port);
    client.subscribe(topic);
}

void Reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char* f2char(double f)
{
  char* value;
  dtostrf(f,8,4,value);
  return value;
}

char* int2char(int i)
{
  char* value;
  String s = String(i,DEC);
  s.toCharArray(value,8);
  return value;
}