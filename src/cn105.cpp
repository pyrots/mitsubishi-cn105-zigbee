#include "cn105.h"
#include "config.h"
#include "version.h"
#include "climate_state.h"

#include <HeatPump.h>

static HardwareSerial CN105Serial(1);
static HeatPump hp;

ClimateMode CN105::heatPumpModeToClimateMode(const char* mode) const
{
  if (mode == nullptr) return MODE_AUTO;

  if (strcmp(mode, "HEAT") == 0) return MODE_HEAT;
  if (strcmp(mode, "COOL") == 0) return MODE_COOL;
  if (strcmp(mode, "DRY")  == 0) return MODE_DRY;
  if (strcmp(mode, "FAN")  == 0) return MODE_FAN;

  return MODE_AUTO;
}

const char* CN105::climateModeToHeatPumpMode(ClimateMode mode) const
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

  hp.connect(&CN105Serial, CN105_BAUDRATE, CN105_RX_PIN, CN105_TX_PIN);

  hp.enableExternalUpdate();
  hp.setFastSync(true);

  Serial.println("[CN105] OK");
}

void CN105::loop()
{
  hp.sync();

  heatpumpSettings settings = hp.getSettings();
  heatpumpStatus status = hp.getStatus();

  _power = settings.power && strcmp(settings.power, "ON") == 0;
  _connected = settings.connected;
  _operating = status.operating;

  _mode = heatPumpModeToClimateMode(settings.mode);

  _targetTemperature = settings.temperature;
  _roomTemperature = status.roomTemperature;

  _fanMode = settings.fan ? settings.fan : "AUTO";
  _vaneMode = settings.vane ? settings.vane : "AUTO";
  _wideVaneMode = settings.wideVane ? settings.wideVane : "|";

  updateClimateState();
}

void CN105::updateClimateState()
{
  climateState.power = _power;
  climateState.connected = _connected;
  climateState.operating = _operating;

  climateState.mode = _mode;

  climateState.targetTemperature = _targetTemperature;
  climateState.roomTemperature = _roomTemperature;

  climateState.fanMode = _fanMode;
  climateState.vaneMode = _vaneMode;
  climateState.wideVaneMode = _wideVaneMode;

  climateState.lastUpdate = millis();
}

bool CN105::getPower() const
{
  return _power;
}

bool CN105::isConnected() const
{
  return _connected;
}

bool CN105::isOperating() const
{
  return _operating;
}

ClimateMode CN105::getMode() const
{
  return _mode;
}

float CN105::getTargetTemperature() const
{
  return _targetTemperature;
}

float CN105::getRoomTemperature() const
{
  return _roomTemperature;
}

const char* CN105::getFanMode() const
{
  return _fanMode;
}

const char* CN105::getVaneMode() const
{
  return _vaneMode;
}

const char* CN105::getWideVaneMode() const
{
  return _wideVaneMode;
}

void CN105::setPower(bool on)
{
  heatpumpSettings settings = hp.getSettings();

  settings.power = on ? "ON" : "OFF";

  hp.setSettings(settings);
  hp.update();

  _power = on;
  updateClimateState();
}

void CN105::setMode(ClimateMode mode)
{
  heatpumpSettings settings = hp.getSettings();

  settings.mode = climateModeToHeatPumpMode(mode);

  hp.setSettings(settings);
  hp.update();

  _mode = mode;
  updateClimateState();
}

void CN105::setTargetTemperature(float temperature)
{
  if (temperature < 16.0) temperature = 16.0;
  if (temperature > 31.0) temperature = 31.0;

  heatpumpSettings settings = hp.getSettings();

  settings.temperature = temperature;

  hp.setSettings(settings);
  hp.update();

  _targetTemperature = temperature;
  updateClimateState();
}

void CN105::setFanMode(const char* fan)
{
  if (fan == nullptr) return;

  heatpumpSettings settings = hp.getSettings();

  settings.fan = fan;

  hp.setSettings(settings);
  hp.update();

  _fanMode = fan;
  updateClimateState();
}

void CN105::setVaneMode(const char* vane)
{
  if (vane == nullptr) return;

  heatpumpSettings settings = hp.getSettings();

  settings.vane = vane;

  hp.setSettings(settings);
  hp.update();

  _vaneMode = vane;
  updateClimateState();
}

void CN105::setWideVaneMode(const char* wideVane)
{
  if (wideVane == nullptr) return;

  heatpumpSettings settings = hp.getSettings();

  settings.wideVane = wideVane;

  hp.setSettings(settings);
  hp.update();

  _wideVaneMode = wideVane;
  updateClimateState();
}