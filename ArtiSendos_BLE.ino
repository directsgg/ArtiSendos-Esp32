#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// SECCION BLE 
BLEServer *pServer = NULL;

BLECharacteristic *box_characteristic = NULL;

String boxValue = "0";

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define BOX_CHARACTERISTIC_UUID "f27b53ad-c63d-49a0-8c0f-9f297e6cc520"

// definiciones para pwm
const int canalPwm = 0;
const int resolucion = 8;
const int frecuencia = 5000;
// pines donde se conectan los motores.
// Cambiar los pines si es necesario, de acuerdo segun el movimiento del robot
const int pins[] = {32, 33, 26, 25};

// velocidades de los motores
int velMIzqDel = 0, // velocidad motor izquierdo delantero
    velMIzqTra = 0, // velocidad motor izquierdo trasero
    velMDerDel = 0, // velocidad motor derecho delantero
    velMDerTra = 0; // velocidad motor derecho trrasero

// callbacks para la conexion o desconexion del bluetooth
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    Serial.println("BLE Conectado");
  };

  void onDisconnect(BLEServer *pServer) {
    Serial.println("BLE Desconectado");
    // reinicio del esp32 para redefinir 
    //las caracteristicas como al principio
    ESP.restart();
  };
};

// callback definicion de la caracteristica onWrite de BLE
class CharacteristicsCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    Serial.print("valor escrito: ");
    Serial.println(pCharacteristic->getValue().c_str());

    const String valueCharacteristic = pCharacteristic->getValue().c_str();
  
    // segun el caracter recibido, se mueven los distintos motores
    if (valueCharacteristic == "a") {
      velMIzqDel = 255;
      velMIzqTra = 0;
      velMDerDel = 255;
      velMDerTra = 0;

    } else if (valueCharacteristic == "r") {
      velMIzqDel = 0;
      velMIzqTra = 255;
      velMDerDel = 0;
      velMDerTra = 255;
      
    } else if (valueCharacteristic == "i") {
      velMIzqDel = 0;
      velMIzqTra = 255;
      velMDerDel = 255;
      velMDerTra = 0;
      
    } else if (valueCharacteristic == "d") {
      velMIzqDel = 255;
      velMIzqTra = 0;
      velMDerDel = 0;
      velMDerTra = 255;
      
    } else if (valueCharacteristic == "p") {
      velMIzqDel = 0;
      velMIzqTra = 0;
      velMDerDel = 0;
      velMDerTra = 0;
      
    }

    // a cada canal se le asigna la velocidad 
    ledcWrite(0, velMIzqDel);
    ledcWrite(1, velMIzqTra);
    ledcWrite(2, velMDerDel);
    ledcWrite(3, velMDerTra);

  };
};

void setup() {
  // Inicializar canales
  // canales 0-15, resolución 1-16 bits, los límites de frecuencia dependen de la resolución
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  for (int i = 0; i < 4; i++) {
    ledcSetup(canalPwm + i, frecuencia, resolucion);
    ledcAttachPin(pins[i], canalPwm + i);
  }


  Serial.begin(115200);
  Serial.println("Inicializando BLE");
  
  // Crear el dispositivo BLE
  // Aqui se cambia el nombre del dispositivo
  BLEDevice::init("Artisendos");

  // Crear el servidor BLE
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Creando el servicio BLE segun UUID
  BLEService *pService = pServer->createService(SERVICE_UUID);
  delay(1000);

  // crear una característica BLE

  box_characteristic = pService->createCharacteristic(
    BOX_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY|
    BLECharacteristic::PROPERTY_INDICATE
  );  

  // Iniciar el servicio BLE
  pService->start();

  // Empezar advertising
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();


  box_characteristic->setValue("0");
  box_characteristic->setCallbacks(new CharacteristicsCallbacks());
  
  Serial.println("¡Característica definida! ¡Ahora puedes leerla en tu teléfono!");
}

void loop() {
 
}
