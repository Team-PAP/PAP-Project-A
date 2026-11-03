#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

extern int assetID[MAX_ASSETS];
extern char assetName[MAX_ASSETS][50];
extern char assetType[MAX_ASSETS][30];
extern float purchaseValue[MAX_ASSETS];
extern char department[MAX_ASSETS][50];
extern char assetCondition[MAX_ASSETS][30];

extern int assetCount;

void addAsset(void);
void displayAssets(void);
void searchAsset(void);
void assetMenu(void);

#endif