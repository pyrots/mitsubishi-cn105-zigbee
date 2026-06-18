#ifndef CLIMATE_STATE_H
#define CLIMATE_STATE_H

#include <Arduino.h>
#include "cn105.h"

struct ClimateState {
  bool power = false;
  bool connected = false;
  bool operating = false;

  ClimateMode mode = MODE_AUTO;

  float targetTemperature = 21.0;
  float roomTemperature = 0.0;

  String fanMode = "AUTO";
  String vaneMode = "AUTO";
  String wideVaneMode = "|";

  unsigned long lastUpdate = 0;
};

extern ClimateState climateState;

#endif