#ifndef REPORTS_H
#define REPORTS_H
// Report function declarations
#include "suppliers.h"

void displayReports(struct Supplier suppliers[], int supplierCount);

void employeeReport(void);
void budgetReport(void);
void supplierReport(struct Supplier suppliers[], int supplierCount);
void assetReport(void);

#endif
