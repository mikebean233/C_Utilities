#ifndef STRINGUTILS_H
#define STRINGUTILS_H

int stringCompareIgnoreCase(char* a, char* b);
int stripNewLines(char* input);
char ** tokenize(char *input, int *tokenCount);
int countTokens(char* input);
char* stringCopy(char* input, int length);

#endif //STRINGUTILS_H
