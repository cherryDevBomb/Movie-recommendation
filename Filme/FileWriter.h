#pragma once
#include "Film.h"
#include <vector>

class FileWriter
{
public:
	virtual void write(std::string filename, std::vector<Film> films) = 0;
};


class CSVFileWriter : public FileWriter
{
public:
	void write(std::string filename, std::vector<Film> films);
};


class HTMLFileWriter : public FileWriter
{
public:
	void write(std::string filename, std::vector<Film> films);
};