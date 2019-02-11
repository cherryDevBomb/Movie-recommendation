#include "stdafx.h"
#include <iomanip>
#include "Film.h"
#include <Windows.h>
#include <shellapi.h>


//default constructor
Film::Film() : title(""), year(0), genre(""), link(""), likes(0) {}


//constructor with 3 parameters (initializes number of likes to 0)
Film::Film(std::string title, unsigned year, std::string genre) :
	title(title), year(year), genre(genre), link(""), likes(0) 
{
	setLink();
}


//constructor with 4 parameters (number of likes specified)
Film::Film(std::string title, unsigned year, std::string genre, int likes) :
	title(title), year(year), genre(genre), link(""), likes(likes) 
{
	setLink();
}


//destructor
Film::~Film()
{
}


//create link to film trailer
void Film::setLink()
{
	std::string searchName = title;		//copy title
	for (size_t i = 0; i < searchName.length(); i++) {
		if (isupper(searchName[i]))				//convert title to lowercase
			searchName[i] = tolower(searchName[i]);
		if (isspace(searchName[i]))				//change spaces to "+"
			searchName[i] = '+';
	}
	std::string link = "http://www.google.com/search?q=" + searchName + "+trailer&btnI=I%27m+Feeling+Lucky";
	this->link = link;
}


//display a film and its attributes
void Film::displayOne()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 115);
	std::string FormattedTitle = title;
	for (size_t i = 0; i < FormattedTitle.length(); i++)	//convert title to uppercase
		FormattedTitle[i] = toupper(FormattedTitle[i]);
	std::cout << "          " << FormattedTitle << std::endl;
	SetConsoleTextAttribute(hConsole, 112);
	std::cout << "          " << genre << "   |    " << year << "    |    " << likes << " likes" << std::endl;
	std::cout << std::endl;
}

//open browser to play trailer
void Film::playTrailer()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", link.c_str(), NULL, SW_SHOWMAXIMIZED);
}


//overload output operator
std::ostream & operator<<(std::ostream & os, const Film & film)
{
	std::string FormattedTitle = film.title;
	for (size_t i = 0; i < FormattedTitle.length(); i++)	//convert title to uppercase
		FormattedTitle[i] = toupper(FormattedTitle[i]);
	os << std::setw(54) << FormattedTitle << std::setw(10) << film.year << std::setw(14) << film.genre << std::setw(9) << film.likes << std::endl;
	return os;
}
