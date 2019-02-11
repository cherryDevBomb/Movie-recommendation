#pragma once
#include "Film.h"
#include <vector>

class FileReader
{
public:
	virtual std::vector<Film> read(std::string filename) = 0;
};

class CSVFileReader : public FileReader
{
public:
	std::vector<Film> read(std::string filename);
};

