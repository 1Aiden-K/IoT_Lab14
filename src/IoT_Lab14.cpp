/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab14/src/IoT_Lab14.ino"
/*
 * Project IoT_Lab14
 * Description:
 * Author:
 * Date:
 */

void callback(char *topic, byte *payload, unsigned int length);
void setup();
void loop();
#line 8 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab14/src/IoT_Lab14.ino"
SYSTEM_THREAD(ENABLED);

#include "MQTT.h"
#include "oled-wing-adafruit.h"

OledWingAdafruit display;

float lat = 0;
float longi = 0;

unsigned long moment = millis();

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  String s = p;
  double value = s.toFloat();

  if (String(topic) == "christianity/lat")
  {
    lat = value;
  }
  else if (String(topic) == "christianity/longi")
  {
    longi = value;
  }
}

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  display.setup();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
}

void loop()
{
  display.loop();
  if (client.isConnected())
  {
    client.loop();

    if (millis() >= moment + 10000)
    {
      moment = millis();
      client.publish("christianity", "GIVE ME THE POSITION!");
    }
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("christianity/lat");
    client.subscribe("christianity/longi");
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Latitude: ");
  display.println(lat);
  display.print("Longitude: ");
  display.println(longi);
  display.display();
}