#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "aWOT.h"
#include "StaticFiles.h"

//TODO:Hacer config.h con estos datos (los relacionados con la conexion) y añadirlo al gitIgnore
//TODO:Devolver el array de JSON por el get
#define WIFI_SSID "RollerfHotspot"
#define WIFI_PASSWORD "123es456"

IPAddress ip(192, 168, 43, 200);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

#define LED_BUILTIN 2

WiFiServer server(80);
Application app;

//StaticJsonDocument<300> doc;

void getJson(Request &req, Response &res) {
  StaticJsonDocument<1000> doc;

  //crearJson();
  JsonObject objUno = doc.createNestedObject("nestedObject1");
  objUno["key"] = 40;
  objUno["description"] = "myDescription40";
  objUno["active"] = true;
  objUno["qty"] = 1.4;
  JsonObject objDos = doc.createNestedObject("nestedObject2");
  objDos["key"] = 41;
  objDos["description"] = "myDescription41";
  objDos["active"] = false;
  objDos["qty"] = 1.5;
  JsonObject objTres = doc.createNestedObject("nestedObject3");
  objTres["key"] = 42;
  objTres["description"] = "myDescription42";
  objTres["active"] = true;
  objTres["qty"] = 1.6;

  delay(1000);

  String response;
  serializeJson(doc, response);
  res.set("Content-Type", "application/json");
  res.print(response);
}

//void updateJson(Request &req, Response &res) {
//  ledOn = (req.read() != '0');
//  digitalWrite(LED_BUILTIN, ledOn);
//  return getJson(req, res);
//}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  app.get("/json", &getJson);
  //app.put("/json", &updateJson);
  app.use(staticFiles());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client.connected()) {
    app.process(&client);
  }
  StaticJsonDocument<1000> doc;

  //crearJson();
  JsonObject objUno = doc.createNestedObject("nestedObject1");
  objUno["key"] = 40;
  objUno["description"] = "myDescription40";
  objUno["active"] = true;
  objUno["qty"] = 1.4;
  JsonObject objDos = doc.createNestedObject("nestedObject2");
  objDos["key"] = 41;
  objDos["description"] = "myDescription41";
  objDos["active"] = false;
  objDos["qty"] = 1.5;
  JsonObject objTres = doc.createNestedObject("nestedObject3");
  objTres["key"] = 42;
  objTres["description"] = "myDescription42";
  objTres["active"] = true;
  objTres["qty"] = 1.6;

  delay(1000);

  serializeJson(doc, Serial);
  //serializeJson(doc, res);
  Serial.println();
}
void crearJson() {
  //  JsonObject objUno = doc.createNestedObject("nestedObject");
  //  objUno["key"] = 40;
  //  objUno["description"] = "myDescription";
  //  objUno["active"] = true;
  //  objUno["qty"] = 1.414;
  //  JsonObject objDos = doc.createNestedObject("nestedObject");
  //  objDos["key"] = 40;
  //  objDos["description"] = "myDescription";
  //  objDos["active"] = true;
  //  objDos["qty"] = 1.414;
  //  JsonObject objTres = doc.createNestedObject("nestedObject");
  //  objTres["key"] = 40;
  //  objTres["description"] = "myDescription";
  //  objTres["active"] = true;
  //  objTres["qty"] = 1.414;
}
