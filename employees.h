#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

#ifndef STR_LEN
#define STR_LEN 50
#endif

typedef struct {
    char id[STR_LEN];
    char name[STR_LEN];
    char department[STR_LEN];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
    double grossSalary;
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void calculateSalary(Employee *emp);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);

#endif
