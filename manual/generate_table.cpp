#include <stdio.h>
#include <stdlib.h>
#include <Rules.h>

void generate_table_row(Colors* rule, int strikes) {
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

int main(int argc, char** argv) {
    freopen("./manual/table.html", "w", stdout);
    int seed = atoi(argv[1]);

    Colors** rules = generate_rules(seed);
    for (int i = 0; i < STRIKE_SECTIONS; i++) {
        generate_table_row(rules[i], i);
    }
}