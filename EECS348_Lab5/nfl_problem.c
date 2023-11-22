#include <stdio.h>

/* Lists how points can be scored. */
int scoringPlays[] = {8, 7, 6, 3, 2};
/* Array that lists the possible socring combination. */
char playDescriptions[][20] = {"TD + 2pt","TD + FG", "TD", "3pt FG", "Safety"};

/* Prints a combination of scoring plays. */
void printCombination(int plays[], int playCounts[]) {
    int first = 1;
    for (int i = 0; i < 5; i++) {
        if (playCounts[i] >= 0) {
            if (!first) {
                printf(", ");
            }
            printf("%d %s", playCounts[i], playDescriptions[i]);
            first = 0;
        }
    }
    printf(".\n");
}

/* Goes through all possible combinations of scoring plays. */
void findCombinations(int score, int plays[], int playCounts[], int currentPlay) {
    if (score == 0) {
        printCombination(plays, playCounts);
        return;
    }
    if (currentPlay == 5) {
        return;
    }

    for (int i = 0; i <= score / scoringPlays[currentPlay]; i++) {
        playCounts[currentPlay] = i;
        findCombinations(score - i * scoringPlays[currentPlay], plays, playCounts, currentPlay + 1);
    }
    playCounts[currentPlay] = 0;
}

/* The function that is called when program is executed. */
int main() {
    int score;
	/* The following defines a loop that repeatedlty prompts the user for a score. */ 
    while (1) {
        printf("Enter score (enter a value <= 1 to end program):  ");
        scanf("%d", &score);
		/* If the score entered is less than one, end program. */
        if (score <= 1) {
            break;
        }

		/* Keeps the scoring plays for a single combination. */ 
        int plays[10]; 
		/* Keeps track of the number for each specific score. */ 
		int playCounts[5] = {0}; 

        printf("Combinations for a score of %d:\n", score);
		/* Prints all the combinations for the input score. */
        findCombinations(score, plays, playCounts, 0);
    }

    printf("Program ended.\n\n");
    return 0;
}


