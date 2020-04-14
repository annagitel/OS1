#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void print(const char *text){
	int i;
	for(i=1; i<20;i++){
		printf("Hello from %s\n", text);
		usleep(10);
	}
}

int main(){

	pid_t pid = fork();
	
	if(pid == 0){
		pid_t pid = fork();

		if(pid == 0){
		
			print("grand child");
			
			char * args[2] = {"./friend", NULL};
			execvp(args[0], args);
		}
		else{
			print("child");
		}
	}
	else{
		print("parent");
	}
	
	return 0;
}
