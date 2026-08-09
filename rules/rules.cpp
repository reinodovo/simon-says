#include <rules.h>

#include <algorithm>
#include <random>

std::mt19937 rng;

ColorShuffle generate_color_shuffle() {
  ColorShuffle cs;
  for (int i = 0; i < COLORS; i++) cs.push_back((Colors)i);
  for (int i = cs.size() - 1; i >= 0; i--) {
    int j = rng() % (i + 1);
    std::swap(cs[i], cs[j]);
  }
  return cs;
}

Rules generate_rules(int seed) {
  rng = std::mt19937(seed);
  Rules rules;
  for (int i = 0; i < STRIKE_SECTIONS; i++) rules.even_solved_modules.push_back(generate_color_shuffle());
  for (int i = 0; i < STRIKE_SECTIONS; i++) rules.odd_solved_modules.push_back(generate_color_shuffle());
  return rules;
}
