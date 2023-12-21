#pragma warning(disable:4996) // Disable the safety warning for using certain functions

#include <stdio.h>

// Procedure to display the menu information in a table
void displayMenu() {
    printf(" --------------------------------------------------------------------------\n");
    printf("| Serial | Ticket Type          | 12-hour/Normal(Rs) | 24-hour(Rs)        |\n");
    printf(" --------------------------------------------------------------------------\n");
    printf("|   1    | One adult            |        2000        |        3000        |\n");
    printf("|   2    | One child            |        1000        |        2000        |\n");
    printf("|   3    | One senior           |        1500        |        2500        |\n");
    printf("|   4    | Family ticket        |        6000        |        9000        |\n");
    printf("|   5    | 6+ people            |        1000        |        2000        |\n");
    printf("|   6    | Lion feeding         |         250        |           0        |\n");
    printf("|   7    | Penguin feeding      |         200        |           0        |\n");
    printf("|   8    | Evening bbq          |         500        |           0        |\n");
    printf(" --------------------------------------------------------------------------\n");
}


