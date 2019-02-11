#include "stdafx.h"
#include "Repository.h"
#include <vector>


//default constructor
List::List()
{
	list = {};
}


//destructor
List::~List()
{
}


//find index of a film in the list
int List::findFilmIndex(std::string & title, unsigned year)
{
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i].getTitle() == title && list[i].getYear() == year)
			return i; //return index of found film
	}
	return -1; //if not found
}


//find a film in the list by its title and year
Film& List::findFilm(std::string & title, unsigned year)
{
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i].getTitle() == title && list[i].getYear() == year)
			return list[i];
	}
	Film * emptyFilm = new Film;
	return *emptyFilm;	//return "empty" film if not found
}


//add film to list
void List::add(Film & item)
{
	list.push_back(item);
}


//delete film from list
void List::remove(Film & item)
{
	std::string title = item.getTitle();
	int index = findFilmIndex(title, item.getYear());
	list.erase(list.begin() + index); //erase element
}



//repo constructr
Repository::Repository()
{
}


//repo destructor
Repository::~Repository()
{
}


//update name
void Repository::updateTitle(Film & item, std::string newTitle)
{
	item.setTitle(newTitle);
}


//update year
void Repository::updateYear(Film & item, unsigned newYear)
{
	item.setYear(newYear);
}


//update genre
void Repository::updateGenre(Film & item, std::string & newGenre)
{
	item.setGenre(newGenre);
}


//increase number of likes
void Repository::updateLikes(Film & item)
{
	item.rateFilm();
}


//get list containing only films of a certain genre
std::vector<Film> Repository::filterByGenre(std::string & genre)
{
	std::vector<Film> found;
	for (Film &item : list) {
		if (item.getGenre() == genre)
			found.push_back(item);
	}
	return found;
}



//add film to memory repo + add to file
void FileRepository::addFilm(Film & item)
{
	add(item);
	iFileWriter->write(filename, getList());
}


//delete film from memory repo + add to file
void FileRepository::deleteFilm(Film & item)
{
	remove(item);
	iFileWriter->write(filename, getList());
}


//update film title + add to file
void FileRepository::updateFilmTitle(Film & item, std::string newTitle)
{
	updateTitle(item, newTitle);
	iFileWriter->write(filename, getList());
}


//update film year + add to file
void FileRepository::updateFilmYear(Film & item, unsigned newYear)
{
	updateYear(item, newYear);
	iFileWriter->write(filename, getList());
}


//update film genre + add to file
void FileRepository::updateFilmGenre(Film & item, std::string & newGenre)
{
	updateGenre(item, newGenre);
	iFileWriter->write(filename, getList());
}


//update film likes + add to file
void FileRepository::updateFilmLikes(Film & item)
{
	updateLikes(item);
	iFileWriter->write(filename, getList());
}


//add film to user watchlist and write to csv and html files
void Watchlist::addToWatchlist(Film & item)
{
	add(item);
	csvFileWriter->write(filename, getList());
	htmlFileWriter->write(filename, getList());
}


//delete film from user watchlist and from csv and html files
void Watchlist::deleteFromWathlist(Film & item)
{
	remove(item);
	csvFileWriter->write(filename, getList());
	htmlFileWriter->write(filename, getList());
}
