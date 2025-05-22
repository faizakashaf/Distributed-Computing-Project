#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ANSI Color Macros
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"

int n, id[MAX], status[MAX], coordinator = -1;

void printDivider() {
    printf(CYAN "----------------------------------------------------\n" RESET);
}

void displayNodes() {
    printDivider();
    printf(GREEN "Node Status:\n" RESET);
    for (int i = 0; i < n; i++) {
        printf("Node %d (ID: %d) : %s\n", i, id[i], status[i] ? GREEN "Active" : RED "Inactive");
    }
    if (coordinator != -1)
        printf(YELLOW "\nCurrent Coordinator: Node with ID %d\n" RESET, id[coordinator]);
    else
        printf(RED "\nNo active coordinator found!\n" RESET);
    printDivider();
}

void startElection(int starter) {
    if (!status[starter]) {
        printf(RED "Node %d is inactive. Cannot start election.\n" RESET, id[starter]);
        return;
    }

    printf(YELLOW "\nElection initiated by Node %d (ID %d)...\n" RESET, starter, id[starter]);
    int newCoordinator = -1;
    for (int i = starter + 1; i < n; i++) {
        if (status[i]) {
            printf(BLUE "→ Node %d (ID %d) responds to election.\n" RESET, i, id[i]);
            newCoordinator = i;
        }
    }

    if (newCoordinator == -1) {
        printf(GREEN "\n✓ Node %d (ID %d) becomes the new Coordinator.\n" RESET, starter, id[starter]);
        coordinator = starter;
    } else {
        startElection(newCoordinator); // Recursively continue election
    }
}

int main() {
    int choice, node;

    printDivider();
    printf(YELLOW "   LEADER ELECTION USING BULLY ALGORITHM (C Simulation)\n" RESET);
    printDivider();

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter unique IDs for %d nodes:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &id[i]);
        status[i] = 1; // All nodes active initially
    }

    // Find initial coordinator
    coordinator = 0;
    for (int i = 1; i < n; i++) {
        if (id[i] > id[coordinator])
            coordinator = i;
    }

    printDivider();
    printf(GREEN "Initial Coordinator is Node with ID %d\n" RESET, id[coordinator]);

    // Menu Loop
    while (1) {
        printDivider();
        printf("1. Fail a Node\n");
        printf("2. Activate a Node\n");
        printf("3. Start Election from a Node\n");
        printf("4. Display Node Status\n");
        printf("5. Exit\n");
        printDivider();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter node index to fail (0 to %d): ", n - 1);
                scanf("%d", &node);
                if (node >= 0 && node < n) {
                    status[node] = 0;
                    printf(RED "Node %d is now inactive.\n" RESET, id[node]);
                    if (node == coordinator) {
                        printf(YELLOW "Coordinator has failed. Start an election.\n" RESET);
                        coordinator = -1;
                    }
                } else {
                    printf(RED "Invalid node index.\n" RESET);
                }
                break;
            case 2:
                printf("Enter node index to activate (0 to %d): ", n - 1);
                scanf("%d", &node);
                if (node >= 0 && node < n) {
                    status[node] = 1;
                    printf(GREEN "Node %d is now active.\n" RESET, id[node]);
                } else {
                    printf(RED "Invalid node index.\n" RESET);
                }
                break;
            case 3:
                printf("Enter index of node to start election (0 to %d): ", n - 1);
                scanf("%d", &node);
                startElection(node);
                break;
            case 4:
                displayNodes();
                break;
            case 5:
                printf(YELLOW "Exiting program...\n" RESET);
                exit(0);
            default:
                printf(RED "Invalid choice. Try again.\n" RESET);
        }
    }

    return 0;
}
