#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Constants for game logic 
#define COOPERATE 0
#define DEFECT 1

// Global variables
int rounds; 

// Function declarations 
void referee(int p1_write[], int p1_read[], int p2_write[], int p2_read[]){
	// create varibles to store the score for each player with intial value 0
	int p1_score = 0, p2_score = 0;

	// variables to keep track of each player's choice 
	int p1_choice, p2_choice; 

	printf("Referee: Starting the game.\n");

	// Notify the players of the start of the game 
	write(p1_write[1], "READY", 5); 
	write(p2_write[1], "READY", 5);

	// Check for the respond of each player 
	char buffer[6]; 
	read(p1_read[0], buffer, 5); 
	buffer[5] = '\0';
	read(p2_read[0], buffer, 5); 
	buffer[5] = '\0'; 

	// start the game 
	for (int i = 0; i < rounds; i++){
		printf("\nReferee: Round %d - Players, make your choice.\n", i+1);

		// Notify the players to make a choice
		write(p1_write[1], "GO", 2);
		write(p2_write[1], "GO", 2);

		// Read the players choices 
		read(p1_read[0], &p1_choice, sizeof(int));
		read(p2_read[0], &p2_choice, sizeof(int));

		// Determine the score 
		if (p1_choice == COOPERATE && p2_choice == COOPERATE){
			p1_score += 3; 
			p2_score += 3;
		} else if (p1_choice == COOPERATE && p2_choice == DEFECT){
			p1_score += 0; 
			p2_score += 5;
		} else if (p1_choice == DEFECT && p2_choice == COOPERATE){
			p1_score += 5;
			p2_score += 0;
		} else if (p1_choice == DEFECT && p2_choice == DEFECT){
			p1_score += 1; 
			p2_score += 1; 
		}

		// output the players' choice and their score for that round to the user
		printf("Referee: Round %d - Player 1 chose %s, Player 2 chose %s.\n",
				i+1, 
				p1_choice == COOPERATE ? "COOPERATE" : "DEFECT", 
				p2_choice == COOPERATE ? "COOPERATE" : "DEFECT"); 
		printf("Referee: Current Scores - Player 1: %d, Player 2: %d.\n", p1_score, p2_score);
		
		// update the players of their score 
		write(p1_write[1], &p1_score, sizeof(int)); 
		write(p2_write[1], &p2_score, sizeof(int));
	} 

	// finalsteps: 
	// tell the players to quit 
	write(p1_write[1], "END", 3);
	write(p2_write[1], "END", 3);

	// Report the final score 
	printf("\nReferee: Game over. Final Scores - Player 1: %d, Player 2: %d.\n", p1_score, p2_score);
}


void player(int read_pipe[], int write_pipe[], const char* name){
	char buffer[6];
	int score = 0, choice; 

	// Wait for the readiness signal from the referee
	read(read_pipe[0], buffer, 5); 
	buffer[5] = '\0'; 
	printf("%s: Received '%s'. Getting ready...\n", name, buffer);

	write(write_pipe[1], "READY", 5);

	while (1)
	{
		read(read_pipe[0], buffer, 2); 
		buffer[2] = '\0';
		if (strcmp(buffer, "GO") == 0){
			//make a choice
			choice = rand() % 2; 
			write(write_pipe[1], &choice, sizeof(int));
		} else if (strcmp(buffer, "END") == 0){
			printf("%s: Exiting.\n", name);
			break;
		} else {
			read(read_pipe[0], &score, sizeof(int));
			printf("%s: Current score: %d.\n", name, score);
		}
	}
	

}

// the main method
int main(){
	
	// local variables
	int p1_write[2], p1_read[2]; //pipe fpr player 1
	int p2_write[2], p2_read[2]; // pipe fpr player 2

	if (pipe(p1_write) == -1 || pipe(p1_read) == -1 || 
	pipe(p2_write) == -1 || pipe(p2_read)){
		perror("one of the pipes was unsuccessful!");
		exit(1);
	}
	

	// userinput prompt for the number of the rounds 
	printf("Please enter the number of the rounds: ");
	
	// save the userinput into the global variable rounds
	scanf("%d", &rounds);

	// Create child processes to act as the players
	pid_t pid1 = fork();

	// check to make sure the child process was successfully created. 
	if (pid1 < 0){
		perror("fork(): the creation of the first child process was unsuccessful!"); 
		exit(1);
	}

	// Create the second child process 
	pid_t pid2 = fork();

	if (pid2 < 0){
	
		perror("fork(): the creation of the second child process was unsuccessful!"); 
		exit(1);
	}

	// Player 1 process
	if (pid1 == 0){
		close(p1_write[0]);
		close(p1_read[1]);
		player(p1_read, p1_write, "Player 1");
		exit(0);	
	}

	// Player 2 process
	if (pid2 == 0){
		close(p2_write[0]);
		close(p2_read[1]);
		player(p2_read, p2_write, "Player 2");
		exit(0);
	}

	
	// Referee process
	close(p1_write[0]);
	close(p1_read[1]);
	close(p2_write[0]);
	close(p2_read[1]);
	referee(p1_read, p1_write, p2_read, p2_write);

	//wait for the players to finish
	wait(NULL);
	wait(NULL);

	return 0; 
}
