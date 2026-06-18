Mitsubishi CN105 Zigbee

ESP32-H2 Zigbee bridge for Mitsubishi Electric air conditioners using the CN105 interface.

Goals

* Native Zigbee communication
* Zigbee2MQTT integration
* No Wi-Fi
* No ESPHome
* OTA ready
* One ESP32-H2 per indoor unit
* Support for multiple splits

Hardware

Indoor units

* Mitsubishi MSZ-SF42VE3 Salon
* Mitsubishi MSZ-SF42VE3 Cuisine
* Mitsubishi MSZ-SF42VE3 Chambre étage

Electronics

* Waveshare ESP32-H2 Zero
* BSS138 level shifter
* CN105 JST 5-pin connector

Software

* Arduino IDE
* ESP32 Arduino Core
* HeatPump library
* Zigbee native support
* Zigbee2MQTT

Planned features

v0.1

* CN105 communication
* State reading
* Power control
* Temperature control
* Fan control
* Vane control

v0.2

* Native Zigbee router
* Diagnostics

v0.3

* Home Assistant climate entity

v1.0

* OTA support
* Stable release