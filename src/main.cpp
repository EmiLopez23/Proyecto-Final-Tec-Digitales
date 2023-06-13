/*
 *  Project 34-websock - main.cpp
 *      Show that using WebSockets is better than using normal Web servers
 *      in near real time systems
 *
 *      Austral 2023 - Electronica Digital - EAM
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "wifi_ruts.h"
#include "webpage.h"

#define PIN_1 14
#define PIN_2 33
#define PIN_3 13

WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

/*
 *  Private functions
 */

void activatePin(int pin1,int pin2,int pint3, int percentage1, int percentage2, int percentage3) {
  digitalWrite(PIN_1, HIGH);
  delay(10000 * percentage1 / 100);
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, HIGH);
  delay(10000 * percentage2 / 100);
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_3, HIGH);
  delay(10000 * percentage3 / 100);
  digitalWrite(PIN_3, LOW);
}

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void fillWithDrink1() {
  Serial.print("Drink 1");
  digitalWrite(PIN_1,HIGH);
  delay(10000);
  digitalWrite(PIN_1,LOW);
  server.send(200, "text/plain", "OK");
}

void fillWithDrink2() {
  int drink2Percentage = server.arg("percentage").toInt();
  Serial.print("Drink 2");
  digitalWrite(PIN_2,HIGH);
  delay(10000);
  digitalWrite(PIN_2,LOW);
  server.send(200, "text/plain", "OK");
}

void fillWithDrink3() {
  int drink3Percentage = server.arg("percentage").toInt();
  Serial.print("Drink 3");
  digitalWrite(PIN_3,HIGH);
  delay(10000);
  digitalWrite(PIN_3,LOW);
  server.send(200, "text/plain", "OK");
}

void handleDrinkPercentages(){
  if (server.hasArg("drink1p") && server.hasArg("drink2p") && server.hasArg("drink3p")) {
    int drink1Percentage = server.arg("drink1p").toInt();
    int drink2Percentage = server.arg("drink2p").toInt();
    int drink3Percentage = server.arg("drink3p").toInt(); 

  Serial.print("Drink 1: ");
  Serial.println(drink1Percentage);

  Serial.print("Drink 2: ");
  Serial.println(drink2Percentage);

  Serial.print("Drink 3: ");
  Serial.println(drink3Percentage);
   
  activatePin(PIN_1, PIN_2, PIN_3, drink1Percentage, drink2Percentage, drink3Percentage);
  server.send(200, "text/plain", "Drink percentages received");}
  else {
    server.send(400, "text/plain", "Drink percentages not received");
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD);

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);

  wifi_connect();
  Serial.println("IP Adress: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/drink1", fillWithDrink1);
  server.on("/drink2", fillWithDrink2);
  server.on("/drink3", fillWithDrink3);
  server.on("/drink", handleDrinkPercentages);

  server.begin();
}

void loop() {
  server.handleClient();
}

