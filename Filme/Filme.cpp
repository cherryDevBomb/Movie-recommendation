// Filme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Windows.h"
#include "Film.h"
#include "Repository.h"
#include "Controller.h"
#include "UI.h"
#include "FileReader.h"
#include "Tests.h"


int main()
{
	Tests::testAll();

	system("color 70");

	//create some films
	Film f1("The martian", 2015, "drama", 100);
	Film f2("Inception", 2010, "Sci-Fi", 98); 
	Film f3("The imitation game", 2014, "drama", 103);
	Film f4("The Shawshank redemption", 1994, "crime", 86); 
	Film f5("Shrek", 2001, "animation", 55);
	Film f6("Doctor strange", 2016, "Sci-Fi", 46);
	Film f7("Minions", 2015, "animation", 77);
	Film f8("V for Vendetta", 2005, "action", 60); 
	Film f9("Star trek", 2009, "Sci-Fi", 67);	
	Film f10("The hangover", 2009, "comedy", 45); 

	Controller c1(new FileRepository("films"), new Watchlist("watchlist"));
	c1.getRepo().setFileReader(new CSVFileReader);
	c1.getRepo().setFileWriter(new CSVFileWriter);
	c1.getWatchlist().setCSVFileWriter(new CSVFileWriter);
	c1.getWatchlist().setHTMLFileWriter(new HTMLFileWriter);
	std::vector<Film> films = c1.getRepo().getFileReader().read(c1.getRepo().getFilename());
	c1.getRepo().setList(films);

	UI ui(c1);
	ui.run();
	system("pause");
    return 0;
}

