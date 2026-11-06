#include <stdio.h>
#include <string.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"


static void printLine(char ch, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        putchar(ch);
    }
    putchar('\n');
}

static void printTitle(const char *title)
{
    printf("\n");
    printLine('=', 60);
    printf("%s\n", title);
    printLine('=', 60);
}
static int readChoice(void)
{
    char buffer[32];
    int choice;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 5;   
    }
    if (sscanf(buffer, "%d", &choice) != 1)
    {
        return -1;
    }
    return choice;
}

/* Gross salary = basic + housing allowance + transport allowance */
static float calculateGross(const Employee *emp)
{
  return emp->basicSalary + emp->housingAllowance + emp->transportAllowance;
}

void employeeReport(void)
{
    int i, highestIndex = 0, lowestIndex = 0;
    float gross, total = 0.0f, highest, lowest, average;

    printTitle("EMPLOYEE REPORT");

        if (employeeCount == 0)
    {
        printf("No employees have been registered yet.\n");
        return;
    }

    highest = lowest = calculateGross(&employees[0]);

        for (i = 0; i < employeeCount; i++)
    {
        gross = calculateGross(&employees[i]);
        total += gross;

        if (gross > highest)
        {
            highest = gross;
            highestIndex = i;
        }
        if (gross < lowest)
        {
            lowest = gross;
            lowestIndex = i;
        }
    }

    
    average = total / employeeCount;

    printf("Total Employees : %d\n", employeeCount);
    printf("Total Payroll   : N$%.2f\n", total);
    printf("Average Salary  : N$%.2f\n", average);
    printf("Highest Salary  : N$%.2f (%s)\n", highest, employees[highestIndex].name);
    printf("Lowest Salary   : N$%.2f (%s)\n", lowest, employees[lowestIndex].name);
}

void budgetReport(void)
{
    int i, exceededCount = 0;
    float totalAllocated = 0.0f, totalExpenditure = 0.0f, remaining;

    printTitle("BUDGET REPORT");

    if (budgetCount == 0)
    {
        printf("No departmental budgets have been entered yet.\n");
        return;
    }

    printf("%-20s %14s %14s %14s  %s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printLine('-', 75);

    for (i = 0; i < budgetCount; i++)
    {
        remaining = budgets[i].allocatedBudget - budgets[i].expenditure;
        totalAllocated += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;

        printf("%-20s %14.2f %14.2f %14.2f  %s\n",
               budgets[i].departmentName,
               budgets[i].allocatedBudget,
               budgets[i].expenditure,
               remaining,
               (remaining >= 0) ? "WITHIN BUDGET" : "OVER BUDGET");

        if (remaining < 0)
        {
            exceededCount++;
        }
    }
    printLine('-', 75);

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("Total Remaining Budget : N$%.2f\n", totalAllocated - totalExpenditure);

    printf("\nDepartments exceeding budget: %d\n", exceededCount);
    if (exceededCount > 0)
    {
        for (i = 0; i < budgetCount; i++)
        {
            if (budgets[i].expenditure > budgets[i].allocatedBudget)
            {
                printf("  - %s (over by N$%.2f)\n",
                       budgets[i].departmentName,
                       budgets[i].expenditure - budgets[i].allocatedBudget);
            }
        }
    }
}

void supplierReport(struct Supplier suppliers[], int supplierCount)
{
    int i;

    printTitle("SUPPLIER REPORT");

    if (supplierCount == 0)
    {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("%-6s %-22s %-26s %-14s %s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 80);

    for (i = 0; i < supplierCount; i++)
    {
        printf("%-6d %-22s %-26s %-14s %s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].telephone,
               suppliers[i].town);
    }
    printLine('-', 80);
    printf("Total Suppliers: %d\n", supplierCount);
}

void assetReport(void)
{
    int i, good = 0, fair = 0, poor = 0;
    float totalValue = 0.0f;

    printTitle("ASSET REPORT");

    if (assetCount == 0)
    {
        printf("No assets have been registered yet.\n");
        return;
    }

    printf("%-6s %-20s %-12s %12s %-16s %s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printLine('-', 80);

    for (i = 0; i < assetCount; i++)
    {
    printf("%-6d %-20s %-12s %12.2f %-16s %s\n",
               assetID[i],
               assetName[i],
               assetType[i],
               purchaseValue[i],
               department[i],
               assetCondition[i]);

        totalValue += purchaseValue[i];

        /* count assets per condition using string comparison */
        if (strcmp(assetCondition[i], "Good") == 0)
        {
            good++;
        }
        else if (strcmp(assetCondition[i], "Fair") == 0)
        {
            fair++;
        }
        else if (strcmp(assetCondition[i], "Poor") == 0)
        {
            poor++;
        }
    }
    printLine('-', 80);

    printf("Total Assets      : %d\n", assetCount);
    printf("Total Asset Value : N$%.2f\n", totalValue);
    printf("Condition summary : Good = %d, Fair = %d, Poor = %d\n", good, fair, poor);
}

void displayReports(struct Supplier suppliers[], int supplierCount)
{
    int choice;

    do
    {
        printTitle("REPORTS MENU");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        choice = readChoice();

        switch (choice)
        {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(suppliers, supplierCount); break;
            case 4: assetReport();    break;
            case 5: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }
    } while (choice != 5);
}
