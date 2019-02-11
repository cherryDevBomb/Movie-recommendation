#pragma once
#include <iostream>
#include <string>


class Film
{
private:
	std::string title; 
	unsigned year;
	std::string genre;
	std::string link;
	int likes;


public:
	Film();
	Film(std::string title, unsigned year, std::string genre);
	Film(std::string title, unsigned year, std::string genre, int likes);
	~Film();

	//attribute getters
	std::string getTitle() const { return title; }
	unsigned getYear() const { return year; }
	std::string getGenre() const { return genre; }
	int getLikes() const { return likes; }
	std::string getLink() const { return link; }

	//atribute setters
	void setTitle(std::string title) { this->title = title; }
	void setYear(unsigned year) { this->year = year; }
	void setGenre(std::string genre) { this->genre = genre; }

	void setLink();						
	void rateFilm() { likes++; }			//increment number of likes

	friend std::ostream& operator<<(std::ostream& os, const Film& film);
	void displayOne();		
	void playTrailer();
};

