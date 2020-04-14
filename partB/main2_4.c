#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <syslog.h>
#include <sched.h>
#define _GNU_SOURCE
#define STACK_SIZE 10000
#define CYCLES 1000

char child_stack[STACK_SIZE+1];

void print1(const char *text){
	int i;
	for(i=1; i<20;i++){
		printf("Hello from %s\n", text);
		usleep(10);
	}
}

void print2(const char *text){
	int i;	
	for(i = 0; i < CYCLES; i++){
		printf("Hello from %s \n", text);
		sleep(10);
	}
}

int child(void *params){
	print2("child_thread");
}



int main(){
/*************************************************************task1****************************************************/
	pid_t pid = fork();
	
	if(pid == 0){
		pid_t pid = fork();

		if(pid == 0){
		
			print1("grand child");
			
			char * args[2] = {"./friend", NULL};
			execvp(args[0], args);
		}
		else{
			print1("child");
		}
	}
	else{
		print1("parent");
	}
	
/*************************************************************task2****************************************************/
	int result = clone(child, child_stack+STACK_SIZE, 0, 0);
	printf("clone result = %d \n", result);
	print2("parent");

/*************************************************************task3****************************************************/
	pid_t pidd = fork();
	
	if(pidd == 0){
		chdir("/");
		setsid();
		printf("starting my daemon\n");
		close(stdout);
		close(stdin);
		close(stderr);
		openlog("myDaemon", LOG_PID, LOG_DAEMON);
		syslog(LOG_NOTICE, "daemon started");
		sleep(3);
		syslog(LOG_NOTICE, "doing some work...");
		sleep(3);
		syslog(LOG_NOTICE, "daemon finished!");
	}
	else{
		printf("daemon PID %d\n", pidd);
	}

	return 0;
}
