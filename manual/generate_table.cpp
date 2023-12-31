#include <rules.h>
#include <stdio.h>
#include <stdlib.h>

void generate_table_row(ColorShuffle rule, int strikes) {
  printf("<tr>\n");
  if (strikes == 0) {
    printf("<th rowspan=\"3\">Button&nbsp;to&nbsp;press:</th>");
    printf("<th>No&nbsp;Strikes</th>");
  } else {
    printf("<th>%d&nbsp;Strike%s</th>", strikes, strikes == 1 ? "" : "s");
  }
  for (int i = 0; i < COLORS; i++) {
    printf("<td>");
    switch (rule[i]) {
    case Red:
      printf("Red");
      break;
    case Blue:
      printf("Blue");
      break;
    case Green:
      printf("Green");
      break;
    case Yellow:
      printf("Yellow");
      break;
    }
    printf("</td>");
  }
  printf("</tr>\n");
}

int main(int argc, char **argv) {
  freopen("./manual/table.html", "w", stdout);
  int seed = atoi(argv[1]);

  Rules rules = generateRules(seed);
  printf("<p>If the number of solved modules is <em>even</em>:</p>");
  printf("<table style=\"width: 98%%; border: none; margin-left: auto; "
         "margin-right: auto; margin-bottom: 2em;\"><tbody><tr><th "
         "colspan=\"2\" class=\"no-border\"></th><th>Red Flash</th><th>Blue "
         "Flash</th><th>Green Flash</th><th>Yellow Flash</th></tr>");
  for (int i = 0; i < STRIKE_SECTIONS; i++)
    generate_table_row(rules.evenSolvedModules[i], i);
  printf("</tbody></table>\n");
  printf("<p>If the number of solved modules is <em>odd</em>:</p>");
  printf("<table style=\"width: 98%%; border: none; margin-left: auto; "
         "margin-right: auto; margin-bottom: 2em;\"><tbody><tr><th "
         "colspan=\"2\" class=\"no-border\"></th><th>Red Flash</th><th>Blue "
         "Flash</th><th>Green Flash</th><th>Yellow Flash</th></tr>");
  for (int i = 0; i < STRIKE_SECTIONS; i++)
    generate_table_row(rules.oddSolvedModules[i], i);
  printf("</tbody></table>\n");
}