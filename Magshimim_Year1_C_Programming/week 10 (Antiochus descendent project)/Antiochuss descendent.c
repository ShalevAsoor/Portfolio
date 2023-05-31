#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define EASY 1
#define MODERATE 2
#define HARD 3
#define IMPOSSIBLE 4

const int EASYTURNES = 20;
const int MODERATETURNES = 15;
const int HARDTURNES = 10;


int creditCode(void);
bool guessCheck(int guess);
void welcomeM(void);
void printDiff(void);
int guesses(int difficulty);
int hitCounter(int guess, int code);
int missCounter(int guess, int code);
void loseMessage(void);
void winMessage(int code);


int main(void)
{
	char again = ' ';

	do {

		srand(time(NULL));
		int code = 0, choice = 0, difficulty = 0, turnes = 0, leftTurnes = 0, i = 0, guess = 0, hits = 0, misses = 0;
		bool diffFlag = true, check = true;

		code = creditCode();

		welcomeM();
		printDiff();
		scanf("%d", &choice);

		do {

			diffFlag = false;


			switch (choice)
			{

			case 1:
				difficulty = EASY;
				diffFlag = false;
				break;
			case 2:
				difficulty = MODERATE;
				diffFlag = false;
				break;
			case 3:
				difficulty = HARD;
				diffFlag = false;
				break;
			case 4:
				difficulty = IMPOSSIBLE;
				diffFlag = false;
				break;
			case 6:

			default:
				printf("Make a choise: ");
				scanf("%d", &choice);
				diffFlag = true;
				break;
			}
		} while (diffFlag == true);

		turnes = guesses(difficulty);

		leftTurnes = turnes; //to calculate the number of turnes the player has left


		i = 0;
		do
		{
			//printf("%d\n",code);  //debugging (turn on for testing)
			do {
				printf("Write your guess (only 1-6)\n");
				if (difficulty != 4)
					printf("%d turnes left\n", leftTurnes);
				else
					printf("You are playing on 'impossible' mode, be careful you could lose any minute\n");

				scanf("%d", &guess);
				check = guessCheck(guess);

			} while ((guess <= 999 || guess > 6666) || (check == false));

			hits = hitCounter(guess, code);
			misses = missCounter(guess, code);

			printf("\nHITS: %d\n", hits);
			printf("MISSES: %d\n\n", misses);

			leftTurnes--;
			i++;

		} while (i < turnes && hits != 4);

		if (hits == 4)
		{
			winMessage(code);
			printf("you won!!, "); //winning messages

			if (i == 1)
			{
				printf("That took you only %d guess!, you are a pro!.\n", i);

			}
			else if (i >= 2 && i <= 3)
			{
				printf("That took you only %d guesses!, you are a pro!.\n", i);
			}
			else if (i >= 4 && i <= 10)
			{
				printf("That took you %d guesses!, thats amazing!", i);
			}
			else
			{
				printf("it took you %d guesses.", i);
			}


		}
		else
		{
			loseMessage();
			printf("you lost ): the code was %d.\n", code);//losing message
		}

		printf("\nwould you like to try again? (Y/N): ");
		getchar();
		again = getchar();

	} while (again == 'y' || again == 'Y');
}


/*
this function makes 1 random 4 digit number and dissasmbles it to 4 seprate 1 digit number to check if the number is valid
input: none
output: 1 random 4 digit number
*/


int creditCode(void)
{
	int num = 0, numC = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0; //numC is used to check if the random generated number is valid

	do {


		num = rand() % (9999 - 1000 + 1) + 1000; //randomizes the code

		numC = num;

		num4 = numC % 10; //dissasmbles the code
		numC = numC / 10;
		num3 = numC % 10;
		numC = numC / 10;
		num2 = numC % 10;
		numC = numC / 10;
		num1 = numC % 10;

	} while ((num1 == num2) || (num1 == num3) || (num1 == num4) || (num2 == num3) || (num2 == num4) || (num3 == num4) || (num1 > 6) || (num2 > 6) || (num3 > 6) || (num4 > 6) || (num1 < 1) || (num2 < 1) || (num3 < 1) || (num4 < 1));

	return num;
}

/*
this function checks to see if the guess is valid or not ( + bonus)
input: none
output: a bool that says if the guess is valid or not
note: i split the 'if' statement into two parts because they were too long
*/

bool guessCheck(int guess)
{

	int guess1 = 0, guess2 = 0, guess3 = 0, guess4 = 0;
	bool check = true;

	guess4 = guess % 10; //dissasmbles the guess
	guess = guess / 10;
	guess3 = guess % 10;
	guess = guess / 10;
	guess2 = guess % 10;
	guess = guess / 10;
	guess1 = guess % 10;

	if ((guess1 > 6) || (guess2 > 6) || (guess3 > 6) || (guess4 > 6) || (guess1 < 1) || (guess2 < 1) || (guess3 < 1) || (guess4 < 1))
	{
		check = false;
	}

	if ((guess1 == guess2) || (guess1 == guess3) || (guess1 == guess4) || (guess2 == guess3) || (guess2 == guess4) || (guess3 == guess4)) //bonus number 2
	{
		check = false;
	}

	return check;
}



/*
this function prints a welcome message
input: none
output: welcome message
*/

void welcomeM(void)
{
	printf("-------------------------------------");
	printf("Welcome to MAGSHIMIM CODE-BREAKER");
	printf("-------------------------------------\n \n");
	printf("FOR THE BEST EXPIRENCE PLEASE PLAY IN FULL SCREEN\n \n");
	printf("\nA secret password was chosen to protect the credit card of Pancratius, the descendant of Antiochus.\nYour mission is to stop Pancratius by revealing his secret password.\n\n");
	printf("The rules are as follows: \n");
	printf("1. In each round you try to guess the secret password (4 distinct digits) \n");
	printf("\n2. After every guess you'll receive two hints about the password\n	HITS:   The number of digits in your guess which were exactly right.\n	MISSES: The number of digits in your guess which belongs to the password but were miss-placed\n");
	printf("\n3. If you'll fail to guess the password after a certain number of rounds Pancratius will buy all the gifts for Hanukkah!!!\n\n");
}

/*
this function prints the difficulty levels
input: none
output: difficulty message
*/

void printDiff(void)
{
	printf("Please choose the game level:\n");
	printf("1 - Easy (20 rounds)\n");
	printf("2 - Moderate (15 rounds)\n");
	printf("3 - Hard (10 rounds)\n");
	printf("4 - Impossible (random number of rounds 5-25)\n"); //changed crazy to impossible because i didnt like the name
	printf("Make a choise: ");
}

/*
this function sets the number if tries the user got with the difficulty they chose
input: chosen difficulty
output: number of turnes
*/


int guesses(int difficulty)
{
	int turnes;

	switch (difficulty) //sets the amount of turns
	{
	case EASY:
		turnes = EASYTURNES;
		break;
	case MODERATE:
		turnes = MODERATETURNES;
		break;
	case HARD:
		turnes = HARDTURNES;
		break;
	case IMPOSSIBLE:
		turnes = rand() % (25 - 5 + 1) + 5; //randomizes the number for the "impossible" mode
		break;
	}
	return turnes;
}

/*
this function checks for HITS
input:the users guess and the credit card code
output:the amount of hits the user got
*/

int hitCounter(int guess, int code)
{
	int hit = 0;
	int code1 = 0, code2 = 0, code3 = 0, code4 = 0;
	int guess1 = 0, guess2 = 0, guess3 = 0, guess4 = 0;


	code4 = code % 10; //dissasmbles the code
	code = code / 10;
	code3 = code % 10;
	code = code / 10;
	code2 = code % 10;
	code = code / 10;
	code1 = code % 10;

	guess4 = guess % 10; //dissasmbles the guess
	guess = guess / 10;
	guess3 = guess % 10;
	guess = guess / 10;
	guess2 = guess % 10;
	guess = guess / 10;
	guess1 = guess % 10;


	if (code4 == guess4) //adds a hit if necessary
		hit++;

	if (code3 == guess3)
		hit++;

	if (code2 == guess2)
		hit++;

	if (code1 == guess1)
		hit++;

	return hit;

}

/*
this function checks for misses
input:the users guess and the credit card code
output:the amount of misses the user got
*/

int missCounter(int guess, int code)
{
	int miss = 0;
	int code1 = 0, code2 = 0, code3 = 0, code4 = 0;
	int guess1 = 0, guess2 = 0, guess3 = 0, guess4 = 0;

	code4 = code % 10; //dissasmbles the code
	code = code / 10;
	code3 = code % 10;
	code = code / 10;
	code2 = code % 10;
	code = code / 10;
	code1 = code % 10;

	guess4 = guess % 10; //dissasmbles the guess
	guess = guess / 10;
	guess3 = guess % 10;
	guess = guess / 10;
	guess2 = guess % 10;
	guess = guess / 10;
	guess1 = guess % 10;

	if (guess1 == code2 || guess1 == code3 || guess1 == code4) //adds a miss if necessary
		miss = miss + 1;

	if (guess2 == code1 || guess2 == code3 || guess2 == code4)
		miss = miss + 1;

	if (guess3 == code1 || guess3 == code2 || guess3 == code4)
		miss = miss + 1;

	if (guess4 == code1 || guess4 == code2 || guess4 == code3)
		miss = miss + 1;


	return miss;
}

/*
this function is for the first bonus(fail message drawing)
input: none
output: none
*/

void loseMessage(void)
{
	printf("         @@@@     @@@/   @@@@@@@@@/   @@@,     @@@                 @@@/           (@@@@@@@@@     @@@@@@@@@@   @@@@@@@@@@@&                            \n");
	printf("          @@@@   @@@(   @@@     @@@&  @@@,     @@@                 @@@/          @@@@     @@@   @@@               @@@@              ,        .        \n");
	printf("           @@@/ @@@/   /@@@     #@@@  @@@,     @@@                 @@@/          @@@#     @@@. ,@@@               @@@@                                \n");
	printf("            @@@/@@,    /@@@     #@@@  @@@,     @@@                 @@@/          @@@#     @@@.  @@@@@@@@@@        @@@@                               \n");
	printf("             @@@@*     /@@@     #@@@  @@@,     @@@                 @@@/          @@@#     @@@.         #@@@,      @@@@                @@@@@@/         \n");
	printf("             /@@@      /@@@     #@@@  @@@,    .@@@                 @@@/          @@@#     @@@.          @@@#      @@@@              @@       #@.      \n");
	printf("             /@@@       @@@@   (@@@*  &@@@.  .@@@@                 @@@/          *@@@/   @@@@          @@@@       @@@@             @@         *@      \n");
	printf("             ,###         /#####(.      ,(#####*                   ############    .(#####/     ########/         (###             ..          ..     \n");
	printf("                                                                                                                                                      \n");
	printf("                                                                                                                                                      \n");
	printf("                                                                                                                                                      \n");
	printf("                                                                                                                                                      \n");
	printf("                                                                                                                                                      \n");
	printf("                                                                                     ./                                                               \n");
	printf("                                                                                     &@                                                               \n");
	printf("                                                                                    .&@,                                                              \n");
	printf("                                                                                   @@@@@@       @@@                                                   \n");
	printf("                                                                @@,                .@@@@@     ,@@@                                                    \n");
	printf("                                                               .@@@                 @@@@@    ,@@@     @@@@@@#                                         \n");
	printf("                                                                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(                                        \n");
	printf("                                                                 (/.      @@@@@,     @@@@     @@@   .@@@@@@(                                          \n");
	printf("                                                                      %@@@@&         #@@@     #@@                                                     \n");
	printf("                                                             @@@. %@@@@@.             @@@      @@@                                                    \n");
	printf("                                                              @@@@@@.                 &@.       @@,                                                   \n\n\n\n\n\n\n");
}

/*
this function is for the first bonus(win message drawing)
input: the randomized code
output: none
*/

void winMessage(int code)
{





	printf("                @@@@    @@@@   @@@@@@@@@@@   @@@,     @@@                 @@@       @@@  @@@@@@@@@@@&  &@@@@     @@&      @@@@                  .@             /  \n");
	printf("                 @@@@  @@@@   @@@@     @@@@  @@@,     @@@                 @@@       @@@  @@@      @@@  &@@@@@    @@&      @@@@                                    \n");
	printf("                  @@@. @@@    @@@@     @@@@  @@@,     @@@                 @@@  @@@ *@@@  @@@      @@@  &@@.@@@   @@&      @@@@                                    \n");
	printf("                   @@@@@@     @@@@     @@@@  @@@,     @@@                 %@@/  @@@ @@@.  @@@      @@@  &@@ .@@@  @@&      @@@@                  @               @\n");
	printf("                    @@@@      @@@@     @@@@  @@@,     @@@                  @@@@@ @,@@@   @@@      @@@  &@@   @@@ @@&      @@@@                  @@            @@  \n");
	printf("                    @@@@      &@@@     @@@@  @@@(     @@@                  @@@@@ @@@@@   @@@      @@@  &@@    @@@@@&                              /@@@@(&@@@@     \n");
	printf("                    @@@@       @@@@@@@@@@@    @@@@@@@@@@*                  @@@@* &@@@@   ,@@@@@@@@@@.  &@@     @@@@&      @@@@                                    \n");
	printf("                                                                                                                                                                  \n");
	printf("                                                                                                                                                                  \n");
	printf("                                                                                                                                                                  \n");
	printf("                                                                                                                                                                  \n");
	printf("                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                  \n");
	printf("                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                  \n");
	printf("                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   @                                                  \n");
	printf("                           @                 @             %d            @                                   @                                                    \n", code);
	printf("                           @                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   @                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @                                                                                   @                                                  \n");
	printf("                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                  \n\n\n\n\n\n\n");
}