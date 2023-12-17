#pragma warning (disable:4996)


#include <stdio.h>
#include <cstring>
#include <ctype.h>

void Validator(int* valPtr, int lower, int upper);

int ticketCounter[8];

//It will take inputs
void InputTickets(int i, int* ticketTypePtr, int* ticketNumberPtr, char* dayNightPtr) {

	printf("Enter the number of the type of ticket you wish to book:  ");
	scanf("%d", ticketTypePtr + i);
	Validator(ticketTypePtr + i,1,8);

	printf("Enter the quantity of tickets you wish to book.You can book 50 at one time or 10 family tickets at one time.");
	scanf("%d", ticketNumberPtr + i);

	for (int a = 0; a <= 8; a++) {
		ticketCounter[a] = 0;
	}

	if (*(ticketTypePtr + i) == 5) {
		Validator(ticketNumberPtr + i, 6, 50);
	}
	else if (*(ticketTypePtr + i) == 4) {
		Validator(ticketNumberPtr + i, 1, 10);
	}
	else {
		Validator(ticketNumberPtr + i, 1, 50);
	}

	*(ticketCounter + *(ticketTypePtr + i) - 1) += *(ticketNumberPtr + i);

	if (*(ticketTypePtr+i) > 0 && *(ticketTypePtr + i) < 6) {
		int hourType;
		printf("Enter type of ticket\n1 for 12 hour\n2 for 24 hour\n  ");
		scanf("%d", &hourType);
		Validator(&hourType, 1, 2);
		if (hourType == 1) {
			*(dayNightPtr + i) = 'D';

		}
		else{
			*(dayNightPtr + i) = 'N';
		}

	}
	else {
		*(dayNightPtr + i) = '-';
	}


}

//It will evaluate the total cost of each item
void CalculateTotal(int i, int ticketTypes[], int ticketNumbers[], int ticketPrice[8][2], int* TotalPtr, char dayNight[]) {

	int j=0;

	if (ticketTypes[i] > 0 && ticketTypes[i] < 6) {
		if (dayNight[i] == 'D') {
			j = 0;
		}
		else {
			j = 1;
		}
	}

	*(TotalPtr + i) = ticketPrice[ticketTypes[i] - 1][j] * ticketNumbers[i];

}

//It will display the bpoking done
void DisplayBooking(int length, int ticketTypes[], int ticketNumbers[],char dayNight[], int ticketTotals[],int BookinNo) {
	int sum = 0;
	printf("Booking Number:  %d\n",BookinNo);
	printf("Sno.\tTicket Type\tNumber\tDay/Night\tTotal\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < length; i++) {

		printf("%d.\t", i + 1);
		switch (ticketTypes[i]) {
		case 1:
			printf("Adult\t");
			break;
		case 2:
			printf("Child\t");
			break;
		case 3:
			printf("Senior\t");
			break;
		case 4:
			printf("Family\t");
			break;
		case 5:
			printf("6+ people");
			break;
		case 6:
			printf("Lion feeding ");
			break;
		case 7:
			printf("Peng feeding");
			break;
		case 8:
			printf("Evening bbq ");
			break;
		}



		printf("\t%d\t%c\t\t%d\n", ticketNumbers[i],dayNight[i], ticketTotals[i]);

		sum += ticketTotals[i];








	}

	printf("\t\t\t\t\t\t%d", sum);
}

//It will show if there are any better options
void EnsureBestBooking(int length, int ticketTypes[], int ticketNumbers[]) {
	
	int totalIndividualTickets = 0;
		for (int i = 0; i < 8; i++) {
			totalIndividualTickets += ticketCounter[i];
	}

	if(totalIndividualTickets >= 6){
		printf("You can buy type 5 ticket and avail 6+ people discount\n");
	}
	if ((ticketCounter[0] >= 2 || ticketCounter[2] >= 2) && (ticketCounter[1] >= 3)) {
		printf("You can buy type 4 family ticket and get better value.\n");
	}
}

//It will take input the tickets and extra attractions required and the calculate the total cost. It will also allocate a booking number. After taking the input it will ask for confirmation by displaying booking number and booking details. 
void bookTickets(int BookingNumber) {

	int ticketPrice[8][2] = {
		{2000,3000},
		{1000,2000},
		{1500,2500},
		{6000,9000},
		{1000,2000},
		{250,0},
		{200,0},
		{500,0}
	};

	int ticketTypes[50];
	int ticketNumbers[50];
	char dayNight[50];
	int ticketTotals[50];

	int confirm = 0;
	while ( confirm ==0) {
		int i = 0;
		char choice = 'y';
		while (choice == 'y') {

			printf("\n\nInput your main tickets from serial number 1 to 5\n  ");
			InputTickets(i, ticketTypes, ticketNumbers, dayNight);
			CalculateTotal(i, ticketTypes, ticketNumbers, ticketPrice, ticketTotals, dayNight);

			i++;

			printf("Do you want to add more things to the cart?Enter y to do so.");
			scanf(" %c", &choice);

			choice = tolower(choice);


		}

		printf("Do you want to add additional activities.Enter y to do so.");
		scanf(" %c", &choice);
		choice = tolower(choice);

		while (choice == 'y') {

			printf("Input your additional tickets from serial number 6 to 8\n");
			InputTickets(i, ticketTypes, ticketNumbers, dayNight);
			CalculateTotal(i, ticketTypes, ticketNumbers, ticketPrice, ticketTotals, dayNight);

			i++;

			printf("Do you want to add more additional activities to the cart? Enter y to do so. ");
			scanf(" %c", &choice);

			choice = tolower(choice);

		}

		printf("\n-------------------------------------------------------------------------------------------\n");
		printf("\nYour booking summary.\n\n");
		DisplayBooking(i, ticketTypes, ticketNumbers, dayNight, ticketTotals, BookingNumber);
		printf("\n\n");
		EnsureBestBooking(i, ticketTypes, ticketNumbers);

		printf("\n\nDo you confirm your booking.\nPress 1 to proceed. Press 0 to make different booking. ");
		scanf("%d", &confirm);
		Validator(&confirm, 0, 1);

	}
	printf("\nYour ticket has been booked successfully.Thank you for your patience.");


}

