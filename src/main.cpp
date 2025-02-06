#include <Arduino.h>
#include <puzzle_module.h>
#include <rules.h>
#include <sequence.h>
#include <utils/button.h>

const int RED_PIN = 22, GREEN_PIN = 23;
const int BUTTON_PINS[COLORS] = {2, 18, 17, 21};
Button buttons[COLORS];

const int MIN_SEQ = 3, MAX_SEQ = 5;

Rules rules;
std::vector<Colors> sequence;
int inputSequenceLength, inputSequenceIndex;

void generateSequence() {
  sequence.clear();
  int length = random(MIN_SEQ, MAX_SEQ + 1);
  for (int i = 0; i < length; i++)
    sequence.push_back((Colors)(random(0, COLORS)));
  inputSequenceLength = inputSequenceIndex = 0;
  Sequence::sequence = sequence;
  Sequence::size = inputSequenceLength + 1;
}

void start() {
  generateSequence();
  Sequence::enabled = true;
  Sequence::stop();
}

void restart() {
  Sequence::enabled = false;
  Sequence::clear();
}

void onManualCode(int code) { rules = generateRules(code); }

struct ButtonFunction {
  Colors color;
  ButtonFunction(Colors color) : color(color) {}
  void operator()(ButtonState newState, ButtonState _) const {
    if (newState != Pressed)
      return;
    Sequence::stop();
    Sequence::startInput();
    Sequence::show(color);
    Module::withBombInfo([this](BombInfo info) {
      Colors sequenceColor = sequence[inputSequenceIndex];
      ColorShuffle correctShuffle = info.solved_puzzle_modules % 2 == 0
                                        ? rules.evenSolvedModules[info.strikes]
                                        : rules.oddSolvedModules[info.strikes];
      Colors expected = correctShuffle[sequenceColor];
      if (expected != color) {
        PuzzleModule::strike();
        generateSequence();
        return;
      }
      inputSequenceIndex++;
      if (inputSequenceIndex <= inputSequenceLength)
        return;
      inputSequenceLength++;
      inputSequenceIndex = 0;
      Sequence::size = inputSequenceLength + 1;
      Sequence::stopInput();
      if (inputSequenceLength == sequence.size()) {
        Sequence::enabled = false;
        PuzzleModule::solve();
      }
    });
  }
};

void setup() {
  Module::onStart = start;
  Module::onRestart = restart;
  Module::onManualCode = onManualCode;

  if (!PuzzleModule::setup(
          "Simon Says", PuzzleModule::StatusLight(RED_PIN, GREEN_PIN, false)))
    ESP.restart();

  for (int i = 0; i < COLORS; i++) {
    buttons[i] = Button(BUTTON_PINS[i]);
    buttons[i].onStateChange = ButtonFunction((Colors)i);
  }

  Sequence::setup();
  Sequence::enabled = false;
}

void loop() {
  PuzzleModule::update();
  Sequence::update();
  if (Module::status() == Module::Status::Started)
    Sequence::enabled = true;
  if (Module::status() == Module::Status::Solved) {
    Sequence::enabled = false;
    return;
  }
  for (int i = 0; i < COLORS; i++)
    buttons[i].update();
}