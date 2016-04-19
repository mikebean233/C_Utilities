stringUtils_test: stringUtils_test.c stringUtils.o
	gcc -o stringUtils_test stringUtils_test.c stringUtils.o

stringUtils.o: stringUtils.c
	gcc -o stringUtils.o -c stringUtils.c