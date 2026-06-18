#ifndef CN105_H
#define CN105_H

#include <Arduino.h>

enum ClimateMode {
    MODE_AUTO,
    MODE_HEAT,
    MODE_COOL,
    MODE_DRY,
    MODE_FAN
};

class CN105 {
public:
    void begin();
    void loop();

    // Lecture
    bool getPower();
    ClimateMode getMode();
    float getTargetTemperature();
    float getRoomTemperature();

    // Commandes
    void setPower(bool on);
    void setMode(ClimateMode mode);
    void setTargetTemperature(float temperature);

private:
    bool _power = false;
    ClimateMode _mode = MODE_AUTO;
    float _targetTemperature = 21.0;
    float _roomTemperature = 0.0;
};

#endif