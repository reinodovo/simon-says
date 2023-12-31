#include <Arduino.h>
#include <puzzle_module.h>
#include <rules.h>
#include <vector>

namespace Sequence {
const int DURATION = 200;
const int COLOR_GAP = 1000;
const int SEQUENCE_GAP = 4000;

bool last_on = false;
unsigned long sequence_start_time = 0, stop_time = 0;
std::vector<Colors> sequence;
int size = 0;
bool enabled = false;
bool isInputing = false;

const int BUZZER_PIN = 13;
const int COLOR_LED_PINS[COLORS] = {15, 5, 16, 19};
const int COLOR_FREQUENCIES[COLORS] = {329, 440, 554, 659};

void setup() {
  for (int i = 0; i < COLORS; i++) {
    pinMode(COLOR_LED_PINS[i], OUTPUT);
    digitalWrite(COLOR_LED_PINS[i], LOW);
  }
  pinMode(BUZZER_PIN, OUTPUT);
  stop_time = -1;
}

void clear() {
  noTone(BUZZER_PIN);
  for (int i = 0; i < COLORS; i++)
    digitalWrite(COLOR_LED_PINS[i], LOW);
}

void stop() {
  clear();
  sequence_start_time = millis() + SEQUENCE_GAP;
}

void startInput() { isInputing = true; }

void stopInput() { isInputing = false; }

void start() { sequence_start_time = millis(); }

void show(Colors color) {
  clear();
  if (!enabled)
    return;
  tone(BUZZER_PIN, 4 * COLOR_FREQUENCIES[color]);
  digitalWrite(COLOR_LED_PINS[color], HIGH);
  stop_time = millis() + DURATION;
}

void update() {
  if (stop_time != -1 && millis() > stop_time) {
    clear();
    stop_time = -1;
  }
  if (sequence_start_time > millis())
    return;
  if (isInputing) {
    PuzzleModule::strike();
    isInputing = false;
  }
  unsigned long time_diff = millis() - sequence_start_time;
  int index = (time_diff / (DURATION + COLOR_GAP));
  if (index >= size)
    return;
  bool on = time_diff % (DURATION + COLOR_GAP) <= DURATION;
  if (last_on == on)
    return;
  last_on = on;
  if (on)
    show(sequence[index]);
  if (index + 1 == size && !on) {
    stop();
    return;
  }
}
}; // namespace Sequence