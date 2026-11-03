#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "validation.h"

int addSupplier(struct Supplier list[], int count)
{
    int i, id, duplicate;

    if (count >= MAX_SUPPLIERS)
    {
        printf("\nSorry, the supplier list is full.\n");
        return 0;
    }

    do
    {
        duplicate = 0;

        if (!promptID("Enter Supplier ID: ", &id))
        {
            return 0;
        }

        for (i = 0; i < count; i++)
        {
            if (list[i].id == id)
            {
                printf("That ID is already used. Try again.\n");
                duplicate = 1;
                break;
            }
        }
    }
    while (duplicate == 1);

    list[count].id = id;

    if (!promptText("Enter Supplier Name: ", list[count].name, sizeof(list[count].name)))
    {
        return 0;
    }

    for (;;)
    {
        if (!promptText("Enter Email: ", list[count].email, sizeof(list[count].email)))
        {
            return 0;
        }
        if (validateEmail(list[count].email))
        {
            break;
        }
        printf("Invalid email. Use a format like name@example.com.\n");
    }

    for (;;)
    {
        if (!promptText("Enter Telephone Number: ", list[count].telephone, sizeof(list[count].telephone)))
        {
            return 0;
        }
        if (validatePhone(list[count].telephone))
        {
            break;
        }
        printf("Invalid telephone number. Use 7 to 15 digits (spaces, + - ( ) allowed).\n");
    }

    if (!promptText("Enter Town/Location: ", list[count].town, sizeof(list[count].town)))
    {
        return 0;
    }

    printf("\nSupplier added successfully.\n");
    return 1;
}

void displaySuppliers(struct Supplier list[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo suppliers to display.\n");
        return;
    }

    printf("====================================================================================\n");
    printf("%-5s %-20s %-25s %-15s %-15s\n", "ID", "Name", "Email", "Telephone", "Town");
    printf("====================================================================================\n");

    for (i = 0; i < count; i++)
    {
        printf("%-5d %-20s %-25s %-15s %-15s\n", list[i].id, list[i].name, list[i].email, list[i].telephone, list[i].town);
    }

    printf("====================================================================================\n");
    printf("Total suppliers: %d\n", count);
}

int searchSuppliers(struct Supplier list[], int count, int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (list[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void compareSuppliers(struct Supplier list[], int count)
{
    int id1, id2, i1, i2;

    if (count < 2)
    {
        printf("\nYou need at least 2 suppliers to compare.\n");
        return;
    }

    if (!promptID("Enter first Supplier ID: ", &id1))
    {
        return;
    }
    if (!promptID("Enter second Supplier ID: ", &id2))
    {
        return;
    }

    i1 = searchSuppliers(list, count, id1);
    i2 = searchSuppliers(list, count, id2);

    if (i1 == -1 || i2 == -1)
    {
        printf("\nOne or both supplier IDs were not found.\n");
        return;
    }

    printf("\n------------------ COMPARISON ------------------\n");
    printf("%-12s %-20s %-20s\n", "FIELD", "SUPPLIER 1", "SUPPLIER 2");
    printf("------------------------------------------------\n");
    printf("%-12s %-20d %-20d\n", "ID", list[i1].id, list[i2].id);
    printf("%-12s %-20s %-20s\n", "NAME", list[i1].name, list[i2].name);
    printf("%-12s %-20s %-20s\n", "EMAIL", list[i1].email, list[i2].email);
    printf("%-12s %-20s %-20s\n", "TELEPHONE", list[i1].telephone, list[i2].telephone);
    printf("%-12s %-20s %-20s\n", "TOWN", list[i1].town, list[i2].town);
    printf("------------------------------------------------\n");

    if (strcmp(list[i1].town, list[i2].town) == 0)
    {
        printf("Both suppliers are in the same town.\n");
    }
    else
    {
        printf("Suppliers are in different towns.\n");
    }
}

void supplierMenu(struct Supplier list[], int *count)
{
    int choice;
    int id, index;

    do
    {
        printf("\n======= SUPPLIER MANAGEMENT =======\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare Suppliers\n");
        printf("5. Back to Main Menu\n");
        printf("Choose an option: ");

        choice = readInt(5);

        switch (choice)
        {
            case 1:
                if (addSupplier(list, *count) == 1)
                {
                    (*count)++;
                }
                break;

            case 2:
                displaySuppliers(list, *count);
                break;

            case 3:
                if (*count == 0)
                {
                    printf("\nNo suppliers to search.\n");
                    break;
                }

                if (!promptID("Enter Supplier ID to search: ", &id))
                {
                    break;
                }

                index = searchSuppliers(list, *count, id);

                if (index == -1)
                {
                    printf("\nSupplier with ID %d was not found.\n", id);
                }
                else
                {
                    printf("\nSupplier found:\n");
                    printf("ID        : %d\n", list[index].id);
                    printf("Name      : %s\n", list[index].name);
                    printf("Email     : %s\n", list[index].email);
                    printf("Telephone : %s\n", list[index].telephone);
                    printf("Town      : %s\n", list[index].town);
                }
                break;

            case 4:
                compareSuppliers(list, *count);
                break;

            case 5:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a number from 1 to 5.\n");
        }
    }
    while (choice != 5);
}
