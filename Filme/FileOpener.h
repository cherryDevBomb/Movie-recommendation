#pragma once
#include <iostream>
#include <string>
#include "Film.h"
#include <vector>
#include <cstdlib>
#include <Windows.h>


class FileOpener
{
public:
	virtual void open(std::string filename) = 0;
};


class CSVFileOpener : public FileOpener
{
	void open(std::string filename);
};


class HTMLFileOpener : public FileOpener
{
	void open(std::string filename);
};

