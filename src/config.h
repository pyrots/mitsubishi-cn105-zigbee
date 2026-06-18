#ifndef CONFIG_H
#define CONFIG_H

// ======================================================
// Sélection de l'unité intérieure
// ======================================================

//#define DEVICE_SALON
//#define DEVICE_CUISINE
#define DEVICE_CHAMBRE_ETAGE

// ======================================================
// Paramètres selon l'unité
// ======================================================

#if defined(DEVICE_SALON)

  #define DEVICE_NAME      "mitsubishi_salon"
  #define DEVICE_LOCATION  "Salon"

#elif defined(DEVICE_CUISINE)

  #define DEVICE_NAME      "mitsubishi_cuisine"
  #define DEVICE_LOCATION  "Cuisine"

#elif defined(DEVICE_CHAMBRE_ETAGE)

  #define DEVICE_NAME      "mitsubishi_chambre_etage"
  #define DEVICE_LOCATION  "Chambre étage"

#else

  #error "Sélectionner DEVICE_SALON, DEVICE_CUISINE ou DEVICE_CHAMBRE_ETAGE"

#endif


// ======================================================
// GPIO ESP32-H2 Zero
// (à confirmer avec la carte réelle)
// ======================================================

#define CN105_RX_PIN 4      // ESP RX  <- TX clim
#define CN105_TX_PIN 5      // ESP TX  -> RX clim

#define LED_PIN      8
#define BUTTON_PIN   9


// ======================================================
// Timers
// ======================================================

#define HEARTBEAT_PERIOD_MS      1000
#define STATUS_PRINT_PERIOD_MS   5000

#endif