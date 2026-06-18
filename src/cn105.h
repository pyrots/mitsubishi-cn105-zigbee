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

  bool getPower() const;
  bool isConnected() const;
  bool isOperating() const;

  ClimateMode getMode() const;

  float getTargetTemperature() const;
  float getRoomTemperature() const;

  const char* getFanMode() const;
  const char* getVaneMode() const;
  const char* getWideVaneMode() const;

  void setPower(bool on);
  void setMode(ClimateMode mode);
  void setTargetTemperature(float temperature);
  void setFanMode(const char* fan);
  void setVaneMode(const char* vane);
  void setWideVaneMode(const char* wideVane);

private:
  bool _power = false;
  bool _connected = false;
  bool _operating = false;

  ClimateMode _mode = MODE_AUTO;

  float _targetTemperature = 21.0;
  float _roomTemperature = 0.0;

  const char* _fanMode = "AUTO";
  const char* _vaneMode = "AUTO";
  const char* _wideVaneMode = "|";

  ClimateMode heatPumpModeToClimateMode(const char* mode) const;
  const char* climateModeToHeatPumpMode(ClimateMode mode) const;

  void updateClimateState();
};

#endif