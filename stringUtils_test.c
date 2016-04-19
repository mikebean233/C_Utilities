#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringUtils.h"

#define LESS             0x01
#define LESS_OR_EQUAL    0x02
#define GREATER          0x04
#define GREATER_OR_EQUAL 0x08
#define EQUAL            0x0F

#define TRUE             0x01
#define FALSE            0x00

// status flags
#define FAILURE          0x0
#define SUCCESS          0x1


int status;
void testStringCompareIgnoreCase(char* inputA, char* inputB, int flags, int value);
void testTokenize(char* input, char** result, int tokenCountTarget);
void testCountTokens(char* input, int targetCount);


int main(){

    /* test stringCompareIgnoreCase */
    status = SUCCESS;
    printf("======== testing stringCompareIgnoreCase() ======\n");
    testStringCompareIgnoreCase("abcde", "ABCDE", EQUAL,   0);
    testStringCompareIgnoreCase("a",     "a",     EQUAL,   0);
    testStringCompareIgnoreCase("b",     "a",     GREATER, 0);
    testStringCompareIgnoreCase("aaaa",  "a",     GREATER, 0);
    testStringCompareIgnoreCase("a",     "aaaa",  LESS,    0);

    if(status == SUCCESS)
        printf("PASSED\n");

    /* test countTokens() */
    printf("========= testing countTokens() =========\n");
    status = SUCCESS;

    testCountTokens("", 0);
    testCountTokens("  ", 0);
    testCountTokens(" \n ", 0);
    testCountTokens("a", 1);
    testCountTokens(" a ", 1);
    testCountTokens("a b", 2);
    testCountTokens("one two three", 3);
    testCountTokens("a.s  ... # 5 )", 5);

    if(status == SUCCESS)
        printf("PASSED\n");
    else
        exit(1);


    /* test tokenize() */
    status = SUCCESS;
    printf("======== testing tokenize() ========\n");

    char* expectedResults[10];

    expectedResults[0] = "one";
    expectedResults[1] = "two";
    expectedResults[2] = "three";
    expectedResults[3] = "four";
    testTokenize("one two three four", expectedResults, 4);

    expectedResults[0] = "...sdf";
    expectedResults[1] = "a.a";
    expectedResults[2] = "123";
    testTokenize(" ...sdf    a.a 123 ", expectedResults, 3);


    if(status == SUCCESS)
        printf("PASSED\n");

}

void testStringCompareIgnoreCase(char* inputA, char* inputB, int flags, int value){
    int result = stringCompareIgnoreCase(inputA, inputB);

    if(
        (flags == LESS             && result >= value) ||
        (flags == GREATER          && result <= value) ||
        (flags == LESS_OR_EQUAL    && result >  value) ||
        (flags == GREATER_OR_EQUAL && result <  value) ||
        (flags == EQUAL            && result != value)) {
        fprintf(stderr, "TEST FAILED: stringCompareIgnoreCase(%s,%s) returned %d\n", inputA, inputB, result);
        status = FAILURE;
    }
}

void testTokenize(char* input, char** targetResult, int tokenCountTarget){
    int tokenCount = 0;
    int haveCorrectResult = TRUE;
    testCountTokens(input, tokenCountTarget);
    if(status != SUCCESS)
        return;

    char **thisResult = tokenize(input, &tokenCount);

    int i = 0;
    for (; i < tokenCount; ++i)
        if ( strcmp(targetResult[i], thisResult[i])) {
            haveCorrectResult = FALSE;
            break;
        }

    if(!haveCorrectResult) {
        status = FAILURE;
        fprintf(stderr, "TEST FAILED: tokenize(%s,...) produced the wrong tokens:\n", input);
        int correctTokenIndex = 0;
        int incorrectTokenIndex = 0;

        fprintf(stderr, "Tokens should be: \n");
        for (; correctTokenIndex < tokenCountTarget; ++correctTokenIndex) {
            fprintf(stderr, "correctToken[%d] = \"%s\"\n", correctTokenIndex, targetResult[correctTokenIndex]);
        }

        fprintf(stderr, "Produced Tokens: \n");
        for (; incorrectTokenIndex < tokenCount; ++incorrectTokenIndex) {
            fprintf(stderr, "producedToken[%d] = \"%s\"\n", incorrectTokenIndex, thisResult[incorrectTokenIndex]);
        }
    }

    for(i = 0; i < tokenCount; ++i){
        free(thisResult[i]);
    }
    free(thisResult);
}

void testCountTokens(char* input, int targetCount){
    if(countTokens(input) != targetCount){
        int result = countTokens(input);
        fprintf(stderr, "TEST FAILED: countTokens(\"%s\") returned %d\n", input, result);
        status = FAILURE;
    }
}





