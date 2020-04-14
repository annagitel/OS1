.PHONY: all
all: task1 task2 task3 lib

task1: hello_Ariel.c hello_Ariel.h main1_1.c
	gcc -o hello1 hello_Ariel.c main1_1.c

task2: hello_Ariel.h main1_2.c lib
	gcc main1_2.c ./libHello.so -o hello2

lib: hello_Ariel.h hello_Ariel.c
	gcc -shared hello_Ariel.c -fPIC -o libHello.so

task3:  hello_Ariel.h main1_3.c lib
	gcc main1_3.c -ldl -o hello3

.PHONY: clean
clean:
	-rm *.o hello1 hello2 hello3 *.so
