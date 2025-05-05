#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // Durée du scan en secondes
BLEScan *pBLEScan;

// Classe pour gérer les callbacks lors de la découverte d'appareils
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        Serial.printf("Appareil trouvé: %s \n", advertisedDevice.toString().c_str());

        // Afficher l'adresse MAC
        Serial.print("Adresse MAC: ");
        Serial.println(advertisedDevice.getAddress().toString().c_str());

        // Afficher le RSSI (force du signal)
        Serial.print("RSSI: ");
        Serial.println(advertisedDevice.getRSSI());

        // Si le nom est disponible, l'afficher
        if (advertisedDevice.haveName())
        {
            Serial.print("Nom: ");
            Serial.println(advertisedDevice.getName().c_str());
        }

        Serial.println("---------------");
    }
};

void setup()
{
    Serial.begin(BAUD_RATE);
    Serial.println("Démarrage du scanner BLE...");

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); // Créer un nouveau scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); // Scan actif consomme plus mais donne plus d'informations
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99); // Moins que l'intervalle pour économiser l'énergie
}

void loop()
{
    Serial.println("Début du scan...");
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    Serial.print("Appareils trouvés: ");
    Serial.println(foundDevices.getCount());
    Serial.println("Scan terminé!");
    pBLEScan->clearResults(); // Libérer la mémoire
    delay(2000);              // Attendre 2 secondes avant le prochain scan
}