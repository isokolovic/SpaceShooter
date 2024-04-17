#pragma once
#include <string>

std::string GetResourceDir() {
//Preprocessor directives for release and debug builds: 
#ifdef NDEBUG 
	return "assets/";
#else
	return "C:/Users/isoko/source/repos/isokolovic/SpaceShooterGame/SpaceShooterGame/assets/";
#endif
}
