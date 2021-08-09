#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CNS, CE

uint8_t address_right[6] = "00001"; // address of right NRF24

/**
 * Setup the NRF24 radio module by
 * initializing power amplifier level, opening reading pipe
 * and starting listening
 */
void setup_NRF24() {
  radio.begin();
  radio.openReadingPipe(0, address_right);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void setup() {
  Serial.begin(9600);

  // Setup NRF24
  setup_NRF24();
}

void loop() {
  if(radio.available()) {
    int values[32] = "";
    radio.read(&values, sizeof(values));
    Serial.println(text);
  }
}
