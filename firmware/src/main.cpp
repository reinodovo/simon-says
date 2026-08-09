#include <Arduino.h>
#include <modules/puzzle_module.h>
#include <rules.h>
#include <sequence.h>
#include <utils/button.h>

const int RED_PIN = 22, GREEN_PIN = 23;
PuzzleModule module(StatusLight(RED_PIN, GREEN_PIN, StatusLightType::CommonCathode));

const int BUTTON_PINS[COLORS] = {2, 18, 17, 21};
Button buttons[COLORS];

const int MIN_SEQ = 3, MAX_SEQ = 5;

Rules rules;
std::vector<Colors> sequence;
int input_sequence_length, input_sequence_index;

void generate_sequence() {
  sequence.clear();
  int length = random(MIN_SEQ, MAX_SEQ + 1);
  for (int i = 0; i < length; i++) sequence.push_back((Colors)(random(0, COLORS)));
  input_sequence_length = input_sequence_index = 0;
  Sequence::sequence = sequence;
  Sequence::size = input_sequence_length + 1;
}

void start() {
  generate_sequence();
  Sequence::enabled = true;
  Sequence::restart_timer();
}

void restart() {
  Sequence::enabled = false;
  Sequence::clear();
}

void on_manual_code(int code) { rules = generate_rules(code); }

struct ButtonFunction {
  Colors color;
  ButtonFunction(Colors color) : color(color) {}
  void operator()(ButtonState new_state, ButtonState _) const {
    if (new_state != Pressed) return;
    Sequence::restart_timer();
    Sequence::start_input();
    Sequence::show(color);
    module.with_bomb_info([this](const BombInfo& info) {
      Colors sequence_color = sequence[input_sequence_index];
      ColorShuffle correct_shuffle = info.solved_puzzle_modules % 2 == 0 ? rules.even_solved_modules[info.strikes]
                                                                         : rules.odd_solved_modules[info.strikes];
      Colors expected = correct_shuffle[sequence_color];
      if (expected != color) {
        module.strike();
        Sequence::stop_input();
        generate_sequence();
        return;
      }
      input_sequence_index++;
      if (input_sequence_index <= input_sequence_length) return;
      input_sequence_length++;
      input_sequence_index = 0;
      Sequence::size = input_sequence_length + 1;
      Sequence::stop_input();
      if (input_sequence_length == sequence.size()) {
        Sequence::enabled = false;
        module.solve();
      }
    });
  }
};

void setup() {
  module.on_start(start);
  module.on_reset(restart);
  module.on_manual_code(on_manual_code);

  if (!module.setup()) ESP.restart();

  for (int i = 0; i < COLORS; i++) {
    buttons[i] = Button(BUTTON_PINS[i]);
    buttons[i].on_state_change(ButtonFunction((Colors)i));
  }

  Sequence::setup([]() {
    module.strike();
  });
  Sequence::enabled = false;
}

void loop() {
  module.update();
  Sequence::update();
  if (module.get_state() == PuzzleModuleState::Started) Sequence::enabled = true;
  if (module.get_state() == PuzzleModuleState::Solved) {
    Sequence::enabled = false;
    return;
  }
  for (int i = 0; i < COLORS; i++) buttons[i].update();
}