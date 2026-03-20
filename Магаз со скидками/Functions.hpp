#include <iostream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

void CheckArrPushback();
void ChangeAccount();
void PrintCheck(double& totalSum);

void CreateNewStorage();

bool isPassSetCreated = false;
bool isSetCreated = false;
void CreateStorage();
void ShowStorage(int mode = 0);
void AddStorageItem();
void ShowSuperAdminMenu();
void ShowAdminMenu();
void ShowuserMenu();
bool IsNumber(const std::string& str);
inline void Getline(std::string& str);
void Start();
bool Login();
bool CheckPass(const std::string& str);
void RemoveStorageItem();
void ChangePrice();
void ChangeStorage();
void AddNewItem();
void ChandeName();
void DeleteItem();
void ShowUsers(int mode = 0);
void AddNewUser();
bool CheckLogin(const std::string& str);
void SetSpecialSymbols();
void ChangeAccount();
void SetPassSymbols();
void AddNewUser();
void ChangePass();
void DeleteUser();
void StorageReturner();
void ShowIncome();
void CreateEmptyStorage();
double VolumeDiscount(double totalSum);
double TimeDiscount(double totalSum);
double SeasonDiscount(double totalSum);
double BirthdayDiscount(double totalSum, const std::string& customerName);
template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize);


