#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;


void PrintMainMenue() {
	cout << "\n================================================\n\n";
	cout << "\t\tMain Menue Screen\n\n";
	cout << "================================================\n\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Updata Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] LogOut.\n\n";
	cout << "================================================\n\n";
}

struct stClientData {
	string AccountNumber = "";
	string PinCode = "";
	string ClientName = "";
	string Phone = "";
	double AccountBalance = 0;
};

struct stUsersInfo {
	string UserName = "";
	string PassWord = "";
	short Permission = 0;
};

enum enMainMenue { ShowClientsList = 1, AddClient, DeleteClient, UpdataClient, FindClient, Transactions, ManageUsers, LogOut };

string ClientsFileName = "Clients.txt";

string UsersFileName = "Users.txt";

enum enMainMenuePermissions { All = -1, pClientsList = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64 };

short ChoiceFromMenue(string st) {
	short choice = 0;
	cout << st;
	cin >> choice;
	return choice;
}

string ChoiceAccountNumber() {
	string AccountNumber = "";
	cout << "\n\nPlease Enter Account Number : ";
	cin >> AccountNumber;
	return AccountNumber;
}

vector <string> SplitStringinVector(string line, string Seprator = "(//)") {
	vector <string> vec;
	short index = 0;
	string word = "";
	while ((index = line.find(Seprator)) != std::string::npos)
	{
		word = line.substr(0, index);
		if (word != "")
		{
			vec.push_back(word);
		}
		line.erase(0, index + Seprator.length());
	}
	if (line != "")
	{
		vec.push_back(line);
	}
	return vec;
}

stClientData ConvertDataFromStringToStructOfstClientData(string& line) {

	vector <string> vec = SplitStringinVector(line);

	stClientData ClientData;

	if (vec.size() == 5)
	{
		ClientData.AccountNumber = vec.at(0);
		ClientData.PinCode = vec.at(1);
		ClientData.ClientName = vec.at(2);
		ClientData.Phone = vec.at(3);
		ClientData.AccountBalance = stod(vec.at(4));
	}

	return ClientData;
}

stUsersInfo ConvertDataFromStringToStructOfstUsersInfo(string& line) {

	vector <string> vec = SplitStringinVector(line);

	stUsersInfo UsersInfo;

	if (vec.size() == 3)
	{
		UsersInfo.UserName = vec.at(0);
		UsersInfo.PassWord = vec.at(1);
		UsersInfo.Permission = stoi(vec.at(2));
	}

	return UsersInfo;
}

vector <string> LoadDataFromFileToVectorOfString(string& FileName) {
	vector <string> vec;
	fstream myfile;
	myfile.open(FileName, ios::in);
	if (myfile.is_open())
	{
		string line = "";
		while (getline(myfile, line))
		{
			vec.push_back(line);
		}
	}
	myfile.close();
	return vec;
}

void PrintHeaderTaple(int size) {
	cout << "\n\n\t\t\t\tClient List (" << size << ") Clients.\n\n";
	cout << "--------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(20) << "Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(20) << "Account Balance";
	cout << "\n\n--------------------------------------------------------------------------------------\n\n";
}

void PrintClientDatainList(stClientData& ClientData) {
	cout << "| " << left << setw(15) << ClientData.AccountNumber;
	cout << "| " << left << setw(10) << ClientData.PinCode;
	cout << "| " << left << setw(20) << ClientData.ClientName;
	cout << "| " << left << setw(15) << ClientData.Phone;
	cout << "| " << left << setw(20) << ClientData.AccountBalance;
}

void PressAnyKeyToBackMainMenueOrTransactionMenue(string st) {
	cout << st;
	system("pause > 0");
}

void PrintClientsList(vector <string>& vec, stClientData& ClientData) {
	PrintHeaderTaple(vec.size());
	for (string& line : vec)
	{
		ClientData = ConvertDataFromStringToStructOfstClientData(line);
		PrintClientDatainList(ClientData);
		cout << endl;
	}
	cout << "\n\n--------------------------------------------------------------------------------------\n\n";
	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Main Menue...");
}

bool AccountNumberIsFound(string& AccountNumber) {
	vector <string> vec = LoadDataFromFileToVectorOfString(ClientsFileName);
	stClientData ClientData;
	for (string& line : vec)
	{
		ClientData = ConvertDataFromStringToStructOfstClientData(line);
		if (ClientData.AccountNumber == AccountNumber)
		{
			return true;
		}
	}
	return false;
}

void ReadStructOfstClientData(stClientData& ClientData) {
	cout << "Enter Account Number  : ";
	getline(cin >> ws, ClientData.AccountNumber);

	while (AccountNumberIsFound(ClientData.AccountNumber))
	{
		cout << "\n\nClient with [" << ClientData.AccountNumber << "] already exists, ";
		cout << "Enter another Account Number : ";
		getline(cin >> ws, ClientData.AccountNumber);
	}

	cout << "Enter Pin Code        : ";
	getline(cin, ClientData.PinCode);

	cout << "Enter Name            : ";
	getline(cin, ClientData.ClientName);

	cout << "Enter Phone           : ";
	getline(cin, ClientData.Phone);

	cout << "Enter Account Balance : ";
	cin >> ClientData.AccountBalance;
}

string ConvertDataFromStructOfstClientDataToString(stClientData& ClientData, string Seprator = "(//)") {
	string line = ClientData.AccountNumber + Seprator;
	line += ClientData.PinCode + Seprator;
	line += ClientData.ClientName + Seprator;
	line += ClientData.Phone + Seprator;
	line += to_string(ClientData.AccountBalance);
	return line;
}

void SaveDataFromVectorOfStringToFile(vector <string>& vec, string& FileName) {
	fstream myfile;
	myfile.open(FileName, ios::out);
	if (myfile.is_open())
	{
		for (string& line : vec)
		{
			if (line != "")
			{
				myfile << line << endl;
			}
		}
	}
	myfile.close();
}

void PrintAddScreen() {
	cout << "--------------------------------";
	cout << "\n\n   Add New Clients Screen\n\n";
	cout << "--------------------------------";
	cout << "\nAdding New Client:\n\n";
}

void AddNewClient(stClientData& ClientData, string FileName) {

	PrintAddScreen();

	string line = "";

	fstream myfile;
	myfile.open(FileName, ios::app);

	if (myfile.is_open())
	{
		char AddAgaine = 'Y';
		while (toupper(AddAgaine) == 'Y')
		{
			ReadStructOfstClientData(ClientData);

			line = ConvertDataFromStructOfstClientDataToString(ClientData);

			myfile << line << endl;

			cout << "\n\nClient Added Successfully.\n";
			cout << "\n\nDo you want to add more clients (Y, N) ?  ";
			cin >> AddAgaine;
		}
	}
	myfile.close();

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Main Menue...");
}

void PrintClientData(stClientData& ClientData) {
	cout << "\n\nClient Data:\n";
	cout << "------------------------------------------------------------\n";
	cout << "Account Number  : " << ClientData.AccountNumber << endl;
	cout << "Pin Code        : " << ClientData.PinCode << endl;
	cout << "Client Name     : " << ClientData.ClientName << endl;
	cout << "Phone           : " << ClientData.Phone << endl;
	cout << "Account Balance : " << ClientData.AccountBalance << endl;
	cout << "------------------------------------------------------------\n\n";
}

bool FindClientByAccountNamber(vector<string>& vec, stClientData& ClientData, short& ClientIndex, string AccountNumber) {

	for (string& line : vec)
	{
		ClientData = ConvertDataFromStringToStructOfstClientData(line);

		if (ClientData.AccountNumber == AccountNumber)
		{
			return true;
		}
		ClientIndex++;
	}
	return false;
}

void PrintDeleteScreen() {
	cout << "--------------------------------";
	cout << "\n\n   Delete Client Screen\n\n";
	cout << "--------------------------------";
}

void DeleteClientUsingAccountNumber(vector<string>& vec, stClientData& ClientData) {

	PrintDeleteScreen();

	string AccountNumber = ChoiceAccountNumber();

	short ClientIndex = 0;

	if (FindClientByAccountNamber(vec, ClientData, ClientIndex, AccountNumber))
	{

		PrintClientData(ClientData);

		char sure = 'Y';
		cout << "\n\nAre you sure you want delete this client (Y, N) ? ";
		cin >> sure;

		if (toupper(sure) == 'Y')
		{
			vec.at(ClientIndex) = "";
			SaveDataFromVectorOfStringToFile(vec, ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
		}
		else
		{
			cout << "\n\nClient don't deleted.";
		}
	}
	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Main Menue...");
}

void ChangeClientData(stClientData& ClientData) {
	cout << "\n\nEnter Pin Code        : ";
	getline(cin >> ws, ClientData.PinCode);

	cout << "Enter Name            : ";
	getline(cin, ClientData.ClientName);

	cout << "Enter Phone           : ";
	getline(cin, ClientData.Phone);

	cout << "Enter Account Balance : ";
	cin >> ClientData.AccountBalance;
}

void PrintUpdataScreen() {
	cout << "--------------------------------";
	cout << "\n\n  Updata Client Info Screen\n\n";
	cout << "--------------------------------";
}

void UpdataClientUsingAccountNumber(vector<string>& vec, stClientData& ClientData) {

	PrintUpdataScreen();

	string AccountNumber = ChoiceAccountNumber();

	short ClientIndex = 0;

	if (FindClientByAccountNamber(vec, ClientData, ClientIndex, AccountNumber))
	{

		PrintClientData(ClientData);

		char sure = 'Y';
		cout << "\n\nAre you sure you want updata this client (Y, N) ? ";
		cin >> sure;

		if (toupper(sure) == 'Y')
		{
			ChangeClientData(ClientData);
			vec.at(ClientIndex) = ConvertDataFromStructOfstClientDataToString(ClientData);
			SaveDataFromVectorOfStringToFile(vec, ClientsFileName);
			cout << "\n\nClient Updata Successfully.";
		}
		else
		{
			cout << "\n\nClient don't updated.";
		}
	}
	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Main Menue...");
}

void PrintFindScreen() {
	cout << "--------------------------------";
	cout << "\n\n\  Find Client Screen\n\n";
	cout << "--------------------------------";
}

void FindAndPrintClientUsingAccountNumber(vector<string>& vec, stClientData& ClientData) {

	PrintFindScreen();

	string AccountNumber = ChoiceAccountNumber();

	short ClientIndex = 0;

	if (FindClientByAccountNamber(vec, ClientData, ClientIndex, AccountNumber))
	{
		PrintClientData(ClientData);
	}
	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Main Menue...");
}

enum enTransactions { Deposit = 1, Withdraw, TotalBalances, MainMenue };

void PrintTransactionsMenue() {
	cout << "\n================================================\n\n";
	cout << "\tTransactions Menue Screen\n\n";
	cout << "================================================\n\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n\n";
	cout << "================================================\n\n";
}

int ReadDepositOrWithdrawAmount(string st) {
	int DepositOrWithdrawAmount = 0;
	cout << st;
	cin >> DepositOrWithdrawAmount;
	return DepositOrWithdrawAmount;
}

void PrintDepositScreen() {
	cout << "--------------------------------";
	cout << "\n\n    Deposit Screen\n\n";
	cout << "--------------------------------";
}

void DepositTransaction(vector<string>& vec, stClientData& ClientData) {

	PrintDepositScreen();

	bool isWrongAccountNumber = true;

	short ClientIndex = 0;

	while (isWrongAccountNumber)
	{
		string AccountNumber = ChoiceAccountNumber();

		if (FindClientByAccountNamber(vec, ClientData, ClientIndex, AccountNumber))
		{
			PrintClientData(ClientData);

			int DepositAmount = 0;

			DepositAmount = ReadDepositOrWithdrawAmount("\n\nPlease enter deposit amount ? ");

			char sure = 'Y';
			cout << "\n\nAre you sure you want peform this transaction (Y, N) ? ";
			cin >> sure;

			if (toupper(sure) == 'Y')
			{
				ClientData.AccountBalance += DepositAmount;
				vec.at(ClientIndex) = ConvertDataFromStructOfstClientDataToString(ClientData);
				SaveDataFromVectorOfStringToFile(vec, ClientsFileName);
				cout << "\nDone Successfully.\nNew Balance is : " << ClientData.AccountBalance;
				break;
			}
			else
			{
				cout << "\n\nNothing happened, Everything it's same.";
				break;
			}

		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
		}

	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Transactions Menue...");
}

void PrintWithdrawScreen() {
	cout << "--------------------------------";
	cout << "\n\n    Withdraw Screen\n\n";
	cout << "--------------------------------";
}

void WithdrawTransaction(vector<string>& vec, stClientData& ClientData) {

	PrintWithdrawScreen();

	bool isWrongAccountNumber = true;

	short ClientIndex = 0;

	while (isWrongAccountNumber)
	{
		string AccountNumber = ChoiceAccountNumber();

		if (FindClientByAccountNamber(vec, ClientData, ClientIndex, AccountNumber))
		{
			PrintClientData(ClientData);

			int WithdrawAmount = 0;

			WithdrawAmount = ReadDepositOrWithdrawAmount("\n\nPlease enter withdraw amount ? ");

			while (WithdrawAmount > ClientData.AccountBalance)
			{
				cout << "\nAmoundt Exeeds the balance, you can withdraw up to : " << ClientData.AccountBalance;
				WithdrawAmount = ReadDepositOrWithdrawAmount("\n\nPlease enter another amount ? ");
			}

			char sure = 'Y';
			cout << "\n\nAre you sure you want peform this transaction (Y, N) ? ";
			cin >> sure;

			if (toupper(sure) == 'Y')
			{
				ClientData.AccountBalance -= WithdrawAmount;
				vec.at(ClientIndex) = ConvertDataFromStructOfstClientDataToString(ClientData);
				SaveDataFromVectorOfStringToFile(vec, ClientsFileName);
				cout << "\nDone Successfully.\nNew Balance is : " << ClientData.AccountBalance;
				break;
			}
			else
			{
				cout << "\n\nNothing happened, Everything it's same.";
				break;
			}

		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
		}

	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Transactions Menue...");
}

void PrintHeaderTapleOfBalances(int size) {
	cout << "\n\n\t\t\t\tBalances List (" << size << ") Clients.\n\n";
	cout << "--------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(20) << "Client Name";
	cout << "| " << left << setw(20) << "Balance";
	cout << "\n\n--------------------------------------------------------------------------------------\n\n";
}

void PrintClientBalanceinList(stClientData& ClientData) {
	cout << "| " << left << setw(15) << ClientData.AccountNumber;
	cout << "| " << left << setw(20) << ClientData.ClientName;
	cout << "| " << left << setw(20) << ClientData.AccountBalance;
}

void PrintTotalBalances(vector<string>& vec, stClientData& ClientData) {

	PrintHeaderTapleOfBalances(vec.size());

	double BalancesSum = 0;

	for (string& line : vec)
	{
		ClientData = ConvertDataFromStringToStructOfstClientData(line);
		BalancesSum += ClientData.AccountBalance;
		PrintClientBalanceinList(ClientData);
		cout << endl;
	}
	cout << "\n\n--------------------------------------------------------------------------------------\n\n";

	cout << "\t\t\t\tTotal Balances = " << BalancesSum;

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Transactions Menue...");
}

void TransactionsBegin(vector<string>& vec, stClientData& ClientData) {

	short choice = 0;

	do
	{
		system("cls");

		PrintTransactionsMenue();

		choice = ChoiceFromMenue("Choose what do you want to do [1 to 4] ?  ");

		if (choice == enTransactions::Deposit)
		{
			system("cls");
			DepositTransaction(vec, ClientData);
		}
		else if (choice == enTransactions::Withdraw)
		{
			system("cls");
			WithdrawTransaction(vec, ClientData);
		}
		else if (choice == enTransactions::TotalBalances)
		{
			system("cls");
			PrintTotalBalances(vec, ClientData);
		}

	} while (choice != enTransactions::MainMenue);

}

void PrintManageUsersMenue() {
	cout << "\n================================================\n\n";
	cout << "\tManage Users Menue Screen\n\n";
	cout << "================================================\n\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Updata User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n\n";
	cout << "================================================\n\n";
}

void PrintHeaderTapleOfUsersList(int size) {
	cout << "\n\n\t\t\t\tUsers List (" << size << ") User(s).\n\n";
	cout << "--------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "PassWord";
	cout << "| " << left << setw(12) << "Permissions";
	cout << "\n\n--------------------------------------------------------------------------------------\n\n";
}

void PrintUserDatainList(stUsersInfo& UsersInfo) {
	cout << "| " << left << setw(15) << UsersInfo.UserName;
	cout << "| " << left << setw(10) << UsersInfo.PassWord;
	cout << "| " << left << setw(12) << UsersInfo.Permission;
}

void PrintUsersList(vector <string>& vec, stUsersInfo& UsersInfo) {

	PrintHeaderTapleOfUsersList(vec.size());

	for (string& line : vec)
	{
		UsersInfo = ConvertDataFromStringToStructOfstUsersInfo(line);
		PrintUserDatainList(UsersInfo);
		cout << endl;
	}

	cout << "\n\n--------------------------------------------------------------------------------------\n\n";

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Manage Users Menue...");
}

bool UserNameIsFound(string& UserName) {
	vector <string> vec = LoadDataFromFileToVectorOfString(UsersFileName);
	stUsersInfo UsersInfo;
	for (string& line : vec)
	{
		UsersInfo = ConvertDataFromStringToStructOfstUsersInfo(line);
		if (UsersInfo.UserName == UserName)
		{
			return true;
		}
	}
	return false;
}

void CheckIsValidAnswer(char& Answer) {

	while (tolower(Answer) != 'y' && tolower(Answer) != 'n')
	{
		cout << "\nInvalid Answer!\n";
		cout << "\nPlease Answer (y, n) ? ";
		cin >> Answer;
	}
}

short ReadPermissions() {

	short Permissions = 0;
	char Answer = 'n';


	cout << "\nDo you want to give full access (y/ n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		return Permissions = enMainMenuePermissions::All;
	}

	cout << "\n\nDo you want to give access to:\n\n";


	cout << "Show Client List (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pClientsList;
	}

	cout << "Add New Client (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pAddClient;
	}

	cout << "Delete Client (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pDeleteClient;
	}

	cout << "Update Client (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pUpdateClient;
	}

	cout << "Find Client (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pFindClient;
	}

	cout << "Transactions (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pTransactions;
	}

	cout << "Manage Users (y, n) ? ";
	cin >> Answer;
	CheckIsValidAnswer(Answer);
	if (tolower(Answer) == 'y')
	{
		Permissions += enMainMenuePermissions::pManageUsers;
	}

	return Permissions;
}

void ReadStructOfstUsersInfo(stUsersInfo& UsersInfo) {

	cout << "\nEnter User Name  : ";
	getline(cin >> ws, UsersInfo.UserName);

	while (UserNameIsFound(UsersInfo.UserName))
	{
		cout << "\n\nUser with User Name [" << UsersInfo.UserName << "] already exists, ";
		cout << "Enter another User Name : ";
		getline(cin >> ws, UsersInfo.UserName);
	}

	cout << "Enter PassWord   : ";
	getline(cin, UsersInfo.PassWord);


	UsersInfo.Permission = ReadPermissions();
}

string ConvertDataFromStructOfstUsersInfoToString(stUsersInfo& UsersInfo, string Seprator = "(//)") {

	string line = UsersInfo.UserName + Seprator;

	line += UsersInfo.PassWord + Seprator;
	line += to_string(UsersInfo.Permission);

	return line;
}

void PrintAddNewUserScreen() {
	cout << "--------------------------------";
	cout << "\n\n   Add New User Screen\n\n";
	cout << "--------------------------------";
	cout << "\nAdding New User:\n\n";
}

void AddNewUser(stUsersInfo& UsersInfo, string UsresFileName) {

	PrintAddNewUserScreen();

	string line = "";

	fstream myfile;
	myfile.open(UsresFileName, ios::app);

	if (myfile.is_open())
	{
		char AddAgaine = 'Y';

		while (toupper(AddAgaine) == 'Y')
		{
			ReadStructOfstUsersInfo(UsersInfo);

			line = ConvertDataFromStructOfstUsersInfoToString(UsersInfo);

			myfile << line << endl;

			cout << "\n\nUser Added Successfully.\n";
			cout << "\n\nDo you want to add more users (Y, N) ?  ";
			cin >> AddAgaine;
		}
	}
	myfile.close();

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Manage Users Menue...");
}

void PrintUserData(stUsersInfo& UsersInfo) {
	cout << "\n\nUser Data:\n";
	cout << "------------------------------------------------------------\n";
	cout << "User Name       : " << UsersInfo.UserName << endl;
	cout << "PassWord        : " << UsersInfo.PassWord << endl;
	cout << "Permissions     : " << UsersInfo.Permission << endl;
	cout << "------------------------------------------------------------\n\n";
}

bool FindUserByUserName(vector<string>& vec, stUsersInfo& UsersInfo, short& UserIndex, string UserName) {

	for (string& line : vec)
	{
		UsersInfo = ConvertDataFromStringToStructOfstUsersInfo(line);

		if (UsersInfo.UserName == UserName)
		{
			return true;
		}

		UserIndex++;
	}
	return false;
}

string ChoiceUserName() {
	string UserName = "";
	cout << "\n\nPlease Enter UserName : ";
	cin >> UserName;
	return UserName;
}

void PrintDeleteUsersScreen() {
	cout << "--------------------------------";
	cout << "\n\n   Delete Users Screen\n\n";
	cout << "--------------------------------";
}

void DeleteUserUsingUserName(vector<string>& vec, stUsersInfo& UsersInfo) {

	PrintDeleteUsersScreen();

	string UserName = ChoiceUserName();

	if (UserName == "admin")
	{
		cout << "\n\nYou cannot delete this user.\n";
		PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Manage Users Menue...");
		return;
	}

	short UserIndex = 0;

	if (FindUserByUserName(vec, UsersInfo, UserIndex, UserName))
	{

		PrintUserData(UsersInfo);

		char sure = 'Y';
		cout << "\n\nAre you sure you want delete this user (Y, N) ? ";
		cin >> sure;

		if (toupper(sure) == 'Y')
		{
			vec.at(UserIndex) = "";
			SaveDataFromVectorOfStringToFile(vec, UsersFileName);
			cout << "\n\nUser Deleted Successfully.";
		}
		else
		{
			cout << "\n\nUser don't deleted.";
		}
	}
	else
	{
		cout << "\n\nUser with UserName (" << UserName << ") is Not Found!\n\n";
	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Manage Users Menue...");
}

void ChangeUserData(stUsersInfo& UsersInfo) {

	cout << "\nEnter PassWord : ";
	getline(cin >> ws, UsersInfo.PassWord);


	UsersInfo.Permission = ReadPermissions();
}

void PrintUpdataUserScreen() {
	cout << "--------------------------------";
	cout << "\n\n  Updata User Info Screen\n\n";
	cout << "--------------------------------";
}

void UpdataUserUsingUserName(vector<string>& vec, stUsersInfo& UsersInfo) {

	PrintUpdataUserScreen();

	string UserName = ChoiceUserName();

	short UserIndex = 0;

	if (FindUserByUserName(vec, UsersInfo, UserIndex, UserName))
	{

		PrintUserData(UsersInfo);

		char sure = 'Y';
		cout << "\n\nAre you sure you want to updata this user (Y, N) ? ";
		cin >> sure;

		if (toupper(sure) == 'Y')
		{
			ChangeUserData(UsersInfo);
			vec.at(UserIndex) = ConvertDataFromStructOfstUsersInfoToString(UsersInfo);
			SaveDataFromVectorOfStringToFile(vec, UsersFileName);
			cout << "\n\nUser Updata Successfully.";
		}
		else
		{
			cout << "\n\nUser don't updated.";
		}
	}
	else
	{
		cout << "\n\nUser with User Name (" << UserName << ") is Not Found!\n\n";
	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Manage Users Menue...");
}

void PrintFindUserScreen() {
	cout << "--------------------------------";
	cout << "\n\n\  Find User Screen\n\n";
	cout << "--------------------------------";
}

void FindAndPrintUserUsingUserName(vector<string>& vec, stUsersInfo& UsersInfo) {

	PrintFindUserScreen();

	string UserName = ChoiceUserName();

	short UserIndex = 0;

	if (FindUserByUserName(vec, UsersInfo, UserIndex, UserName))
	{
		PrintUserData(UsersInfo);
	}
	else
	{
		cout << "\n\nUser with User Name (" << UserName << ") is Not Found!\n\n";
	}

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Manage Users Menue...");
}

void PrintAccessDeniedMassage() {
	cout << "\n\n---------------------------------------------\n\n";
	cout << "Access Denied,\n";
	cout << "You dont have permission to do this,\n";
	cout << "Please Connect Your Admin.";
	cout << "\n\n---------------------------------------------";

	PressAnyKeyToBackMainMenueOrTransactionMenue("\n\nPress any key to go back to Main Menue...");
}

enum enManageUsers { ListUsers = 1, AddUser, DeleteUser, UpdateUser, FindUser, MainMenue2 };

void ManageUsersBegin() {

	vector <string> vec;
	stUsersInfo UsersInfo;
	short choice = 0;

	do
	{
		system("cls");

		vec = LoadDataFromFileToVectorOfString(UsersFileName);

		PrintManageUsersMenue();

		choice = ChoiceFromMenue("Choose what do you want to do [1 to 6] ?  ");

		if (choice == enManageUsers::ListUsers)
		{
			system("cls");
			PrintUsersList(vec, UsersInfo);
		}
		else if (choice == enManageUsers::AddUser)
		{
			system("cls");
			AddNewUser(UsersInfo, UsersFileName);
		}
		else if (choice == enManageUsers::DeleteUser)
		{
			system("cls");
			DeleteUserUsingUserName(vec, UsersInfo);
		}
		else if (choice == enManageUsers::UpdateUser)
		{
			system("cls");
			UpdataUserUsingUserName(vec, UsersInfo);
		}
		else if (choice == enManageUsers::FindUser)
		{
			system("cls");
			FindAndPrintUserUsingUserName(vec, UsersInfo);
		}

	} while (choice != enManageUsers::MainMenue2);
}

bool CheckFromPermission(short UserPermission, short Permission) {

	if (UserPermission == enMainMenuePermissions::All)
	{
		return true;
	}

	if ((UserPermission & Permission) == Permission)
	{
		return true;
	}

	return false;
}

void LogIn();

void ProgramBegin(short UserPermission) {

	vector <string> vec;
	stClientData ClientData;
	short choice = 0;

	do
	{
		system("cls");

		vec = LoadDataFromFileToVectorOfString(ClientsFileName);

		PrintMainMenue();

		choice = ChoiceFromMenue("Choose what do you want to do [1 to 8] ?  ");

		if (choice == enMainMenue::ShowClientsList)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pClientsList))
			{
				system("cls");
				PrintClientsList(vec, ClientData);
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::AddClient)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pAddClient))
			{
				system("cls");
				AddNewClient(ClientData, ClientsFileName);
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::DeleteClient)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pDeleteClient))
			{
				system("cls");
				DeleteClientUsingAccountNumber(vec, ClientData);
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::UpdataClient)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pUpdateClient))
			{
				system("cls");
				UpdataClientUsingAccountNumber(vec, ClientData);
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::FindClient)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pFindClient))
			{
				system("cls");
				FindAndPrintClientUsingAccountNumber(vec, ClientData);
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::Transactions)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pTransactions))
			{
				system("cls");
				TransactionsBegin(vec, ClientData);
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::ManageUsers)
		{
			if (CheckFromPermission(UserPermission, enMainMenuePermissions::pManageUsers))
			{
				system("cls");
				ManageUsersBegin();
			}
			else
			{
				system("cls");
				PrintAccessDeniedMassage();
			}
		}
		else if (choice == enMainMenue::LogOut)
		{
			system("cls");
			LogIn();
		}
	} while (choice != 0);
}

void PrintLogInScreen() {
	cout << "\n---------------------------------\n\n";
	cout << "\tLogin Screen";
	cout << "\n\n---------------------------------\n\n";
}

stUsersInfo ReadUsersInfoByUserNameAndPassword() {

	stUsersInfo UsersInfo;

	cout << "Enter UserName : ";
	getline(cin >> ws, UsersInfo.UserName);

	cout << "Enter PassWord : ";
	getline(cin, UsersInfo.PassWord);


	return UsersInfo;
}

bool findUser(stUsersInfo& UsersInfo) {

	stUsersInfo UsIn;

	fstream UsersFile;
	UsersFile.open(UsersFileName, ios::in);

	if (UsersFile.is_open())
	{
		string line = "";

		while (getline(UsersFile, line))
		{
			UsIn = ConvertDataFromStringToStructOfstUsersInfo(line);

			if (UsIn.UserName == UsersInfo.UserName && UsIn.PassWord == UsersInfo.PassWord)
			{
				UsersInfo.Permission = UsIn.Permission;
				return true;
			}
		}
	}

	return false;
}

void LogIn() {

	PrintLogInScreen();

	stUsersInfo UsersInfo = ReadUsersInfoByUserNameAndPassword();

	while (!findUser(UsersInfo))
	{
		system("cls");
		PrintLogInScreen();
		cout << "Invalid UserName / PassWord!\n\n";
		UsersInfo = ReadUsersInfoByUserNameAndPassword();
	}

	ProgramBegin(UsersInfo.Permission);

}

int main()
{

	LogIn();


	system("pause > 0");
	return 0;
}


