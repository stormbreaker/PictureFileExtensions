/*************************************************************************//**
* @file
*****************************************************************************/
#include "Functions.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This function is the main processing function.  It calls most other functions
and subesquently is the longest.  This function is the loop the processes each
file
within the directory while int main is the loop which switches directories.  
*
* @param[in, out]      height - Used to store the string version of an image 
height once computed
* @param[in, out]      width - used to store the string version of an image 
width once computed
* @param[in, out]   initHeight variable passed into extraction functions as 
0 but returns by reference 
as computed height
* @param[in, out] initWidth - variable passed into extraction functions as 
0 but returns by reference 
as computed width
* @param[in, out] file - this is the file object which is being processed.
It passes into each function
which then analyzes it and changes the file.name accordingly.  
* @param[in] handle - a pointer to allow for looping through a directory
and processing files
*
*
*
* @returns No returns.  Outputs error messages if a certain part failed.
*
*****************************************************************************/
void processDirectory()
{
	string height, width;
	int initHeight, initWidth;
	_finddata_t file;
	intptr_t handle = 0;
	handle = _findfirst("*.*", &file);
	if (handle == -1)
	{
		return;
	}
	do
	{
		initHeight = 0;
		initWidth = 0;
		if (file.attrib & _A_SUBDIR)
		{
		}
		else if (isGIF(file))
		{
			extractGIF(file, initHeight, initWidth);
			height = intToString(initHeight);
			width = intToString(initWidth);
			if (rename(file.name, createName(".gif", width, height, file.name).c_str()) != 0)
			{
				cout << "Unable to rename " << file.name << " to " << createName(".gif", width, height, file.name);
			}

		}
		else if (isBMP(file))
		{
			extractBMP(file, initHeight, initWidth);
			height = intToString(initHeight);
			width = intToString(initWidth);
			if (rename(file.name, createName(".bmp", width, height, file.name).c_str()) != 0)
			{
				cout << "Unable to rename " << file.name << " to " << createName(".bmp", width, height, file.name);
			}
		}
		else if (isPNG(file))
		{
			extractPNG(file, initHeight, initWidth);
			height = intToString(initHeight);
			width = intToString(initWidth);
			if (rename(file.name, createName(".png", width, height, file.name).c_str()) != 0)
			{
				cout << "Unable to rename " << file.name << " to " << createName(".png", width, height, file.name);
			}
		}
		else if (isJPG(file))
		{
			if (rename(file.name, createJPG(file.name).c_str()) != 0)
			{
				cout << "Unable to rename " << file.name << " to " << createJPG(file.name).c_str();
			}
		}
	} while (_findnext(handle, &file) == 0);
	_findclose(handle);
	return;
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description: This function determines if a file is a .gif file or not.
* It uses bitwise operatores to determine this.  If it is, returns true. 
Else false.
* 
*
* @param[in, out]      filestruct - this is the file object that get passes 
into the function
* for analysis.  However nothing is modified.  
* @param[in]     fin - this is the ifstream created for manipulating this file
* @param[in]  bytes - an array used to store the bytes read in which must be analyzsed to
* determine true or false.
*
* @returns true - is a .gif file
* @returns false -  is not a .gif file
*
*****************************************************************************/
bool isGIF(_finddata_t& filestruct)
{
	ifstream fin;
	unsigned char bytes[6];
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.read((char*) &bytes, 6);
		fin.close();
		if ((bytes[0] == 'G') && (bytes[1] == 'I') && (bytes[2] == 'F') && (bytes[3] == '8') && (bytes[4] == '9' || '7') && (bytes[5] == 'a'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
		return false;
	}
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This function extracts the width and height out of a .gif image file using
bitwise
* operators only.  It returns nothing except via reference on the variables
which were
* passed in.  These are the height, and the width.  
* 
* @param[in, out]      filestruct - this is the file object that get passes 
into the function
* for analysis.  However nothing is modified.  
* @param[in, out]     height - this is an integer that is passed in as 0 and
is created
* using bitwise operators to concatenate several chars together.  
* @param[in,out]  width - this is an integer that is passed in as 0 and is 
created
* using bitwise operators to concatenate several chars together.  
* @param[in] fin - this is the ifstream created for manipulating this file
* @param[in] reader - a character array used to store the correct bytes and
then or them with height and width
* 
* @returns nothing since it is a void function.  The only things which are
changed is through pass by reference
*
*****************************************************************************/
void extractGIF(_finddata_t& filestruct, int& height, int& width)
{
	ifstream fin;
	unsigned char reader[2];
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.seekg(6, ios::beg);
		fin.read((char*) &reader, 2);
		width = width | reader[1];
		width = width << 8;
		width = width | reader[0];
		fin.read((char*) &reader, 2);
		height = height | reader[1];
		height = height << 8;
		height = height | reader[0];
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
	}
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description: This function determines if a file is a .bmp file or not.
* It uses bitwise operatores to determine this.  If it is, returns true. Else
false.
*
*
* @param[in, out]      filestruct - this is the file object that get passes 
into the function
* for analysis.  However nothing is modified.
* @param[in]     fin - this is the ifstream created for manipulating this
file
* @param[in]  bytes - an array used to store the bytes read in which must be
analyzsed to
* determine true or false.
*
* @returns true - is a .bmp file
* @returns false -  is not a .bmp file
*
*****************************************************************************/
bool isBMP(_finddata_t& filestruct)
{
	ifstream fin;
	unsigned char bytes[2];
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.read((char*) &bytes, 2);
		if (bytes[0] == 'B' && bytes[1] == 'M')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
		return false;
	}
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This function extracts the width and height out of a .bmp image file using
bitwise
* operators only.  It returns nothing except via reference on the variables
which were
* passed in.  These are the height, and the width.
*
* @param[in, out]      filestruct - this is the file object that get passes
into the function
* for analysis.  However nothing is modified.
* @param[in, out]     height - this is an integer that is passed in as 0
and is created
* using bitwise operators to concatenate several chars together.
* @param[in,out]  width - this is an integer that is passed in as 0 and
is created
* using bitwise operators to concatenate several chars together.
* @param[in] fin - this is the ifstream created for manipulating this file
* @param[in] reader - a character array used to store the correct bytes and
then or them with height and width
*
* @returns nothing since it is a void function.  The only things which are 
changed is through pass by reference
*
*****************************************************************************/
void extractBMP(_finddata_t& filestruct, int& height, int& width)
{
	ifstream fin;
	unsigned char reader[4];
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.seekg(18, ios::beg);
		fin.read((char*) &reader, 4);
		width = width | reader[3];
		width = width << 8;
		width = width | reader[2];
		width = width << 8;
		width = width | reader[1];
		width = width << 8;
		width = width | reader[0];
		fin.read((char*) &reader, 2);
		height = height | reader[3];
		height = height << 8;
		height = height | reader[2];
		height = height << 8;
		height = height | reader[1];
		height = height << 8;
		height = height | reader[0];
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
	}
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description: This function determines if a file is a .png file or not.
* It uses bitwise operatores to determine this.  If it is, returns true. 
Else false.
*
*
* @param[in, out]      filestruct - this is the file object that get passes
into the function
* for analysis.  However nothing is modified.
* @param[in]     fin - this is the ifstream created for manipulating this file
* @param[in]  bytes - an array used to store the bytes read in which must be 
analyzsed to
* determine true or false.
*
* @returns true - is a .png file
* @returns false -  is not a .png file
*
*****************************************************************************/
bool isPNG(_finddata_t& filestruct)
{
	ifstream fin;
	unsigned char bytes[8];
	unsigned char array[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.read((char*) &bytes, 8);
		if (bytes[0] == array[0] && bytes[1] == array[1] && bytes[2] == array[2] && bytes[3] == array [3] && bytes[4] == array[4] 
			&& bytes[5] == array[5] && bytes[6] == array[6] && bytes[7] == array[7])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
		return false;
	}
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This function extracts the width and height out of a .png image file using
bitwise
* operators only.  It returns nothing except via reference on the variables
which were
* passed in.  These are the height, and the width.
*
* @param[in, out]      filestruct - this is the file object that get passes
into the function
* for analysis.  However nothing is modified.
* @param[in, out]     height - this is an integer that is passed in as 0 and
is created
* using bitwise operators to concatenate several chars together.
* @param[in,out]  width - this is an integer that is passed in as 0 and is 
created
* using bitwise operators to concatenate several chars together.
* @param[in] fin - this is the ifstream created for manipulating this file
* @param[in] reader - a character array used to store the correct bytes and
then or them with height and width
*
* @returns nothing since it is a void function.  The only things which are 
changed is through pass by reference
*
*****************************************************************************/
void extractPNG(_finddata_t& filestruct, int& height, int& width)
{
	ifstream fin;
	unsigned char reader[4];
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.seekg(16, ios::beg);
		fin.read((char*)&reader, 4);
		width = width | reader[0];
		width = width << 8;
		width = width | reader[1];
		width = width << 8;
		width = width | reader[2];
		width = width << 8;
		width = width | reader[3];
		fin.read((char*) &reader, 4);
		height = height | reader[0];
		height = height << 8;
		height = height | reader[1];
		height = height << 8;
		height = height | reader[2];
		height = height << 8;
		height = height | reader[3];
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
	}
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description: This function determines if a file is a .jpg file or not.
* It uses bitwise operatores to determine this.  If it is, returns true. Else
false.
*
*
* @param[in, out]      filestruct - this is the file object that get passes 
into the function
* for analysis.  However nothing is modified.
* @param[in]     fin - this is the ifstream created for manipulating this 
file
* @param[in]  bytes - an array used to store the bytes read in which must be 
analyzsed to
* determine true or false.
*
* @returns true - is a .jpg file
* @returns false -  is not a .jpg file
*
*****************************************************************************/
bool isJPG(_finddata_t& filestruct)
{
	ifstream fin;
	unsigned char bytes[2];
	fin.open(filestruct.name, ios::in | ios::binary);
	if (fin.is_open())
	{
		fin.read((char*) &bytes, 2);
		if (bytes[0] == 255 && bytes[1] == 216)
		{
			fin.seekg(-2, ios::end);
			fin.read((char*)&bytes, 2);
			if (bytes[0] == 255 && bytes[1] == 217)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Unable to open " << filestruct.name << endl;
		return false;
	}
}

/**************************************************************************//**
* @author http://www.cplusplus.com/articles/D9j2Nwbp/
*
* @par Description:
* This function takes an integer as an input and using a string stream and the
.str() function
* converts the int to a string.  This was found online and modified to suit
my needs.
* 
*
* @param[in]      num - this is the integer which is desired to be converted
* @param[out]     result - This is the string which results from the 
conversion
* @param[in]  convert - This is the string stream which performs the 
conversionb
*
* @returns result - the resulting string
*
*****************************************************************************/
string intToString(int num)
{
	string result;
	ostringstream convert;   // stream used for the conversion

	convert << num;      // insert the textual representation of 'num' in the characters in the stream
	result = convert.str();
	return result;// set 'result' to the contents of the stream
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This is a function designed to forumlate the entirity of the filename for 
the image.
* As an input, the extension is passed in.  When called in this program, it
is a literal string.
* The previously created width and height strings are passed in as well as 
the original file.name.
* The one line simply concatenates all four into one string stored and 
returned as result.  
* The file works for .bmp, .gif, and .png
* 
* @param[in]     extension - the file extension to be appended to the end.
* @param[in]     width - correct width to be attached in the middle of the 
file name.
* @param[in]     height - correct width to be attached
* @param[in]     filename - original filename w/o extension
* @param[out]  result - the string to be outputted
*
* @returns result - the resulting complete file name to send to rename 
function.  
*
*****************************************************************************/
string createName(string extension, string width, string height, string filename)
{
	string result;

	result = filename + "_" + width + "_x_" + height + extension;

	return result;
}
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This function was specialized to create a complete filename for .jpg files.
* It simply reads in the name, concatenates ".jpg" to itself and returns name.  
* 
*
* @param[in, out]      name - this is the file name for .jpg which is passed in
* and then is returned after ".jpg" is appended.  
*
*
* @returns name
*
*****************************************************************************/
string createJPG(string name)
{
	name = name + ".jpg";
	return name;
}