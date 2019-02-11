#include "stdafx.h"
#include "Tests.h"
#include <cassert>


void Tests::testFilm()
{
	Film test1("The martian", 2015, "drama");
	assert(test1.getTitle() == "The martian");
	assert(test1.getYear() == 2015);
	assert(test1.getGenre() == "drama");
	assert(test1.getLikes() == 0);
	assert(test1.getLink() == "http://www.google.com/search?q=the+martian+trailer&btnI=I%27m+Feeling+Lucky");

	Film test2("Inception", 2010, "Sci-Fi", 98);
	assert(test2.getTitle() == "Inception");
	assert(test2.getYear() == 2010);
	assert(test2.getGenre() == "Sci-Fi");
	assert(test2.getLikes() == 98);
	assert(test2.getLink() == "http://www.google.com/search?q=inception+trailer&btnI=I%27m+Feeling+Lucky");
}


void Tests::testRepo()
{
	Film test1("The martian", 2015, "drama");
	Film test2("Inception", 2010, "Sci-Fi", 98);
	std::string title1 = "The martian";
	std::string title2 = "Inception";
	std::string genre = "Sci-Fi";
	FileRepository testRepo("file");
	assert(testRepo.getList().size() == 0);
	testRepo.add(test1);
	testRepo.add(test2);
	assert(testRepo.getList().size() == 2); 
	assert(testRepo.findFilmIndex(title2, 2010) == 1);
	assert(testRepo.findFilmIndex(title2, 2000) == -1);
	Film* notFound = new Film;
	assert(testRepo.findFilm(title2, 2000).getTitle() == "");
	testRepo.updateTitle(test1, title2);
	assert(test1.getTitle() == title2);
	testRepo.updateYear(test1, 1999);
	assert(test1.getYear() == 1999);
	testRepo.updateGenre(test1, genre);
	assert(test1.getGenre() == genre);
	testRepo.updateLikes(test1);
	assert(test1.getLikes() == 1);
	std::vector<Film> filtered = testRepo.filterByGenre(genre);
	assert(filtered.size() == 1);
}


void Tests::testController()
{
	std::string title1 = "The martian";
	std::string title2 = "Inception";
	std::string genre1 = "drama";
	std::string genre2 = "thriller";
	
	Controller testCtrl(new FileRepository("file"), new Watchlist("wfile"));
	testCtrl.getRepo().setFileReader(new CSVFileReader);
	testCtrl.getRepo().setFileWriter(new CSVFileWriter);
	testCtrl.getWatchlist().setCSVFileWriter(new CSVFileWriter);
	testCtrl.getWatchlist().setFileOpener(new CSVFileOpener);
	testCtrl.getWatchlist().setHTMLFileWriter(new HTMLFileWriter);
	testCtrl.addToRepo(title1, 2010, genre1);
	testCtrl.addToRepo(title2, 2001, genre1);
	assert(testCtrl.getRepo().getList().size() == 2);
	testCtrl.updateTitle(title1, 2010, title2);
	assert(testCtrl.getRepo().findFilmIndex(title2, 2010) == 0);
	testCtrl.updateYear(title2, 2010, 2020);
	assert(testCtrl.getRepo().findFilmIndex(title2, 2020) == 0);
	testCtrl.updateGenre(title2, 2001, genre2);
	assert(testCtrl.getRepo().findFilm(title2, 2001).getGenre() == genre2);
	testCtrl.updateLikes(title2, 2001);
	assert(testCtrl.getRepo().findFilm(title2, 2001).getLikes() == 1);
	testCtrl.deleteFromRepo(title2, 2020);
	testCtrl.deleteFromRepo(title2, 2001);
	assert(testCtrl.getRepo().getList().size() == 0);
	Film testFilm(title1, 2001, genre1);
	testCtrl.getWatchlist().addToWatchlist(testFilm);
	assert(testCtrl.getWatchlist().getList().size() == 1);
	testCtrl.getRepo().getFileWriter().write(testCtrl.getRepo().getFilename(), testCtrl.getWatchlist().getList());
	testCtrl.getWatchlist().deleteFromWathlist(testFilm);
	assert(testCtrl.getWatchlist().getList().size() == 0);
	testCtrl.getRepo().getFileReader().read(testCtrl.getRepo().getFilename());
	

}


void Tests::testAll()
{
	testFilm();
	testRepo();
	testController();
}
