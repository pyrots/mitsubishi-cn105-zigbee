#ifndef CLIMATE_STATE_H
#define CLIMATE_STATE_H

#include "cn105.h"

struct ClimateState {
    bool power = false;

    ClimateMode mode = MODE_AUTO;

    float roomTemperature = 0.0;
    float targetTemperature = 21.0;

    String fanMode = "AUTO";
    String vaneMode = "AUTO";

    unsigned long lastUpdate = 0;
};

extern ClimateState climateState;

#endif