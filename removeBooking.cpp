#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void removeBooking() {
    FILE* fptr, * fptr2;
    int bookingNo;
    char date[10] = "", filename[32], bookingNoString[20] = "", input[1024];

    printf("\n\nEnter the booking number to delete:\n");
    scanf("%d", &bookingNo);

    printf("\n\nEnter the date booking was made for:\n");
    getchar();
    gets_s(date, 9);

    snprintf(filename, sizeof(filename), "%s.txt", date);

    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("\n\nError opening file %s. Either the file does not exist or there was an issue.\n", filename);
        return;
    }

    fptr2 = fopen("temp.txt", "w");
    if (fptr2 == NULL) {
        printf("\n\nError opening file for writing. Either the file does not exist or there was an issue.\n");
        fclose(fptr);
        return;
    }

    // Flag to indicate whether the current line is part of the booking to be removed
    int isInBooking = 0;

    while (fgets(input, sizeof(input), fptr)) {
        // Check the length of the line before accessing its characters
        if (strlen(input) >= 21 && input[21] == '\n') {
            for (int i = 12, j = 0; i < 21; i++, j++) {
                bookingNoString[j] = input[i];
            }

            if (atoi(bookingNoString) == bookingNo) {
                // If this line contains the booking number, set the flag
                isInBooking = 1;
            }
        }


        if (!isInBooking) {
            // If not in the booking to be removed, write the line to the temporary file
            fputs(input, fptr2);
        }

        // Check for the end of the booking (empty line)
        if (input[0] == '\n') {
            // Reset the flag when the end of the booking is reached
            isInBooking = 0;
        }
    }

    fclose(fptr);
    fclose(fptr2);

    remove(filename);
    rename("temp.txt", filename);

    printf("\n\nBooking %d has been removed successfully.\n", bookingNo);
}
