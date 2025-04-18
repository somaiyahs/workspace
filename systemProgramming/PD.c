#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Constants for game logic
#define COOPERATE 0
#define DEFECT 1
#define ROUNDS 5

// Function declarations
void referee(int p1_write[], int p1_read[], int p2_write[], int p2_read[]);
void player(int read_pipe[], int write_pipe[], const char* name);

int main() {
    int p1_write[2], p1_read[2]; // Pipes for player 1
    int p2_write[2], p2_read[2]; // Pipes for player 2

    if (pipe(p1_write) == -1 || pipe(p1_read) == -1 ||
        pipe(p2_write) == -1 || pipe(p2_read) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        // Player 1 process
        close(p1_write[0]);
        close(p1_read[1]);
        player(p1_read, p1_write, "Player 1");
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        // Player 2 process
        close(p2_write[0]);
        close(p2_read[1]);
        player(p2_read, p2_write, "Player 2");
        exit(0);
    }

    // Referee process
    close(p1_write[1]);
    close(p1_read[0]);
    close(p2_write[1]);
    close(p2_read[0]);
    referee(p1_write, p1_read, p2_write, p2_read);

    // Wait for players to finish
    wait(NULL);
    wait(NULL);

    return 0;
}

void referee(int p1_write[], int p1_read[], int p2_write[], int p2_read[]) {
    int rounds = ROUNDS;
    int p1_score = 0, p2_score = 0;
    int p1_choice, p2_choice;

    printf("Referee: Starting the game with %d rounds.\n", rounds);

    // Signal players to get ready
    write(p1_write[1], "READY", 5);
    write(p2_write[1], "READY", 5);

    char buffer[6];
    read(p1_read[0], buffer, 5); buffer[5] = '\0';
    read(p2_read[0], buffer, 5); buffer[5] = '\0';

    for (int i = 0; i < rounds; ++i) {
        printf("\nReferee: Round %d - Players, make your choices.\n", i + 1);

        // Notify players to make a choice
        write(p1_write[1], "GO", 2);
        write(p2_write[1], "GO", 2);

        // Read players' choices
        read(p1_read[0], &p1_choice, sizeof(int));
        read(p2_read[0], &p2_choice, sizeof(int));

        // Determine scores
        if (p1_choice == COOPERATE && p2_choice == COOPERATE) {
            p1_score += 3; p2_score += 3;
        } else if (p1_choice == COOPERATE && p2_choice == DEFECT) {
            p1_score += 0; p2_score += 5;
        } else if (p1_choice == DEFECT && p2_choice == COOPERATE) {
            p1_score += 5; p2_score += 0;
        } else if (p1_choice == DEFECT && p2_choice == DEFECT) {
            p1_score += 1; p2_score += 1;
        }

        // Send updated scores to players
        write(p1_write[1], &p1_score, sizeof(int));
        write(p2_write[1], &p2_score, sizeof(int));

        printf("Referee: Round %d - Player 1 chose %s, Player 2 chose %s.\n",
               i + 1,
               p1_choice == COOPERATE ? "COOPERATE" : "DEFECT",
               p2_choice == COOPERATE ? "COOPERATE" : "DEFECT");
        printf("Referee: Current Scores - Player 1: %d, Player 2: %d.\n",
               p1_score, p2_score);
    }

    // End game
    write(p1_write[1], "END", 3);
    write(p2_write[1], "END", 3);

    printf("\nReferee: Game over. Final Scores - Player 1: %d, Player 2: %d.\n", p1_score, p2_score);
}

void player(int read_pipe[], int write_pipe[], const char* name) {
    char buffer[6];
    int score = 0, choice;

    // Wait for readiness signal
    read(read_pipe[0], buffer, 5); buffer[5] = '\0';
    printf("%s: Received '%s'. Getting ready...\n", name, buffer);

    write(write_pipe[1], "READY", 5);

    while (1) {
        read(read_pipe[0], buffer, 2); buffer[2] = '\0';
        if (strcmp(buffer, "GO") == 0) {
            // Make a choice (COOPERATE or DEFECT)
            choice = rand() % 2; // Random choice for demonstration
            write(write_pipe[1], &choice, sizeof(int));
        } else if (strcmp(buffer, "END") == 0) {
            printf("%s: Game over. Exiting.\n", name);
            break;
        } else {
            read(read_pipe[0], &score, sizeof(int));
            printf("%s: Current Score: %d.\n", name, score);
        }
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void referee(int p1_write, int p1_read, int p2_write, int p2_read, int rounds) {
    char buffer[10];
    int score1 = 0, score2 = 0;

    // Signal players to get ready
    write(p1_write, "ready", 5);
    write(p2_write, "ready", 5);

    // Wait for players' readiness
    read(p1_read, buffer, sizeof(buffer));
    read(p2_read, buffer, sizeof(buffer));

    printf("Referee: Both players are ready!\n");

    for (int round = 1; round <= rounds; ++round) {
        printf("\n--- Round %d ---\n", round);

        // Ask players for their choices
        write(p1_write, "choice", 6);
        write(p2_write, "choice", 6);

        // Read players' choices
        char choice1, choice2;
        read(p1_read, &choice1, 1);
        read(p2_read, &choice2, 1);

        printf("Player 1 chose: %c\n", choice1);
        printf("Player 2 chose: %c\n", choice2);

        // Calculate scores
        if (choice1 == 'C' && choice2 == 'C') {
            score1 += 3;
            score2 += 3;
        } else if (choice1 == 'C' && choice2 == 'D') {
            score2 += 5;
        } else if (choice1 == 'D' && choice2 == 'C') {
            score1 += 5;
        } else if (choice1 == 'D' && choice2 == 'D') {
            score1 += 1;
            score2 += 1;
        }

        // Report scores
        printf("Scores: Player 1 = %d, Player 2 = %d\n", score1, score2);

        // Update players
        write(p1_write, &score1, sizeof(int));
        write(p2_write, &score2, sizeof(int));
    }

    // End the game
    write(p1_write, "quit", 4);
    write(p2_write, "quit", 4);

    // Output final scores
    printf("\n--- Game Over ---\n");
    printf("Final Scores: Player 1 = %d, Player 2 = %d\n", score1, score2);
}

void player(int write_fd, int read_fd, int player_id) {
    char buffer[10];
    int score = 0;

    // Wait for referee's readiness signal
    read(read_fd, buffer, sizeof(buffer));
    printf("Player %d: Ready!\n", player_id);

    // Notify referee of readiness
    write(write_fd, "ready", 5);

    while (1) {
        // Wait for referee's message
        read(read_fd, buffer, sizeof(buffer));

        if (strcmp(buffer, "choice") == 0) {
            // Make a choice (C or D)
            char choice = (rand() % 2 == 0) ? 'C' : 'D';
            write(write_fd, &choice, 1);
        } else if (strcmp(buffer, "quit") == 0) {
            break;
        } else {
            // Update score
            read(read_fd, &score, sizeof(int));
            printf("Player %d: My current score is %d\n", player_id, score);
        }
    }

    printf("Player %d: Exiting...\n", player_id);
}

int main() {
    int p1_fd[2][2]; // Pipes for Player 1
    int p2_fd[2][2]; // Pipes for Player 2

    pipe(p1_fd[0]); // Referee -> Player 1
    pipe(p1_fd[1]); // Player 1 -> Referee

    pipe(p2_fd[0]); // Referee -> Player 2
    pipe(p2_fd[1]); // Player 2 -> Referee

    int rounds;
    printf("Enter the number of rounds: ");
    scanf("%d", &rounds);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Player 1
        close(p1_fd[0][1]);
        close(p1_fd[1][0]);
        player(p1_fd[1][1], p1_fd[0][0], 1);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Player 2
        close(p2_fd[0][1]);
        close(p2_fd[1][0]);
        player(p2_fd[1][1], p2_fd[0][0], 2);
        exit(0);
    }

    // Referee
    close(p1_fd[0][0]);
    close(p1_fd[1][1]);
    close(p2_fd[0][0]);
    close(p2_fd[1][1]);
    referee(p1_fd[0][1], p1_fd[1][0], p2_fd[0][1], p2_fd[1][0], rounds);

    // Wait for players to finish
    wait(NULL);
    wait(NULL);

    return 0;
}





