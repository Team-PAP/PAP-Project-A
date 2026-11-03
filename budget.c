#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "validation.h"

Budget budgets[MAX_DEPARTMENTS];
int budgetCount = 0;

void calculateBudgetStatus(Budget *b) {
    b->remainingBudget = b->allocatedBudget - b->expenditure;

    if (b->remainingBudget < 0) {
        b->isExceeded = 1;
    } else {
        b->isExceeded = 0;
    }
}

void manageBudgets(void) {
    Budget tempBudget;
    int foundIndex = -1;

    printf("\n--- Departmental Budget Entry ---\n");

    if (!promptText("Enter Department Name: ", tempBudget.departmentName, sizeof(tempBudget.departmentName))) return;
    if (!promptMoney("Enter Allocated Budget (N$): ", &tempBudget.allocatedBudget)) return;
    if (!promptMoney("Enter Total Expenditure (N$): ", &tempBudget.expenditure)) return;

    calculateBudgetStatus(&tempBudget);

    for (int i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].departmentName, tempBudget.departmentName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        budgets[foundIndex] = tempBudget;
        printf("Budget for %s updated successfully!\n", tempBudget.departmentName);
    } else {
        if (budgetCount >= MAX_DEPARTMENTS) {
            printf("\nError: Cannot add more departments. Storage full.\n");
            return;
        }
        budgets[budgetCount] = tempBudget;
        budgetCount++;
        printf("New budget recorded successfully!\n");
    }

    printf("Remaining: N$%.2f - Status: %s\n", tempBudget.remainingBudget,
           tempBudget.isExceeded ? "OVER BUDGET" : "WITHIN BUDGET");
}

void displayBudgets(void) {
    if (budgetCount == 0) {
        printf("\nNo budget records found.\n");
        return;
    }

    printf("\n============================================================================================\n");
    printf("%-20s %-18s %-18s %-18s %s\n", "Department", "Allocated (N$)", "Expenditure (N$)", "Remaining (N$)", "Status");
    printf("============================================================================================\n");

    for (int i = 0; i < budgetCount; i++) {
        char statusStr[20];

        if (budgets[i].isExceeded == 1) {
            strcpy(statusStr, "OVER BUDGET");
        } else {
            strcpy(statusStr, "WITHIN BUDGET");
        }

        printf("%-20s N$%-16.2f N$%-16.2f N$%-16.2f %-12s\n",
               budgets[i].departmentName,
               budgets[i].allocatedBudget,
               budgets[i].expenditure,
               budgets[i].remainingBudget,
               statusStr);
    }
    printf("============================================================================================\n");
}

void budgetMenu(void) {
    int choice;

    do {
        printf("\n====================================\n");
        printf("         BUDGET MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Enter / Update Department Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Back to Main Menu\n");
        printf("====================================\n");
        printf("Enter your choice: ");

        choice = readInt(3);

        switch (choice) {
            case 1:
                manageBudgets();
                break;

            case 2:
                displayBudgets();
                break;

            case 3:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Please enter a number from 1 to 3.\n");
        }
    } while (choice != 3);
}
