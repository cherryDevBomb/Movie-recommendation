#pragma once
#include <iostream>
#include "Repository.h"
#include "Film.h"


class Controller
{
private:
	std::unique_ptr<FileRepository> repo;	//full movie list managed by admin
	std::unique_ptr<Watchlist> watchlist;	//user-defined movie watchlist
public:
	Controller(FileRepository* repo, Watchlist* watchlist);
	~Controller();

	FileRepository & getRepo() const { return *repo; }
	Watchlist & getWatchlist() const { return *watchlist; }

	void addToRepo(std::string& title, unsigned year, std::string& genre);
	void deleteFromRepo(std::string& title, unsigned year);
	void updateTitle(std::string& title, unsigned year, std::string& newTitle);
	void updateYear(std::string& title, unsigned year, unsigned newYear);
	void updateGenre(std::string& title, unsigned year, std::string& newGenre);
	void updateLikes(std::string& title, unsigned year);
};

