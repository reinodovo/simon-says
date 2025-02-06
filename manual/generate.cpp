#include <manual.h>
#include <rules.h>

const std::string color_names[4] = {"Red", "Blue", "Green", "Yellow"};

manual::json populateJson(std::string type,
                          std::vector<ColorShuffle> &shuffle) {
  manual::json data;
  data["type"] = type;
  data["rows"] = manual::json::array();
  for (int i = 0; i < STRIKE_SECTIONS; i++) {
    manual::json colors = manual::json::array();
    for (int j = 0; j < COLORS; j++) {
      colors.push_back(color_names[shuffle[i][j]]);
    }
    data["rows"].push_back(colors);
  }
  return data;
}

int main(int argc, char **argv) {
  int code = atoi(argv[1]);
  Rules rules = generateRules(code);

  manual::json data =
      manual::init("Simon Says", "Simon Says",
                   "This is like one of those toys you played with as a kid "
                   "where you have to match the"
                   "pattern that appears, except this one is a knockoff that "
                   "was probably purchased at a dollar store.",
                   APP_VERSION);

  data["sections"] = manual::json::array();
  data["sections"].push_back(populateJson("even", rules.evenSolvedModules));
  data["sections"].push_back(populateJson("odd", rules.oddSolvedModules));

  manual::save(data, code);
}