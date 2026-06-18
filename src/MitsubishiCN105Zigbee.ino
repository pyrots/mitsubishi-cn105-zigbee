#include <Arduino.h>

#include "version.h"
#include "config.h"
#include "cn105.h"
#include "climate_state.h"

CN105 cn105;

unsigned long lastHeartbeat = 0;
unsigned long lastStatusPrint = 0;

const char* modeToString(ClimateMode mode)
{
  switch (mode)
  {
    case MODE_HEAT: return "HEAT";
    case MODE_COOL: return "COOL";
    case MODE_DRY:  return "DRY";
    case MODE_FAN:  return "FAN";
    case MODE_AUTO:
    default:        return "AUTO";
  }
}

void printBanner()
{
  Serial.println();
  Serial.println("=======================================");
  Serial.println(FW_NAME);
  Serial.println("=======================================");
  Serial.print("Version      : ");
  Serial.println(FW_VERSION);
  Serial.print("Build        : ");
  Serial.println(FW_BUILD_DATE);
  Serial.print("Manufacturer : ");
  Serial.println(DEVICE_MANUFACTURER);
  Serial.print("Model        : ");
  Serial.println(DEVICE_MODEL);
  Serial.print("Device       : ");
  Serial.println(DEVICE_NAME);
  Serial.print("Location     : ");
  Serial.println(DEVICE_LOCATION);
  Serial.println("Mode         : CN105 v0.1");
  Serial.println("Zigbee       : prepared, not active");
  Serial.println("OTA          : prepared, not active");
  Serial.println("=======================================");
}

void printStatus()
{
  Serial.println();
  Serial.println("------------ CLIMATE STATE ------------");

  Serial.print("Power        : ");
  Serial.println(climateState.power ? "ON" : "OFF");

  Serial.print("Mode         : ");
  Serial.println(modeToString(climateState.mode));

  Serial.print("Target temp  : ");
  Serial.print(climateState.targetTemperature, 1);
  Serial.println(" °C");

  Serial.print("Room temp    : ");
  Serial.print(climateState.roomTemperature, 1);
  Serial.println(" °C");

  Serial.print("Fan          : ");
  Serial.println(climateState.fanMode);

  Serial.print("Vane         : ");
  Serial.println(climateState.vaneMode);

  Serial.print("Last update  : ");
  Serial.print(climateState.lastUpdate);
  Serial.println(" ms");

  Serial.print("Uptime       : ");
  Serial.print(millis() / 1000);
  Serial.println(" s");

  Serial.println("----------------------------------------");
}

void heartbeat()
{
  unsigned long now = millis();

  if (now - lastHeartbeat >= HEARTBEAT_PERIOD_MS)
  {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    lastHeartbeat = now;
  }
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  delay(1500);

  printBanner();

  Serial.println("[BOOT] Initialisation CN105...");
  cn105.begin();

  Serial.println("[BOOT] Démarrage terminé.");
}

void loop()
{
  cn105.loop();
  heartbeat();

  unsigned long now = millis();

  if (now - lastStatusPrint >= STATUS_PRINT_PERIOD_MS)
  {
    printStatus();
    lastStatusPrint = now;
  }

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    Serial.println("[BUTTON] Bouton pressé - action réservée v0.2/v0.3");
    delay(500);
  }

  delay(100);
}