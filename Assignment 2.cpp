// January 22, 2021
// This program saves students' names, how many tests they have taken,
// and their grades for each test. The program then displays the information
// to the user. 

#include <iostream>
#include <string>
using namespace std;

int inputData(string*&, double**&);
void displayData(string*, double**, int);
void cleanHeap(string*, double**, int);

int* numGrades;

int main()
{
	string *name;
	double **tests;
	int num;
	num = inputData(name, tests);
	displayData(name, tests, num);
	cleanHeap(name, tests, num);

  
}

// Function inputData
// Receives a string pointer and a pointer to a double pointer.
// Returns the number of students in the system.
// This function stores the number of students inputted by the user along
// with their names, how many tests taken, and grades for each test.
int inputData(string *&name, double **&tests) {
	int i;
	int j;
	int numStudents;
	int numTests;
	cout << "How many students do you have in the system? ";
	cin >> numStudents;
	if (numStudents <= 0) {
		cout << "Please enter a positive number of students. ";
		cout << "How many students do you have in the system?" << endl;
		cin >> numStudents;
	} 

	name = new string[numStudents];
	tests = new double*[numStudents];
	numGrades = new int[numStudents];

	for (i = 1; i <= numStudents; i++) {
		cout << "Enter the student's name: ";
		cin.ignore();
		getline(cin, name[i - 1]);
		while (true) {
			cout << "Enter how many tests " << name[i-1] << " took: ";
			cin >> numTests;
			if (numTests <= 0) {
				cout << "Please enter a positive number of tests taken " << endl;
			}
			else {
				break;
			}
		}
		numGrades[i - 1] = numTests;
		tests[i - 1] = new double[numTests];

		for (j = 1; j <= numTests; j++) {
			while (true) {
				cout << "Enter grade # " << j << ":";
				cin >> tests[i - 1][j - 1];

				if (tests[i - 1][j - 1] < 0 || tests[i - 1][j - 1] > 100) {
					cout << "Please enter a test score between 0 and 100" << endl;
				}
				else {
					break;
				}
			}
		}
		cout << endl;
	}
	return numStudents;
}

// Function displayData
// Receives a pointer to the array of student names,
// a pointer to the array of student test scores, and
// the number of students.
// This function does not return anything. 
// This function displays the data of the information inputted 
// by the user.
void displayData(string *name, double **tests, int numStudents) {
	int i;
	int j;
	cout << endl;
	cout << "You have " << numStudents << " students in the system." << endl;
	for (i = 0; i < numStudents; i++) {
		cout << "Name of student # " << (i + 1) << ": " << name[i] << endl;
		cout << "Grades for student # " << (i + 1) << ": ";
		for (j = 0; j < numGrades[i]; j++) {
			cout << " " << tests[i][j];
		}
		cout << endl;
	}
}

// Function cleanHeap
// This function recieves a pointer to the array of student names,
// a pointer to the array of student test scores, and the number 
// of students.
// No return of any value.
// The function cleans all dynamically-allocated memory.
void cleanHeap(string* name, double** tests, int numStudents) {
	delete[] name;
	for (int i = 0; i < numStudents; i++)
	{
		delete[] tests[i];
	}
	delete[] tests;
}

//Sample Run:
//How many students do you have in the system ? 3
//Enter the student's name: John Smith
//Enter how many tests John Smith took : 4
//Enter grade # 1:85.4
//Enter grade # 2:78.6
//Enter grade # 3:95.5
//Enter grade # 4:86.6
//
//Enter the student's name: Anna Mull
//Enter how many tests Anna Mull took : 3
//Enter grade # 1:75
//Enter grade # 2:58
//Enter grade # 3:95.2
//
//Enter the student's name: Bryan Jackson
//Enter how many tests Bryan Jackson took : -6
//Please enter a positive number of tests taken
//Enter how many tests Bryan Jackson took : 2
//Enter grade # 1:89.4
//Enter grade # 2:-55
//Please enter a test score between 0 and 100
//Enter grade # 2:78
//
//
//You have 3 students in the system.
//Name of student # 1: John Smith
//Grades for student # 1:  85.4 78.6 95.5 86.6
//Name of student # 2: Anna Mull
//Grades for student # 2:  75 58 95.2
//Name of student # 3: Bryan Jackson
//Grades for student # 3:  89.4 78
//
//C : \Users\bruni\OneDrive\Desktop\C++ 22B Alameer\Assignment 2\Debug\
//Assignment 2.exe(process 23632) exited with code 0.
//Press any key to close this window . . .