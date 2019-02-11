#include "stdafx.h"
#include "UI.h"
#include "Validator.h"
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "Exception.h"
#include <iostream>
using namespace std;


//constructor
UI::UI(Controller & ctrl) : ctrl(ctrl) {}


//destructor
UI::~UI()
{
}


//add new film to list
void UI::addNewFilm()
{
	setColor(63);
	setCursor(1, 1);
	cout << " 1. Add film ";
	setCursor(0, 4);
	setColor(112);
	
	//get validated user input 
	std::string title = Validator::validateTitle();
	int year = Validator::validateYear();

	int found = ctrl.getRepo().findFilmIndex(title, year);
	if (found == -1) {
		std::string genre = Validator::validateGenre();
		ctrl.addToRepo(title, year, genre);
		setColor(115);
		cout << endl << "Film successfully added" << endl << endl;
	}
	else {
		setColor(116);
		throw FilmAlreadyInListException();
	}
	setColor(112);
}


//delete film from list
void UI::deleteFilm()
{
	setColor(63);
	setCursor(15, 1);
	cout << " 2. Delete film ";
	setCursor(0, 4);
	setColor(112);

	//get validated user input
	std::string title = Validator::validateTitle();
	int year = Validator::validateYear();

	int found = ctrl.getRepo().findFilmIndex(title, year);
	if (found == -1) {
		setColor(116);
		throw FilmNotInListException();
	}
	else {
		ctrl.deleteFromRepo(title, year);
		setColor(115);
		cout << endl << "Film successfully deleted" << endl << endl;
	}
	setColor(112);
}


//update attributes of selected film
void UI::update()
{
	setColor(63);
	setCursor(32, 1);
	cout << " 3. Update film ";
	setCursor(0, 4);
	setColor(112);

	std::string title = Validator::validateTitle();	//get attributes of film to update
	unsigned year = Validator::validateYear();
	cout << endl;
	int found = ctrl.getRepo().findFilmIndex(title, year);	//search for film in repo
	if (found == -1) {
		setColor(116);
		throw FilmNotInListException();
	}
	else {
		setColor(112);
		cout << setw(10) << "Press " << " 1 to update title" << endl;
		cout << "           2 to update year" << endl;
		cout << "           3 to update genre" << endl;
		char option = _getch();
		cout << endl << endl;
		if (option == '1') {											//update title
			cout << "   Update" << endl;
			std::string newTitle = Validator::validateTitle();
			ctrl.updateTitle(title, year, newTitle);
			setColor(115);
			cout << endl << "Film successfully updated" << endl << endl;
		}
		else if (option == '2') {										//update year
			cout << "   Update" << endl;
			unsigned newYear = Validator::validateYear();
			ctrl.updateYear(title, year, newYear);
			setColor(115);
			cout << endl << "Film successfully updated" << endl << endl;
		}
		else if (option == '3') {										//update genre
			cout << "   Update" << endl; 
			std::string newGenre = Validator::validateGenre();
			ctrl.updateGenre(title, year, newGenre);
			setColor(115);
			cout << endl << "Film successfully updated" << endl << endl;
		}
	}
	setColor(112);
}


//display all films contained in the list
void UI::viewAll(List & list)
{
	setCursor(0, 4);
	setColor(112);

	std::vector<Film> allFilms = list.getList();
	if (allFilms.size() == 0) {
		cout << " Your watchlist is empty. Press 1 to search for some films." << endl << endl;
		return;
	}
	for (int i = 0; i < 34; i++)
		cout << " ";
	setColor(63);
	cout << setw(20) << "Title" << setw(10) << "Year" << setw(14) << "Genre" << setw(9) << "Likes" << endl << endl;
	setColor(112);
	for (Film& item : allFilms) 
		cout << item << endl;
	cout << endl;
}

void UI::searchByGenre()
{
	setColor(63);
	setCursor(1, 1);
	cout << " 1. Search film ";
	setCursor(0, 4);
	setColor(112);

	cout << "    What genre would you like to search for?" << endl << "    ";
	std::string genre;
	getline(cin, genre);
	system("cls");
	userMenu();
	setColor(63);
	setCursor(1, 1);
	cout << " 1. Search film ";
	setCursor(0, 4);
	setColor(112);
	
	//cin.ignore();
	std::vector<Film> found = ctrl.getRepo().getList(); //get all films
	if (genre != "")
		found = ctrl.getRepo().filterByGenre(genre);	//get films with specified genre
	if (found.size() == 0) {
		setColor(124);
		throw EmptyGenreException();
		setColor(112);
		system("pause");
		return;
	}
	char option;
	for (Film& item : found) {
		std::string title = item.getTitle();
		if (ctrl.getWatchlist().findFilmIndex(title, item.getYear()) != -1)	//film already in user's watchlist
			continue;
		item.displayOne();		//show film title and other attributes
		item.playTrailer();
		option = ' ';
		cout << "Would you like to add " << item.getTitle() << " to your watchlist?" << endl;
		cout << "    y - Yes" << endl;
		cout << "    n - No" << endl; 
		while (option != 'y' && option != 'n') {	//read option until it's y or n
			option = _getch();
		}
		if (option == 'y') {
			ctrl.getWatchlist().addToWatchlist(item);
			setColor(114);
			cout << item.getTitle() << " was added to your watchlist" << endl;
			setColor(112);
		}
		cout << endl << "Would you like to go to the next film?" << endl;
		cout << "    y - Yes" << endl;
		cout << "    n - No" << endl;
		option = ' ';
		while (option != 'y' && option != 'n') {	//read option until it's y or n
			option = _getch();
		}
		if (option == 'y') {
			system("cls");
			userMenu();
			setColor(63);
			setCursor(1, 1);
			cout << " 1. Search film ";
			setCursor(0, 4);
			setColor(112);
			continue;
		}
		else
			cout << endl;
			system("pause");
			return;
	}
	cout << "There are no more films of this genre." << endl << endl;
	system("pause");
}

void UI::deleteFromWatchlist()
{
	setColor(63);
	setCursor(18, 1);
	cout << " 2. Delete film from watchlist ";
	setCursor(0, 4);
	setColor(112);

	cout << "   What film would you like to delete? " << endl;
	std::string title = Validator::validateTitle();
	unsigned year = Validator::validateYear();
	setColor(112);
	cout << endl;
	Film& found = ctrl.getWatchlist().findFilm(title, year);
	if (found.getTitle() == "") {		//check if film was not found
		setColor(124);
		throw FilmNotInListException();
		setColor(112);
	}
	else {
		system("cls");
		userMenu();
		setColor(63);
		setCursor(18, 1);
		cout << " 2. Delete film from watchlist ";
		setCursor(0, 4);
		setColor(112);
		ctrl.getWatchlist().deleteFromWathlist(found);	//remove from watchlist
		cout << "This film was succesfully deleted from your watchlist." << endl << endl;
		found = ctrl.getRepo().findFilm(title, year);
		found.displayOne();
		cout << endl;
		cout << "Did you like the film?" << endl;
		cout << "    y - Yes" << endl;
		cout << "    n - No" << endl;
		char option = ' ';
		while (option != 'y' && option != 'n') {	//read option until it's y or n
			option = _getch();
		}
		if (option == 'y') {
			ctrl.updateLikes(title, year);	//increase number of likes in repository
			setCursor(0, 7);
			cout << "          " << found.getGenre() << "   |    " << found.getYear() << "    |    " << found.getLikes() << " likes";
			setColor(114);
			cout << "    + 1";
			Sleep(1000);
			setCursor(0, 7);
			setColor(112);
			cout << "          " << found.getGenre() << "   |    " << found.getYear() << "    |    ";
			setColor(114);
			cout << found.getLikes() + 1;
			setColor(112);
			cout << " likes";
			setCursor(0, 14);
		}
	}
	system("pause");
}

void UI::displayWatchlist()
{
	if (ctrl.getWatchlist().getList().size() > 0) {

		cout << endl;
		cout << "    Choose format to view your watchlist: 1. CSV" << endl;
		cout << "                                          2. HTML" << endl;
		char option = ' ';
		while (option != '1' && option != '2') {	//read option until it's 1 or 2
			option = _getch();
		}
		if (option == '1')
			ctrl.getWatchlist().setFileOpener(new CSVFileOpener);
		else if (option == '2')
			ctrl.getWatchlist().setFileOpener(new HTMLFileOpener);
		ctrl.getWatchlist().getFileOpener().open("watchlist");
	}
}


//change color of console text and background
void UI::setColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


//move cursor at given coordinates
void UI::setCursor(short x, short y)
{
	COORD p = { x, y };
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, p);
}


//homepage interface
void UI::mainPage()
{
	for (int i = 0; i < 6; i++)
		cout << endl;
	
	setColor(0);
	for (int i = 0; i < 120; i++)
		cout << " ";
	for (int i = 0; i < 30; i++) {
		setColor(255);
		cout << "  ";
		setColor(0);
		cout << "  ";
	}
	for (int i = 0; i < 120; i++)
		cout << " ";

	for (int i = 0; i < 12; i++) {
		setColor(0);
		cout << " ";
		setColor(128);
		cout << "                            ";
		setColor(0);
		cout << " ";
		cout << endl;
	}

	short currentY = 9;
	setColor(0);
	for (int i = 0; i < 12; i++) {
		setCursor(60, currentY++);
		cout << " ";
	}

	setColor(128);
	setCursor(30, 9);
	cout << "                              ";
	setCursor(30, 10);
	cout << "        Press A to run        ";
	setCursor(30, 11);
	cout << "      ADMINISTRATOR mode      ";
	setCursor(30, 12);
	cout << "                              ";
	setCursor(30, 13);
	cout << "                              ";
	setCursor(30, 14);
	cout << "        ****                  ";
	setCursor(30, 15);
	cout << "       ******                 ";
	setCursor(30, 16);
	cout << "      ***  *************      ";
	setCursor(30, 17);
	cout << "      ***  *************      ";
	setCursor(30, 18);
	cout << "       ******      ** **      ";
	setCursor(30, 19);
	cout << "        ****                  ";
	setCursor(30, 20);
	cout << "                              ";

	setCursor(61, 9);
	cout << "                             ";
	setCursor(61, 10);
	cout << "       Press U to run        ";
	setCursor(61, 11);
	cout << "          USER mode          ";
	setCursor(61, 12);
	cout << "                             ";
	setCursor(61, 13);
	cout << "                             ";
	setCursor(61, 14);
	cout << "            *****            ";
	setCursor(61, 15);
	cout << "           *******           ";
	setCursor(61, 16);
	cout << "           *******           ";
	setCursor(61, 17);
	cout << "            *****            ";
	setCursor(61, 18);
	cout << "          *********          ";
	setCursor(61, 19);
	cout << "         ***********         ";
	setCursor(61, 20);
	cout << "                             ";

	currentY = 9;
	for (int i = 0; i < 12; i++) {
		setCursor(90, currentY++);
		setColor(0);
		cout << " ";
		setColor(128);
		cout << "                            ";
		setColor(0);
		cout << " ";
	}

	cout << endl;
	setColor(0);
	for (int i = 0; i < 120; i++)
		cout << " ";
	for (int i = 0; i < 30; i++) {
		setColor(255);
		cout << "  ";
		setColor(0);
		cout << "  ";
	}
	for (int i = 0; i < 120; i++)
		cout << " ";

	setColor(116);	
}


//administrator menu interface
void UI::adminMenu()
{
	setColor(128);
	for (int i = 0; i < 120; i++)
		cout << " ";
	cout << endl;
	cout << "  1. Add film | 2. Delete film | 3. Update film | 4. View all | ESC. Exit |                                             " << endl;
	for (int i = 0; i < 120; i++)
		cout << "_";
	cout << endl << endl;
	setColor(112);
}


//user menu interface
void UI::userMenu()
{
	setColor(128);
	for (int i = 0; i < 120; i++)
		cout << " ";
	cout << endl;
	cout << "  1. Search film | 2. Delete film from watchlist | 3. View all | ESC. Exit |                                            " << endl;
	for (int i = 0; i < 120; i++)
		cout << "_";
	cout << endl << endl;
	setColor(112);
}


//run administrator menu
void UI::adminRun()
{
	char option;
	while (true) {
		system("cls");
		adminMenu();
		option = _getch();
		if (option == 27)
			break;
		else if (option == '1') {
			try {
				addNewFilm();
			}
			catch (FilmAlreadyInListException &ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
		}
		else if (option == '2') {
			try {
				deleteFilm();
			}
			catch (FilmNotInListException &ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
		}
		else if (option == '3') {
			try {
				update();
			}

			catch (FilmNotInListException &ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
		}
		else if (option == '4') {
			setColor(63);
			setCursor(49, 1);
			cout << " 4. View all ";
			viewAll(ctrl.getRepo());
		}
		else
			continue;
		system("pause");
	}
}


//run user menu
	void UI::userRun()
{
	char option;
	while (true) {
		system("cls");
		userMenu();
		option = _getch();
		if (option == 27)
			break;
		else if (option == '1') {
			try {
				searchByGenre();
			}
			catch (EmptyGenreException &ex) {
				std::cout << ex.what() << std::endl << std::endl;
				system("pause");
			}
		}
		else if (option == '2') {
			try {
				deleteFromWatchlist();
			}
			catch (FilmNotInListException &ex) {
				std::cout << ex.what() << std::endl << std::endl;
				system("pause");
			}
		}
		else if (option == '3') {
			setColor(63);
			setCursor(50, 1);
			cout << " 3. View all ";
			viewAll(ctrl.getWatchlist());
			displayWatchlist();
			system("pause");
		}
	}
}


//run general menu
void UI::run()
{
	char mainOption;
	while (true) {
		system("cls");
		system("color 70");
		mainPage();
		mainOption = _getch();
		if (mainOption == 'A')
			adminRun();
		else if (mainOption == 'U')
			userRun();
		else if (mainOption == 27)
			break;
		else
			continue;
	}
}