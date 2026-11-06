#include <stdio.h>
#include <string.h>
#include "budget.h"

void clearInputBuffer(void);

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
    if (budgetCount >= MAX_DEPARTMENTS) {
        printf("\nError: Cannot add more departments. Storage full.\n");
        return;
    }

    Budget tempBudget;
    int valid = 0;
    int foundIndex = -1;

    printf("\n--- Departmental Budget Entry ---\n");
    clearInputBuffer();

    printf("Enter Department Name: ");
    fgets(tempBudget.departmentName, STR_LEN, stdin);
    tempBudget.departmentName[strcspn(tempBudget.departmentName, "\n")] = '\0';

    while (!valid) {
        printf("Enter Allocated Budget (N$): ");
        if (scanf("%lf", &tempBudget.allocatedBudget) == 1 && tempBudget.allocatedBudget >= 0) {
            valid = 1;
        } else {
            printf("Invalid amount. Please enter a positive number.\n");
            clearInputBuffer();
        }
    }

    valid = 0;
    while (!valid) {
        printf("Enter Total Expenditure (N$): ");
        if (scanf("%lf", &tempBudget.expenditure) == 1 && tempBudget.expenditure >= 0) {
            valid = 1;
        } else {
            printf("Invalid amount. Please enter a positive number.\n");
            clearInputBuffer();
        }
    }

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
        budgets[budgetCount] = tempBudget;
        budgetCount++;
        printf("New budget recorded successfully!\n");
    }
}

void displayBudgets(void) {
    if (budgetCount == 0) {
        printf("\nNo budget records found.\n");
        return;
    }

    printf("\n====================================================================================\n");
    printf("%-20s %-18s %-18s %-18s %-18s\n", "Department", "Allocated (N$)", "Expenditure (N$)", "Remaining (N$)", "Status");
    printf("====================================================================================\n");

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
    printf("====================================================================================\n");
}
