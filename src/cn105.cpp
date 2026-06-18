#include "cn105.h"
#include "config.h"
#include "version.h"
#include "climate_state.h"

#include <HeatPump.h>

HardwareSerial CN105Serial(1);
HeatPump hp;

static ClimateMode heatPumpModeToClimateMode(const String &mode)
{
  if (mode == "HEAT") return MODE_HEAT;
  if (mode == "COOL") return MODE_COOL;
  if (mode == "DRY")  return MODE_DRY;
  if (mode == "FAN")  return MODE_FAN;
  return MODE_AUTO;
}

static const char* climateModeToHeatPumpMode(ClimateMode mode)
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

void CN105::begin()
{
  Serial.println("[CN105] Initialisation");

  CN105Serial.begin(
    CN105_BAUDRATE,
    SERIAL_8E1,
    CN105_RX_PIN,
    CN105_TX_PIN
  );

  hp.connect(&CN105Serial);

  hp.enableExternalUpdate();
  hp.setFastSync(true);

  Serial.println("[CN105] OK");
}

void CN105::loop()
{
  hp.sync();

  heatpumpSettings current = hp.getSettings();

  _power = (String(current.power) == "ON");
  _mode = heatPumpModeToClimateMode(String(current.mode));
  _targetTemperature = current.temperature;
  _roomTemperature = current.roomTemperature;

  climateState.power = _power;
  climateState.mode = _mode;
  climateState.targetTemperature = _targetTemperature;
  climateState.roomTemperature = _roomTemperature;
  climateState.fanMode = String(current.fan);
  climateState.vaneMode = String(current.vane);
  climateState.lastUpdate = millis();
}

bool CN105::getPower()
{
  return _power;
}

ClimateMode CN105::getMode()
{
  return _mode;
}

float CN105::getTargetTemperature()
{
  return _targetTemperature;
}

float CN105::getRoomTemperature()
{
  return _roomTemperature;
}

void CN105::setPower(bool on)
{
  heatpumpSettings s = hp.getSettings();

  s.power = on ? "ON" : "OFF";

  hp.setSettings(s);
  hp.update();

  _power = on;
  climateState.power = _power;
  climateState.lastUpdate = millis();
}

void CN105::setMode(ClimateMode mode)
{
  heatpumpSettings s = hp.getSettings();

  s.mode = climateModeToHeatPumpMode(mode);

  hp.setSettings(s);
  hp.update();

  _mode = mode;
  climateState.mode = _mode;
  climateState.lastUpdate = millis();
}

void CN105::setTargetTemperature(float temperature)
{
  heatpumpSettings s = hp.getSettings();

  s.temperature = temperature;

  hp.setSettings(s);
  hp.update();

  _targetTemperature = temperature;
  climateState.targetTemperature = _targetTemperature;
  climateState.lastUpdate = millis();
}