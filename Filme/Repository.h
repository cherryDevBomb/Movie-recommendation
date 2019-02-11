#pragma once

#include <iostream>
#include <vector>
#include "Film.h"
#include <memory>
#include "FileReader.h"
#include "FileWriter.h"
#include "FileOpener.h"


class List
{
protected:
	std::vector<Film> list;
public:
	List();
	~List();
	
	std::vector<Film> getList() const { return list; }
	void setList(std::vector<Film> & list) { this->list = list; }

	int findFilmIndex(std::string& title, unsigned year);
	Film& findFilm(std::string& title, unsigned year);

	virtual void add(Film& item);
	virtual void remove(Film& item);
};


class Repository : public List
{
public:
	Repository();
	~Repository();

	virtual void updateTitle(Film& item, std::string newTitle);
	virtual void updateYear(Film& item, unsigned newYear);
	virtual void updateGenre(Film& item, std::string & newGenre);
	virtual void updateLikes(Film& item);
	
	std::vector<Film> filterByGenre(std::string& genre);
};


class FileRepository : public Repository
{
public:
	FileRepository(std::string filename) : Repository() { this->filename = filename; }
	
	void setFileReader(FileReader* myFileReader) { iFileReader.reset(myFileReader); }
	void setFileWriter(FileWriter* myFileWriter) { iFileWriter.reset(myFileWriter); }
	
	std::string & getFilename() { return filename; }
	FileReader & getFileReader() { return *iFileReader; }
	FileWriter & getFileWriter() { return *iFileWriter; }

	virtual void addFilm(Film& item);
	virtual void deleteFilm(Film& item);
	virtual void updateFilmTitle(Film& item, std::string newTitle);
	virtual void updateFilmYear(Film& item, unsigned newYear);
	virtual void updateFilmGenre(Film& item, std::string & newGenre);
	virtual void updateFilmLikes(Film& item);
private:
	std::string filename;
	std::unique_ptr<FileReader> iFileReader;
	std::unique_ptr<FileWriter> iFileWriter;
};



class Watchlist : public List
{
public:
	Watchlist(std::string filename) : List() { this->filename = filename; }

	void setCSVFileWriter(FileWriter* myFileWriter) { csvFileWriter.reset(myFileWriter); }
	void setHTMLFileWriter(FileWriter* myFileWriter) { htmlFileWriter.reset(myFileWriter); }
	void setFileOpener(FileOpener* myFileOpener) { iFileOpener.reset(myFileOpener); }

	std::string & getFilename() { return filename; }
	FileWriter & getCSVFileWriter() { return *csvFileWriter; }
	FileWriter & getHTMLFileWriter() { return *htmlFileWriter; }
	FileOpener & getFileOpener() { return *iFileOpener; }

	virtual void addToWatchlist(Film& item);
	virtual void deleteFromWathlist(Film& item);

private:
	std::string filename;
	std::unique_ptr<FileWriter> csvFileWriter;
	std::unique_ptr<FileWriter> htmlFileWriter;
	std::unique_ptr<FileOpener> iFileOpener;  
};