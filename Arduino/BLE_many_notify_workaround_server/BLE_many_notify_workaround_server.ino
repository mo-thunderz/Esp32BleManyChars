/*
  Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
  Ported to Arduino ESP32 by Evandro Copercini
  updated by chegewara and MoThunderz
  BLE Tutorial part 3: using many characteristics
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic_0 = NULL;
BLECharacteristic* pCharacteristic_1 = NULL;
BLECharacteristic* pCharacteristic_2 = NULL;
BLECharacteristic* pCharacteristic_3 = NULL;
BLECharacteristic* pCharacteristic_4 = NULL;
BLECharacteristic* pCharacteristic_5 = NULL;
BLECharacteristic* pCharacteristic_6 = NULL;
BLECharacteristic* pCharacteristic_7 = NULL;

BLEDescriptor *pDescr;

BLE2902 *pBLE2902;

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID_0 "4a6c23b0-de9f-4b93-bc0d-d28f552ec204"
#define CHARACTERISTIC_UUID_1 "d7be7b90-2423-4d6e-926d-239bc96bb2fd"
#define CHARACTERISTIC_UUID_2 "47524f89-07c8-43b6-bf06-a21c77bfdee8"
#define CHARACTERISTIC_UUID_3 "f13163b4-cc7f-456b-9ea4-5c6d9cec8ee3"
#define CHARACTERISTIC_UUID_4 "97f57b70-9465-4c46-a2e2-38b604f76451"
#define CHARACTERISTIC_UUID_5 "81104088-d388-4fb9-84ba-427103a7b784"
#define CHARACTERISTIC_UUID_6 "2daa1b8c-c744-43ef-88ba-b0170515b9e2"
#define CHARACTERISTIC_UUID_7 "8a6957c1-5655-47e2-b4d0-a11dd6fa14a3"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID), 256, 0);  // the 30 in this line defines the number of chars to be used, increase as needed

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY 
                      );   
  pCharacteristic_0 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_0,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );                       
  pCharacteristic_1 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_1,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );    
  pCharacteristic_2 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_2,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );    
  pCharacteristic_3 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_3,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );    
  pCharacteristic_4 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_4,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );                                            
  pCharacteristic_5 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_5,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );    
  pCharacteristic_6 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_6,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );    
  pCharacteristic_7 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_7,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE 
                      );      
  // Create a BLE Descriptor
  
  pDescr = new BLEDescriptor((uint16_t)0x2901);
  pDescr->setValue("Callback indicator");
  pCharacteristic->addDescriptor(pDescr);
  
  pBLE2902 = new BLE2902();
  pBLE2902->setNotifications(true);
  pCharacteristic->addDescriptor(pBLE2902);

  pCharacteristic_0->addDescriptor(new BLE2902());
  pCharacteristic_1->addDescriptor(new BLE2902());
  pCharacteristic_2->addDescriptor(new BLE2902());
  pCharacteristic_3->addDescriptor(new BLE2902());
  pCharacteristic_4->addDescriptor(new BLE2902());
  pCharacteristic_5->addDescriptor(new BLE2902());
  pCharacteristic_6->addDescriptor(new BLE2902());
  pCharacteristic_7->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
    // notify changed value
    if (deviceConnected) {
      switch (value%8) {
        case 0:
          pCharacteristic_0->setValue(value);
          break;
        case 1:
          pCharacteristic_1->setValue(value);
          break;
        case 2:
          pCharacteristic_2->setValue(value);
          break;
        case 3:
          pCharacteristic_3->setValue(value);
          break;
        case 4:
          pCharacteristic_4->setValue(value);
          break;
        case 5:
          pCharacteristic_5->setValue(value);
          break;
        case 6:
          pCharacteristic_6->setValue(value);
          break;
        case 7:
          pCharacteristic_7->setValue(value);
          break;
      }
      uint16_t tmp = value%8;
      pCharacteristic->setValue(tmp);
      pCharacteristic->notify();
      value++;
      delay(500);
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
