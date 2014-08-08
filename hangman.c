#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char * selectWord();
void printWelcomeMessages(int wordLength);
char printPrompt();

struct letter 
{
	char character;
	int beenGuessed;
};

int main(int argc, char * argv[]) 
{
	char * word;
	char * tempPtr;
	int wordLength = 0;
	word = selectWord();
	tempPtr = word;

	while( *tempPtr != 0 )
	{
		wordLength++;
		tempPtr++;
	}

	printWelcomeMessages( wordLength );

	char input;
	while( input != -1 )
	{
		printf( "Guess a letter: ");
		input = getchar();
	}
	

	return 0;
}

void printWelcomeMessages(int wordLength)
{
	system("clear");
	printf("WELCOME TO HANGMAN\n");
	printf("\nSelecting a random word.");
	printf("\nYour word is %d characters long...Good Luck!", wordLength);
	puts("\n");
}

char printPrompt()
{
	char input;
	printf("\nGuess a letter: ");
	scanf( "%c", &input );
	return input;
}

char * selectWord()
{
	FILE * fp = fopen("./words", "r" );
	char randomWord[80];
	int lineCount = 235886; //number of words in local dictionary
	srand(time(NULL));
	int randomLine = rand() % lineCount; //random line
	int index = 0;
	while( index < randomLine )
	{
		index++;
		fgets( randomWord, 80, fp );
	}


	fclose(fp);

	char * word = randomWord;
	return word;

}


