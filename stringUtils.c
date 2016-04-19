#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "stringutils.h"


int stringCompareIgnoreCase(char *a, char *b) {
    int aLength = strlen(a);
    int bLength = strlen(b);

    int maxLength = (aLength > bLength) ? aLength : bLength;

    int i;
    for (i = 0; i < maxLength; ++i) {

        if (i > aLength)
            return -1;
        if (i > bLength)
            return 1;

        char aChar = tolower(a[i]);
        char bChar = tolower(b[i]);

        if (aChar > bChar)
            return 1;
        if (bChar > aChar)
            return -1;
    }
    return 0;
}

int stripNewLines(char* input){
    int length = strlen(input);
    int i = 0;
    for(; i < length; ++i){
        if(input[i] == '\n'){
            input[i] = '\0';
            return 1;
        }
    }
    return 0;
}

int countTokens(char* input){
    int length = strlen(input);
    char leadChar, followChar;
    int tokenCount = 0;

    int i = 0;
    for(; i <= length; ++i){
        leadChar   = input[i + 1];
        followChar = input[i];

        int leadOnToken   = !isspace((int)leadChar)   && leadChar != '\0';
        int followOnToken = !isspace((int)followChar) && followChar != '\0';

        // we are just stepping onto a token
        if(!followOnToken && leadOnToken){
            // do nothing
        }

        // we are in the middle of a token
        if(followOnToken && leadOnToken){
            // do nothing
        }

        // we are stepping off of a token
        if(followOnToken && !leadOnToken){
            ++ tokenCount;
        }

        // we are not touching a token
        if(!followOnToken && !leadOnToken){
            // do nothing
        }
    }
    return tokenCount;
}

/*
 * input[in]       : The string to be tokenized
 * tokenCount[out] : The number of tokens found in the string
 */
char ** tokenize(char *input, int *tokenCount){
    if(input == NULL)
        fprintf(stderr, "Error: tokenize() received a NULL pointer for input\n");

    if(tokenCount == NULL)
        fprintf(stderr, "Error: tokenize() received a NULL pointer for tokenCount\n");

    if(!((int)input | (int)tokenCount))
        return NULL;

    (*tokenCount) = countTokens(input);

    char** output = (char**) calloc(sizeof(char*), *tokenCount);
    if(output == NULL){
        fprintf(stderr, "Error: stringCopy was unable to allocate memory using calloc()\n");
        return NULL;
    }

    int length = strlen(input);
    int currentTokenLength = 0;
    int tokenIndex = 0;
    char leadChar, followChar;

    int i;
    for(i = 0; i <= length; ++i){
        leadChar   = input[i + 1];
        followChar = input[i];

        int leadOnToken   = !isspace((int)leadChar)   && leadChar != '\0';
        int followOnToken = !isspace((int)followChar) && followChar != '\0';

        // we are just stepping onto a token
        if(!followOnToken && leadOnToken){
            // do nothing
        }

        // we are in the middle of a token
        if(followOnToken && leadOnToken){
            ++currentTokenLength;
        }

        // we are stepping off of a token
        if(followOnToken && !leadOnToken){
            ++currentTokenLength;
            char* tokenStartPos = input + (i - (currentTokenLength - 1));

            // make a dynamic copy of this token
            char* thisToken = stringCopy(tokenStartPos, currentTokenLength);

            output[tokenIndex++] = thisToken;

            currentTokenLength = 0;
        }

        // we are not touching a token
        if(!followOnToken && !leadOnToken){
        }
    }
    return output;
}

char* stringCopy(char* input, int length){
    if(length == 0 || input == NULL)
        return NULL;

    char* output = (char*)calloc(sizeof(char), (length + 1));
    if(output == NULL){
        fprintf(stderr, "Error: stringCopy was unable to allocate memory using calloc()\n");
        return NULL;
    }

    int i = 0;
    for(; i < length; ++i){
        output[i] = input[i];
    }
    output[i] = '\0';
    return output;
}