#include <Arduino.h>
#include <TeensyThreads.h>

#define LED_RED 51
#define LED_RED_FLASH_MS 400

#define LED_WHITE 52
#define LED_WHITE_FLASH_MS 500

#define LED_BLUE 53
#define LED_BLUE_FLASH_MS 600

void blinkLedRed() {
  while(1) {
    digitalWrite(LED_RED, HIGH);
    threads.delay(LED_RED_FLASH_MS);
    digitalWrite(LED_RED, LOW);
    threads.delay(LED_RED_FLASH_MS);
    threads.yield();
  }
}

void blinkLedWhite() {
  while(1) {
    digitalWrite(LED_WHITE, HIGH);
    threads.delay(LED_WHITE_FLASH_MS);
    digitalWrite(LED_WHITE, LOW);
    threads.delay(LED_WHITE_FLASH_MS);
    threads.yield();
  }
}

void blinkLedBlue() {
  while(1) {
    digitalWrite(LED_BLUE, HIGH);
    threads.delay(LED_BLUE_FLASH_MS);
    digitalWrite(LED_BLUE, LOW);
    threads.delay(LED_BLUE_FLASH_MS);
    threads.yield();
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  threads.addThread(blinkLedRed);
  threads.addThread(blinkLedWhite);
  threads.addThread(blinkLedBlue);
}

void loop() {
  // put your main code here, to run repeatedly:
}
