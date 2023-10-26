#include <Rules.h>
#include <random>
#include <algorithm>

std::mt19937 rng;

Colors* generate_strike_rule() {
    Colors* rule = new Colors[COLORS];
    for (int i = 0; i < COLORS; i++)
        rule[i] = (Colors)i;
    std::shuffle(rule, rule + COLORS, rng);
    return rule;
}

Colors** generate_rules(int seed) {
    rng = std::mt19937(seed);
    Colors** rules = new Colors*[STRIKE_SECTIONS];
    for (int i = 0; i < STRIKE_SECTIONS; i++)
        rules[i] = generate_strike_rule();
    return rules;
}