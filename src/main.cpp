#include <Arduino.h>
#include <PuzzleModule.h>

const int redPin = 22, greenPin = 23;
const int COLORS = 4;
const int COLOR_LED_PINS[COLORS] = {5, 19, 16, 15};

void onSeed(int seed)
{
}

void setup()
{
  for (int i = 0; i < COLORS; i++)
  {
    pinMode(COLOR_LED_PINS[i], OUTPUT);
    digitalWrite(COLOR_LED_PINS[i], LOW);
  }

  PuzzleModule::StatusLight statusLight;
  statusLight.init(redPin, greenPin);

  if (!PuzzleModule::init(statusLight, onSeed))
    ESP.restart();
}

void loop()
{
  for (int i = 0; i < COLORS; i++)
  {
    digitalWrite(COLOR_LED_PINS[i], HIGH);
    delay(200);
    digitalWrite(COLOR_LED_PINS[i], LOW);
    delay(200);
  }
}