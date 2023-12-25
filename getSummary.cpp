#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to get the summary from a file
void getSummary() {

    int ticketNumbers[] = { 0,0,0,0,0,0,0,0 };
    int ticketTotals[] = { 0,0,0,0,0,0,0,0 };

    char filename[20], date[10], string[164] ;
    int sum = 0;

    int sno, ticketnumber, tickethourtype, tickettotal,hourtype;
    char tickettype[30];

    printf("\n\nEnter date booking was made for (DDMMYYYY) to get summary:\n");
    getchar();
    gets_s(date, 10);

    snprintf(filename, 20, "%s.txt", date);

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }


    while (fgets(string, sizeof(string), file)) {
        if (isdigit(string[0])==0) {
            continue;
        }
        sscanf(string, "%d %s %d %d %d", &sno, tickettype, &ticketnumber,&tickethourtype, &tickettotal);

        printf("\t");

        if (strcmp(tickettype, "Adult") == 0) {
            ticketNumbers[0] += ticketnumber;
            ticketTotals[0] += tickettotal;
        }
        else if (strcmp(tickettype, "Child") == 0) {
            ticketNumbers[1] += ticketnumber;
            ticketTotals[1] += tickettotal;
        }
        else if (strcmp(tickettype, "Senior") == 0) {
            ticketNumbers[2] += ticketnumber;
            ticketTotals[2] += tickettotal;
        }
        else if (strcmp(tickettype, "Family") == 0) {
            ticketNumbers[3] += ticketnumber;
            ticketTotals[3] += tickettotal;
        }
        else if (strcmp(tickettype, "6+_people") == 0) {
            ticketNumbers[4] += ticketnumber;
            ticketTotals[4] += tickettotal;
        }
        else if (strcmp(tickettype, "Lion_feeding") == 0) {
            ticketNumbers[5] += ticketnumber;
            ticketTotals[5] += tickettotal;
        }
        else if (strcmp(tickettype, "Peng_feeding") == 0) {
            ticketNumbers[6] += ticketnumber;
            ticketTotals[6] += tickettotal;
        }
        else if (strcmp(tickettype, "Evening_bbq") == 0) {
            ticketNumbers[7] += ticketnumber;
            ticketTotals[7] += tickettotal;
        }
        sum += tickettotal;
    }

    fclose(file);

    // Display summary
    printf("\n\n");
    printf("| Ticket Type    | Tickets Sold | Total Price |\n");
    printf("--------------------------------------------------------------------------\n");

    for (int a = 0; a < 8; a++) {
        switch (a) {
        case 0:
            printf("Adult\t\t");
            break;
        case 1:
            printf("Child\t\t");
            break;
        case 2:
            printf("Senior\t\t");
            break;
        case 3:
            printf("Family\t\t");
            break;
        case 4:
            printf("6+_people\t");
            break;
        case 5:
            printf("Lion_feeding\t");
            break;
        case 6:
            printf("Peng_feeding\t");
            break;
        case 7:
            printf("Evening_bbq\t");
            break;
        }

        printf("\t%d\t\t%d\n",ticketNumbers[a],ticketTotals[a]);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Net Total: %d\n", sum);

    
}