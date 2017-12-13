#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#pragma warning(disable : 4996) //Disable POSIX getch() warning

int getScore(void);
int updateScore(int newScore);
void displayTip(int *rnd);
void displayLine(void);
void displayScore(void);

int score = 0;

int main(void)
{
	//Operator declaration
	char a[][30] = { "++ (ex. a = a++)", "-- (ex. a = a--)", "()", "[]", ".", "->", "(type){list}",
						"++ (ex. a = ++a)", "-- (ex. a = --a)" ,"+ (ex. a = +a)", "- (ex. a = -a)", "~", "!", "(type)", "* (ex. int *a;)", "& (Address-of)", "sizeof", "_Alignof",
						"* (ex. a = a*a)", "/ (ex. a = a/a)", "% (ex. a = a%a)",
						"+ (ex. a = a+a)", "- (ex. a = a-a)",
						"<<", ">>",
						"<", "<=", ">", ">=",
						"==", "!=",
						"& (Bitwise)",
						"^",
						"|",
						"&&",
						"||",
						"?:",
						"=",
						"-=", "+=",
						"*=", "/=", "%=",
						">>=", "<<=",
						"|=", "^=", "&=",
						"," };
	int rnd[10],
		answer,
		loop = 1,
		operators,
		i, y,
		levels,
		level = 0,
		streak = 0;

	srand((unsigned int)time(NULL));	//Generating random seed
	operators = (sizeof(a) / sizeof(*a));	//Calculating number of operators
	levels = (sizeof(rnd) / sizeof(*rnd));	//Calculating number of levels
	score = getScore();

	displayScore();

	while (loop != 0)
	{
		//Generating random numbers
		for (i = 0; i < 10; i++)
		{
			rnd[i] = (rand() % operators);
			//Trying to avoid equal random numbers
			for (y = 0; y < i; y++)
			{
				if (rnd[i] == rnd[y])
				{
					i--;
					break;
				}
			}
		}

		printf("Which operator has the highest precedence?");
		for (i = 0; i <= level; i++)
		{
			printf("\n%d) %s", i+1, a[rnd[i]]);
		}
		printf("Answer: ");

		answer = -1;
		while ((answer < 1) && (answer > level))
		{
			answer = getch();
			if (answer == 27)	//Exit on escape
			{
				return 0;
			}
			answer -= 48;
			if (answer == 0)
			{
				return 0;
			}
		}

		if ((answer > 1) && (answer < level))
		{
			printf("%s\n", a[rnd[(answer - 1)]]);
			//Checking if the chosen random operator has a higher priority (lower number) than the other one
			if (rnd[(answer - 1)] < rnd[!(answer - 1)])
			{
				streak++;
				printf("CORRECT! :)                    STREAK = %d\n\n", streak);
			}
			else
			{
				printf("WRONG! :(                      STREAK = %d", streak);
				displayLine();
				printf("ADDITIONAL INFORMATION:\n");

				//Displaying operator predecence number
				printf("%d = \"%s\"\n%d = \"%s\"", rnd[0], a[rnd[0]], rnd[1], a[rnd[1]]);
				displayTip(rnd);
				displayLine();
				updateScore(streak);
				streak = 0;
				printf("Press any key to restart...");
				getch();
				system("cls");
				displayScore();
			}
		}
		else if (answer == 0)		//Exiting if user has typed in 0. Answer is -1 because we substracted 1 from it.
		{
			loop = 0;
		}
	}

	getch();
}

int updateScore(int scoreNew)
{
	FILE *scoreFile;

	if (scoreNew > score)
	{
		printf("\n>>>>>>>>>>>>> NEW HIGHSCORE! <<<<<<<<<<<<<\n");
		score = scoreNew;
		scoreFile = fopen("score", "w");
		if (scoreFile != NULL)
		{
			fprintf(scoreFile, "%d", scoreNew);
			fclose(scoreFile);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int getScore(void)
{
	FILE *scoreFile;
	int scoreRead;

	scoreFile = fopen("score", "r");
	if (scoreFile != NULL)
	{
		fscanf(scoreFile, "%d", &scoreRead);
		fclose(scoreFile);
		return scoreRead;
	}
	else
	{
		return 0;
	}

}

void displayTip(int *rnd)
{
	if (((rnd[0] == 0 || rnd[0] == 1) && (rnd[1] == 0 || rnd[1] == 1))
		|| ((rnd[0] == 18 || rnd[0] == 19 || rnd[0] == 20) && (rnd[1] == 18 || rnd[1] == 19 || rnd[1] == 20))
		|| ((rnd[0] == 21 || rnd[0] == 22) && (rnd[1] == 21 || rnd[1] == 22))
		|| ((rnd[0] == 23 || rnd[0] == 24) && (rnd[1] == 23 || rnd[1] == 24))
		|| ((rnd[0] == 25 || rnd[0] == 26) && (rnd[1] == 25 || rnd[1] == 26))
		|| ((rnd[0] == 27 || rnd[0] == 28) && (rnd[1] == 27 || rnd[1] == 28))
		|| ((rnd[0] == 29 || rnd[0] == 30) && (rnd[1] == 29 || rnd[1] == 30))
		)
	{
		printf("\nTIP: LEFT-TO-RIGHT\n");
	}
	else if (((rnd[0] == 7 || rnd[0] == 8) && (rnd[1] == 7 || rnd[1] == 8))
		|| ((rnd[0] == 9 || rnd[0] == 10) && (rnd[1] == 9 || rnd[1] == 10))
		|| ((rnd[0] == 11 || rnd[0] == 12) && (rnd[1] == 11 || rnd[1] == 12))
		|| ((rnd[0] == 38 || rnd[0] == 39) && (rnd[1] == 38 || rnd[1] == 39))
		|| ((rnd[0] == 39 || rnd[0] == 40 || rnd[0] == 41) && (rnd[1] == 39 || rnd[1] == 40 || rnd[1] == 41))
		|| ((rnd[0] == 42 || rnd[0] == 43) && (rnd[1] == 42 || rnd[1] == 43))
		|| ((rnd[0] == 44 || rnd[0] == 45 || rnd[0] == 46) && (rnd[1] == 44 || rnd[1] == 45 || rnd[1] == 46))
		)
	{
		printf("\nTIP: RIGHT-TO-LEFT\n");
	}
}

void displayLine(void)
{
	printf("\n__________________________________________\n");
}

void displayScore(void)
{
	printf("###########################################\n");
	printf("High Score = %d", score);
	printf("\n###########################################\n");
}