#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char * selectWord();

int main() 
{

  char discoveredLetters[] = "hello";
  char * word;
  char * tempPtr;
  selectWord(word);
  printf( "%c\n", *word );
  
}

char * selectWord()
{
  FILE * fp = fopen("words", "r" );
  static char * ch;
  int lineCount = 235886;
  srand(time(NULL));
  int wordLineNumber = rand() %lineCount;
  int index = 0;
  while( index < wordLineNumber )
  {
    index++;
    fgets( ch, 80, fp );
  }

  
  fclose(fp);

}


