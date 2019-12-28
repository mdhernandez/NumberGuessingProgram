/*
Author: Michael Hernandez
UIS ID: mhern61
Date last modified: 11/7/2019
*/

/*
Program Description:

A guessing game where two players take turns trying to guess a pseudorandom number between 0 and 9999.
Each turn the player has the option to make a guess or pass their turn.
A player may only pass three times and cannot pass two turns in a row.
After each guess the program will inform the players if the guess was too low or too high.
Play continues until a player guesses the correct number.
*/

/*
Program Purpose:

To abstractly demonstrate the ability of an operating system to juggle different processes (i.e. players) while keeping
records of the state of each process (i.e. remaining passes and if they passed last turn)
*/

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/*
Returns 0 if the guessed number is equal to the answer. 
Otherwise it prints whether the guess is too low or too high and returns a value of 1
*/
int isGuessCorrect(int guessNum, int answer)
{
	if (guessNum == answer)
	{
		//signifies a correct guess (true)
		return 0;
	}

	if (guessNum < answer)
	{
		printf("Too low\n");
	}

	else
	{
		printf("Too high\n");
	}
	//signifies an incorrect guess (false)
	return 1;
}
/*
Contains main game loop and other major game operations
*/
int main(int argc, const char* argv[])
{
	int correctNum;//stores the pseudo-random answer
	int guess = -1;//stores user input as an integer
	char guessString[5];//stores raw user input
	int playerNum;//stores current player number
	int playerSelfID;//allows user to enter their player number for verification
	int passedLastTurn[2] = { 0, 0 };//represents boolean values for whether a player passed the previous turn
	int playerPasses[2] = { 3, 3 };

	//Current time is used as the seed for the random number generator
	srand(time(0));

	//assigns a pseudo-random value between 0 and 9999 to correctNum
	correctNum = rand() % 10000;

	//starting player is assigned randomly
	playerNum = (rand() % 2) + 1;

	//introduction and explanation of the game
	printf("Welcome to the number guessing game for 2 players!\n");
	printf("You will take turns entering your player number and guessing a number until one of you guesses the correct number\n");
	printf("After each guess, you will be told if your guess is correct, too high, or too low\n");
	printf("The correct number in each game is a random number between 0 and 9999\n");
	printf("Good luck!\nThe game begins now!\n\n");

	//main game loop (start)
	do
	{
		//player identification block (start)
		printf("Player %d's turn\n", playerNum);
		printf("Enter your player number, 1 or 2\n");
		
		//Note* scanf statements are encapsulated in if statements to prevent issues
		//with some compilers requiring the return value of scanf to be used.
		if (scanf("%d", &playerSelfID)) {};
		
		//loops until the correct player ID is input
		while (playerSelfID != playerNum)
		{
			printf("It is not your turn!\n\n");
			printf("Player %d's turn\n", playerNum);
			printf("Enter your player number, 1 or 2\n");
			if (scanf("%d", &playerSelfID)) {};
		}
		//player identification block (end)
		
		//player guess block (start)
		printf("Enter your guess or enter PASS:\n");

		if (scanf("%s", &guessString)) {};
		guessString[4] = '\0';//adds a null terminator to the array to help with conversions
		
		//this if statement makes it impossible for the index of the passedLastTurn array
		//to be out of bounds, preventing warnings from some compilers.
		if (playerNum <= 2 && playerNum >-1) {
			//if a player attempts to pass their turn
			if (strcmp(guessString, "PASS") == 0)
			{
				//player is informed they passed last turn and the turn starts over
				if (passedLastTurn[playerNum-1] == 1)
				{
					printf("You cannot pass two turns in a row\n\n");
					continue;//turn is reset
				}

					//if the choice to pass is valid
					if (playerPasses[playerNum-1] > 0)
					{
						//PASS operations
						playerPasses[playerNum-1] = playerPasses[playerNum-1] - 1;
						passedLastTurn[playerNum-1] = 1;
						printf("You have passed %d number of times, you have %d more times left.\n", 3 - playerPasses[playerNum-1], playerPasses[playerNum-1]);
					}
				
				//the player is informed they have no more passes and the turn starts over
				else
				{
					printf("You do not have any passes remaining\nRe-do this turn and enter a guess.\n\n");
					continue;//turn resets
				}
			}

			//if the turn is not passed
			else
			{
				guess = atoi(guessString);//converts the guess to an integer
			
				//if the guess is invalid
				if (guess < 0 || guess > 9999) 
				{
					printf("Invalid Guess\nPlease enter a number between 0 and 9999\n\n");
					continue;
				}
				passedLastTurn[playerNum-1] = 0;//signifies that a player did not pass this turn
				
				//calls procedure isGuessCorrect, if 0 is returned the game loop is terminated
				if (isGuessCorrect(guess, correctNum) == 0)
				{
					break;
				}
			}
		}
		//player guess block (end)
		
		playerNum = (playerNum % 2) + 1;//swaps the active player
		printf("\n");//formatting
	} while (correctNum != guess);//play continues until a correct guess is made
	//main game loop (end)
		

	//displays an end of game message
	printf("\nPlayer %d wins!\nThanks for playing!\n", playerNum);

	return 0;
}