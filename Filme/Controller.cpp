#include "stdafx.h"
#include "Controller.h"
#include <iostream>


//constructor
Controller::Controller(FileRepository * repo, Watchlist * watchlist)
{
	this->repo.reset(repo);
	this->watchlist.reset(watchlist);
} 


//destructor
Controller::~Controller()
{
}


//add film with specified attributes to Repository
void Controller::addToRepo(std::string& title, unsigned year, std::string& genre)
{
	Film toAdd(title, year, genre);
	repo->addFilm(toAdd);
}


//delete film with specified attributes from Repository
void Controller::deleteFromRepo(std::string & title, unsigned year)
{
	Film & toErase = repo->findFilm(title, year); //get element to erase
	repo->deleteFilm(toErase);
}


//update title of film with specified attributes
void Controller::updateTitle(std::string & title, unsigned year, std::string & newTitle)
{
	Film & toUpdate = repo->findFilm(title, year);
	repo->updateFilmTitle(toUpdate, newTitle);
}


//update year of film with specified attributes
void Controller::updateYear(std::string& title, unsigned year, unsigned newYear)
{
	Film & toUpdate = repo->findFilm(title, year);
	repo->updateFilmYear(toUpdate, newYear);
}


//update genre of film with specified attributes
void Controller::updateGenre(std::string & title, unsigned year, std::string & newGenre)
{
	Film & toUpdate = repo->findFilm(title, year);
	repo->updateFilmGenre(toUpdate, newGenre);
}

void Controller::updateLikes(std::string & title, unsigned year)
{
	Film & toRate = repo->findFilm(title, year);
	repo->updateFilmLikes(toRate);
}
