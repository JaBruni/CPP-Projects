// February 9, 2021
/*
    This program simulates a vending machine that sells chips,
    candy, and soda. The programs asks the user to enter a 
    number of quarters. The program converts the quarters into
    dollars and cents. The user must then choose a snack to dispense.
    If the user makes a valid selection and has enough money, the snack will
    dispense. The program will also dispense the amount of change 
    the user receives. With each selection of snack the amount of stock will
    decrease and the amount of snacks sold will increase. After the user
    quits, the program will display and end-of-sale report.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

class Snack {
private:
    string name;
    double price;
    int stock;
    int itemsSold;
    string* transaction;
    string getCurrentTime() {
        time_t t = time(0);
        struct tm ts;
        char buff[10];
        ts = *localtime(&t);
        strftime(buff, sizeof(buff), "%X", &ts);
        return buff;
    }
public:
    Snack();
    Snack(string, double, int);
    ~Snack();

    // Sets the name of the Snack
    void setName(string n) {
        name = n;
    }

    //Sets the price of the Snack
    void setPrice(double p) {
        price = p;
    }

    //Sets the amount of stock of the Snack
    void setStock(int s) {
        stock = s;
        transaction = new string[s];
        for (int i = 0; i < s; i++)
            transaction[i] = "";
    }

    //Sets the amount of stock sold
    void setItemsSold(int a) {
        a = itemsSold;
    }

    //Returns the name of the snack
    string getName() const {
        return name;
    }

    //Returns the price of the snack
    double getPrice() const {
        return price;
    }

    //Returns the stock of the Snack
    int getStock() const {
        return stock;
    }

    //Returns the amount of stock sold
    int getItemsSold() const {
        return itemsSold;
    }

    bool buyItem(double& moneyEntered);
};

//Default Constructor
Snack::Snack() {
    name = "";
    price = 0.0;
    stock = 0;
    itemsSold = 0;
    transaction = nullptr;
}

//Overloaded constructor
Snack::Snack(string n, double p, int s) {
    name = n;
    price = p;
    stock = s;
    itemsSold = 0;
    transaction = new string[s];
    for (int i = 0; i < s; i++)
        transaction[i] = "";
}

//Snack Destructor
Snack::~Snack() {
    if (itemsSold) {
        cout << "Closing info for " << name << ":" << endl;
        cout << "\n" << stock << " in stock" << endl;
        cout << "\n" << itemsSold << " sold for a profit of $" 
            << price * itemsSold << endl;
        cout << endl << "Transactions ocurred at:" << endl;
        for (int i = 0; i < itemsSold; i++) {
            cout << "\n" << transaction[i] << endl;
        }
    }
    delete[] transaction;
    transaction = nullptr;
    cout << endl;
}

/*
    Receives a double value passed by reference
    This class function records the time transactions
    took place and tracks the amount of stock left and the amount of
    stock that has been sold. It also validates if the user 
    has enough money to buy an item. It returns false if an item has 
    been sold out or the amount of money is less than the 
    snack price.
*/
bool Snack::buyItem(double& moneyEntered) {
    if (stock == 0) {
        cout << "Error: item is sold out" << endl;
        return false;
    }
    if (moneyEntered >= price) {
        moneyEntered = moneyEntered - price;
        transaction[itemsSold] = getCurrentTime();
        stock--;
        itemsSold++;
        cout << "Item has been dispensed below" << endl;
    }
    else if (moneyEntered < price) {
        if (moneyEntered < 0) {
            cout << "Please enter a number greater than 0" << endl;
        }
        else {
            cout << "Amount is less than the price $" << price << endl;
        }
        return false;
    }
}

void displayVendingMachine(const Snack[], int);
int getQuarters();
void userBuyItem(Snack[], int);
bool promptToContinue();

int main()
{
    const int size = 3;
    bool choice = true;
    Snack snack[size] = {Snack(), Snack("Candy", 1.25, 5), 
                         Snack("Soda", 1.0, 2)};
    snack[0].setName("Chips");
    snack[0].setPrice(double(1.75));
    snack[0].setStock(3);
    cout << "Welcome to the vending machine!" << endl << endl;
    do {
        userBuyItem(snack, size);
        choice = promptToContinue();
    } while (choice);
    return 0;
}

/*
    This function receives a constant array of Snack objects
    and the number of elements in the array. It displays the content
    in formatted fashion.
*/
void displayVendingMachine(const Snack snack[], int size) {
    cout << "Item #" << setw(14) << "Item Name" << setw(10)
        << "Price" << setw(14) << "# in-stock" << endl;
    for (int i = 0; i < 47; i++)
        cout << "-";
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << i + 1 << setw(16) << snack[i].getName() << setw(12)
            << fixed << setprecision(2) << snack[i].getPrice() << setw(10)
            << snack[i].getStock();
        cout << endl;
    }
    cout << endl;
}

/*
    This function prompts the user to enter a number of quarters. If the 
    number is less than 1, an error message is displayed and prompts
    the user to enter a valid amount.
    It returns the amount of quarters entered.
*/
int getQuarters() {
    int numQuarters;
    cout << "Please enter a number of quarters: ";
    cin >> numQuarters;
    if (numQuarters < 1) {
        cout << "Please enter a valid number of quarters: ";
        cin >> numQuarters;
        return numQuarters;
    }
    else {
        return numQuarters;
    }
}

/*
    This functions accepts an array of Snack objects and the number
    of elements in the array. It displays the contents of the 
    vending machine and prompts the user to enter the amount of 
    quarters.It converts the amout of quarters into dollars and cents.
    The user is then prompted to enter an item number to buy.
    If the user doesn't make a valid choice, an error message is
    displayed and prompts the user again. If a valid choice is made,
    the buyItem method is used on the snack chosen.
*/
void userBuyItem(Snack snack[], int size) {
    displayVendingMachine(snack, size);
    int numQuarters = getQuarters();
    int choice;
    cout << "Amount Entered: $" << numQuarters * 0.25 << endl;
    while (true) {
        cout << endl << "Enter a number between 1 and " << size << ": " 
            << endl;
        cin >> choice;
        if (choice >= 1 && choice <= size)
            break;
        cout << "Error: enter a valid selection";
    }
    double change = numQuarters * 0.25;
    bool res = snack[choice - 1].buyItem(change);
    if (change > 0)
        cout << "$" << change << " dispensed below" << endl;
}

/* This function asks the user if they would like to continue the program
   by entering 'y' or 'n'. If 'y', the function returns true; otherwise
   it returns false.
*/ 

bool promptToContinue() {
    cout << endl;
    cout << "Would you like to continue? (Y/N): ";
    char choice;
    cin >> choice;
    cout << endl;
    if (choice == 'Y' || choice == 'y')
        return true;
    else
        return false;
}

/*
SAMPLE RUN:
Welcome to the vending machine!

Item #     Item Name     Price    # in-stock
-----------------------------------------------
1           Chips        1.75         3
2           Candy        1.25         5
3            Soda        1.00         2

Please enter a number of quarters: -1
Please enter a valid number of quarters: 5
Amount Entered: $1.25

Enter a number between 1 and 3:
2
Item has been dispensed below

Would you like to continue? (Y/N): y

Item #     Item Name     Price    # in-stock
-----------------------------------------------
1           Chips        1.75         3
2           Candy        1.25         4
3            Soda        1.00         2

Please enter a number of quarters: 7
Amount Entered: $1.75

Enter a number between 1 and 3:
2
Item has been dispensed below
$0.50 dispensed below

Would you like to continue? (Y/N): y

Item #     Item Name     Price    # in-stock
-----------------------------------------------
1           Chips        1.75         3
2           Candy        1.25         3
3            Soda        1.00         2

Please enter a number of quarters: 10
Amount Entered: $2.50

Enter a number between 1 and 3:
0
Error: enter a valid selection
Enter a number between 1 and 3:
3
Item has been dispensed below
$1.50 dispensed below

Would you like to continue? (Y/N): y

Item #     Item Name     Price    # in-stock
-----------------------------------------------
1           Chips        1.75         3
2           Candy        1.25         3
3            Soda        1.00         1

Please enter a number of quarters: 4
Amount Entered: $1.00

Enter a number between 1 and 3:
2
Amount is less than the price $1.25
$1.00 dispensed below

Would you like to continue? (Y/N): y

Item #     Item Name     Price    # in-stock
-----------------------------------------------
1           Chips        1.75         3
2           Candy        1.25         3
3            Soda        1.00         1

Please enter a number of quarters: 7
Amount Entered: $1.75

Enter a number between 1 and 3:
3
Item has been dispensed below
$0.75 dispensed below

Would you like to continue? (Y/N): y

Item #     Item Name     Price    # in-stock
-----------------------------------------------
1           Chips        1.75         3
2           Candy        1.25         3
3            Soda        1.00         0

Please enter a number of quarters: 6
Amount Entered: $1.50

Enter a number between 1 and 3:
3
Error: item is sold out
$1.50 dispensed below

Would you like to continue? (Y/N): n

Closing info for Soda:

0 in stock

2 sold for a profit of $2.00

Transactions ocurred at:

22:17:27

22:18:01

Closing info for Candy:

3 in stock

2 sold for a profit of $2.50

Transactions ocurred at:

22:16:39

22:17:01
*/