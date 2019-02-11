#include "stdafx.h"
#include "Validator.h"
#include "Windows.h"
#include <iostream>
#include <iomanip>
using namespace std;


//title input validation
std::string Validator::validateTitle()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::string title;
	SetConsoleTextAttribute(hConsole, 112);
	cout << setw(10) << "Title: "; //get first input
	getline(cin, title);
	while (title == "") {
		cout << '\b' << '\r' << setw(10) << "Title: ";
		SetConsoleTextAttribute(hConsole, 124); //red for validation error
		cout << "x  Title cannot be empty";
		cin.get();
		SetConsoleTextAttribute(hConsole, 112);
		cout << '\b' << '\r';	//clear area
		for (int i = 0; i < 120; i++)
			cout << " ";
		cout << '\b' << '\r' << setw(10) << "Title: ";	//retry
		getline(cin, title);
	}
	cout << '\b' << '\r' << setw(10) << "Title: " << title;	//show validated message
	SetConsoleTextAttribute(hConsole, 114);
	cout << "  v" << endl;
	return title;
}


//year input validation
int Validator::validateYear()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::string year = "";
	bool validated = false;
	int numYear = 0; 
	do {
		SetConsoleTextAttribute(hConsole, 112);
		cout << setw(10) << "Year: ";	//get input
		getline(cin, year);
		try {
			numYear = stoi(year);	//convert to integer
		}
		catch (invalid_argument) {
			cout << '\b' << '\r' << setw(10) << "Year: " << year;
			SetConsoleTextAttribute(hConsole, 124); //red for validation error
			cout << " x  Year must be an integer between 1900 and 2020";
			cin.get();
			cout << '\b' << '\r';	//clear area
			for (int i = 0; i < 120; i++)
				cout << " ";
			cout << '\b' << '\r';
			continue;
		}

		//handle invalid range
		if (numYear < 1900 || numYear > 2020) {		
			cout << '\b' << '\r' << setw(10) << "Year: " << year;
			SetConsoleTextAttribute(hConsole, 124); //red for validation error
			cout << " x  Year must be an integer between 1900 and 2020";
			cin.get();
			cout << '\b' << '\r';	//clear area
			for (int i = 0; i < 120; i++)
				cout << " ";
			cout << '\b' << '\r';
			continue;
		}
		else {
			validated = true;
			cout << '\b' << '\r' << setw(10) << "Year: " << year;	//show validated message
			SetConsoleTextAttribute(hConsole, 114);
			cout << "  v" << endl;
		}

	} while (!validated);
	return numYear;
}


//genre input validation
std::string Validator::validateGenre()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::string genre;
	SetConsoleTextAttribute(hConsole, 112);
	cout << setw(10) << "Genre: ";	//get first input
	getline(cin, genre);
	while (genre == "") {
		cout << '\b' << '\r' << setw(10) << "Genre: ";
		SetConsoleTextAttribute(hConsole, 124); //red for validation error
		cout << "x  Genre cannot be empty";
		cin.get();
		SetConsoleTextAttribute(hConsole, 112);
		cout << '\b' << '\r';	//clear area
		for (int i = 0; i < 120; i++)
			cout << " ";
		cout << '\b' << '\r' << setw(10) << "Genre: ";	//retry
		getline(cin, genre);
	}
	cout << '\b' << '\r' << setw(10) << "Genre: " << genre;	//show validated message
	SetConsoleTextAttribute(hConsole, 114);
	cout << "  v" << endl;
	return genre;
}
