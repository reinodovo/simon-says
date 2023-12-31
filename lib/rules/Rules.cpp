#include <algorithm>
#include <random>
#include <rules.h>

std::mt19937 rng;

ColorShuffle generateColorShuffle() {
  ColorShuffle cs;
  for (int i = 0; i < COLORS; i++)
    cs.push_back((Colors)i);
  for (int i = cs.size() - 1; i >= 0; i--) {
    int j = rng() % (i + 1);
    std::swap(cs[i], cs[j]);
  }
  return cs;
}

Rules generateRules(int seed) {
  rng = std::mt19937(seed);
  Rules rules;
  for (int i = 0; i < STRIKE_SECTIONS; i++)
    rules.evenSolvedModules.push_back(generateColorShuffle());
  for (int i = 0; i < STRIKE_SECTIONS; i++)
    rules.oddSolvedModules.push_back(generateColorShuffle());
  return rules;
}