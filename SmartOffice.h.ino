
#include <IRremote.h>
#include <dht.h>
#include <IRsend.h>
#include "esp_camera.h"
#include "Arduino.h"
// model we already trained and converted to tensorflow lite then into arduino header
#include "model.h"
#define dht_apin A0 // Analog Pin sensor is connected to
  // An IR Receiver is connected to GPIO pin D4
// e.g. D4 on an ESP32 board.
const uint16_t RecvPin = D4;
const uint32_t BaudRate = 115200;
const uint16_t CaptureBufferSize = 1024;


//In this starter code we will be testing two value of Sumsung  Air conditioner encoder : powerOn and cool mode , if validated we add all others 
uint16_t powerOn[] = {9058, 4438,  512, 1728,  512, 1726,  512, 610,  510, 608, 510, 610,510, 608,  510, 608,  510, 1728,  510, 610,  510, 1728,  510, 1728,  510, 610,  510, 608,510, 610,  510, 610,  510, 608,  510, 610,  510, 608,  510, 1728,  512, 608,  510, 610,  510, 608,  510, 610,  510, 610,  510, 610,  510, 1730,  510, 610,  510, 610,  510, 608,  510, 610, 608,  510, 608,  510, 610,  510, 608,  510, 608,  510, 608,  510, 608,  510, 608,  510, 608,510, 610,  510, 608,  510, 608,  510, 610,  510, 608,  510, 608,  510, 608,  510, 608,  510, 610,  510};
 
uint16_t ModeCool[] = {9050, 4356, 510, 610,510, 608,  510, 608,  510, 1728,  510, 610,  510, 1728,  510, 1728,  510, 610,  510, 608,510, 610,  510, 610,  510, 608,  510, 610,  510, 608,  510, 1728,  512, 608,  510, 610,  510, 608,  510, 610,  510, 610,  510, 610,  510, 1730,  510, 610,  510, 610,  510, 608,  510, 610, , 608,  510, 608,  510, 610,  510, 608,  510, 608,  510, 608,  510, 608,  510, 608,  510, 608,510, 610,  510, 608,  510, 608,  510, 610,  510, 608,  510, 608,  510, 608,  510, 608,  510, 610,  510, 608,  510, 610,  510, 610, 610,  510, 608};
uint8_t samsungState[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};

//Pins for IR sender :
const uint16_t IrPin = D4; // ESP32 GPIO pin to use. Recommended: (D4).
IRsend irsend(IrPin);  // Set the GPIO to be used to sending the message.

dht DHT;

int RECV_PIN = 15;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  //we need to set up the pinMode : It's more convenient to let them till testing phase to set them correctely
   

 irsend.begin()
  // define our setup function where the braudrate is initialized to communicate with the receiver in AC
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  
  Serial.begin(115200, SERIAL_8N1);
#endif  
  Serial.begin(115200);
  irrecv.enableIRIn();
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
}

void loop() {


   //Read Temperature Value :
   int readData = DHT.read11(dataPin);
   temp = DHT.temperature;
   Serial.println(temp);
 
  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  
  // Read IR input Value :
    
  if (irrecv.decode(&results)) {
    if(results.value == powerOn && temp > 26 ){
       fb = esp_camera_fb_get();  
       if(model.true) {)
            irsend.sendRaw(powerOn, sizeof(powerOn) / sizeof(powerOn[0]), 38);  // Send a raw data capture at 38kHz.
            irsend.sendRaw(ModeCool, sizeof(ModeCool) / sizeof(ModeCool[0]), 38);
            delay(2000);
            irsend.sendSamsungAC(samsungState);
      }
        
    irrecv.resume(); // Receive the next value
  }








}
