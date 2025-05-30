#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_JUDGES 5
#define NAME_LEN 50
#define ID_LEN 10
#define CATEGORY_COUNT 5

const char *categories[CATEGORY_COUNT] = {
    "Music Proficiency", "Dance", "Vocal", "Visual", "Expression"
};

// Candidate names and 6-digit unique IDs
char candidate_names[NUM_CANDIDATES][NAME_LEN] = {
    "Jiyeon Park", "Ethan Smith", "Suphanan Wong", "Helena Silva", "Karolina Nowak", "Liam Wilson"
};
char candidate_ids[NUM_CANDIDATES][ID_LEN] = {
    "234561", "342789", "457123", "124587", "934562", "782345"
};

// Scoring sheets: 6 candidates x 7 values per judge [ID, 5 scores, total]
int scoring_sheets[NUM_JUDGES][NUM_CANDIDATES][7];

// Final total scores per candidate (aggregated from all judges)
int final_total_scores[NUM_CANDIDATES] = {0};

// Judge info
char judge_names[NUM_JUDGES][NAME_LEN];
char judge_expertise[NUM_JUDGES][NAME_LEN];

// Function prototypes
void enter_judge_info();
void enter_scores();
void review_scores(int judge_index);
int validate_score(int score);
void modify_scores(int judge_index);
void compute_final_scores();
void display_final_selection();

int main() {
    printf("########################################\n");
    printf("#    Welcome to Milliways Auditions!   #\n");
    printf("########################################\n\n");

    enter_judge_info();

    for (int i = 0; i < NUM_JUDGES; i++) {
        printf("\n####################################\n");
        printf("#   Audition Evaluation Entry (%d)   #\n", i + 1);
        printf("####################################\n");

        printf("> Judge Name: ");
        fgets(judge_names[i], NAME_LEN, stdin);
        judge_names[i][strcspn(judge_names[i], "\n")] = '\0';

        printf("> Expertise: ");
        fgets(judge_expertise[i], NAME_LEN, stdin);
        judge_expertise[i][strcspn(judge_expertise[i], "\n")] = '\0';

        enter_scores(i);

        char confirm;
        while (1) {
            review_scores(i);
            printf("Would you like to submit? (Y/N): ");
            scanf(" %c", &confirm);
            getchar(); // consume newline

            if (confirm == 'Y' || confirm == 'y') {
                printf("***Final submission completed.***\n");
                break;
            } else if (confirm == 'N' || confirm == 'n') {
                modify_scores(i);
            } else {
                printf("Invalid input. Please enter Y or N.\n");
            }
        }
    }

    compute_final_scores();
    display_final_selection();

    return 0;
}

void enter_judge_info() {
    printf("Total Number of Judges: %d\n", NUM_JUDGES);
    printf("Number of Selected Members: 4\n");
}

void enter_scores(int judge_index) {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("------------------------------------\n");
        printf("Candidate: %s (ID: %s)\n", candidate_names[i], candidate_ids[i]);
        scoring_sheets[judge_index][i][0] = atoi(candidate_ids[i]);
        int total = 0;
        for (int j = 0; j < CATEGORY_COUNT; j++) {
            int score;
            while (1) {
                printf("%s (10-100): ", categories[j]);
                scanf("%d", &score);
                if (validate_score(score)) {
                    scoring_sheets[judge_index][i][j + 1] = score;
                    total += score;
                    break;
                } else {
                    printf("Invalid score. Try again.\n");
                }
            }
        }
        scoring_sheets[judge_index][i][6] = total;
    }
    getchar(); // consume newline
}

int validate_score(int score) {
    return score >= 10 && score <= 100;
}

void review_scores(int judge_index) {
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\nPlease review your input!\n");
    printf("------------------------------------\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidate_names[i], scoring_sheets[judge_index][i][6]);
    }
}

void modify_scores(int judge_index) {
    char name_input[NAME_LEN];
    char id_input[ID_LEN];
    while (1) {
        printf("Enter candidate name to modify (or 'exit' to finish): ");
        fgets(name_input, NAME_LEN, stdin);
        name_input[strcspn(name_input, "\n")] = '\0';

        if (strcmp(name_input, "exit") == 0) break;

        printf("Enter candidate 6-digit ID: ");
        fgets(id_input, ID_LEN, stdin);
        id_input[strcspn(id_input, "\n")] = '\0';

        int found = -1;
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(candidate_names[i], name_input) == 0 && strcmp(candidate_ids[i], id_input) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("Candidate not found. Try again.\n");
        } else {
            int total = 0;
            for (int j = 0; j < CATEGORY_COUNT; j++) {
                int score;
                while (1) {
                    printf("New %s score (10-100): ", categories[j]);
                    scanf("%d", &score);
                    if (validate_score(score)) {
                        scoring_sheets[judge_index][found][j + 1] = score;
                        total += score;
                        break;
                    } else {
                        printf("Invalid score. Try again.\n");
                    }
                }
            }
            scoring_sheets[judge_index][found][6] = total;
            getchar(); // consume newline
            printf("Scores updated for %s.\n", candidate_names[found]);
        }
    }
}

void compute_final_scores() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        final_total_scores[i] = 0;
        for (int j = 0; j < NUM_JUDGES; j++) {
            final_total_scores[i] += scoring_sheets[j][i][6];
        }
    }
}

void display_final_selection() {
    printf("\n=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");

    int indices[NUM_CANDIDATES];
    for (int i = 0; i < NUM_CANDIDATES; i++) indices[i] = i;

    // Simple selection sort by score descending
    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (final_total_scores[indices[j]] > final_total_scores[indices[i]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[indices[i]]);
    }
}
