/*************************************************************************//**
* @file
*****************************************************************************/
/*!
* @brief This define declares all functions used in prog1.cpp and these are implemented in functions.cpp
*/
#ifndef _Prog1FunctionsBK_
#define _Prog1FunctionsBK_
#include <string>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <iostream>
using namespace std;
void processDirectory();
bool isGIF(_finddata_t& filestruct);
bool isBMP(_finddata_t& filestruct);
bool isJPG(_finddata_t& filestruct);
bool isPNG(_finddata_t& filestruct);
void extractBMP(_finddata_t& filestruct, int& height, int& width);
void extractGIF(_finddata_t& filestruct, int& height, int& width);
void extractPNG(_finddata_t& filestruct, int& height, int& width);
string intToString(int num);
string createName(string extension, string width, string height, string filename);
string createJPG(string name);

#endif