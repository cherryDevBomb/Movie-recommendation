#pragma once
#include "Controller.h"

class UI
{
private:
	Controller & ctrl;
public:
	UI(Controller& ctrl);
	~UI();

	Controller& getCtrl() const { return ctrl; }

	void addNewFilm();
	void deleteFilm();
	void update();
	void viewAll(List& list);
	void searchByGenre();
	void deleteFromWatchlist();
	void displayWatchlist();

	void setColor(int color);
	void setCursor(short x, short y);

	void mainPage();
	void adminMenu();
	void userMenu();

	void adminRun();
	void userRun();
	void run();
};

