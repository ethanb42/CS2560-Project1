/*
 * theater.c
 *
 *  Created on: Feb 17, 2019
 *      Author: Ethan Balderas
 *
 */

#include <stdio.h>
//declaring variables
double seatPrices[15];       //an array to hold the seat prices per row
char theater[15][30];        //an array to represent the theater
double ticketSalesTotal =0;     //total sales from all tickets
int soldSeats =0;              //number of seats sold
int row;
int column;
int columnTwo;
int loop =1;
int wasValid =0;

//declare methods
int initializeTheater();
int priceInput();
int displayTheater();
int purchaseTickets();
int seatsOpenPerRow();
int seatsAvailbleAuditorium();
int displayTotalSales();
int validSeat(int r, int c);



int mainMenu(){
	//initialize theater
	initializeTheater();
	//get the price per row
	priceInput();
	//display seating chart
	displayTheater();
	//ticket purchase loop
	purchaseTickets();

	return 0;
}

//resets the theater to all empty seats
int initializeTheater(){
	for (int x=0; x<15; x++){
		for (int y=0; y<30; y++){
			theater[x][y] = '#';
		}
	}

	return 0;
}

//prints out the current theaters display
int displayTheater(){
	printf("\n                   Seats\n");
	printf("        123456789012345678901234567890");
	for (int x=0; x<15; x++){
		//aligns the chart
		if(x<9){
			printf("\nRow %d   ", x+1);
		}
		else{
			printf("\nRow %d  ", x+1);
		}

		for (int y=0; y<30; y++){
			printf("%c", theater[x][y]);
		}
	}

	return 0;
}

//takes in the price for each row and stores them in an array
int priceInput(){
	printf("Welcome to Theater Seat Manager, lets being by entering the prices for each row. \n\n");
	//for the 15 rows
	for (int x=0; x<15; x++){
		do{
			printf("Please enter the price for row %d: $", x+1);
			fflush(stdout); //ECLIPSE BUG
			scanf("%lf", &seatPrices[x]);

			if(seatPrices[x]< 0){
				printf("Whoops you entered a value less than zero, try again.\n");
			}


		} while (seatPrices[x] < 0);

	}

	return 0;

}

//lets the user select a seat to buy or a group of seats in a row.
int purchaseTickets(){



	while(loop==1){

		printf("\n\nSelect an option below....\n"
				"1. Sell an Individual Seat\n"
				"2. Sell seats next to each other in same row\n"
				"3. View total seats sold. \n"
				"4. View total seats available in each row.\n"
				"5. View total seats available in auditorium\n"
				"6. Display total sales.\n"
				"7. Exit (Warning this will delete data) \n"
				"Input: ");

		int choice;
		fflush(stdout); //ECLIPSE BUG
		scanf("%d",&choice);

		switch(choice){
		//if there are not tickets let it be known
		case 1:
			//user wants to by one seat
			do{
				printf("\nEnter Row Number: ");
				fflush(stdout);        //ECLIPSE BUG
				scanf("%d", &row);     //stores value inputed to the row
				//user input
				printf("Enter Seat Number:");
				fflush(stdout);        //ECLIPSE BUG
				scanf("%d", &column);     //stores value inputed to the row

				if(validSeat(row, column) == 0){
					printf("\nYou entered a seat that is already taken or not in range, try again");
				}
			} while (validSeat(row, column) == 0);
			//update all applicable variables and the space

			//display the cost of the ticket
			printf("The ticket price is $%0.2f \n", seatPrices[row-1]);

			printf("To complete transaction press 'y' \nTo cancel and return to menu press any key...\n\n");

			//clears the scan
			while ((getchar()) != '\n');
			fflush(stdout);  //ECLIPSE bug
			char response = getchar();

			if (response == 'Y' || response == 'y'){
				//continue
				//ask to complete transaction
				soldSeats++;                                //a seat was sold
				ticketSalesTotal += seatPrices[row-1];        //the seat price in the row was added to total cost
				theater[row-1][column-1] = '*';
				//display seating chart
				displayTheater();
			}
			else{
				//the ticket was not purchases go back to menu
				printf("Returning to menu......\n\n");
				//display seating chart
				displayTheater();

			}



			break;
		case 2:
			wasValid=1;
			while (wasValid !=0){

				//user wants to buy a group of seats in a row
				printf("Enter Row Number: ");
				//user input
				fflush(stdout);        //ECLIPSE BUG
				scanf("%d", &row);     //stores value inputed to the row

				printf("Enter Starting Seat: ");
				//user input
				fflush(stdout);        //ECLIPSE BUG
				scanf("%d", &column);     //stores value inputed to the row

				printf("Enter Ending Seat: ");
				fflush(stdout);        //ECLIPSE BUG
				scanf("%d", &columnTwo);     //stores value inputed to the row

				//use a loop to test each seat in the row
				wasValid =0;  //assume it was valid till it is not
				for (int x=column; x<=columnTwo; x++){
					if(column - columnTwo >0){
						wasValid++;
					}
					if(validSeat(row,x) == 0){
						wasValid++;  //if there is an invalid move it ticks the counter
					}
				}
				if(wasValid !=0){
					//offer to quit to menu or repeat
					printf("Seat selection was not valid! \nTo try again type 'y', to return to main menu press enter.");
					while ((getchar()) != '\n');   //clear the buffer
					fflush(stdout);  //ECLIPSE bug
					response = getchar();
					if (response == 'Y' || response == 'y'){
						//go again
					}
					else{
						wasValid =0;
					}

				}
				else{
					printf("The ticket price is $%0.2f \n", seatPrices[row-1] *(1+columnTwo-column));

					printf("To complete transaction press 'y' \nTo cancel and return to menu press any key...\n\n");

					//clears the scan
					while ((getchar()) != '\n');
					fflush(stdout);  //ECLIPSE bug
					response = getchar();

					if (response == 'Y' || response == 'y'){
						//continue
						for (int x = column; x<columnTwo+1; x++){
							soldSeats++;                                //a seat was sold
							ticketSalesTotal += seatPrices[row-1];        //the seat price in the row was added to total cost
							theater[row-1][x-1] = '*';
						}
						//display seating chart
						displayTheater();

					}
					else{
						//the ticket was not purchases go back to menu
						printf("Returning to menu......\n\n");
						wasValid =0;
						//display seating chart
						displayTheater();
					}
				}

			}

			break;

		case 3:
			printf("\nA total of %d seats have been sold!\n",soldSeats);
			break;

		case 4:
			//seats available in each row
			seatsOpenPerRow();
			break;

		case 5:
			//total available
			seatsAvailbleAuditorium();
			break;
		case 6:
			//total sales
			displayTotalSales();
			break;

		case 7:
			//ends the program
			loop =0;
			break;
		default:
			printf("Invalid input, try again!\n\n");
			break;

		}

		//check if the seats are all sold out
		if(soldSeats == 450){
			//no more seats are available
			printf("The theater is sold out!");
			loop=0;
		}

	}
	return 0;

}



//displays the number of seats available per row
int seatsOpenPerRow(){
	int temp =0;

	for (int x=0; x<15; x++){
		temp =0;
		for (int y=0; y<30; y++){
			if(theater[x][y] == '#'){
				temp++;
			}

		}

		printf("There are %d seats open in row %d.\n",temp, x);
	}



	return 0;
}

//displays total seats available
int seatsAvailbleAuditorium(){
	printf("There are a total of %d seats available. \n",  450 -soldSeats);
	return 0;
}


//displays total number of seats sold
int totalSeatsSold(){
	printf("You have sold %d seats\n",soldSeats+1);
	return 0;

}

int displayTotalSales(){

	printf("\nTotal ticket sales: $%0.2f", ticketSalesTotal);
	return 0;
}

//returns 0 if it isn't a valid seat
//returns 1 if it is a valid seat
int validSeat(int r, int c){

	if(r<1){
		return 0;
	}
	if(r>15){
		return 0;
	}
	if(c<1){
		return 0;
	}
	if(c>30){
		return 0;
	}
	//check if the seat is taken
	if (theater[r-1][c-1] != '#'){
		return 0;
	}

	//it is in range and not taken
	return 1;

}


int main(){

	mainMenu();

	return 0;
}
