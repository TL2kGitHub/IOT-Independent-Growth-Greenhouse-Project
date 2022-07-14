#include <dht.h>
#include "WiFiEsp.h"
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"

#include "webPageTop.h" //print webpage
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

#define SensorPin A0
#define DHT11_PIN 8

dht DHT;
const int MTR = 10;
const int PMP = 13;
const int RGBP = 9;
const int NUML = 30;
const int LDR = A1;

char ssid[] = "5GGG";            // your network SSID (name)
char pass[] = "12345678";        // your network password
int status = WL_IDLE_STATUS;

int ledStatus = LOW;

WiFiEspServer server(80);
RingBuffer buf(8);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUML, RGBP, NEO_GRB + NEO_KHZ800);
void setup()
{
  lcd.begin(16, 2);
  pinMode(MTR, OUTPUT);
  pinMode(PMP, OUTPUT);
  pixels.begin();
  pixels.setBrightness(80);
  pinMode(LDR, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();

  // start the web server on port 80
  server.begin();
}


void loop()
{
  MTR_PMP_LCD();
  WiFiEspClient client = server.available();  // listen for incoming clients

  if (client) {                               // if you get a client,
    Serial.println("New client");             // print a message out the serial port
    buf.init();                               // initialize the circular buffer
    while (client.connected()) {              // loop while the client's connected
      if (client.available()) {               // if there's bytes to read from the client,
        char c = client.read();               // read a byte, then
        buf.push(c);                          // push it to the ring buffer


        if (buf.endsWith("\r\n\r\n")) {
          sendHttpResponse(client);
          break;
        }

        if (buf.endsWith("/z1")) {
          digitalWrite(MTR, HIGH);
          Serial.println("Turn fan ON");
        }
        if (buf.endsWith("/z0")) {
          digitalWrite(MTR, LOW);
          Serial.println("Turn fan OFF");
        }
        if (buf.endsWith("/P1")) {
          digitalWrite(PMP, HIGH);
          Serial.println("Turn pump ON");
        }
        if (buf.endsWith("/P0")) {
          digitalWrite(PMP, LOW);
          Serial.println("Turn pump OFF");
        }
      }
    }

    // close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}


void sendHttpResponse(WiFiEspClient client)
{
  client.print(
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    //"Refresh: 5\r\n"
    "\r\n");

}
void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
