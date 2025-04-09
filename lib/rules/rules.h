#ifndef RULES_H
#define RULES_H

#include <vector>

const int COLORS = 4;
const int STRIKE_SECTIONS = 3;
enum Colors { Red, Blue, Green, Yellow };

using ColorShuffle = std::vector<Colors>;
struct Rules {
  std::vector<ColorShuffle> evenSolvedModules;
  std::vector<ColorShuffle> oddSolvedModules;
};

Rules generateRules(int seed);

#endif // RULES_H
