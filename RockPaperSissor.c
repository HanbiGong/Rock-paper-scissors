#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

void displayMenu();
void gameInstructions();
int getUserChoice();
int getComputerChoice();
char *getCurrentTime(struct tm *t);

int main() {
    char menuChoice;
    char *roundsInput = malloc(sizeof(char) * 10);
    int rounds;
    int userChoice;
    int computerChoice;
    int userWins = 0;
    int computerWins = 0;
    int draws = 0;

    FILE *resultFile;

    struct tm *currentTime;
    time_t timer;

    timer = time(NULL);
    currentTime = localtime(&timer);

    printf("\n◎ Rock-Paper-Scissors Game\n");
    while(1) {
        displayMenu();
        scanf("%s", &menuChoice);

        printf("------------------------------------------------------------------------\n");

        if(menuChoice == '2') {
            printf("\n Exiting the game\n");
            exit(0);
        }
        else if(menuChoice == '1') {
            printf("\n Starting the game\n");

            while(1) {
                printf(" Enter the number of rounds (1 ~ 5) : ");
                scanf("%s", roundsInput);

                if(*roundsInput >= '1' && *roundsInput <= '5') {
                    rounds = atoi(roundsInput);

                    for(int i=0; i<rounds; i++) {
                        userChoice = getUserChoice();
                        computerChoice = getComputerChoice();

                        printf("\n Rock-Paper-Scissors!\n");

                        usleep(1000000); // 1 second delay (microseconds)

                        printf(" User : %d, Computer : %d\n", userChoice, computerChoice);

                        if(userChoice == 0) {
                            if(computerChoice == 0) {
                                printf(" = Draw!\n\n");
                                draws++;
                            }
                            else if(computerChoice == 1) {
                                printf(" = Computer wins!\n\n");
                                computerWins++;
                            }
                            else if(computerChoice == 2) {
                                printf(" = User wins!\n\n");
                                userWins++;
                            }
                        }
                        else if(userChoice == 1) {
                            if(computerChoice == 0) {
                                printf(" = User wins!\n\n");
                                userWins++;
                            }
                            else if(computerChoice == 1) {
                                printf(" = Draw!\n\n");
                                draws++;
                            }
                            else if(computerChoice == 2) {
                                printf(" = Computer wins!\n\n");
                                computerWins++;
                            }
                        }
                        else if(userChoice == 2) {
                            if(computerChoice == 0) {
                                printf(" = Computer wins!\n\n");
                                computerWins++;
                            }
                            else if(computerChoice == 1) {
                                printf(" = User wins!\n\n");
                                userWins++;
                            }
                            else if(computerChoice == 2) {
                                printf(" = Draw!\n\n");
                                draws++;
                            }
                        }
                        else {
                            printf(" Invalid input (Treated as computer win)\n\n");
                            computerWins++;
                        }

                        usleep(1000000);
                    }

                    printf(" Result : %d wins %d losses %d draws\n\n", userWins, computerWins, draws);

                    resultFile = fopen("Result_Save.txt", "a");
                    fprintf(resultFile, "%s %d wins %d losses %d draws\n\n", getCurrentTime(currentTime), userWins, computerWins, draws);

                    userWins = 0;
                    computerWins = 0;
                    draws = 0;

                    break;
                }
                else {
                    printf(" Please enter a number between 1 and 5\n\n");
                }
            }
        }
        else if(menuChoice == '3') {
            gameInstructions();
        }
        else {
            printf(" Please select a valid menu option\n\n\n");
        }
    }

    fclose(resultFile);

    return 0;
}

void displayMenu() {
    printf("------------------------------------------------------------------------\n");
    printf(" 1. Start game\n");
    printf(" 2. Exit game\n");
    printf(" 3. Game instructions\n");
    printf("------------------------------------------------------------------------\n");
    printf(" Enter the menu number : ");
}

void gameInstructions() {
    printf("------------------------------------------------------------------------\n");
    printf(" ※Game Instructions※\n\n");
    printf(" This is a game of Rock-Paper-Scissors between the user and the computer\n"); 
    printf(" After the game starts, the user can choose the number of rounds (up to 5)\n");
    printf(" The outcome can be win/lose/draw\n");
    printf(" If the user enters any other character or number besides 0, 1, or 2, it will be treated as a loss\n");
    printf(" After each round, the menu will be displayed again\n");
    printf(" If you want to continue the game, select 1. If you want to exit, select 2\n\n");
    printf("------------------------------------------------------------------------\n");
}

int getUserChoice() {
    int userChoice;

    printf("\n Please choose Rock(0), Paper(1), or Scissors(2) : ");
    scanf("%d", &userChoice);

    return userChoice;
}

int getComputerChoice() {
    srand(time(NULL));
    int computerChoice;

    computerChoice = rand() % 3;

    return computerChoice;
}

char *getCurrentTime(struct tm *t) {
    static char timeStr[20];

    sprintf(timeStr, "%04d-%02d-%02d %02d:%02d:%02d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    return timeStr;
}
