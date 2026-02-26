#ifndef RULES_H
#define RULES_H

#include <vector>

const int COLORS = 4;
const int STRIKE_SECTIONS = 3;
enum Colors { Red, Blue, Green, Yellow };

using ColorShuffle = std::vector<Colors>;
struct Rules {
  std::vector<ColorShuffle> even_solved_modules;
  std::vector<ColorShuffle> odd_solved_modules;
};

Rules generate_rules(int seed);

#endif  // RULES_H
