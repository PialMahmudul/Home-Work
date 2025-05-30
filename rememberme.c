#include <stdio.h>

#define TOTAL_CANDIDATES 6
#define SUCCESSFUL_CANDIDATES 4
#define FAILED_CANDIDATES 2
#define MAX_MESSAGES 10
#define MAX_LENGTH 256

// Immutable array: basic info for failed candidates + audition + rolling paper section
const char *memorial07_arr[FAILED_CANDIDATES] = {
    "Lily Kim,Female,20051212,Seoul,010-1111-2222,lily@kpop.com,milliways",
    "Noah Lee,Male,20060324,Busan,010-3333-4444,noah@kpop.com,milliways"
};

// Rolling paper messages
char rollingpp07_arr[MAX_MESSAGES][MAX_LENGTH];
int message_count = 0;

// Candidate names (from problem 3)
const char *candidate_names[TOTAL_CANDIDATES] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva", "Liam Wilson", "Lily Kim", "Noah Lee"
};

void display_failed_candidates() {
    printf("\n[ Unsuccessful Candidates List ]\n");
    for (int i = 0; i < FAILED_CANDIDATES; i++) {
        printf("%d. %s\n", i + 1, memorial07_arr[i]);
    }
}

void write_message() {
    int i;
    char sender[MAX_LENGTH];
    char message[MAX_LENGTH];
    int recipient_idx;

    for (i = 0; i < SUCCESSFUL_CANDIDATES; i++) {
        printf("\n[%s] Choose a recipient (1 or 2): ", candidate_names[i]);
        scanf("%d", &recipient_idx);
        getchar(); // consume newline

        if (recipient_idx < 1 || recipient_idx > FAILED_CANDIDATES) {
            printf("Invalid recipient. Skipping.\n");
            continue;
        }

        printf("Enter your message to %s: ", candidate_names[SUCCESSFUL_CANDIDATES + recipient_idx - 1]);
        fgets(message, MAX_LENGTH, stdin);

        // Remove newline
        int len = 0;
        while (message[len] != '\0') {
            if (message[len] == '\n') message[len] = '\0';
            len++;
        }

        snprintf(rollingpp07_arr[message_count], MAX_LENGTH, "%s: %s", candidate_names[i], message);
        message_count++;
    }
}

void show_messages_for_failed() {
    int choice;
    display_failed_candidates();
    printf("\nSelect candidate to view messages (1 or 2): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > FAILED_CANDIDATES) {
        printf("Invalid selection.\n");
        return;
    }

    const char *recipient_name = candidate_names[SUCCESSFUL_CANDIDATES + choice - 1];
    const char *recipient_email = memorial07_arr[choice - 1];

    printf("\nMessages for %s (%s):\n", recipient_name, recipient_email);
    for (int i = 0; i < message_count; i++) {
        printf("- %s\n", rollingpp07_arr[i]);
    }

    // Bonus: Ask to send email
    char send_choice;
    printf("\nWould you like to send the email to %s? (Y/N): ", recipient_email);
    scanf(" %c", &send_choice);
    if (send_choice == 'Y') {
        printf("Email has been sent.\n");
    } else {
        printf("Email was not sent.\n");
    }
}

int main() {
    printf("\n==== Welcome to RememberMe System ====");
    write_message();
    show_messages_for_failed();
    return 0;
}
