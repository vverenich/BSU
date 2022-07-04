/* main.c */
#include <stdio.h>
#include <string.h>

int getCountOfParticularCharInWord (char requiredChar, char *word){
  int length = strlen(word);
  int count  = 0;
  
  for (int i = 0; i < length; ++i){
    if(word[i] == requiredChar ){
      ++count;
    }
  }
  
  return count;
}

int main (int argc, char *argv[])
{
  
  if (argc < 3){
    return 0;
  }

  char requiredSymbol = argv[1][0];
  int numberOfWords   = argc - 2;
  
  int count = 0;
  for(int i = 0; i < numberOfWords; ++i){
    count += getCountOfParticularCharInWord(requiredSymbol, argv[i+2]); 
  }
  
	printf ("The count of symbol %c is %d", requiredSymbol, count);
  
  return 0;
}
