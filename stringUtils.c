#include <string.h>
#include <ctype.h>
#include"stringutils.h"


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
    int newLineCount = 0;
    for(; i < length; ++i){
        if(input[i] == '\n'){
            input[i] = '\0';
            return 1;
        }
    }
    return 0;
}
