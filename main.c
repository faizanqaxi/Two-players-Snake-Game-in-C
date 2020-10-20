//     SNAKE GAME PROJECT


/* About game : 
		*Some Basic Rules are given in code.
                *It has two mode 
			1) Classic Mode 
			2)Solid mode
		*It has two palying modes 
			1) 1 player mode 
			2) 2 player mode

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define ROWS 20
#define COLOUMNS 40
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4



//Global variables
int x, y, fruitX, fruitY = 0;
int BonusFruitX, BonusFruitY = 0;
int fruitCounter = 0;
int fruitTimer = 0;
int direction, gameOver, score, tailCounter = 0;
char ch;
char reverseDirection;
int tailX[800], tailY[800];
int choice = 0;
int speed = 0;
int s = 10;
char playAgain;
int x_2, y_2 = 0;
int direction_2, gameOver_2, score_2, tailCounter_2 = 0;
char ch_2;
char reverseDirection_2;
int tailX_2[800], tailY_2[800];
int players = 0;
int timer = 0;
int twoPlayersTime = 500;
int inputTime = 60;
float speedFactor = 0;
float timeFactor = 0;
int inputTimeDisplay = 60;

//Function prototypes
void gotoxy(x, y);
void loadingscreen();
void mainscreen();
void menu();
void rules();
void initializers();
void startingValues();
void snake_speed();
void BonusFruit();
void BonusTimer();
void fruit();
void board();
void input();
void tail();
void play_classic();
void play_solid();
void startingValues_2();
void board_2();
void tail_2();
void play_classic_2();
void play_solid_2();
void twoPlayersRespawn();
void twoPlayersTimeFormula();
void timeDisplayFormula();

int main()
{
	srand(time(NULL));
	system("color 80");  //Color of console changes to gray
	mainscreen();  //Welcome to snake game display
	system("cls");  //Clear screen command
	system("color 80");  //Color of console changes to gray again
	system("cls");  //Clear screen command
START:
	fruit();
	initializers();
	startingValues();
	startingValues_2();
	menu();  //Shows menu of game interface
	system("cls");
	loadingscreen(); //Loading screen function calling, displays loading
	if (players == 1)
	{
		while (gameOver == 0)  //While loop for quiting the game
		{
			board();
			input();
			if (choice == 1)
			{
				play_classic();
			}
			else if (choice == 2)
			{
				play_solid();
			}
			_sleep(speed);  //Slows down execution speed
		}
		printf("\n Game Over! Your score is %d", score);
	}

	else if (players == 2)
	{
		twoPlayersTimeFormula();
		timeDisplayFormula();
		timer = twoPlayersTime;
		while (timer > 0)
		{
			timeDisplayFormula();
			board_2();
			twoPlayersRespawn();
			input();
			if (choice == 1)
			{
				play_classic();
				play_classic_2();
			}
			else if (choice == 2)
			{
				play_solid();
				play_solid_2();
			}
			timer--;
			_sleep(speed);  //Slows down execution speed
		}
		printf("\n Time's up! Game Over!");
		if (score > score_2)  //If statements for win check
		{
			printf("\n PLAYER 1 WINS! ");
		}
		if (score_2 > score)
		{
			printf("\n PLAYER 2 WINS ! ");
		}
		if (score == score_2)  //Draw match
		{
			printf("\n THE MATCH IS A DRAW !");
		}
	}

	printf("\n Enter p to play again any other key to quit : ");
	scanf(" %c", &playAgain);

	if (playAgain == 'p' || playAgain == 'P') //If statement for playing again
	{
		system("cls");  //Clear screen
		goto START;  //New game starts
	}

	return 0;
}


void mainscreen()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	char ch;

	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute(h, 140);

	printf("##     ##  ########  ##         #######  ######  ####  ###  ########     \n");
	printf("##     ##  ##        ##         ##       ######  ####  ###  ##           \n");
	printf("##     ##  ##        ##         ##       ##  ##  ##  ## ##  ##           \n");
	printf("##     ##  ########  ##         ##       #    #  ##     ##  ########     \n");
	printf("##  .  ##  ##        ##         ##       #    #  ##     ##  ##           \n");
	printf("##  #  ##  ##        ##         ##       ##  ##  ##     ##  ##           \n");
	printf("## ### ##  ########  #########  #######  ######  ##     ##  ########     \n");

	_sleep(1000);  //Slows down execution speed by 1 second. 1000 milli seconds = 1 second.



	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute(h, wOldColorAttrs);


	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute(h, 130);
	printf("                      ###########  ########                                  \n");
	printf("                          ##       ###  ###                                  \n");
	printf("                          ##       ##    ##                                  \n");
	printf("                          ##       ##    ##                                  \n");
	printf("                          ##       ###  ###                                  \n");
	printf("                          ##       ########                                  \n");


	_sleep(1000);  //Slows down execution speed by 1 second. 1000 milli seconds = 1 second.

	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute(h, wOldColorAttrs);


	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute(h, 137);
	printf("#########  ###      ###  ##########  ###     ##  ##########  ##   \n");
	printf("#########  #####    ###  ##########  ###    ##   ##########  ##  \n");
	printf("###        ### ##   ###  ###    ###  ###   ##    ###         ##  \n");
	printf("#########  ###  ##  ###  ##########  #### ##     ##########  ##  \n");
	printf("#########  ###   ## ###  ##########  ###  ##     ##########  ##  \n");
	printf("      ###  ###    #####  ###    ###  ###   ##    ###         ##  \n");
	printf("#########  ###     ####  ###    ###  ###    ##   ##########   \n");
	printf("#########  ###      ###  ###    ###  ###     ##  ##########  ##  \n");

	_sleep(1000);  //Slows down execution speed by 1 second. 1000 milli seconds = 1 second.


	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute(h, wOldColorAttrs);


	printf("\n\t\tPress any key to start the game!!");
	getch();
}

void gotoxy(x, y) // For gotoxy function
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void loadingscreen()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	gotoxy(32, 16);  //Goes to (32, 16) coordinates and displays loading bar
	printf("Loading... Please Wait");
	gotoxy(32, 18);

	for (int q = 0; q <= 30; q++)  //For printing loading bar
	{
		SetConsoleTextAttribute(h, 143);

		printf("%c", 177);
		_sleep(100);  //Slowing loading process
	}
}


void menu()  //Prints menu for user to choose from
{
MENU:
	system("color 80");
	printf("Please choose your option: ");
	printf("\n Enter: ");
	printf("\n 0 To adjust the snake speed: ");
	printf("\n 1 for 1 player mode: ");
	printf("\n 2 for 2 players mode: ");
	printf("\n 3 To read rules and instructions: ");
	printf("\n 4 To adjust the 2 players timer: \n");
	printf("\n Player 1 snake: oooO \n");
	printf("\n Player 2 snake: %c%c%c%c \n", 254, 254, 254, 254);
	scanf("%d", &players);

	if (players == 0)
	{
		system("cls");
	sLabel:
		printf("\n Enter the speed you want from 1(min) to 20(max): ");
		scanf("%d", &s);
		if (!(s >= 1 && s <= 20))  //If statement for invalid data entry
		{
			printf("\n Invalid speed! Please enter a valid speed: ");
			goto sLabel;
		}
		else
		{
			snake_speed();
			twoPlayersTimeFormula();
			timeDisplayFormula();
			system("cls");
			printf("New speed adjusted! \n");
			goto MENU;
		}

	}
	if (players == 3)
	{
		rules();
		printf("\n Read all the instructions carefully then press any key to go back to the menu: \n");
		getch();
		system("cls");
		goto MENU;

	}

	if (players == 4)
	{
		system("cls");

	TIMEadjust:
		printf("Adjust the match time : ");
		printf("\n Please enter how much time you want(in seconds) : ");
		scanf("%d", &inputTime);
		if (inputTime < 1)
		{
			system("cls");
			printf("Invalid time entered ! Please enter a valid time. \n");
			goto TIMEadjust;
		}
		else
		{
			twoPlayersTimeFormula();
			timeDisplayFormula();
			system("cls");
			printf("\n Your new time is adjusted ! ");
			goto MENU;
		}

	}

	if (players != 1 && players != 2 && players != 0 && players != 3 && players != 4)
	{
		system("cls");
		printf("INVALID INPUT! PLEASE ENTER A VALID INPUT. \n");
		goto MENU;
	}
	system("cls");

MODE:

	printf("Please choose your option: ");
	printf("\n Enter: ");
	printf("\n 1 To play classic mode: ");
	printf("\n 2 To play solid mode: ");
	scanf("%d", &choice);

	if (choice != 1 && choice != 2)  //If statement for invalid data entry
	{
		system("cls");
		printf("Invalid input please enter a correct option! \n");
		goto MODE;
	}
}

void rules()  //Prints different rules of the game
{
	system("cls");
	printf("\n\t\t Welcome to the snake game!");
	printf("\n * This game has both 1 player option and 2 players option");
	printf("\n * There are two modes in this game: (1)Solid Mode (2)Classic Mode");
	printf("\n * In Solid mode if the snake touches the wall it dies.");
	printf("\n * In Classic mode if the snake touches the wall it reappears from the other side.");
	printf("\n * Make sure your 'CAPS LOCK' is off");
	printf("\n * The keys to move the snake are 'w' 'a' 's' 'd'");
	printf("\n * 'w' moves the snake up");
	printf("\n * 'a' moves the snake left");
	printf("\n * 's'moves the snake down");
	printf("\n * 'd' moves the snake right");
	printf("\n * For 2 players the keys to move the player 2 snake are 'i' 'j' 'k' 'l'");
	printf("\n * 'i' moves the snake up");
	printf("\n * 'j' moves the snake left");
	printf("\n * 'k'moves the snake down");
	printf("\n * 'l' moves the snake right");
	printf("\n * The controls of player 1 remains the same which is in 1 player i.e: 'w' 'a' 's' 'd'");
	printf("\n * If you hit the tail of the snake you die.");
	printf("\n * The size of the snake increases as you eat a fruit");
	printf("\n * You get points on each fruit you eat depnding upon the snake speed you have set.");
	printf("\n * A bonus fruit appears after eating every 5 fruits.");
	printf("\n * The score of bonus fruit depends in the time you eat it and the snake speed.");
	printf("\n * Quicker you eat the bonus fruit, more score you get.");
	printf("\n * The bonus fruit disappears after sometime which also depends on the snake speed set.");
	printf("\n * More the snake speed, quicker the bonus fruit disappears.");
	printf("\n * In 2 players classic mode if the two snakes touch each other they will just pass through each other without dying.");
	printf("\n * In 2 players solid mode if the heads of the two snakes touch each other they will both die but if they just touch the tail they won't die and just pass through each other.");
	printf("\n * In 1 player whenever the snake dies the game is over.");
	printf("\n * In 2 players whenever the snake of a player dies his\her score reduces by the speed of game set(i.e: 10 by default) and the snake reduces to it's original form and respawns.");
	printf("\n * In 2 players the game keeps on until the time ends.");
	printf("\n * In 2 players whichever player has more score at the end of the time, HE/SHE wins.");
	printf("\n\t\t  Good Luck!");
}

void initializers()  //Function for changing variable values to 0
{
	fruitCounter = 0;
	BonusFruitX = 0;
	BonusFruitY = 0;
	choice = 0;
	snake_speed();
	score = 0;
	score_2 = 0;
	gameOver = 0;
	gameOver_2 = 0;
	fruitTimer = 0;
	twoPlayersTimeFormula();
	timeDisplayFormula();
}

void startingValues()
{
	x = COLOUMNS / 2;
	y = ROWS / 2;
	gameOver = 0;
	direction = 0;
	ch = '0';
	reverseDirection = ' ';
	for (int i = 0; i < 800; i++)
	{
		tailX[i] = 0;
		tailY[i] = 0;
	}
	tailCounter = 0;

}

void startingValues_2()
{
	x_2 = COLOUMNS / 2;
	y_2 = ROWS / 2 + 1;
	gameOver_2 = 0;
	direction_2 = 0;
	ch_2 = '0';
	reverseDirection_2 = ' ';
	tailCounter_2 = 0;
	for (int i = 0; i < 800; i++)
	{
		tailX_2[i] = 0;
		tailY_2[i] = 0;
	}

}
void snake_speed() //formula for speed meter ofr snake
{
	speed = (200 - 10 * s);
}


void board()
{
	system("cls");
	system("color F0");

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	BonusTimer();
	int i, j, k, space = 0;
	for (i = 1; i <= ROWS; i++)
	{
		for (j = 1; j <= COLOUMNS; j++)
		{
			if (i == 1 || i == ROWS || j == 1 || j == COLOUMNS)
			{
				/*
				* First save the current color information
				*/
				GetConsoleScreenBufferInfo(h, &csbiInfo);
				wOldColorAttrs = csbiInfo.wAttributes;

				/*
				* Set the new color information
				*/
				SetConsoleTextAttribute(h, 248);

				printf("%c", 178);

				/*
				* Restore the original colors
				*/
				SetConsoleTextAttribute(h, wOldColorAttrs);
			}

			else
			{
				if (j == x && i == y)
				{
					/*
					* First save the current color information
					*/
					GetConsoleScreenBufferInfo(h, &csbiInfo);
					wOldColorAttrs = csbiInfo.wAttributes;

					/*
					* Set the new color information
					*/
					SetConsoleTextAttribute(h, 252);

					printf("O");

					/*
					* Restore the original colors
					*/
					SetConsoleTextAttribute(h, wOldColorAttrs);

				}
				else if (j == fruitX && i == fruitY)
				{
					printf("*");
				}
				else if ((j == BonusFruitX && i == BonusFruitY) && (fruitTimer > 0))
				{
					/*
					* First save the current color information
					*/
					GetConsoleScreenBufferInfo(h, &csbiInfo);
					wOldColorAttrs = csbiInfo.wAttributes;

					/*
					* Set the new color information
					*/
					SetConsoleTextAttribute(h, 242);

					printf("$");

					/*
					* Restore the original colors
					*/
					SetConsoleTextAttribute(h, wOldColorAttrs);
				}
				else
				{
					int space = 1;
					for (int m = 0; m < tailCounter; m++)
					{
						if (j == tailX[m] && i == tailY[m])
						{
							/*
							* First save the current color information
							*/
							GetConsoleScreenBufferInfo(h, &csbiInfo);
							wOldColorAttrs = csbiInfo.wAttributes;

							/*
							* Set the new color information
							*/
							SetConsoleTextAttribute(h, 252);
							printf("o");

							/*
							* Restore the original colors
							*/
							SetConsoleTextAttribute(h, wOldColorAttrs);


							space = 0;
						}
					}
					if (space)
					{
						printf(" ");
					}

				}

			}
		}
		printf("\n");
	}
	printf("\n SCORE: %d \n", score);
	if (fruitTimer > 0)
	{
		for (int t = 0; t <= fruitTimer; t++)
		{
			/*
			* First save the current color information
			*/
			GetConsoleScreenBufferInfo(h, &csbiInfo);
			wOldColorAttrs = csbiInfo.wAttributes;

			/*
			* Set the new color information
			*/
			SetConsoleTextAttribute(h, 242);

			printf("%c", 178);

			/*
			* Restore the original colors
			*/
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
	}
}

void board_2()
{
	system("cls");
	system("color F0");

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;



	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute(h, 244);

	printf("\t\t TIME REMAINING = %d \n", inputTimeDisplay);

	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute(h, wOldColorAttrs);


	BonusTimer();

	int i, j, k, space = 0;
	for (i = 1; i <= ROWS; i++)
	{
		for (j = 1; j <= COLOUMNS; j++)
		{
			if (i == 1 || i == ROWS || j == 1 || j == COLOUMNS)
			{
				/*
				* First save the current color information
				*/
				GetConsoleScreenBufferInfo(h, &csbiInfo);
				wOldColorAttrs = csbiInfo.wAttributes;

				/*
				* Set the new color information
				*/
				SetConsoleTextAttribute(h, 248);

				printf("%c", 178);

				/*
				* Restore the original colors
				*/
				SetConsoleTextAttribute(h, wOldColorAttrs);

			}

			else
			{
				if (j == x && i == y)
				{

					/*
					* First save the current color information
					*/
					GetConsoleScreenBufferInfo(h, &csbiInfo);
					wOldColorAttrs = csbiInfo.wAttributes;

					/*
					* Set the new color information
					*/
					SetConsoleTextAttribute(h, 252);

					printf("O");

					/*
					* Restore the original colors
					*/
					SetConsoleTextAttribute(h, wOldColorAttrs);

				}
				else if (j == x_2 && i == y_2)
				{
					/*
					* First save the current color information
					*/
					GetConsoleScreenBufferInfo(h, &csbiInfo);
					wOldColorAttrs = csbiInfo.wAttributes;

					/*
					* Set the new color information
					*/
					SetConsoleTextAttribute(h, 249);

					printf("%c", 254);

					/*
					* Restore the original colors
					*/
					SetConsoleTextAttribute(h, wOldColorAttrs);
				}
				else if (j == fruitX && i == fruitY)
				{
					printf("*");
				}
				else if ((j == BonusFruitX && i == BonusFruitY) && (fruitTimer > 0))
				{
					/*
					* First save the current color information
					*/
					GetConsoleScreenBufferInfo(h, &csbiInfo);
					wOldColorAttrs = csbiInfo.wAttributes;

					/*
					* Set the new color information
					*/
					SetConsoleTextAttribute(h, 242);

					printf("$");

					/*
					* Restore the original colors
					*/
					SetConsoleTextAttribute(h, wOldColorAttrs);
				}
				else
				{
					int k = 0;
					for (int m = 0; m < tailCounter; m++)
					{
						if (j == tailX[m] && i == tailY[m])
						{

							/*
							* First save the current color information
							*/
							GetConsoleScreenBufferInfo(h, &csbiInfo);
							wOldColorAttrs = csbiInfo.wAttributes;

							/*
							* Set the new color information
							*/
							SetConsoleTextAttribute(h, 252);
							printf("o");

							/*
							* Restore the original colors
							*/
							SetConsoleTextAttribute(h, wOldColorAttrs);


							k = 1;
						}
					}
					if (k != 1)
					{
						for (int m = 0; m < tailCounter_2; m++)
						{
							if (j == tailX_2[m] && i == tailY_2[m])
							{
								/*
								* First save the current color information
								*/
								GetConsoleScreenBufferInfo(h, &csbiInfo);
								wOldColorAttrs = csbiInfo.wAttributes;

								/*
								* Set the new color information
								*/
								SetConsoleTextAttribute(h, 249);

								printf("%c", 254);

								/*
								* Restore the original colors
								*/
								SetConsoleTextAttribute(h, wOldColorAttrs);


								k = 2;
							}
						}
					}

					if (k == 0)
					{
						printf(" ");
					}

				}

			}
		}
		printf("\n");
	}

	printf("\n SCORE = ");



	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute(h, 252);

	printf("Player 1 : %d \t ", score);

	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute(h, wOldColorAttrs);



	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute(h, 249);

	printf("Player 2 : %d \n ", score_2);

	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute(h, wOldColorAttrs);


	if (fruitTimer > 0)
	{
		for (int t = 0; t <= fruitTimer; t++)
		{
			/*
			* First save the current color information
			*/
			GetConsoleScreenBufferInfo(h, &csbiInfo);
			wOldColorAttrs = csbiInfo.wAttributes;

			/*
			* Set the new color information
			*/
			SetConsoleTextAttribute(h, 242);

			printf("%c", 178);

			/*
			* Restore the original colors
			*/
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
	}
}

void fruit() //for fruit
{
label:
label1 :
	fruitX = rand() % COLOUMNS;
	   if (fruitX < 2)
	   {
		   goto label1;
	   }
   label2:
	   fruitY = rand() % ROWS;
	   if (fruitY < 2)
	   {
		   goto label2;
	   }
	   if ((fruitX == x && fruitY == y) || (fruitX == BonusFruitX && fruitY == BonusFruitY))
	   {
		   goto label;
	   }
	   if ((fruitX == x_2 && fruitY == y_2) || (fruitX == BonusFruitX && fruitY == BonusFruitY))
	   {
		   goto label;
	   }
	   for (int i = 0; i < tailCounter; i++)
	   {
		   if (fruitX == tailX[i] && fruitY == tailY[i])
		   {
			   goto label;
		   }
	   }
	   for (int i = 0; i < tailCounter_2; i++)
	   {
		   if (fruitX == tailX_2[i] && fruitY == tailY_2[i])
		   {
			   goto label;
		   }
	   }
}
void BonusFruit() //for bonus fruit
{
label:
label1 :
	BonusFruitX = rand() % COLOUMNS;
	   if (BonusFruitX < 2)
	   {
		   goto label1;
	   }
   label2:
	   BonusFruitY = rand() % ROWS;
	   if (BonusFruitY < 2)
	   {
		   goto label2;
	   }
	   if ((BonusFruitX == x && BonusFruitY == y) || (BonusFruitX == fruitX && BonusFruitY == fruitY))
	   {
		   goto label;
	   }
	   for (int i = 0; i < tailCounter; i++)
	   {
		   if (BonusFruitX == tailX[i] && BonusFruitY == tailY[i])
		   {
			   goto label;
		   }
	   }
	   if ((BonusFruitX == x_2 && BonusFruitY == y_2) || (BonusFruitX == fruitX && BonusFruitY == fruitY))
	   {
		   goto label;
	   }
	   for (int i = 0; i < tailCounter; i++)
	   {
		   if (BonusFruitX == tailX_2[i] && BonusFruitY == tailY_2[i])
		   {
			   goto label;
		   }
	   }
}

void BonusTimer() //for bonus timer
{
	fruitTimer--;
	if (fruitTimer < 0)
	{
		fruitTimer = 0;
	}
}

void tail() //for tail of snake
{
	int prevX, prevY, prev2X, prev2Y = 0;
	prevX = tailX[0];
	prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;

	for (int k = 1; k < tailCounter; k++)
	{
		prev2X = tailX[k];
		prev2Y = tailY[k];
		tailX[k] = prevX;
		tailY[k] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
}

void tail_2() //for 2 nd player snake tail
{
	int prevX_2, prevY_2, prev2X_2, prev2Y_2 = 0;
	prevX_2 = tailX_2[0];
	prevY_2 = tailY_2[0];
	tailX_2[0] = x_2;
	tailY_2[0] = y_2;

	for (int k = 1; k < tailCounter_2; k++)
	{
		prev2X_2 = tailX_2[k];
		prev2Y_2 = tailY_2[k];
		tailX_2[k] = prevX_2;
		tailY_2[k] = prevY_2;
		prevX_2 = prev2X_2;
		prevY_2 = prev2Y_2;

	}
}


void input()  //Function for keyboard input while playing the game
{
	if (kbhit())
	{
		ch = getch();
		if (ch != reverseDirection && ch != reverseDirection_2)
		{
			switch (ch)
			{
			case 'w':
				direction = UP;
				reverseDirection = 's';
				break;
			case 's':
				direction = DOWN;
				reverseDirection = 'w';
				break;
			case 'a':
				direction = LEFT;
				reverseDirection = 'd';
				break;
			case 'd':
				direction = RIGHT;
				reverseDirection = 'a';
				break;


			case 'i':
				direction_2 = UP;
				reverseDirection_2 = 'k';
				break;
			case 'k':
				direction_2 = DOWN;
				reverseDirection_2 = 'i';
				break;
			case 'j':
				direction_2 = LEFT;
				reverseDirection_2 = 'l';
				break;
			case 'l':
				direction_2 = RIGHT;
				reverseDirection_2 = 'j';
				break;


			}
		}
	}
}



void play_classic() //for movement of snake
{

	tail();

	switch (direction)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	}
	if (x == 1)
	{
		x = COLOUMNS - 1;
	}
	else if (y == 1)
	{
		y = ROWS - 1;
	}
	else if (x == COLOUMNS)
	{
		x = 1 + 1;
	}
	else if (y == ROWS)
	{
		y = 1 + 1;
	}

	for (int n = 1; n < tailCounter; n++)
	{
		if (x == tailX[n] && y == tailY[n])
		{
			gameOver = 1;
		}
	}
	if (x == fruitX && y == fruitY)
	{
		fruit();
		score += s;
		tailCounter++;
		fruitCounter++;
		if (fruitCounter % 5 == 0)
		{
			BonusFruit();
			fruitTimer = 40;
		}
	}
	if (x == BonusFruitX && y == BonusFruitY)
	{
		fruitCounter++;
		score += fruitTimer * s;
		BonusFruitX = 0;
		BonusFruitY = 0;
		fruitTimer = 0;
	}
	if (fruitTimer < 1)
	{
		BonusFruitX = 0;
		BonusFruitY = 0;
	}
}
void play_classic_2()
{

	tail_2();

	switch (direction_2)
	{
	case UP:
		y_2--;
		break;
	case DOWN:
		y_2++;
		break;
	case LEFT:
		x_2--;
		break;
	case RIGHT:
		x_2++;
		break;
	}
	if (x_2 == 1)
	{
		x_2 = COLOUMNS - 1;
	}
	else if (y_2 == 1)
	{
		y_2 = ROWS - 1;
	}
	else if (x_2 == COLOUMNS)
	{
		x_2 = 1 + 1;
	}
	else if (y_2 == ROWS)
	{
		y_2 = 1 + 1;
	}

	for (int n = 1; n < tailCounter_2; n++)
	{
		if (x_2 == tailX_2[n] && y_2 == tailY_2[n])
		{
			gameOver_2 = 1;
		}
	}
	if (x_2 == fruitX && y_2 == fruitY)
	{
		fruit();
		score_2 += s;
		tailCounter_2++;
		fruitCounter++;
		if (fruitCounter % 5 == 0)
		{
			BonusFruit();
			fruitTimer = 40;
		}
	}
	if (x_2 == BonusFruitX && y_2 == BonusFruitY)
	{
		fruitCounter++;
		score_2 += fruitTimer * s;
		BonusFruitX = 0;
		BonusFruitY = 0;
		fruitTimer = 0;
	}
	if (fruitTimer < 1)
	{
		BonusFruitX = 0;
		BonusFruitY = 0;
	}
}

void play_solid() //for solid mode
{

	tail();

	switch (direction)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	}
	if (x == 1 || y == 1 || x == COLOUMNS || y == ROWS)
	{
		gameOver = 1;
	}
	if (x == x_2 && y == y_2)
	{
		gameOver = 1;
		gameOver_2 = 1;
	}

	for (int n = 1; n < tailCounter; n++)
	{
		if (x == tailX[n] && y == tailY[n])
		{
			gameOver = 1;
		}
	}
	if (x == fruitX && y == fruitY)
	{
		fruit();
		score += s;
		tailCounter++;
		fruitCounter++;
		if (fruitCounter % 5 == 0)
		{
			BonusFruit();
			fruitTimer = 40;
		}
	}
	if (x == BonusFruitX && y == BonusFruitY)
	{
		fruitCounter++;
		score += fruitTimer * s;
		BonusFruitX = 0;
		BonusFruitY = 0;
		fruitTimer = 0;
	}
	if (fruitTimer < 1)
	{
		BonusFruitX = 0;
		BonusFruitY = 0;
	}
}
void play_solid_2()
{

	tail_2();

	switch (direction_2)
	{
	case UP:
		y_2--;
		break;
	case DOWN:
		y_2++;
		break;
	case LEFT:
		x_2--;
		break;
	case RIGHT:
		x_2++;
		break;
	}
	if (x_2 == 1 || y_2 == 1 || x_2 == COLOUMNS || y_2 == ROWS)
	{
		gameOver_2 = 1;
	}
	if (x_2 == x && y_2 == y)
	{
		gameOver = 1;
		gameOver_2 = 1;
	}
	for (int n = 1; n < tailCounter_2; n++)
	{
		if (x_2 == tailX_2[n] && y_2 == tailY_2[n])
		{
			gameOver_2 = 1;
		}
	}
	if (x_2 == fruitX && y_2 == fruitY)
	{
		fruit();
		score_2 += s;
		tailCounter_2++;
		fruitCounter++;
		if (fruitCounter % 5 == 0)
		{
			BonusFruit();
			fruitTimer = 40;
		}
	}
	if (x_2 == BonusFruitX && y_2 == BonusFruitY)
	{
		fruitCounter++;
		score_2 += fruitTimer * s;
		BonusFruitX = 0;
		BonusFruitY = 0;
		fruitTimer = 0;
	}
	if (fruitTimer < 1)
	{
		BonusFruitX = 0;
		BonusFruitY = 0;
	}
}

void twoPlayersRespawn() //for respawn of players if they died before time
{
	if (gameOver == 1)
	{
		score -= s;
		startingValues();
	}
	if (gameOver_2 == 1)
	{
		score_2 -= s;
		startingValues_2();
	}
}

void twoPlayersTimeFormula() //Two players timer formula
{
	speedFactor = 2.5 / s;
	timeFactor = speedFactor * s * 1.6;
	twoPlayersTime = (inputTime)* timeFactor;

}

void timeDisplayFormula()
{
	inputTimeDisplay = timer / timeFactor;
}

