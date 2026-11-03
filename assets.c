#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "assets.h"
#include "validation.h"

/* Parallel arrays: index i in every array describes the same asset */
int assetID[MAX_ASSETS];
char assetName[MAX_ASSETS][50];
char assetType[MAX_ASSETS][30];
float purchaseValue[MAX_ASSETS];
char department[MAX_ASSETS][50];
char assetCondition[MAX_ASSETS][30];

int assetCount = 0;

/* Accepts good/fair/poor in any letter case and rewrites it as Good/Fair/Poor.
   Returns 1 if recognised, 0 otherwise. */
static int normalizeCondition(char *text)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        text[i] = (char)tolower((unsigned char)text[i]);
    }

    if (strcmp(text, "good") == 0)
    {
        strcpy(text, "Good");
        return 1;
    }
    if (strcmp(text, "fair") == 0)
    {
        strcpy(text, "Fair");
        return 1;
    }
    if (strcmp(text, "poor") == 0)
    {
        strcpy(text, "Poor");
        return 1;
    }
    return 0;
}

/* Returns the index of the asset with this ID, or -1 if not found */
static int findAsset(int id)
{
    for (int i = 0; i < assetCount; i++)
    {
        if (assetID[i] == id)
        {
            return i;
        }
    }
    return -1;
}

static void printAsset(int i)
{
    printf("Asset ID: %d\n", assetID[i]);
    printf("Asset Name: %s\n", assetName[i]);
    printf("Asset Type: %s\n", assetType[i]);
    printf("Purchase Value: N$%.2f\n", purchaseValue[i]);
    printf("Department: %s\n", department[i]);
    printf("Condition: %s\n", assetCondition[i]);
}

void addAsset(void){

    int id;
    double value;

    if (assetCount >= MAX_ASSETS)
    {
        printf("\nMaximum limit reached. Cannot add more assets.\n");
        return;
    }

    printf("\n========== ADD ASSET ==========\n");

    for (;;)
    {
        if (!promptID("Enter Asset ID: ", &id))
        {
            return;
        }
        if (findAsset(id) == -1)
        {
            break;
        }
        printf("That Asset ID is already in use. Try again.\n");
    }
    assetID[assetCount] = id;

    if (!promptText("Enter Asset Name: ", assetName[assetCount], sizeof(assetName[assetCount]))) return;
    if (!promptText("Enter Asset Type: ", assetType[assetCount], sizeof(assetType[assetCount]))) return;

    if (!promptMoney("Enter Purchase Value (N$): ", &value)) return;
    purchaseValue[assetCount] = (float)value;

    if (!promptText("Enter Department: ", department[assetCount], sizeof(department[assetCount]))) return;

    for (;;)
    {
        if (!promptText("Enter Condition (Good / Fair / Poor): ", assetCondition[assetCount], sizeof(assetCondition[assetCount])))
        {
            return;
        }
        if (normalizeCondition(assetCondition[assetCount]))
        {
            break;
        }
        printf("Condition must be Good, Fair or Poor.\n");
    }

    assetCount++;

    printf("\nAsset added successfully!\n");
}

void displayAssets(void){

    if (assetCount == 0)
    {
        printf("\nNo assets have been registered.\n");
        return;
    }

    printf("\n========== REGISTERED ASSETS ==========\n");

    for (int i = 0; i < assetCount; i++)
    {
        printf("\nAsset %d\n", i + 1);
        printf("-----------------------------\n");
        printAsset(i);
    }
}

void searchAsset(void){

    int searchID;
    int index;

    if (assetCount == 0)
    {
        printf("\nNo assets have been registered.\n");
        return;
    }

    printf("\n========== SEARCH ASSET ==========\n");

    if (!promptID("Enter Asset ID to search: ", &searchID))
    {
        return;
    }

    index = findAsset(searchID);

    if (index == -1)
    {
        printf("\nAsset not found.\n");
        return;
    }

    printf("\nAsset Found!\n");
    printf("-----------------------------\n");
    printAsset(index);
}

void assetMenu(void){

    int choice;

    do
    {
        printf("\n====================================\n");
        printf("       ASSET MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Return to Main Menu\n");
        printf("====================================\n");
        printf("Enter your choice: ");

        choice = readInt(4);

        switch (choice)
        {
            case 1:
                addAsset();
                break;

            case 2:
                displayAssets();
                break;

            case 3:
                searchAsset();
                break;

            case 4:
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please select 1-4.\n");
        }

    } while (choice != 4);
}
