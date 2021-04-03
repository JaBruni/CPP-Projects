// Date: January 14, 2021
// Program: This is a Memory Game program, where a grid of face down cards
// is created. Players will choose two cards by entering two pairs of
// of cooordinates. The goal is to find all matching pairs.
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>
const int LENGTH = 4;
using namespace std;

// Function prototypes
void InitializeCards(int cards[][LENGTH]);
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]);
// you may have more function prototypes

// ======================
//     main function
// ======================
int main()
{
	// 1) Welcome the user and ask him to enter his full name.
	string name;
	cout << "Hello welcome to my game. Please enter your full name:" << endl;
	getline(cin, name);

	// 2) Create a two 2D array that will hold the number for each card. 
	// 	Pass it to   InitializeCards function. 

	int cards[LENGTH][LENGTH];
	InitializeCards(cards);

	// 3) Create the 2D array of Booleans. 
	// 	  This should be initialized to all FALSE at first. 

	bool faceup[LENGTH][LENGTH];
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			faceup[i][j] = false;
		}
	}
	// 4) while the game is not over :
	int numMatch = 0;
	bool gameOver = false;
	int x1, x2, y1, y2;
	char choice;
	int attempts = 0;
	while (!gameOver) {
		// Display the current state of the game board. 
		// Remember that non-matched pairs should be "facedown"
		// and that matched pairs should be "faceup"

		ShowCards(cards, faceup);

		// Prompt the user to enter the coordinates of two cards
		// Note: user can choose to quit

		cout << "Enter the coordinates of your first card: ";
		cin >> x1 >> y1;

		if (x1 >= LENGTH || y1 >= LENGTH) {
			cout << "Invalid coordinates, please try again." << endl;
			cout << "Enter the coordinates of your first card: ";
			cin >> x1 >> y1;
		}

		cout << "Enter the coodinates of your second card: ";

		cin >> x2 >> y2;

		if (x1 >= LENGTH || y2 >= LENGTH) {
			cout << "Invalid coordinates, please try again." << endl;
			cout << "Enter the coordinates of your second card: ";
			cin >> x2 >> y2;
		}

		attempts++;

		// If the values of the two coordinates match :
		//  say that a match has been found and flip the cards over forever

		
		if (cards[x1][y1] == cards[x2][y2]) {
			cout << "A match has been found!";
			faceup[x1][y1] = true;
			faceup[x2][y2] = true;
			numMatch++;
			ShowCards(cards, faceup);
			if (numMatch == 2 * LENGTH) {
				gameOver = true;
			}
		}
		else {
			cout << endl;
			cout << "No match found." << endl;
			faceup[x1][y1] = true;
			faceup[x2][y2] = true;
			ShowCards(cards, faceup);
			faceup[x1][y1] = false;
			faceup[x2][y2] = false;
			cout << "Lets try again." << endl;
		}

		cout << "Enter 'q' to quit or press any key to continue...";
		cin.ignore();
		cin.get(choice);
		if (choice == 'q') {
			exit(0);
		}

	}

	// 5) Save the user’s name and how many turns it took to win the game
	// into an output text file. If he quits
	// before winning save “Don’t give up” message in the file.
	ofstream myfile;
	myfile.open("results.txt");
	if (numMatch != 2 * LENGTH) {
		myfile << "Dont give up!" << endl;
	}
	else {
		myfile << name << " :" << endl;
		myfile << "it took " << attempts << " attempts to win" << endl;
	}
	
	return 0;
}

// InitializeCards
// Places pairs of numbers in the 2D array and then
// randomly shuffles them.
// Receives a 2D Array
// ======================
void InitializeCards(int cards[][LENGTH]) {
	//seed rand() - remember to always do this before using rand()
	// also make sure to include the <time.h> library.
	srand(time(NULL));
	int x1, y1, x2, y2;
	int i;
	int temp;

	// Place pairs in known locations 
	cards[0][0] = 1; cards[0][1] = 1;//   1  1  2  2
	cards[0][2] = 2; cards[0][3] = 2;
	cards[1][0] = 3; cards[1][1] = 3;//   3  3  4  4
	cards[1][2] = 4; cards[1][3] = 4;
	cards[2][0] = 5; cards[2][1] = 5;//   5  5  6   6
	cards[2][2] = 6; cards[2][3] = 6;
	cards[3][0] = 7; cards[3][1] = 7;//   7  7  8   8
	cards[3][2] = 8; cards[3][3] = 8;

	// Now that 2D has been initialized with 8 pairs, 
	// we want to shuffle the board so
	// that the pairs aren't right next to each other
	for (int i = 0; i < 30; i++) {
		//Get set of random coordinates and swap
		//First random coordinate on our 2d "grid"
		y1 = rand() % LENGTH;
		x1 = rand() % LENGTH;
		//Second random coordinate of our 2d "grid"
		y2 = rand() % LENGTH;
		x2 = rand() % LENGTH;

		//Now we swap value at (x1, y1) with value at(x2, y2)
		temp = cards[x1][y1];
		cards[x1][y1] = cards[x2][y2];
		cards[x2][y2] = temp;
	}
}
// ======================
// ShowCards
// Generates a display on the screen.  If faceup=false,
// an * is output, otherwise the card in that slot is output.
// Receives a 2D Array of int type and a
// a 2D Array of Boolean type
// ======================
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]) {
	// add your code here
	cout << endl << left << setw(3) << "";
	for (int i = 0; i < LENGTH; i++) {
		cout << right << setw(2) << i;
	}
	cout << endl << "    =======" << endl;
	for (int i = 0; i < LENGTH; i++) {
		cout << endl << left << setw(2) << i << left << setw(2) << "|";
		for (int j = 0; j < LENGTH; j++) {
			if (faceup[i][j] == false)
				cout << left << setw(2) << "*";
			else
				cout << left << setw(2) << cards[i][j];
		}
		cout << left << setw(2) << "|";
	}
	
	cout << endl << "    =======" << endl;
}

// FIRST RUN:
// Hello welcome to my game. Please enter your full name:
// Jason Bruni

// 0 1 2 3
// =======
// 
// 0 | **** |
// 1 | **** |
// 2 | **** |
// 3 | **** |
// =======
// Enter the coordinates of your first card : 5 4
// Invalid coordinates, please try again.
// Enter the coordinates of your first card :

// SECOND RUN:
// Hello welcome to my game.Please enter your full name :
// Jason Bruni

// 0 1 2 3
// =======

// 0 | **** |
// 1 | **** |
// 2 | **** |
// 3 | **** |
// =======
// Enter the coordinates of your first card : 0 0
// Enter the coodinates of your second card : 0 1

// No match found.

// 0 1 2 3
// =======

// 0 | 8 3 * *|
// 1 | * * * *|
// 2 | * * * *|
// 3 | * * * *|
// =======
// Lets try again.
// Enter 'q' to quit or press any key to continue...

// 0 1 2 3
// =======

// 0 | **** |
// 1 | **** |
// 2 | **** |
// 3 | **** |
// =======
// Enter the coordinates of your first card : 0 2
// Enter the coodinates of your second card : 1 2

// No match found.

// 0 1 2 3
// =======

// 0 | **8 * |
// 1 | **6 * |
// 2 | *** * |
// 3 | *** * | 
// ====== =
// Lets try again.
// Enter 'q' to quit or press any key to continue...

// 0 1 2 3
// =======

// 0 | **** |
// 1 | **** |
// 2 | **** |
// 3 | **** |
// =======
// Enter the coordinates of your first card : 0 0
// Enter the coodinates of your second card : 0 2
// A match has been found!
// 0 1 2 3
// =======

// 0 | 8 * 8 * |
// 1 | * * * * |
// 2 | * * * * |
// 3 | * * * * |
// =======
// Enter 'q' to quit or press any key to continue...

// THIRD RUN:
// Hello welcome to my game.Please enter your full name :
// Jason Bruni

// 0 1 2 3
// =======

// 0 | ****|
// 1 | ****|
// 2 | ****|
// 3 | ****|
// =======
// Enter the coordinates of your first card : 0 0
// Enter the coodinates of your second card : 0 1

// No match found.

// 0 1 2 3
// =======

// 0 | 1 2 * *|
// 1 | * * * *|
// 2 | * * * *|
// 3 | * * * *|
// =======
// Lets try again.
// Enter 'q' to quit or press any key to continue...q

// C : \Users\bruni\OneDrive\Desktop\C++ 22B Alameer\Assignment 1\Debug\Assignment 1.exe(process 18780) exited with code 0.
// To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
// Press any key to close this window . . .