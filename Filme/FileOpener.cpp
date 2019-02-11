#include "stdafx.h"
#include <iostream>
#include "FileOpener.h"


void CSVFileOpener::open(std::string filename)
{
	filename.append(".csv");
	system(filename.c_str());
}

void HTMLFileOpener::open(std::string filename)
{
	filename.append(".html");
	ShellExecuteA(NULL, NULL, "firefox.exe", filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}
