#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define DASH '_'

typedef struct Game
{
	int gameOver;  /* If the whole word has been guessed */
  int numRight;   /* Number of letters correctly guessed */
	char randomWord[80]; /* holds the word */
	int totalGuesses; /* hold the total number of guesses made correct & incorrect */
	char lettersGuessed[80];

}Game;

int selectWord(char letters []);
int compareChar(char input, char * originalWord, char guesses []);
int gameOver(int numRight, int wordLength, char letters []);
void printWelcomeMessages(int wordLength);
void printChar(char guesses [], int length);
void newGame(Game newGame, char letters []);
void printLettersGuessed( Game * game, int totalGuesses );
int contains( char * word, char * character );

int main(int argc, char * argv[]) 
{

  Game game = {FALSE, 0};
  char guesses[80];
  int wordLength;
  int dashes;
  int incorrectGuesses;
  int maxTries;

  while(game.gameOver == FALSE)
  {
    char * word;
    char * ptr;
   	wordLength = 0;
    dashes = 0;
    incorrectGuesses = 0;
    maxTries = 15;
	  wordLength = selectWord(game.randomWord);        /* Selecting random word */
	  word = game.randomWord;                          /* Assigning word  to the randomWord */
    ptr = strchr(word,'\n');                           /* Getting rid of the new line */ 
    *ptr = '\0';

    for (dashes = 0; dashes < wordLength; dashes ++)  /* For loop to print out the dashes */
    {
      guesses[dashes] = DASH;
    }
  
    printWelcomeMessages( wordLength );
	
    char input;
	
    while(game.gameOver == FALSE)
	  {
			
      printf("Number of guesses: %i\n",incorrectGuesses);
      printf("Number of tries left: %i\n",(maxTries - incorrectGuesses));
			printLettersGuessed( &game, game.totalGuesses );
		  printf( "Guess a letter: ");
			scanf( " %c", &input );

      if (input == '\n' || input == ' ')
      {
        input = getchar();
      }
			game.lettersGuessed[game.totalGuesses] = input;
			game.totalGuesses++;
      if (compareChar(input,word,guesses))
      {
        printf("\n\nYou guessed '%c' correctly\n\n",input);
      }
      else
      {
        printf("\n\nSorry, '%c' is not a letter in the word\n\n",input);
				incorrectGuesses++;
      }

      printChar(guesses,wordLength);
      if (!gameOver(game.numRight,wordLength,guesses))
      {
				system("clear");
        printf("Congratulations! You have correctly guessed '%s'!\n\n",guesses);
        break;
      }
      if (incorrectGuesses == maxTries)
      {
				system("clear");
        printf("GAME OVER!\nYou have failed to guess '%s'\n\n",word);
        break;
      }
      
	  }

    newGame(game,guesses);
  }
	return 0;
}

void printLettersGuessed( Game * game, int totalGuesses )
{
	if( totalGuesses == 0 ) { return; }

	printf("You have guessed the following letters: " );
	char * word = game -> randomWord;
	for( int i = 0; i < totalGuesses; i++ )
	{
		char * character = &(game -> lettersGuessed[i]);
		if( contains( word, character ) )
		{
			printf( "\x1b[32m %s \x1b[0m", character ); //print in green -- is correct
		}
		else
		{
			printf( "\x1b[31m %s \x1b[0m", character ); //print in green -- not correct
		}
	}
	printf( "\n" );
	
}

void newGame(Game newGame, char letters [])
{

  memset(&newGame,0,sizeof(Game));
  memset(letters,' ',80);
  newGame.numRight = 0;
  newGame.gameOver = FALSE;
	newGame.totalGuesses = 0;
  printf("Starting a new game...\n");
}

int gameOver(int numRight, int wordLength, char letters [])
{
  int index;
  numRight = 0;
  for (index = 0; index < wordLength; index++)
  {
    if (letters[index] != DASH)
      numRight++;
  }
  
  return (wordLength - numRight);
}

int contains( char * word, char * character )
{
	char * result = (char * ) strstr( word, character );

	if( result == NULL )
	{
		return 0;
	}
	return 1;
}

void printChar(char guesses [], int length)
{
  int i = 0;
  for ( i = 0; i < length; printf("%c ",guesses[i]), i++);
  puts("\n");
}

int compareChar(char input, char * originalWord, char guesses [])
{
  char * tempPtr = originalWord;
  int index = 0;
  int guess = FALSE;
  while (*tempPtr != '\n')
  {
    if (input == *tempPtr)
    {
      guess = TRUE;
      guesses[index] = *tempPtr;
    }
    tempPtr++;
    index++;
  }
  return guess;
}

void printWelcomeMessages(int wordLength)
{

  int dashes;
	printf("WELCOME TO HANGMAN\n");
	printf("\nSelecting a random word.");
	printf("\nYour word is %d characters long...Good Luck!", wordLength);
	puts("\n");

  for (dashes = 0; dashes < wordLength; dashes++)
  {
    printf("_ ");
  }
  puts("\n");
}

int selectWord( char letters[])
{
	FILE * fp = fopen("./words", "r" );
  char c;
  int index = 0;
	int lineCount = 235886; //number of words in local dictionary
	srand(time(NULL));
	int randomLine = rand() % lineCount; //random line
	while( index < randomLine )
	{
		index++;
		(void)fgets( letters, 80, fp );
	}
  index = 0;
  do {
    c = fgetc(fp);
    letters[index] = tolower(c);
    index++;
    } while (c != '\n');
	
  fclose(fp);
  return (index - 1);
}




