#include "stdafx.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>



std::vector<Film> CSVFileReader::read(std::string filename)
{
	filename.append(".csv");
	std::ifstream csvFile { filename };
	std::string title;
	std::string yearStr;
	unsigned year;
	std::string genre;
	std::string likesStr;
	int likes;
	std::vector<Film> films;
	while (csvFile) {
		getline(csvFile, title, ',');
		getline(csvFile, yearStr, ',');
		year = stoul(yearStr);
		getline(csvFile, genre, ','); 
		getline(csvFile, likesStr);
		likes = stoi(likesStr);
		Film item(title, year, genre, likes);
		films.push_back(item);
	}
	films.pop_back();
	return films;
}

