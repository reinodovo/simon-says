#ifndef RULES_H
#define RULES_H

#include <vector>

const int COLORS = 4;
const int STRIKE_SECTIONS = 3;
enum Colors {
    Red, Blue, Green, Yellow
};

Colors** generate_rules(int seed);

#endif // RULES_H