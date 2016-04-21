#include<iostream>
#include<time.h>
#include<cstdlib>
#include<string.h>
#include<vector>
#define clrscr() system("cls")
#define getch() system("pause")
using namespace std;




struct PersonDetails
{
	std::string Name;

	std::string Address;

	long int PhoneNumber;
};

struct AccountDetails
{
	long int AccountNumber;
	long int PIN_Number;
	float Balance;

};

struct Loan
{
	float Amount;
	float intrest;
	float rate;
	float monthlyCharges;
	char CollateralObject[50];
	float collateralWorth;
	int time;
};

struct tempData
{
	std::string name;
	long int num;
	tempData();
};


class Bank
{
private:

	PersonDetails personDets;
	AccountDetails accountDets;
	Loan loanDets;

	void fill_PersonDetails();
	void fill_AccountDetails();
public:
	Bank();
	void __init();
	Bank(int id) { accountDets.AccountNumber = id; }
	std::string getAccountName() { return personDets.Name; }
	long int getAccountNumber() { return accountDets.AccountNumber; }
	float getMonthlyInstallment() { return loanDets.monthlyCharges; }
	float getBalance() { return accountDets.Balance; }
	void setBalance(float amt);
	void Take_Loan();
	void setNewPinNumber();
	void ToString();
	~Bank();

protected :
	long int getPIN() { return accountDets.PIN_Number; }
};

vector<Bank> accounts;

void View_Balance( Bank& acc);
void Withdraw_Cash( Bank& acc);
void Deposit_Cash(Bank& acc);
void Pay_Loan_Monthly_Installment( Bank& acc);

Bank getAccount(int);
int fetchAccount();
void Create_Account();
void ViewAllAccounts();
void GiveLoan();
void ChangePin();
void CloseAccount();



void Menu();

int main() {

	Menu();

}

int Authority_Menu() {
	int x =0;
	//TODO: Implement a password function
	while (x != 6)
	{
		clrscr();
		cout << "1. Create New Account" << endl
			<< "2. Close Account" << endl
			<< "3. Change Pin Number" << endl
			<< "4. Give Loan" << endl
			<< "5. View All Accounts" << endl
			<< "6.LOG OUT\n>> ";
		cin >> x;
		switch (x)
		{
		case 1: Create_Account(); break;
		case 2: CloseAccount(); break;
		case 3: ChangePin(); break;
		case 4:	GiveLoan(); break;
		case 5: ViewAllAccounts(); break;
		case 6: break;

		default: cout << "Invalid Number";
			break;
		}

	}
	return 0;
}
int Customer_Menu() {
	int x = 0;
	Bank acc;

	int index = fetchAccount();
	if (index != -1)
		acc = getAccount(index);
	else {
		cout << "Account Not Found\n";
		getch();
		x = 5;
	}

	getch();
	while (x != 5)
	{
		clrscr();
		cout << "1. View Balance" << endl
			<< "2. Withdraw Cash" << endl
			<< "3. Deposit Cash" << endl
			<< "4. Pay Monthly Installment" << endl
			<< "5. LOG OUT" << endl
			<< ">> ";
		cin >> x;
		switch (x)
		{
		case 1: View_Balance( acc); break;
		case 2: Withdraw_Cash(acc); break;
		case 3: Deposit_Cash(acc); break;
		case 4:	Pay_Loan_Monthly_Installment(acc); break;
		case 5:  break;
		default: cout << "Invalid Number";
			break;
		}

	}
	return 0;

}

void Menu() {
	int x;

	while (true)
	{
		clrscr();
		cout << "1. Authority" << endl
			<< "2. Customer" << endl
			<< "3. Exit\n>> ";
		cin >> x;
		switch (x)
		{
		case 1: Authority_Menu(); break;
		case 2: Customer_Menu(); break;
		case 3: exit(0); break;

		default: cout << "Invalid Number";
			break;
		}
	}
}



int fetchAccount()
{
	tempData t;
	int flag = 0,index = 0;
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountName()== t.name  && accounts[i].getAccountNumber() == t.num) {
			flag = 1;
			index = i;
			break;
		}
		else {
			flag = 0;
		}
	}

	return flag == 1 ? index : -1;

}



tempData::tempData() {
	clrscr();
	cout << "Enter Account Holder Name : ";
	cin >> name;

	cout << "Enter Account Holder Number : ";
	cin >> num;

}


void Create_Account() {
	int x;
	cout << "How Many accounts? : ";
	cin >> x;

	for (int i = 0; i < x; i++) {
		Bank b;
		b.__init();
		accounts.push_back(b);
	}
}

void CloseAccount() {

	int index = fetchAccount();
	if (index != -1)
	{
		accounts.erase(accounts.begin() + index);
		clrscr();
		cout << "\nAccount is Closed. We are sorry to see you go :(\n";
	}
	else cout << "Account Not Found";

	getch();

}

void ChangePin() {


	int index = fetchAccount();
	if (index != -1)
		accounts.at(index).setNewPinNumber();
	else cout << "Account Not Found";
	getch();
}

Bank getAccount(int index) {
	return accounts.at( index);
}
void GiveLoan() {

	int index = fetchAccount();
	if (index != -1)
		accounts.at(index).Take_Loan();
	else cout << "Account Not Found";

}


void ViewAllAccounts() {
	clrscr();
	for(int i = 0; i<accounts.size(); i++) {
		accounts[i].ToString();
		getch();
	}
}


Bank::Bank()
{
	loanDets.Amount = -1;

}

void Bank::__init() {
	fill_PersonDetails();
	fill_AccountDetails();
}
int digits(int n) {
	int dig = 0;
	for (int i = n; i != 0; i /= 10) {
		dig++;
	}
	return dig;
}
void Bank::fill_PersonDetails() {
	std::cout << "Enter Name : ";
	std::cin >> personDets.Name;
	std::cout << "Enter Address : ";
	std::cin >> personDets.Address;
	std::cout << "Enter Phone Number : ";
	std::cin >> personDets.PhoneNumber;
}
void Bank::fill_AccountDetails() {
	float x;
	srand(time(NULL));
	accountDets.AccountNumber = rand() % 10000000000 + 10000000000;
	accountDets.PIN_Number = rand() % 1000000 + 1000000;

	clrscr();
	std::cout << "Your account is successfully created, \n"
		<< "Your Details are : \n"
		<< "Account Holder Name : " << personDets.Name << std::endl
		<< "Account Number : " << accountDets.AccountNumber
		<< "\nPIN Number : " << accountDets.PIN_Number
		<< "\n\t\tCAUTTION:NEVER SHARE YOUR PIN NUMBER WITH ANYONE\n"
		<< "\t\tKeep This data safe \n";

	getch();


	std::cout << "You need to make a FIRST DEPOSIT (Atleast 1000) : \n"
		<< "Enter Amount >> ";
	std::cin >> x;

	accountDets.Balance = x;
}

void Bank::setBalance(float amt)
{
	accountDets.Balance +=amt;
}
void Bank::setNewPinNumber()
{
	long int pin;
	int x = 0;

	do
	{
		clrscr();
		std::cout << "Enter New Pin (6 digits long): ";
		std::cin >> pin;
		x = digits(pin);

	} while (x != 6);
	accountDets.PIN_Number = pin;
}
void Bank::Take_Loan()
{
	int x = 0, flag = 1;
	while (x != 3)
	{
		std::cout << "What is your collateral? :\n"
			<< "1. Vehicle -> loan possibility 5,000-10,000\n"
			<< "2. House -> loan possibility 10,000-100,000\n"
			<< "3. I don't Want a loan now"
			<< "\n>> ";
		std::cin >> x;
		switch (x)
		{
		case 1: flag = 1;
			strcpy(loanDets.CollateralObject, "CAR");
			loanDets.collateralWorth = 10000;
			break;
		case 2: flag = 1;
			strcpy(loanDets.CollateralObject, "HOUSE");
			loanDets.collateralWorth = 100000;
			break;
		case 3: return;
		default: std::cout << "Invalid Number";
			flag = 0;
			break;
		}
		x = 3;
	}
	flag = 0;

	do
	{
		std::cout << "Enter Principle : ";
		std::cin >> loanDets.Amount;
		if (loanDets.Amount > loanDets.collateralWorth)
			flag = 1;
		else flag = 0;
	} while (flag == 1);
	loanDets.rate = rand() % 10 + 5;
	std::cout << "The intrest is : " << loanDets.rate;
	do
	{
		std::cout << "\nEnter the number of years for the loan (max 15): ";
		std::cin >> loanDets.time;

	} while (loanDets.time > 15 && loanDets.time<0);

	loanDets.intrest = loanDets.Amount*0.01*loanDets.rate*loanDets.time;
	loanDets.Amount += loanDets.intrest;
	loanDets.monthlyCharges = loanDets.Amount / (loanDets.time * 12);
	std::cout << "Your monthly installment is : " << loanDets.monthlyCharges<<std::endl;

	getch();

}

void Bank::ToString() {

	std::cout << "Name : " << personDets.Name << std::endl
		<< "Account Number : " << accountDets.AccountNumber << std::endl
		<< "Address : " << personDets.Address << std::endl
		<< "Phone Number : " << personDets.PhoneNumber<<std::endl;
	if (loanDets.Amount != -1)
		std::cout << "Loan Amount" << loanDets.Amount<<std::endl;

}

Bank::~Bank()
{
}


void View_Balance(  Bank& acc)
{
	cout << "Your Balance is : " << acc.getBalance() << endl;
	getch();
}
void Withdraw_Cash(  Bank& acc)
{
	int flag = 1;
	float x;
	while (flag == 1)
	{
		clrscr();
		cout << "Enter Amount >> ";
		cin >> x;
		if (x < acc.getBalance())
		{
			acc.setBalance(-x);
			flag = 0;
		}
		else
		{
			cout << "You Do Not Have enough Balance to withdraw that amount\nPLease Try again...";
			getch();
			flag = 1;
		}
	}

}

void Deposit_Cash(  Bank& acc)
{
	float x;
	cout << "Enter the amount to deposit : ";
	cin >> x;
	acc.setBalance(x);
	getch();
}

void Pay_Loan_Monthly_Installment(Bank& acc)
{
	char choice;
	cout << "Your Monthly installment is : " << acc.getMonthlyInstallment() << endl;
	cout << "Would you like to pay it? (y/n)";
	cin >> choice;

	switch (choice)
	{
	case 'y':
		if (acc.getBalance() > acc.getMonthlyInstallment())
		{
			acc.setBalance(-acc.getMonthlyInstallment());
			cout << "Your Dues have been paid successfully";
		}
		else cout << "you don't Have sufficient Balance to pay your dues";
		getch();
	case 'n':
		break;
	default:
		break;
	}

}
