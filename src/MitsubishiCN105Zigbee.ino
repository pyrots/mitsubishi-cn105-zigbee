#include <Arduino.h>

#include "version.h"
#include "config.h"
#include "cn105.h"

// ======================================================
// Objets globaux
// ======================================================

CN105 cn105;

// ======================================================
// Timers
// ======================================================

unsigned long lastHeartbeat = 0;
unsigned long lastStatusPrint = 0;

// ======================================================
// Fonctions utilitaires
// ======================================================

const char* modeToString(ClimateMode mode)
{
  switch (mode)
  {
    case MODE_HEAT:
      return "HEAT";
    case MODE_COOL:
      return "COOL";
    case MODE_DRY:
      return "DRY";
    case MODE_FAN:
      return "FAN";
    case MODE_AUTO:
    default:
      return "AUTO";
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
  Serial.println("------------ CN105 STATUS ------------");

  Serial.print("Power        : ");
  Serial.println(cn105.getPower() ? "ON" : "OFF");

  Serial.print("Mode         : ");
  Serial.println(modeToString(cn105.getMode()));

  Serial.print("Target temp  : ");
  Serial.print(cn105.getTargetTemperature(), 1);
  Serial.println(" °C");

  Serial.print("Room temp    : ");
  Serial.print(cn105.getRoomTemperature(), 1);
  Serial.println(" °C");

  Serial.print("Uptime       : ");
  Serial.print(millis() / 1000);
  Serial.println(" s");

  Serial.println("---------------------------------------");
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

// ======================================================
// SETUP
// ======================================================

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

// ======================================================
// LOOP
// ======================================================

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

  // Réservé pour factory reset Zigbee plus tard
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    Serial.println("[BUTTON] Bouton pressé - action réservée v0.2/v0.3");
    delay(500);
  }

  delay(100);
}