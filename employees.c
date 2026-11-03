#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void calculateSalary(Employee *emp) {
    emp->grossSalary = emp->basicSalary + emp->housingAllowance + emp->transportAllowance;
}

/* Returns 1 if an employee with this ID is already stored */
static int employeeIdExists(const char *id) {
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

void addEmployee(void) {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("\nError: Employee database is full!\n");
        return;
    }

    Employee e;
    printf("\n--- Add New Employee ---\n");

    for (;;) {
        if (!promptText("Enter Employee ID: ", e.id, sizeof(e.id))) {
            return;
        }
        if (strchr(e.id, ' ') != NULL) {
            printf("Employee ID cannot contain spaces.\n");
        } else if (employeeIdExists(e.id)) {
            printf("That Employee ID is already in use.\n");
        } else {
            break;
        }
    }

    if (!promptText("Enter Employee Name: ", e.name, sizeof(e.name))) return;
    if (!promptText("Enter Department: ", e.department, sizeof(e.department))) return;
    if (!promptMoney("Enter Basic Salary (N$): ", &e.basicSalary)) return;
    if (!promptMoney("Enter Housing Allowance (N$): ", &e.housingAllowance)) return;
    if (!promptMoney("Enter Transport Allowance (N$): ", &e.transportAllowance)) return;

    calculateSalary(&e);
    employees[employeeCount++] = e;

    printf("Employee added successfully!\n");
}

void displayEmployees(void) {
    if (employeeCount == 0) {
        printf("\nNo employees recorded in the system.\n");
        return;
    }

    printf("\n====================================================================================================\n");
    printf("%-10s %-20s %-20s %-12s %-12s %-12s %-12s\n", "ID", "Name", "Department", "Basic", "Housing", "Transport", "Gross Pay");
    printf("====================================================================================================\n");

    for (int i = 0; i < employeeCount; i++) {
        printf("%-10s %-20s %-20s N$%-10.2f N$%-10.2f N$%-10.2f N$%-10.2f\n",
               employees[i].id, employees[i].name, employees[i].department,
               employees[i].basicSalary, employees[i].housingAllowance,
               employees[i].transportAllowance, employees[i].grossSalary);
    }
    printf("====================================================================================================\n");
}

void searchEmployee(void) {
    if (employeeCount == 0) {
        printf("\nNo employees available to search.\n");
        return;
    }

    char searchKey[STR_LEN];
    printf("\n");
    if (!promptText("Enter Employee ID or Name to Search: ", searchKey, sizeof(searchKey))) {
        return;
    }

    int found = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, searchKey) == 0 || strstr(employees[i].name, searchKey) != NULL) {
            printf("\n--- Match Found ---\n");
            printf("ID: %s\nName: %s\nDepartment: %s\nBasic Salary: N$%.2f\nHousing: N$%.2f\nTransport: N$%.2f\nGross Salary: N$%.2f\n",
                   employees[i].id, employees[i].name, employees[i].department,
                   employees[i].basicSalary, employees[i].housingAllowance,
                   employees[i].transportAllowance, employees[i].grossSalary);
            found = 1;
        }
    }

    if (!found) {
        printf("No employee matching '%s' was found.\n", searchKey);
    }
}
