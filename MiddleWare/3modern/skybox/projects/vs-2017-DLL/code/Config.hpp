/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/

#pragma once

#ifdef MY_STATIC_LIBRARY // En caso de usar librer�a est�tica
#define API
#else  // En caso de usar librer�a din�mica
#ifdef MY_DYNAMIC_LIBRARY
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#endif