/**
 * A BLE client example to receive many characteristics.
 * There is a lot new capabilities implemented.
 * author unknown
 * updated by chegewara and MoThunderz
 */

#include "BLEDevice.h"
//#include "BLEScan.h"

// Define UUIDs:
static BLEUUID    serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
static BLEUUID    charUUID_0("4a6c23b0-de9f-4b93-bc0d-d28f552ec204");
static BLEUUID    charUUID_1("d7be7b90-2423-4d6e-926d-239bc96bb2fd");
static BLEUUID    charUUID_2("47524f89-07c8-43b6-bf06-a21c77bfdee8");
static BLEUUID    charUUID_3("f13163b4-cc7f-456b-9ea4-5c6d9cec8ee3");
static BLEUUID    charUUID_4("97f57b70-9465-4c46-a2e2-38b604f76451");
static BLEUUID    charUUID_5("81104088-d388-4fb9-84ba-427103a7b784");
static BLEUUID    charUUID_6("2daa1b8c-c744-43ef-88ba-b0170515b9e2");
static BLEUUID    charUUID_7("8a6957c1-5655-47e2-b4d0-a11dd6fa14a3");


// Some variables to keep track on device connected
static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;

// Define pointer for the BLE connection
static BLEAdvertisedDevice* myDevice;
BLERemoteCharacteristic* pRemoteChar;
BLERemoteCharacteristic* pRemoteChar_0;
BLERemoteCharacteristic* pRemoteChar_1;
BLERemoteCharacteristic* pRemoteChar_2;
BLERemoteCharacteristic* pRemoteChar_3;
BLERemoteCharacteristic* pRemoteChar_4;
BLERemoteCharacteristic* pRemoteChar_5;
BLERemoteCharacteristic* pRemoteChar_6;
BLERemoteCharacteristic* pRemoteChar_7;

volatile bool readChar_0 = false;
volatile bool readChar_1 = false;
volatile bool readChar_2 = false;
volatile bool readChar_3 = false;
volatile bool readChar_4 = false;
volatile bool readChar_5 = false;
volatile bool readChar_6 = false;
volatile bool readChar_7 = false;

// Callback function for Notify function
static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                            uint8_t* pData,
                            size_t length,
                            bool isNotify) {
  if(pBLERemoteCharacteristic->getUUID().toString() == charUUID.toString()) {

    // convert received bytes to integer
    uint32_t counter = pData[0];
    for(int i = 1; i<length; i++) {
      counter = counter | (pData[i] << i*8);
    }

    if(counter < 8) {
      switch (counter) {
        case 0:
          readChar_0 = true;
          break;
        case 1:
          readChar_1 = true;
          break;
        case 2:
          readChar_2 = true;
          break;
        case 3:
          readChar_3 = true;
          break;
        case 4:
          readChar_4 = true;
          break;
        case 5:
          readChar_5 = true;
          break;
        case 6:
          readChar_6 = true;
          break;
        case 7:
          readChar_7 = true;
          break;
      }
    }

    // print to Serial
    if(0) {                                                           // For this example I disabled the printing of the notify function so that you easily see in the console that all characteristics are read correctly
      Serial.print("readChar: ");
      Serial.println(counter );  
    }
  }
}

// Callback function that is called whenever a client is connected or disconnected
class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

// Function that is run whenever the server is connected
bool connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());
  
  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");
  Serial.println(pClient->setMTU(517)); 

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  connected = true;
  pRemoteChar = pRemoteService->getCharacteristic(charUUID);
  pRemoteChar_0 = pRemoteService->getCharacteristic(charUUID_0);
  pRemoteChar_1 = pRemoteService->getCharacteristic(charUUID_1);
  pRemoteChar_2 = pRemoteService->getCharacteristic(charUUID_2);
  pRemoteChar_3 = pRemoteService->getCharacteristic(charUUID_3);
  pRemoteChar_4 = pRemoteService->getCharacteristic(charUUID_4);
  pRemoteChar_5 = pRemoteService->getCharacteristic(charUUID_5);
  pRemoteChar_6 = pRemoteService->getCharacteristic(charUUID_6);
  pRemoteChar_7 = pRemoteService->getCharacteristic(charUUID_7);
  
  if(connectCharacteristic(pRemoteService, pRemoteChar) == false) {
    connected = false;
    Serial.println("char 0");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_0) == false) {
    connected = false;    
    Serial.println("char 0");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_1) == false) {
    connected = false;
    Serial.println("char 1");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_2) == false) {
    connected = false;
    Serial.println("char 2");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_3) == false) {
    connected = false;
    Serial.println("char 3");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_4) == false) {
    connected = false;    
    Serial.println("char 4");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_5) == false) {
    connected = false;    
    Serial.println("char 5");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_6) == false) {
    connected = false;    
    Serial.println("char 6");
  }
  else if(connectCharacteristic(pRemoteService, pRemoteChar_7) == false) {
    connected = false;    
    Serial.println("char 7");
  }

  if(connected == false) {
    pClient-> disconnect();
    Serial.println("At least one characteristic UUID not found");
    return false;
  }
  return true;
}

// Function to check Characteristic
bool connectCharacteristic(BLERemoteService* pRemoteService, BLERemoteCharacteristic* l_BLERemoteChar) {
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  if (l_BLERemoteChar == nullptr) {
    Serial.print("Failed to find one of the characteristics");
    Serial.print(l_BLERemoteChar->getUUID().toString().c_str());
    return false;
  }
  std::string rxValue = l_BLERemoteChar->readValue();
  Serial.println(" - Found characteristic: " + String(l_BLERemoteChar->getUUID().toString().c_str()) + ", with value: " + String(rxValue.c_str()));

  if(l_BLERemoteChar->canNotify())
    l_BLERemoteChar->registerForNotify(notifyCallback);
  return true;
}

// Scan for BLE servers and find the first one that advertises the service we are looking for.
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  //Called for each advertising BLE server.
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());
  
    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
  
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;
  
    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");
  // BLEDevice::setMTU(517);

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
} // End of setup.

void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    if(readChar_0 == true) {
      std::string rxValue = pRemoteChar_0->readValue();
      Serial.print("Characteristic 0 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_0 = false;
    }
    if(readChar_1 == true) {
      std::string rxValue = pRemoteChar_1->readValue();
      Serial.print("Characteristic 1 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_1 = false;
    }
    if(readChar_2 == true) {
      std::string rxValue = pRemoteChar_2->readValue();
      Serial.print("Characteristic 2 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_2 = false;
    }
    if(readChar_3 == true) {
      std::string rxValue = pRemoteChar_3->readValue();
      Serial.print("Characteristic 3 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_3 = false;
    }
    if(readChar_4 == true) {
      std::string rxValue = pRemoteChar_4->readValue();
      Serial.print("Characteristic 4 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_4 = false;
    }
    if(readChar_5 == true) {
      std::string rxValue = pRemoteChar_5->readValue();
      Serial.print("Characteristic 5 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_5 = false;
    }
    if(readChar_6 == true) {
      std::string rxValue = pRemoteChar_6->readValue();
      Serial.print("Characteristic 6 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_6 = false;
    }
    if(readChar_7 == true) {
      std::string rxValue = pRemoteChar_7->readValue();
      Serial.print("Characteristic 7 (readValue): ");
      Serial.println(rxValue.c_str());
      readChar_7 = false;
    }

  }else if(doScan){
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }
}
