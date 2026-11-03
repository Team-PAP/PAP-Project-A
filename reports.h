#ifndef REPORTS_H
#define REPORTS_H

#include "suppliers.h"

void displayReports(struct Supplier suppliers[], int supplierCount);

void employeeReport(void);
void budgetReport(void);
void supplierReport(struct Supplier suppliers[], int supplierCount);
void assetReport(void);

#endif
