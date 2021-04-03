// January 29, 2021
// This program reads a file with a list of movies and their descriptions.
// It then asks the user to search for a movie, in which the program displays 
// the description. The user chooses if they want to save the movie in a 
// a favorites file. They can keep saving movies or quit. The program displays
// the saved movies at the end.
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Movie
{
    string title;
    double grossTotal;
    string director;
    string releaseDate;
    int runtime;
};

int numberOfLines(ifstream&);
void populateMovieFromFile(ifstream&, Movie&);
void displayMovie(const Movie&);
Movie* createDatabase(int&);
bool caseInsensitiveCmp(string, string);
void findMovie(Movie*, int);
void saveToFile(const Movie&);
bool promptToContinue();
void displayFavorites();

int main()
{
    int size;
    Movie* movies = createDatabase(size);
    findMovie(movies, size);
    displayFavorites();
    return 0;
}

// This function receieves an input file passed by reference
// and returns an integer representing the number of lines in the file.
// The function reads the number of lines in the file and counts them.
int numberOfLines(ifstream& inFile) {
    int count = 0;
    string line;

    while (getline(inFile, line)) {
        count++;
    }

    return count;
}

// This function receives an input file passed by reference and a Movie object
// passed by reference. It doesn't return a data type.
// It populates one single movie object
void populateMovieFromFile(ifstream& inFile, Movie& properties) {
    string line;
    getline(inFile, line, ',');
    properties.title = line;
    getline(inFile, line, ',');
    properties.grossTotal = stod(line);
    getline(inFile, line, ',');
    properties.director = line;
    getline(inFile, line, ',');
    properties.releaseDate = line;
    getline(inFile, line);
    properties.runtime = stoi(line);

}

// This function receives a Movie object passed by constant reference
// and displays the contents of that object in a formatted fashion.
// It does not return any data type.
void displayMovie(const Movie& properties) {
    cout << "       Title: " << properties.title << endl;
    cout << " Gross Total: " << properties.grossTotal << " billion dollars" << endl;
    cout << "    Director: " << properties.director << endl;
    cout << "Release Date: " << properties.releaseDate << endl;
    cout << "     Runtime: " << properties.runtime << " minutes" << endl;
}

/* 
   This function receives an integer passed by reference 
   and returns a pointer to the array of Movie objects.
   This function prompts the user to enter the input file
   It then counts the number of lines in the file by calling the 
   numberOfLines function. A dynamically-allocated array of Movie
   objects is created. It loops through the array and stores a movie 
   in each index by caalling  populateMovieFromFile function which 
   uses array of Movie objects.
*/

Movie* createDatabase(int& numMovies) {
    ifstream inFile;
    string filename;
    cout << "Enter a file name: ";
    cin >> filename;
    inFile.open(filename);
    if (filename != "movies.txt") {
        cout << "Enter a valid file name: ";
        cin >> filename;
        inFile.open(filename);
    }

    //Create dynamic array of movie
    numMovies = numberOfLines(inFile);
    inFile.close();
    inFile.open(filename);

    Movie* ptr = new Movie[numMovies];

    inFile.clear();
    inFile.seekg(0, ios::beg);
    for (int i = 0; i < numMovies; i++)
    {
        populateMovieFromFile(inFile, ptr[i]);
    }
    inFile.close();
    return ptr;
    delete[] ptr;
}

// This function receives two strings and does a non-case sensitive comparison
// on the two strings. If the two strings aren't the same, the function will 
// return false. If they are the same, if lowercase or uppercase,
// it will return true.
bool caseInsensitiveCmp(string s1, string s2){
    if (s1.size() != s2.size()) {
        return false;
    }
    for (int i = 0; i < s1.size(); i++) {
        if (toupper(s1[i]) != toupper (s2[i])) {
            return false;
        }
    }
    return true;
}

/* 
    This function recieves a pointer to an array of Movie objects
     and the number of Movies in the array. The functions asks the user 
    to enter a movie title to search for. It searches through the array
    of movie objects for the title. If the movie is found, the information
    is displayed and asks the user if they would like to save the movie.
    If yes, the movie is saved to a "favorites" file. If there is no movie
    found, it displays an error message. It loops as long as the user chooses
    to continue.
 */
void findMovie(Movie* properties, int numMovies) {
    string title;
    do {
        bool found = false;
        cout << "Enter a movie title to search for: ";
        cin.ignore();
        getline(cin, title);
        cout << endl;
        for (int i = 0; i < numMovies; i++) {
            if (caseInsensitiveCmp(title, properties[i].title)) {
                displayMovie(properties[i]);
                found = true;
                cout << endl;
                cout << "Would you like to save this above movie? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    saveToFile(properties[i]);
                    cout << "Successfully saved to favorites.text!" << endl;
                    cout << endl;
                }

            }
        }
        if (!found) {
            cout << endl;
            cout << "Error: " << title << " not found in database."
                << " Please try again." << endl;
                
        }
    } 
    while (promptToContinue());
}

// This function receives a Movie object passed by constant reference
// It saves the movie object to the "favorites.txt" file.
// It returns nothing.
void saveToFile(const Movie& properties)
{
    ofstream outFile ("favorites.txt", ios:: app);
    outFile << "       Title: " << properties.title << endl;
    outFile << " Gross Total: " << properties.grossTotal << " billion dollars" << endl;
    outFile << "    Director: " << properties.director << endl;
    outFile << "Release Date: " << properties.releaseDate << endl;
    outFile << "     Runtime: " << properties.runtime << " minutes" << endl;
    outFile << endl;
    outFile.close();
}

// This function asks the user if they would like exit the program
// by entering 'y' or 'n'. If 'y', the function returns false; otherwise
// it returns true.
bool promptToContinue() {
    cout << endl;
    cout << "Would you like to exit? (Y/N): ";
    char choice;
    cin >> choice;
    cout << endl;
    if (choice == 'Y' || choice == 'y')
        return false;
    else
        return true;
}

// This function displays all saved favorite movies by outputting to the
// to the "favorites.txt file." If there aren't any saved movies, it displays
// an error. If there saved movies, it displays the output file to the console.
void displayFavorites()
{
    ifstream inFile("favorites.txt");
    if (inFile.peek() == ifstream::traits_type::eof()) {
        cout << "No movies saved.";
    }
    cout << "Your saved movies are: " << endl;
    cout << endl;
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
}

/*
Enter a file name: movies.txt
Enter a movie title to search for: SkyFALL

       Title: Skyfall
 Gross Total: 1.109 billion dollars
    Director:  Sam Mendes
Release Date:  11/9/12
     Runtime: 143 minutes

Would you like to save this above movie? (y/n): y
Successfully saved to favorites.text!


Would you like to exit? (Y/N): n

Enter a movie title to search for: IRON MAN 3

       Title: Iron Man 3
 Gross Total: 1.215 billion dollars
    Director:  Shane Black
Release Date:  5/3/13
     Runtime: 130 minutes

Would you like to save this above movie? (y/n): Y
Successfully saved to favorites.text!


Would you like to exit? (Y/N): N

Enter a movie title to search for: Minion


Error: Minion not found in database. Please try again.

Would you like to exit? (Y/N): y

Your saved movies are:

       Title: Skyfall
 Gross Total: 1.109 billion dollars
    Director:  Sam Mendes
Release Date:  11/9/12
     Runtime: 143 minutes

       Title: Iron Man 3
 Gross Total: 1.215 billion dollars
    Director:  Shane Black
Release Date:  5/3/13
     Runtime: 130 minutes

*/












