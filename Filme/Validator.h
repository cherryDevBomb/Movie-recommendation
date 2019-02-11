#pragma once
#include "Controller.h"


class Validator
{
public:
	static std::string validateTitle();
	static int validateYear();
	static std::string validateGenre();
};

