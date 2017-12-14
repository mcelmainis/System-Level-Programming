

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


// returns the number of spaces in the string
int countSpaces(char theString[]) {
  int i; 
  int count = 0; 
  for (i = 0; i < strlen(theString); i++) {
    if (theString[i] == ' ')
      count++;
  } // end for
  return count;
} // end countSpaces


/*
 * Splits a string into individual words.  
 * First parameter: a string.  Assumes that the words in the string are separated by
 *   single spaces, with no spaces before the first word or after the second word.  So
 *   the number of words is equal to the number of spaces plus 1.
 * Second parameter: the address of an integer in which the function will store the
 *   number of words in the string.
 * Return value: pointer to the beginning of an array of strings containing the individual
 * words from the sentence.  This function creates that array and the strings inside the array,
 * using space from the heap.  The strings are copies of words from the sentence, not pointers
 * into the sentence. These will be separate strings, not pointers into the sentence.
 */
char** splitString(char theString[], int *arraySize) {
  // the number of words in the string is one more than the number of spaces
  int numWords = countSpaces(theString)+1;
  char **wordArray = malloc(numWords * sizeof(char*));
  if (wordArray == NULL) {
    printf("Error: out of heap space\n");
    exit(1);
  } // end if

  int index = 0; 
  int wordNum = 0;
  while (theString[index] != '\0') { 
      int start = index;
      while (theString[index] != ' ' && theString[index] != '\0') 
	index++;
      int wordLength = index-start;
      char *newWord = malloc((wordLength+1)*sizeof(char));
      if (newWord == NULL) {
	printf("Error: out of heap space\n");
	exit(1);
      } // end if
      strncpy(newWord, &theString[start], wordLength);
      newWord[wordLength] = '\0';
      wordArray[wordNum] = newWord;
      wordNum++;
      
      // if we're not at the end  of a word we're at a space, so skip it
      if (theString[index] == ' ')
	index++;
  } // end while
  *arraySize = numWords;
  return wordArray;
} // end splitString

/* Cleans up the space used by an array of words.  
 * Parameters: array of words and its length
 * Assumes that the array of words and each individual word are
 * stored on the heap.
 */
void cleanup(char *words[], int numWords) {
  int i;
  for (i = 0; i < numWords; i++) {
    free(words[i]);
  }
  free(words);
} // end cleanup


 
