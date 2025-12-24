#include <iostream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

size_t userSize = 3;
size_t staffCount = 1;
std::string userStatus[3]{ "Супер администратор","Администратор","Сотрудник" };

std::string* loginArr = new std::string[userSize]{ "admin", "adminOne","user" };
std::string* passArr = new std::string[userSize]{ "admin","adminOne","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[1],userStatus[2] };
double* salesArr = new double[userSize] {0.0, 0.0, 0.0};
unsigned int* userIdArr = new unsigned int[userSize] {1, 2, 3};
unsigned int currentId = 0;
std::string currentStatus;
void CheckArrPushback();
void ChangeAccount();
void PrintCheck(double& totalSum);

size_t storageSize = 10;
size_t maxItemSize = 299;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
double* priceArr = nullptr;
unsigned int* coutArr = nullptr;
bool isStorageCreated = false;
std::unordered_set<char> specialSymbols;
void CreateNewStorage();
size_t NewstorageSize = 10;
std::string input;

std::unordered_set<char> passSymbols;
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
size_t checkSize = 0;
int* idArrCheck;
std::string* nameArrCheck;
unsigned int* countArrCheck;
double* priceArrCheck;
double* totalPriceArrCheck;

double cashIncome = 0.0;
double bankIncome = 0.0;
double cash = 30000 + rand() % 700;

void Selling();

inline void Getline(std::string& str);
inline void Err();
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	Start();
	delete[]loginArr, passArr, statusArr, salesArr, userIdArr;
	if (isStorageCreated)
	{
		delete[]idArr, nameArr, coutArr, priceArr;
	}
	return 0;
}

double VolumeDiscount(double totalSum)
{
	if (totalSum >= 25000)
		return totalSum * 0.10;
	else if (totalSum >= 10000)
		return totalSum * 0.05;

	return 0.0;
}

double TimeDiscount(double totalSum)
{
	time_t now = time(nullptr);
	tm localTime{};
	localtime_s(&localTime, &now);

	int hour = localTime.tm_hour;

	if (hour >= 12 && hour < 14)
		return totalSum * 0.07;

	return 0.0;
}

double SeasonDiscount(double totalSum)
{
	time_t now = time(nullptr);
	tm localTime{};
	localtime_s(&localTime, &now);

	int month = localTime.tm_mon + 1;

	if (month == 12 || month == 1)
		return totalSum * 0.15;
	else if (month >= 6 && month <= 8)
		return totalSum * 0.10;

	return 0.0;
}

double BirthdayDiscount(double totalSum, const std::string& customerName)
{
	time_t now = time(nullptr);
	tm localTime{};
	localtime_s(&localTime, &now);

	static const std::unordered_set<std::string> birthdayCustomers = {
		"иван", "анна", "сергей", "мария", "алексей"
	};

	std::string nameLower = customerName;
	std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

	if (birthdayCustomers.find(nameLower) != birthdayCustomers.end())
	{
		int day = localTime.tm_mday;
		if ((day >= 1 && day <= 7) || rand() % 100 < 10)
		{
			std::cout << "С днем рождения, " << customerName << "! ";
			return totalSum * 0.20;
		}
	}

	return 0.0;
}

void Selling()
{
	if (!isStorageCreated || storageSize == 0)
	{
		std::cout << "Склад пуст. Продажа невозможна.\n";
		Sleep(1500);
		return;
	}
	std::string chooseId, chooseCount, chooseMoney, choose, customerName;
	unsigned int id = 0, count = 0, index = -1;
	double money = 0.0, totalSum = 0.0;
	bool isFirst = false;
	checkSize = 0;

	std::cout << "Введите имя покупателя (или Enter для пропуска): ";
	Getline(customerName);
	if (customerName.empty()) {
		customerName = "Гость";
	}

	while (true)
	{
		ShowStorage();

		std::cout << "Введите ID товара для покупки или \"exit\" для завершения покупок: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			system("cls");
			if (isFirst == false)
			{
				std::cout << "Выход без покупок\n";
				Sleep(1500);
				break;
			}

			std::cout << "Покупатель: " << customerName << "\n\n";

			double discount1 = VolumeDiscount(totalSum);
			double discount2 = TimeDiscount(totalSum);
			double discount3 = SeasonDiscount(totalSum);
			double discount4 = BirthdayDiscount(totalSum, customerName);

			double totalDiscount = discount1 + discount2 + discount3 + discount4;
			double finalSum = totalSum - totalDiscount;

			std::cout << "Примененные скидки:\n";
			if (discount1 > 0)
				std::cout << "Объемная скидка: -" << discount1 << " руб.\n";
			if (discount2 > 0)
				std::cout << "Скидка по времени: -" << discount2 << " руб.\n";
			if (discount3 > 0)
				std::cout << "Сезонная скидка: -" << discount3 << " руб.\n";
			if (discount4 > 0)
				std::cout << "Именинная скидка: -" << discount4 << " руб.\n";

			if (totalDiscount > 0) {
				std::cout << "Итого скидка: -" << totalDiscount << " руб.\n";
				std::cout << "Сумма без скидки: " << totalSum << " руб.\n";
			}

			std::cout << "К оплате: " << finalSum << " руб.\n\n";

			totalSum = finalSum;
			PrintCheck(totalSum);

			std::cout << "\nПодтвердить покупку?\n1 - Да\n2 - Добавить еще товар\n3 - Отмена\nВвод: ";
			Getline(choose);

			if (choose == "1")
			{
				while (true)
				{
					system("cls");
					std::cout << "Введите способ оплаты\n1 - Наличными\n2 - Безнал\nВвод: ";
					Getline(choose);
					if (choose == "1")
					{
						std::cout << "Введите кол-во наличных: ";
						Getline(chooseMoney);
						if (IsNumber(chooseMoney))
						{
							money = std::stod(chooseMoney);
							if (money < totalSum)
							{
								std::cout << "Недостаточно средств!\n";
								Sleep(1500);
								continue;
							}
							else if (money - totalSum > cash)
							{
								std::cout << "Нет возможности дать сдачу, повторите попытку!\n";
								Sleep(1500);
								continue;
							}
							else
							{
								std::cout << "Ваши деньги: " << money << "\n";
								Sleep(400);
								std::cout << "Оплата прошла успешно. Сдача: " << money - totalSum << " рублей\n";
								Sleep(2000);
								cash += totalSum;
								cash -= money - totalSum;
								cashIncome += totalSum;
								salesArr[currentId] += totalSum;
								system("cls");
								break;
							}
						}
					}
					else if (choose == "2")
					{
						std::cout << "Приложите карту\n\n";
						Sleep(1000);
						if (rand() % 10 <= 2)
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Sleep(500);
							}
							std::cout << "\nОплата прошла успешно\n\nСпасибо за покупку!";
							bankIncome += totalSum;
							salesArr[currentId] += totalSum;
							system("cls");
							Sleep(1500);
							break;
						}
					}
					else if (choose == "Samsung")
					{
						std::cout << "Великий самсунг оплатил вам чек. Всего доброго\n";
						Sleep(1500);
						system("cls");
						break;
					}
					else
					{
						Err();
					}
				}
				break;
			}
			else if (choose == "2")
			{
				continue;
			}
			else if (choose == "3")
			{
				std::cout << "Отмена покупки!\n";
				StorageReturner();
				Sleep(1500);
				return;
			}
			else
			{
				Err();
				continue;
			}
		}

		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			continue;
		}

		std::cout << "\nВведите кол-во товара или \"exit\" для завершения покупок: ";
		Getline(chooseCount);
		if (chooseCount == "exit")
		{
			std::cout << "Отмена покупки товара: " << nameArr[id] << "\n\n";
			Sleep(1500);
			continue;
		}
		if (IsNumber(chooseCount))
		{
			count = std::stoi(chooseCount);
			if (count < 1 || count > coutArr[id])
			{
				std::cout << "Ошибка кол-ва! Максимум: " << coutArr[id] << "\n\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			Err();
			continue;
		}

		CheckArrPushback();
		if (isFirst == false)
		{
			isFirst = true;
		}
		index++;
		idArrCheck[index] = idArr[id];
		nameArrCheck[index] = nameArr[id];
		priceArrCheck[index] = priceArr[id];
		countArrCheck[index] = count;
		totalPriceArrCheck[index] = count * priceArr[id];
		coutArr[id] -= count;
		totalSum += totalPriceArrCheck[index];

		std::cout << "\nТовар добавлен в чек\n\n";
		Sleep(1000);
	}

	if (checkSize > 0) {
		delete[] idArrCheck;
		delete[] nameArrCheck;
		delete[] countArrCheck;
		delete[] priceArrCheck;
		delete[] totalPriceArrCheck;
		idArrCheck = nullptr;
		nameArrCheck = nullptr;
		countArrCheck = nullptr;
		priceArrCheck = nullptr;
		totalPriceArrCheck = nullptr;
	}
}

void PrintCheck(double& totalSum)
{
	std::cout << "№\t" << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
		<< "Цена за ед\t" << "Кол-во\t" << "Итого\n";
	for (size_t i = 0; i < checkSize; i++)
	{
		std::cout << i + 1 << "\t" << idArrCheck[i] << "\t" << std::left << std::setw(25) << nameArrCheck[i] << "\t"
			<< priceArrCheck[i] << "\t\t" << countArrCheck[i] << "\t" << totalPriceArrCheck[i] << "\n";
	}
	std::cout << "\nИтого к оплате: " << totalSum << " руб.\n\n";
}

void CheckArrPushback()
{
	if (checkSize == 0) {
		idArrCheck = new int[1];
		nameArrCheck = new std::string[1];
		countArrCheck = new unsigned int[1];
		priceArrCheck = new double[1];
		totalPriceArrCheck = new double[1];
		checkSize = 1;
		return;
	}

	checkSize++;
	int* idArrCheckTemp = new int[checkSize];
	std::string* nameArrCheckTemp = new std::string[checkSize];
	unsigned int* countArrCheckTemp = new unsigned int[checkSize];
	double* priceArrCheckTemp = new double[checkSize];
	double* totalPriceArrCheckTemp = new double[checkSize];

	for (size_t i = 0; i < checkSize - 1; i++) {
		idArrCheckTemp[i] = idArrCheck[i];
		nameArrCheckTemp[i] = nameArrCheck[i];
		countArrCheckTemp[i] = countArrCheck[i];
		priceArrCheckTemp[i] = priceArrCheck[i];
		totalPriceArrCheckTemp[i] = totalPriceArrCheck[i];
	}

	delete[] idArrCheck;
	delete[] nameArrCheck;
	delete[] countArrCheck;
	delete[] priceArrCheck;
	delete[] totalPriceArrCheck;

	idArrCheck = idArrCheckTemp;
	nameArrCheck = nameArrCheckTemp;
	countArrCheck = countArrCheckTemp;
	priceArrCheck = priceArrCheckTemp;
	totalPriceArrCheck = totalPriceArrCheckTemp;
}

void ChangePrice()
{
	if (!isStorageCreated || storageSize == 0)
	{
		std::cout << "Склад пуст. Нет товаров для изменения цены.\n";
		Sleep(1500);
		return;
	}

	std::string chooseId, choosePrice, choose;
	unsigned int id = 0;
	double newPrice;
	while (true)
	{
		system("cls");
		ShowStorage(2);
		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции изменения цены!\n";
			Sleep(1500);
			system("cls");
			break;
		}
		std::cout << "Введите новую цену для товара: ";
		Getline(choosePrice);

		if (IsNumber(chooseId) && IsNumber(choosePrice))
		{
			id = std::stoi(chooseId) - 1;
			newPrice = std::stod(choosePrice);

			if (id < 0 || id > storageSize - 1 || newPrice < 0 || newPrice > 10000000)
			{
				std::cout << "Некорректный id или цена\nМаксимальная цена - " << 10000000 << "\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
					<< priceArr[id] << " ---> " << newPrice << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					priceArr[id] = newPrice;
					std::cout << "Цена успешно изменена\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена изменения цены!\n";
					Sleep(1500);
					system("cls");
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void SetSpecialSymbols()
{
	for (char i = '0'; i <= '9'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		specialSymbols.insert(i);
	}
	isSetCreated = true;
}

void SetPassSymbols()
{
	for (char i = '!'; i <= '&'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '('; i <= '+'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '/'; i <= '~'; i++)
	{
		passSymbols.insert(i);
	}
	isPassSetCreated = true;
}

bool CheckPass(const std::string& str)
{
	if (str.size() < 8 || str.size() > 30)
	{
		std::cout << "Ошибка длины пароля\n";
		Sleep(1500);
		return false;
	}
	int numCount = 0, symCount = 0;
	std::unordered_set<char> specialPassSym{ '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '/', '?', '|', '\\', '\"', '\'', ',', '.', '<', '>', '~', '`', ':', ';', '{', '}', '[', ']' };
	for (char sym : str)
	{
		if (!passSymbols.count(sym))
		{
			std::cout << "Некорректный символ в пароле\n";
			Sleep(1500);
			return false;
		}
		if (std::isdigit(sym))
		{
			numCount++;
		}
		if (specialPassSym.count(sym))
		{
			symCount++;
		}
	}

	if (numCount >= 3 && symCount >= 3)
	{
		return true;
	}
	else
	{
		std::cout << "Минимум 3 цифры и 3 специальных символа\n";
		return false;
	}
}

void AddNewUser()
{
	std::string newLogin, newPass, newRole, choose;
	bool exit = true;

	if (!isSetCreated) SetSpecialSymbols();
	if (!isPassSetCreated) SetPassSymbols();

	while (exit)
	{
		system("cls");
		std::cout << "Добавление нового пользователя\n\n";

		while (true)
		{
			std::cout << "Введите логин нового пользователя или \"exit\" для выхода: ";
			Getline(newLogin);
			if (newLogin == "exit")
			{
				std::cout << "Отмена добавления нового пользователя!\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (CheckLogin(newLogin))
			{
				break;
			}
		}
		if (!exit) break;

		while (true)
		{
			std::cout << "Введите пароль нового пользователя или \"exit\" для выхода: ";
			Getline(newPass);
			if (newPass == "exit")
			{
				std::cout << "Отмена добавления нового пользователя!\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (CheckPass(newPass))
			{
				break;
			}
		}
		if (!exit) break;

		while (true)
		{
			std::cout << "Выберите роль:\n1 - Администратор\n2 - Сотрудник\nВвод: ";
			Getline(choose);
			if (choose == "exit")
			{
				std::cout << "Отмена добавления нового пользователя!\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (choose == "1")
			{
				newRole = userStatus[1];
				break;
			}
			else if (choose == "2")
			{
				newRole = userStatus[2];
				break;
			}
			else
			{
				Err();
			}
		}
		if (!exit) break;

		std::cout << "\nПользователь: " << newLogin << "\n";
		std::cout << "Роль: " << newRole << "\n\n";
		std::cout << "Подтвердить?\n1 - Да\n2- Нет\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{
			userSize++;
			if (newRole == userStatus[2])
			{
				staffCount++;
			}

			std::string* loginArrTemp = new std::string[userSize];
			std::string* passArrTemp = new std::string[userSize];
			std::string* statusArrTemp = new std::string[userSize];
			double* salesArrTemp = new double[userSize];
			unsigned int* userIdArrTemp = new unsigned int[userSize];

			for (size_t i = 0; i < userSize - 1; i++) {
				loginArrTemp[i] = loginArr[i];
				passArrTemp[i] = passArr[i];
				statusArrTemp[i] = statusArr[i];
				salesArrTemp[i] = salesArr[i];
				userIdArrTemp[i] = userIdArr[i];
			}

			loginArrTemp[userSize - 1] = newLogin;
			passArrTemp[userSize - 1] = newPass;
			statusArrTemp[userSize - 1] = newRole;
			salesArrTemp[userSize - 1] = 0.0;
			userIdArrTemp[userSize - 1] = userSize;

			delete[] loginArr;
			delete[] passArr;
			delete[] statusArr;
			delete[] salesArr;
			delete[] userIdArr;

			loginArr = loginArrTemp;
			passArr = passArrTemp;
			statusArr = statusArrTemp;
			salesArr = salesArrTemp;
			userIdArr = userIdArrTemp;

			std::cout << "Идет подготовка...";
			Sleep(2000);
			std::cout << "Пользователь успешно добавлен!\n\n";
			Sleep(1500);
			break;
		}
		else if (choose == "2")
		{
			std::cout << "Отмена\n";
			Sleep(1500);
			break;
		}
		else
		{
			Err();
		}
	}
}

void ChangeStorage()
{
	if (!isStorageCreated)
	{
		std::cout << "Склад не создан.\n";
		Sleep(1500);
		return;
	}
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить новый товар\n";
		std::cout << "2 - Изменить название товара\n";
		std::cout << "3 - Удалить товар\n";
		std::cout << "0 - Выход из редактора склада\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewItem();
		}
		else if (choose == "2")
		{
			ChandeName();
		}
		else if (choose == "3")
		{
			DeleteItem();
		}
		else if (choose == "0")
		{
			break;
		}
		else
		{
			Err();
		}
	}
}

void ShowUsers(int mode)
{
	if (userSize == 0)
	{
		std::cout << "Нет пользователей.\n";
		return;
	}

	if (mode == 0)
	{
		system("cls");
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "Пароль\t\t\t" << "Роль\n";
		for (size_t i = 1; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
				<< "\t\t\t" << statusArr[i] << "\n";
		}
		std::cout << "\n";
	}
	else if (mode == 1)
	{
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "Пароль\t\t\t" << "Роль\n";
		for (size_t i = 0; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
				<< "\t\t\t" << statusArr[i] << "\n";
		}
	}
}

bool Logout();
void AddNewItem()
{
	std::string newName, newPrice, newCount, choose;
	double price = 0.0;
	unsigned int count = 0;
	bool exit = true;

	while (exit)
	{
		system("cls");
		std::cout << "Добавление нового товара!\nВведите \"exit\" для прекращения операции\n\n";

		while (true)
		{
			std::cout << "Введите название нового товара: ";
			Getline(newName);
			if (newName == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (newName.size() <= 0 || newName.size() >= 50)
			{
				std::cout << "Максимальная длина названия 50 символов\n";
				Sleep(1500);
			}
			else
			{
				break;
			}
		}
		if (!exit) break;

		while (true)
		{
			std::cout << "Введите кол-во нового товара: ";
			Getline(newCount);
			if (newCount == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > maxItemSize)
				{
					std::cout << "Ошибка! Максимум " << maxItemSize << " ед.\n\n";
					Sleep(1500);
				}
				else
				{
					break;
				}
			}
		}
		if (!exit) break;

		while (true)
		{
			system("cls");
			std::cout << "Введите цену нового товара: ";
			Getline(newPrice);
			if (newPrice == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newPrice))
			{
				price = std::stod(newPrice);
				if (price > 10000000)
				{
					std::cout << "Ошибка! Максимум 10000000 руб.\n\n";
					Sleep(1500);
				}
				else
				{
					break;
				}
			}
		}
		if (!exit) break;

		std::cout << "\nНовый товар: " << newName << "\nКол-во: " << count << "\nЦена: " << price << "\n\n";
		std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
		Getline(choose);

		if (choose == "1")
		{
			storageSize++;
			unsigned int* idArrTemp = new unsigned int[storageSize];
			std::string* nameArrTemp = new std::string[storageSize];
			unsigned int* countArrTemp = new unsigned int[storageSize];
			double* priceArrTemp = new double[storageSize];

			for (size_t i = 0; i < storageSize - 1; i++) {
				idArrTemp[i] = idArr[i];
				nameArrTemp[i] = nameArr[i];
				countArrTemp[i] = coutArr[i];
				priceArrTemp[i] = priceArr[i];
			}

			idArrTemp[storageSize - 1] = storageSize;
			nameArrTemp[storageSize - 1] = newName;
			countArrTemp[storageSize - 1] = count;
			priceArrTemp[storageSize - 1] = price;

			delete[] idArr;
			delete[] nameArr;
			delete[] coutArr;
			delete[] priceArr;

			idArr = idArrTemp;
			nameArr = nameArrTemp;
			coutArr = countArrTemp;
			priceArr = priceArrTemp;

			std::cout << "Идет подготовка...";
			Sleep(2000);
			std::cout << "Товар успешно добавлен!\n\n";
			Sleep(1500);
			break;
		}
		else if (choose == "2")
		{
			std::cout << "Отмена\n\n";
			Sleep(1500);
			break;
		}
		else
		{
			Err();
		}
	}
}

void DeleteItem()
{
	std::string chooseId, choose;
	unsigned int id = 0;

	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара для удаления или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Операция удаления товара прервана!\n\n";
			Sleep(1500);
			break;
		}
		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID!\n";
				Sleep(1500);
			}
			else
			{
				std::cout << "Удаляемый товар: " << nameArr[id] << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					storageSize--;
					unsigned int* idArrTemp = new unsigned int[storageSize];
					std::string* nameArrTemp = new std::string[storageSize];
					unsigned int* countArrTemp = new unsigned int[storageSize];
					double* priceArrTemp = new double[storageSize];

					for (size_t i = 0, c = 0; i < storageSize; i++, c++)
					{
						if (c == id) c++;
						idArrTemp[i] = i + 1;
						nameArrTemp[i] = nameArr[c];
						countArrTemp[i] = coutArr[c];
						priceArrTemp[i] = priceArr[c];
					}

					delete[] idArr;
					delete[] nameArr;
					delete[] coutArr;
					delete[] priceArr;

					idArr = idArrTemp;
					nameArr = nameArrTemp;
					coutArr = countArrTemp;
					priceArr = priceArrTemp;

					std::cout << "Идет подготовка...";
					Sleep(2000);
					std::cout << "Товар успешно удален!\n\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена удаления\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void ChandeName()
{
	std::string chooseId, newName, choose;
	unsigned int id = 0;
	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);

		if (chooseId == "exit")
		{
			std::cout << "Операция смены названия прервана!\n\n";
			Sleep(1500);
			break;
		}

		std::cout << "Введите новое название товара: ";
		Getline(newName);

		if (newName.size() <= 0 || newName.size() >= 50)
		{
			std::cout << "Максимальная длина названия 50 символов\n";
			Sleep(1500);
		}
		else if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID!\n";
				Sleep(1500);
			}
			else
			{
				std::cout << "\n" << std::left << std::setw(25)
					<< nameArr[id] << " ---> " << newName << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					nameArr[id] = newName;
					std::cout << "Изменение названия успешно завершено\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void DeleteUser()
{
	std::string chooseNumber, choose, checkPass;
	int userNumber = 0;
	int isAdmin = 0;

	if (currentStatus == userStatus[0])
	{
		if (userSize <= 1)
		{
			std::cout << "Нет допустимых пользователей для удаления\n";
			Sleep(1500);
			return;
		}
		ShowUsers();
		isAdmin = 0;
	}
	else if (currentStatus == userStatus[1])
	{
		if (staffCount < 1)
		{
			std::cout << "Нет доступных пользователей для удаления\n";
			Sleep(1500);
			return;
		}
		ShowUsers();
		isAdmin = 1;
	}

	while (true)
	{
		std::cout << "\nВведите номер пользователя для удаления или \"exit\" для выхода: ";
		Getline(choose);

		if (choose == "exit")
		{
			std::cout << "Отмена удаления пользователя!\n";
			Sleep(1500);
			break;
		}
		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);

			if (userNumber < isAdmin || userNumber >= userSize)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
				continue;
			}

			if (currentStatus == userStatus[1] && statusArr[userNumber] != userStatus[2])
			{
				std::cout << "Нельзя удалять администратора\n";
				Sleep(1500);
				break;
			}

			system("cls");
			std::cout << "Удалить пользователя: " << loginArr[userNumber] << "\n\n";

			if (currentStatus == userStatus[0])
			{
				std::cout << "Для подтверждения введите пароль супер админа или \"exit\" для выхода: ";
				Getline(checkPass);

				if (checkPass == "exit")
				{
					std::cout << "Отмена удаления пользователя!\n";
					Sleep(1500);
					break;
				}
				else if (checkPass == passArr[0])
				{
					userSize--;
					if (statusArr[userNumber] == userStatus[2])
					{
						staffCount--;
					}

					std::string* loginArrTemp = new std::string[userSize];
					std::string* passArrTemp = new std::string[userSize];
					std::string* statusArrTemp = new std::string[userSize];
					double* salesArrTemp = new double[userSize];
					unsigned int* userIdArrTemp = new unsigned int[userSize];

					for (size_t i = 0, c = 0; i < userSize; i++, c++)
					{
						if (c == userNumber) c++;
						loginArrTemp[i] = loginArr[c];
						passArrTemp[i] = passArr[c];
						statusArrTemp[i] = statusArr[c];
						salesArrTemp[i] = salesArr[c];
						userIdArrTemp[i] = userIdArr[c];
					}

					delete[] loginArr;
					delete[] passArr;
					delete[] statusArr;
					delete[] salesArr;
					delete[] userIdArr;

					loginArr = loginArrTemp;
					passArr = passArrTemp;
					statusArr = statusArrTemp;
					salesArr = salesArrTemp;
					userIdArr = userIdArrTemp;

					std::cout << "Идет подготовка...";
					Sleep(2000);
					std::cout << "Пользователь успешно удален!\n\n";
					Sleep(1500);
					break;
				}
				else
				{
					std::cout << "Некорректный пароль\n";
					Sleep(1500);
				}
			}
			else
			{
				std::cout << "Подтвердить удаление?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					userSize--;
					staffCount--;

					std::string* loginArrTemp = new std::string[userSize];
					std::string* passArrTemp = new std::string[userSize];
					std::string* statusArrTemp = new std::string[userSize];
					double* salesArrTemp = new double[userSize];
					unsigned int* userIdArrTemp = new unsigned int[userSize];

					for (size_t i = 0, c = 0; i < userSize; i++, c++)
					{
						if (c == userNumber) c++;
						loginArrTemp[i] = loginArr[c];
						passArrTemp[i] = passArr[c];
						statusArrTemp[i] = statusArr[c];
						salesArrTemp[i] = salesArr[c];
						userIdArrTemp[i] = userIdArr[c];
					}

					delete[] loginArr;
					delete[] passArr;
					delete[] statusArr;
					delete[] salesArr;
					delete[] userIdArr;

					loginArr = loginArrTemp;
					passArr = passArrTemp;
					statusArr = statusArrTemp;
					salesArr = salesArrTemp;
					userIdArr = userIdArrTemp;

					std::cout << "Идет подготовка...";
					Sleep(2000);
					std::cout << "Пользователь успешно удален!\n\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена удаления\n";
					Sleep(1500);
					break;
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void StorageReturner()
{
	if (checkSize == 0) return;

	for (size_t i = 0; i < checkSize; i++)
	{
		coutArr[idArrCheck[i] - 1] += countArrCheck[i];
	}

	delete[] idArrCheck;
	delete[] nameArrCheck;
	delete[] countArrCheck;
	delete[] priceArrCheck;
	delete[] totalPriceArrCheck;

	idArrCheck = nullptr;
	nameArrCheck = nullptr;
	countArrCheck = nullptr;
	priceArrCheck = nullptr;
	totalPriceArrCheck = nullptr;
	checkSize = 0;
}

void ShowIncome()
{
	system("cls");
	std::cout << "Текущая прибыль за смену\n\n";
	std::cout << "Наличный расчет: " << cashIncome << "\n";
	std::cout << "Безналичный расчет: " << bankIncome << "\n";
	std::cout << "Итого: " << bankIncome + cashIncome << "\n\n";
	std::cout << "Сумма ваших продаж: " << salesArr[currentId] << "\n\n";

	system("pause");
	system("cls");
}

void ChangePass()
{
	std::string newPass1, newPass2, choose;
	int userNumber = 0;
	int isAdmin = 0;

	if (currentStatus == userStatus[0])
	{
		ShowUsers(1);
		isAdmin = 0;
	}
	else
	{
		ShowUsers();
		isAdmin = 1;
	}

	while (true)
	{
		std::cout << "\nВведите номер пользователя или \"exit\" для выхода: ";
		Getline(choose);

		if (choose == "exit")
		{
			std::cout << "Отмена изменения пароля!\n";
			Sleep(1500);
			break;
		}
		if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);

			if (userNumber < isAdmin || userNumber >= userSize)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
				continue;
			}

			if (currentStatus == userStatus[1] && statusArr[userNumber] == userStatus[1])
			{
				std::cout << "Нельзя менять пароли Администраторам\n";
				Sleep(1500);
				break;
			}

			system("cls");
			std::cout << "Введите новый пароль для пользователя " << loginArr[userNumber] << ": ";
			Getline(newPass1);
			std::cout << "Подтвердите новый пароль для пользователя " << loginArr[userNumber] << ": ";
			Getline(newPass2);

			if (newPass1 == newPass2)
			{
				if (CheckPass(newPass1))
				{
					passArr[userNumber] = newPass1;
					std::cout << "Пароль успешно изменен!\n";
					Sleep(1500);
					break;
				}
			}
			else
			{
				std::cout << "Пароли не совпадают. Повторите попытку\n";
				Sleep(1500);
			}
		}
	}
}

void CreateNewStorage()
{
	if (isStorageCreated) {
		delete[] idArr;
		delete[] nameArr;
		delete[] priceArr;
		delete[] coutArr;
	}

	while (true) {
		system("cls");
		std::cout << "Создание нового склада\n";

		std::cout << "Введите количество товаров на складе (от 1 до " << NewstorageSize << ")\nВвод: ";
		Getline(input);

		if (!IsNumber(input)) {
			std::cout << "Ошибка! Введите число.\n";
			Sleep(1500);
			continue;
		}

		size_t itemCount = std::stoi(input);

		if (itemCount < 1 || itemCount > NewstorageSize) {
			std::cout << "Ошибка! Количество должно быть от 1 до " << NewstorageSize << ".\n";
			Sleep(1500);
			continue;
		}

		storageSize = itemCount;
		idArr = new unsigned int[storageSize];
		nameArr = new std::string[storageSize];
		priceArr = new double[storageSize];
		coutArr = new unsigned int[storageSize];
		isStorageCreated = true;

		std::cout << "\nСклад создан! Размер: " << storageSize << " товаров.\n";
		Sleep(1000);

		for (size_t i = 0; i < storageSize; i++) {
			system("cls");

			std::cout << "Добавление товара № " << (i + 1) << " из " << storageSize << "\n";

			idArr[i] = i + 1;

			while (true) {
				std::cout << "Название товара: ";
				Getline(input);

				if (input.empty() || input.size() > 50) {
					std::cout << "Ошибка! Название должно быть от 1 до 50 символов.\n";
					Sleep(1000);
					continue;
				}
				nameArr[i] = input;
				break;
			}

			while (true) {
				std::cout << "Цена товара (0-10000000): ";
				Getline(input);

				if (!IsNumber(input)) {
					std::cout << "Ошибка! Введите число.\n";
					Sleep(1000);
					continue;
				}

				double price = std::stod(input);
				if (price < 0 || price > 10000000) {
					std::cout << "Ошибка! Цена должна быть от 0 до 10000000.\n";
					Sleep(1000);
					continue;
				}

				priceArr[i] = price;
				break;
			}

			while (true) {
				std::cout << "Количество товара (0-" << maxItemSize << "): ";
				Getline(input);

				if (!IsNumber(input)) {
					std::cout << "Ошибка! Введите число.\n";
					Sleep(1000);
					continue;
				}

				unsigned int count = std::stoi(input);
				if (count > maxItemSize) {
					std::cout << "Ошибка! Количество должно быть до " << maxItemSize << ".\n";
					Sleep(1000);
					continue;
				}

				coutArr[i] = count;
				break;
			}

			std::cout << "\nТовар добавлен!\n";
			std::cout << "ID: " << idArr[i] << "\n";
			std::cout << "Название: " << nameArr[i] << "\n";
			std::cout << "Цена: " << priceArr[i] << " руб.\n";
			std::cout << "Количество: " << coutArr[i] << " шт.\n\n";

			if (i < storageSize - 1) {
				std::cout << "Нажмите Enter для продолжения...";
				std::cin.get();
			}
		}

		std::cout << "Склад успешно создан!\n";
		std::cout << "Всего товаров: " << storageSize << "\n";
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.get();
		break;
	}
}

void CreateStorage()
{
	const size_t staticSize = 10;
	unsigned int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 };
	std::string name[staticSize]
	{
		"Sanya", "Sonya", "Goga", "Yarik", "Generalyskie", "Casio", "Rolex", "kukushka", "Mexebexa", "Nastennie"
	};
	double price[staticSize]{ 15000, 3000, 5000, 1490.99, 3599, 12999, 28000, 40000, 7777, 25000 };
	unsigned int count[staticSize]{ 50,45,3,100,150,15,500,1,7,1000 };

	if (isStorageCreated)
	{
		delete[]idArr;
		delete[]nameArr;
		delete[]coutArr;
		delete[]priceArr;
	}

	storageSize = staticSize;
	idArr = new unsigned int[storageSize];
	nameArr = new std::string[storageSize];
	coutArr = new unsigned int[storageSize];
	priceArr = new double[storageSize];
	isStorageCreated = true;

	for (size_t i = 0; i < storageSize; i++) {
		idArr[i] = id[i];
		nameArr[i] = name[i];
		coutArr[i] = count[i];
		priceArr[i] = price[i];
	}
}

bool CheckLogin(const std::string& str)
{
	if (str.size() < 5 || str.size() >= 20)
	{
		std::cout << "Недопустимая длина логина. От 5 до 20 символов\n";
		Sleep(1500);
		return false;
	}

	if (!isSetCreated) SetSpecialSymbols();

	for (char sym : str)
	{
		if (!specialSymbols.count(sym))
		{
			std::cout << "Некорректные символы в логине!\n\n";
			Sleep(1500);
			return false;
		}
	}

	for (size_t i = 0; i < userSize; i++)
	{
		if (str == loginArr[i])
		{
			std::cout << "Имя уже занято\n\n";
			Sleep(1500);
			return false;
		}
	}

	return true;
}

void ShowStorage(int mode)
{
	if (!isStorageCreated || storageSize == 0)
	{
		std::cout << "Склад пуст.\n";
		Sleep(1500);
		system("cls");
		return;
	}

	if (mode == 0)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
			<< "Цена\t" << "Кол-во\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
				<< priceArr[i] << "\t" << coutArr[i] << "\n";
		}
		std::cout << "\n";
	}
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
				<< coutArr[i] << "\n";
		}
		std::cout << "\n";
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
				<< priceArr[i] << "\n";
		}
		std::cout << "\n";
	}
	else if (mode == 3)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\n";
		}
		std::cout << "\n";
	}
}

void ChangeAccount()
{
	std::string choose;
	if (!isSetCreated)
	{
		SetSpecialSymbols();
	}
	if (!isPassSetCreated)
	{
		SetPassSymbols();
	}

	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить нового пользователя\n";
		std::cout << "2 - Показать пользователей\n";
		std::cout << "3 - Изменить пароль пользователя\n";
		std::cout << "4 - Удалить пользователя\n";
		std::cout << "0 - Выход из редактора аккаунтов\n";
		std::cout << "Ввод: ";
		Getline(choose);

		if (choose == "1")
		{
			AddNewUser();
		}
		else if (choose == "2")
		{
			ShowUsers();
			system("pause");
			system("cls");
		}
		else if (choose == "3")
		{
			ChangePass();
		}
		else if (choose == "4")
		{
			DeleteUser();
		}
		else if (choose == "0")
		{
			break;
		}
		else
		{
			Err();
		}
		system("cls");
	}
}

void AddStorageItem()
{
	if (!isStorageCreated || storageSize == 0)
	{
		std::cout << "Склад пуст. Сначала добавьте товары.\n";
		Sleep(1500);
		return;
	}

	std::string chooseId, chooseCount, choose;
	unsigned int id = 0, count = 0;
	while (true)
	{
		system("cls");
		ShowStorage(1);
		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции пополнения склада!\n";
			Sleep(1500);
			system("cls");
			break;
		}
		std::cout << "Введите кол-во товара для пополнения: ";
		Getline(chooseCount);

		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > maxItemSize)
			{
				std::cout << "Некорректный id или кол-во\nМаксимальное кол-во - " << maxItemSize << "\n\n";
				Sleep(1500);
			}
			else if (coutArr[id] + count > maxItemSize)
			{
				std::cout << "Превышен лимит товара! Максимум " << maxItemSize << "\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
					<< coutArr[id] << " ---> " << coutArr[id] + count << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					coutArr[id] += count;
					std::cout << "Товар успешно пополнен\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена пополнения!\n";
					Sleep(1500);
					system("cls");
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void RemoveStorageItem()
{
	if (!isStorageCreated || storageSize == 0)
	{
		std::cout << "Склад пуст. Списание невозможно.\n";
		Sleep(1500);
		return;
	}

	std::string chooseId, chooseCount, choose;
	unsigned int id = 0, count = 0;
	while (true)
	{
		system("cls");
		ShowStorage(1);
		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции списания товара!\n";
			Sleep(1500);
			system("cls");
			break;
		}
		std::cout << "Введите кол-во товара для списания: ";
		Getline(chooseCount);

		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > coutArr[id])
			{
				std::cout << "Некорректный id или кол-во\nМаксимальное кол-во - " << coutArr[id] << "\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
					<< coutArr[id] << " ---> " << coutArr[id] - count << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					coutArr[id] -= count;
					std::cout << "Товар успешно списан\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена списания!\n";
					Sleep(1500);
					system("cls");
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void ShowSuperAdminMenu()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Изменить цену\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчет о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		Getline(choose);

		if (choose == "1")
		{
			Selling();
			system("cls");
		}
		else if (choose == "2")
		{
			ShowStorage();
			system("pause");
			system("cls");
		}
		else if (choose == "3")
		{
			AddStorageItem();
		}
		else if (choose == "4")
		{
			RemoveStorageItem();
		}
		else if (choose == "5")
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeAccount();
		}
		else if (choose == "8")
		{
			ShowIncome();
		}
		else if (choose == "0")
		{
			if (Logout() == true)
			{
				break;
			}
			system("cls");
		}
		else
		{
			Err();
		}
	}
}

void ShowAdminMenu()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Изменить цену\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчет о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		Getline(choose);

		if (choose == "1")
		{
			Selling();
			system("cls");
		}
		else if (choose == "2")
		{
			ShowStorage();
			system("pause");
			system("cls");
		}
		else if (choose == "3")
		{
			AddStorageItem();
		}
		else if (choose == "4")
		{
			RemoveStorageItem();
		}
		else if (choose == "5")
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeAccount();
		}
		else if (choose == "8")
		{
			ShowIncome();
		}
		else if (choose == "0")
		{
			if (Logout() == true)
			{
				break;
			}
			system("cls");
		}
		else
		{
			Err();
		}
	}
}

void ShowuserMenu()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Отчет о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		Getline(choose);

		if (choose == "1")
		{
			Selling();
			system("cls");
		}
		else if (choose == "2")
		{
			ShowStorage();
			system("pause");
			system("cls");
		}
		else if (choose == "3")
		{
			ShowIncome();
		}
		else if (choose == "0")
		{
			if (Logout() == true)
			{
				break;
			}
			system("cls");
		}
		else
		{
			Err();
		}
	}
}

bool IsNumber(const std::string& str)
{
	if (str.empty() || str.size() >= 10)
	{
		std::cout << "Некорректный ввод\n";
		std::cout << "Ошибка размера числа. От 1 до 9 символов включительно\n\n";
		Sleep(1500);
		return false;
	}

	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Некорректный ввод\n";
			std::cout << "Введенные данные не являются числом\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}

void Start()
{
	std::string choose;
	std::cout << "\n\n\nСистема управления складом\n\n\n";
	while (true)
	{
		if (Login())
		{
			system("cls");
			if (currentStatus == userStatus[0])
			{
				while (true)
				{
					std::cout << "Выберите тип склада\n1 - Готовый\n2 - Новый\nВвод: ";
					Getline(choose);
					if (choose == "1")
					{
						if (!isStorageCreated)
						{
							CreateStorage();
						}
						system("cls");
						ShowSuperAdminMenu();
						break;
					}
					else if (choose == "2")
					{
						if (!isStorageCreated)
						{
							CreateNewStorage();
						}
						system("cls");
						ShowSuperAdminMenu();
						break;
					}
					else
					{
						Err();
					}
				}
			}
			else if (currentStatus == userStatus[1])
			{
				if (!isStorageCreated)
				{
					CreateStorage();
				}
				system("cls");
				ShowAdminMenu();
			}
			else if (currentStatus == userStatus[2])
			{
				if (!isStorageCreated)
				{
					CreateStorage();
				}
				system("cls");
				ShowuserMenu();
			}
		}
		else
		{
			system("cls");
			std::cout << "Итоговая прибыль за смену: " << cashIncome + bankIncome;
			std::cout << "\n\nЗавершение работы\n";
			Sleep(2000);
			system("cls");
			break;
		}
	}
}

void CreateEmptyStorage()
{
	if (isStorageCreated)
	{
		delete[] idArr;
		delete[] nameArr;
		delete[] coutArr;
		delete[] priceArr;
	}

	storageSize = 0;
	idArr = nullptr;
	nameArr = nullptr;
	coutArr = nullptr;
	priceArr = nullptr;
	isStorageCreated = true;

	std::cout << "Новый склад успешно создан (пустой)\n";
	Sleep(1500);
}

bool Login()
{
	std::string login, pass;
	while (true)
	{
		std::cout << "Введите логин (или \"exit\" для выхода): ";
		Getline(login);
		std::cout << "Введите пароль: ";
		Getline(pass);

		if (login == "exit" && pass == "exit")
		{
			currentStatus = "";
			return false;
		}

		if (login == loginArr[0] && pass == passArr[0])
		{
			std::cout << "Пользователь: " << loginArr[0] << "\nДобро пожаловать!\n";
			std::cout << "Ваш статус: " << userStatus[0] << "\n\n";
			currentStatus = statusArr[0];
			currentId = 0;
			system("pause");
			return true;
		}

		for (size_t i = 1; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				std::cout << "Пользователь: " << loginArr[i] << "\nДобро пожаловать!\n";
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
				currentStatus = statusArr[i];
				currentId = i;
				system("pause");
				return true;
			}
		}

		Err();
		Sleep(1500);
		system("cls");
	}
}

inline void Getline(std::string& str)
{
	std::getline(std::cin, str);
}

inline void Err()
{
	std::cout << "Некорректный ввод\n\n";
	Sleep(1000);
}

bool Logout()
{
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "Для подтверждения выхода из пользователя введите ваш пароль или \"exit\" для возврата в меню: ";
		Getline(choose);
		if (choose == "exit")
		{
			system("cls");
			return false;
		}
		else if (currentId == 0 && choose == passArr[0])
		{
			system("cls");
			return true;
		}
		else if (currentId > 0 && choose == passArr[currentId])
		{
			system("cls");
			return true;
		}
		else
		{
			Err();
		}
	}
}

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
		dynamicArr[i] = staticArr[i];
	}
}