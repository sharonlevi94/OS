/*
 * ex2b.c
 *
 *  Created on: Nov 24, 2020
 *      Author: sharonlevi
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

//-----------------------
void do_dad(int num,pid_t status);
void do_son(int num);
void terminate ();
void catch_sigusr1(int sig_num);

//-------------------------
int main () {
	signal(SIGUSR1,catch_sigusr1);

	srand(17);
	int num=0;
	pid_t status;
	status=fork();

	if(status<0)
		terminate();

	if(status>0)
		do_dad(num,status);
	else
		do_son(num);

	return EXIT_SUCCESS;
}

//===============================================
void terminate(){
	perror ("error in fork()");
			exit(EXIT_FAILURE);
}
//--------------------------------------
void do_dad (int num,pid_t son_pid){
	while(1) {
		num = rand()%10;
		if(num<3) {
			printf ("proccess %d ends\n",getpid());
			exit(EXIT_SUCCESS);
		}
		else {
		kill(son_pid,SIGUSR1); //send signal to son
		alarm(5); //wait 5 sec to signal
				printf("process %d has a partner\n",getpid());
		}

	}
}
//--------------------------------------
void do_son (int num){
	while(1) {
		num = rand()%10;
		if(num<3) {
			printf ("proccess %d ends\n",getpid());
			exit(EXIT_SUCCESS);
		}
		else {
			kill(getppid(),SIGUSR1); //send signal to dad
			alarm(5); //wait 5 sec to signal
					printf("process %d has a partner\n",getpid());
		}
	}
}
//--------------------------------------
void catch_sigusr1(int sig_num){
	printf("process %d was left alone, and quits\n", getpid());
		exit (EXIT_SUCCESS);
}
//--------------------------------------
