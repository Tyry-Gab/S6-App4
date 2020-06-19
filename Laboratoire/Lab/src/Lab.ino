#include "Particle.h"

SYSTEM_THREAD(ENABLED);

void threadFunction(void *param);

//Thread thread("testThread", threadFunction);

volatile uint_fast64_t g_TickCount = 0;

Timer timer(1, interruptTimer);


void setup() {
	Serial.begin(9600);
  pinMode(D2, OUTPUT);
  timer.start();
}

void loop() {
	//generateSignal(2, 0.1, D2);
}

void interruptTimer() {
  g_TickCount++;
  generateSignal(10, 0.1, D2);
}

void generateSignal(int period_ms, float dutyCyle, uint8_t outputPin) {
  int current_tick = g_TickCount % period_ms;
  if(current_tick <= (int)(dutyCyle*period_ms)) {
    pinResetFast(outputPin);
  }
  else {
    pinSetFast(outputPin);
  }
}
