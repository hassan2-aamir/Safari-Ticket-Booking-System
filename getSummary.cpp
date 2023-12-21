#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a booking entry
struct BookingEntry {
    int bookingNumber;
    int* ticketTypes;
    int* ticketNumbers;
    char* dayNight;
    int* ticketTotals;
    int length;
};

// Function to dynamically allocate memory for a BookingEntry
void initializeBookingEntry(struct BookingEntry* entry, int length) {
    entry->ticketTypes = (int*)malloc(length * sizeof(int));
    entry->ticketNumbers = (int*)malloc(length * sizeof(int));
    entry->dayNight = (char*)malloc(length * sizeof(char));
    entry->ticketTotals = (int*)malloc(length * sizeof(int));
    entry->length = length;
}

// Function to release dynamically allocated memory for a BookingEntry
void freeBookingEntry(struct BookingEntry* entry) {
    free(entry->ticketTypes);
    free(entry->ticketNumbers);
    free(entry->dayNight);
    free(entry->ticketTotals);
}

// Function to get the summary from a file
void getSummary() {
    char filename[20], date[10];

    printf("\n\nEnter date booking was made for (DDMMYYYY) to get summary:\n");
    getchar();
    gets_s(date, 10);

    snprintf(filename, 20, "%s.txt", date);

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    int maxEntries = 50; // Assuming a maximum of 50 booking entries per day
    int currentEntries = 0;

    struct BookingEntry* entries = (struct BookingEntry*)malloc(maxEntries * sizeof(struct BookingEntry));

    while (fscanf(file, "Booking Number: %d", &entries[currentEntries].bookingNumber) == 1) {
        int i = 0;

        while (fscanf(file, "%d %c %d", &entries[currentEntries].ticketTypes[i],
            &entries[currentEntries].dayNight[i], &entries[currentEntries].ticketTotals[i]) == 3) {
            i++;
        }

        entries[currentEntries].length = i;

        // Dynamically allocate memory for the entry
        initializeBookingEntry(&entries[currentEntries], i);

        // Read the next line to prepare for the next booking entry
        fgetc(file); // consume newline
        fgetc(file); // consume newline

        currentEntries++;

        // Resize the array if necessary
        if (currentEntries == maxEntries) {
            maxEntries *= 2;
            entries = (struct BookingEntry*)realloc(entries, maxEntries * sizeof(struct BookingEntry));
        }
    }

    fclose(file);

    // Display summary
    printf("--------------------------------------------------------------------------\n");
    printf("| Ticket Type    | Tickets Sold | Total Price |\n");
    printf("--------------------------------------------------------------------------\n");

    int netTotal = 0;

    for (int i = 0; i < currentEntries; i++) {
        for (int j = 0; j < entries[i].length; j++) {
            int total = entries[i].ticketTotals[j];
            printf("| %-13d | %-12d | %-11d |\n", entries[i].ticketTypes[j], entries[i].ticketNumbers[j], total);
            netTotal += total;
        }
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Net Total: %-18d %-11d\n", netTotal, netTotal);

    // Free dynamically allocated memory
    for (int i = 0; i < currentEntries; i++) {
        freeBookingEntry(&entries[i]);
    }

    free(entries);
}