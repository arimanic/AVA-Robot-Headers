#ifndef arrayHelpers_h
#define arrayHelpers_h

bool arrayEquals(bool a1[], bool a2[], int len);

void arraySubset(bool arr[], int startIndex, int newLength, bool newArr[]);

void arraySubset(int arr[], int startIndex, int newLength, int newArr[]);

void setArray(bool arr[], bool newArr[], int len);

void notArray(bool arr[], int len);
#endif