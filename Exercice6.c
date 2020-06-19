#include "Particle.h"

SYSTEM_THREAD(ENABLED);

int output = D8;
int input = D6;

unsigned long lastImpulsion = 0;
unsigned long lastImpulsionTime = 0;

void setup() {
    pinMode(input, INPUT);
    pinMode(output, OUTPUT);

	Serial.begin(9600);
    analogWrite(output, 127, 50);
    delay(10);
    attachInterrupt(input, onImpulsionHigh, RISING);
}

void onImpulsionHigh()
{
    lastImpulsionTime = millis() - lastImpulsion;
    WITH_LOCK(Serial) {
        Serial.printlnf("Period=%d", lastImpulsionTime);
    }
    lastImpulsion = millis();
}
