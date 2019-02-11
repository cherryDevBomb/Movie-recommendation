#pragma once
#include <exception>

class FilmAlreadyInListException : public std::exception
{
public:
	const char* what() const { return "Film already in list!"; }

};


class FilmNotInListException : public std::exception
{
public:
	const char* what() const { return "Film not found!"; }

};


class EmptyGenreException : public std::exception
{
public:
	const char* what() const { return "There are no films of this genre."; }
};