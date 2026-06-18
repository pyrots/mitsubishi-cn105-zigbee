#include "cn105.h"
#include "config.h"

#include <HeatPump.h>

HardwareSerial CN105Serial(1);
HeatPump hp;

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

    // Permet de conserver la télécommande IR
    hp.enableExternalUpdate();

    // Synchronisation plus rapide
    hp.setFastSync(true);

    Serial.println("[CN105] OK");
}

void CN105::loop()
{
    hp.sync();

    heatpumpSettings current = hp.getSettings();

    _power = (String(current.power) == "ON");

    if (String(current.mode) == "HEAT")
        _mode = MODE_HEAT;
    else if (String(current.mode) == "COOL")
        _mode = MODE_COOL;
    else if (String(current.mode) == "DRY")
        _mode = MODE_DRY;
    else if (String(current.mode) == "FAN")
        _mode = MODE_FAN;
    else
        _mode = MODE_AUTO;

    _targetTemperature = current.temperature;
    _roomTemperature = current.roomTemperature;
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
}

void CN105::setMode(ClimateMode mode)
{
    heatpumpSettings s = hp.getSettings();

    switch (mode)
    {
        case MODE_HEAT:
            s.mode = "HEAT";
            break;

        case MODE_COOL:
            s.mode = "COOL";
            break;

        case MODE_DRY:
            s.mode = "DRY";
            break;

        case MODE_FAN:
            s.mode = "FAN";
            break;

        default:
            s.mode = "AUTO";
            break;
    }

    hp.setSettings(s);
    hp.update();
}

void CN105::setTargetTemperature(float temperature)
{
    heatpumpSettings s = hp.getSettings();

    s.temperature = temperature;

    hp.setSettings(s);
    hp.update();
}