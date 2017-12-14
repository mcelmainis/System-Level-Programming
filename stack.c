#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Parameter: a stack
 * Returns TRUE if the stack is empty and FALSE if it's not.
 * Does not change the stack.
 */
int isEmpty(Stack *stack) {
  return (stack == NULL); 
} // isEmpty

/* 
 * This function pushes an integer onto the top of a stack.
 * Parameters: 
 *    1. a stack (NULL or a pointer to the top node)
 *    2. an integer value to push onto the top of the stack
 * Returns a pointer to the start of the modified stack.
 */
Stack *pushInt(Stack *stack, int value) {
  Stack *newFirstNode = malloc(sizeof(Stack));
  newFirstNode->intTop = TRUE;
  newFirstNode->data.intValue = value;
  newFirstNode->next = stack;
  return newTopNode;
} // end pushInt

/*
 * Parameter: a stack
 * Prints the stack to the standard output from top to bottom, 
 * in a format like this: 
 *    [1,2,"apple","computer",17,"Queens"]
 * The values are enclosed in square brackets and separated
 * by commas, with no spaces.  There are quotes around the 
 * string values so that the user can tell the difference between
 * the number 42 and the string "42".
 * The stack is printed on one line, followed by an end-of-line
 * character.  If the stack is empty the output is "[]", followed 
 * by an end of line character.
 */
void printStack(Stack *stack) {
  Stack *node = stack;
  printf("[");
  int first = TRUE;
  while (node != NULL) {
    if (!first)
      printf(",");
    if (node->intTop)
      printf("%d", node->data.intValue);
    else
      printf("\"%s\"", node->data.stringValue);
    first = FALSE;
    node = node->next;
  } // end while
  printf("]\n");
} // end printList


/*
 * This function pushes a string onto the top of a stack.
 * Parameters: 
 *    1. a stack (NULL or a pointer to the top node)
 *    2. a string value to push onto the top of the stack
 * Returns a pointer to the start of the modified stack.
 * The string is copied into the stack; the stack will not
 * contain a pointer to the original parameter.
 */
Stack *pushString(Stack *stack, char *value) {
  Stack *newTopNode = malloc(sizeof(Stack));
  newTopNode->intTop = FALSE;
  strncpy(newTopNode->data.stringValue, value, MAX_STRING_LENGTH);
  newTopNode->data.stringValue[MAX_STRING_LENGTH-1] = '\0';
  newTopNode->next = stack;
  return newTopNode; 
} // end pushString


/*
 * Takes a stack as a parameter and returns TRUE
 * if its top element is an integer, false if 
 * it's a string.
 */
int topIsInt(Stack *stack) {
  return stack->intTop; 
}

/*
 * This function returns the value of the "top" element of a 
 * stack if that value is an integer.  Does not change the stack.
 * If this function is called when the stack is empty or when the
 * top element is a string, it writes an error message and returns
 * 0.
 */
int topInt(Stack *stack) {
  if (isEmpty(stack)) {
    fprintf(stderr, "ERROR: topInt called with empty stack\n");
    return 0;
  }
  else if (!stack->intTop) {
    fprintf(stderr, "ERROR: topInt called when top element is a string\n");
    return 0;
  }
  else {
    return stack->data.intValue;
  } // end if
} // end topInt

/*
 * This function copies the "top" string of a stack into a 
 * string supplied by the caller.  The supplied string MUST
 * have enough room for MAX_STRING_LEN characters plus the
 * ending '\0'.  Does not change the stack. 
 * 
 * If this function is called when the stack is empty or when
 * the top element is an integer, it writes an error message and
 * puts an empty string into the result parameter.
 */
void topString(Stack *stack, char *result) {
  if (isEmpty(stack)) {
    fprintf(stderr, "ERROR: topString called with empty stack\n");
  }
  else if (stack->intTop) {
    fprintf(stderr, "ERROR: topString called when top element ");
    fprintf(stderr, "is an int\n");
    result[0] = '\0'; // result is empty string
  }
  else {
    strcpy(result, stack->data.stringValue);
  } // end if
} // end topString

/* 
 * This function "pops" the top value off of a stack and returns
 * the modified stack.  If called for an empty stack, writes an 
 * error message and returns the empty stack without changing it.
 * Besides changing the stack, it frees the heap space used by
 * the popped element.
 */
Stack* pop(Stack *stack) {
  if (stack == NULL) {
    fprintf(stderr, "ERROR: trying to pop from empty stack\n");
    fprintf(stderr, "Stack not changed\n");
    return NULL;
  }
  else {
    Stack *second = stack->next; // the new top node
    stack->next = NULL;
    free(stack);
    return second;
  } // end if  
} // end pop

/*
 * This function returns the number of integers in a stack.
 */
int countInts(Stack *stack) {
  int count = 0;
  Stack *currentNode = stack;
  while (currentNode != NULL) {
    if (currentNode->intTop) 
      count++;
    currentNode = currentNode->next;
  }
  return count; 
} // end countInts

/*
 * This function returns the number of strings in a stack.
 */
int countStrings(Stack *stack) {
  int count = 0;
  Stack *currentNode = stack;
  while (currentNode != NULL) {
    if (!currentNode->intTop) 
      count++;
    currentNode = currentNode->next;
  }
  return count; 
} // end countStrings

