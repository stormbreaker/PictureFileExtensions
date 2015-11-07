/*************************************************************************//**
* @file
*
* @mainpage Program 1 - Image Detection
*
* @section course_section Course Information
*
* @author Benjamin Kaiser
*
* @date 10-13-14
* @par Professor:
*         Roger Schrader
*
* @par Course:
*         CSC 250 - M002 -  3 PM
*
* @par Location:
*         McLaury - 316
*
* @section program_section Program Information
*
* @details The scenario is at a company who recently was hacked by a 
* disgruntled employee
  who deleted all the file extensions to pertinent files such as pictures 
* files used for 
the website, the documents, the forms, etc.  The purpose of this program
is to identify
the image files, extract the width and height, it then renames the files 
using this information
and appends the correct file extension to the end of the file thus creating
the correct file.
The program does this for .png, .bmp, and .gif picture files.  .jpg files
are simply created using the file
extension as it is extremely difficult to extract height and width from a .jpg.
*
*
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      No special instructions
*
* @par Usage:
@verbatim
c:\> prog1.exe <dir1> <dir2> <etc>
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug Not aware of any bugs
*
* @todo Not aware of items to do.
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Sept 24, 2014 Detect command line arguments, valid directories, output dir
Oct 1, 2014	 Worked out logic on paper
Oct 12, 2014 finalized logic on paper.  Began coding
Oct 13, 2014 coded
@endverbatim
*
*****************************************************************************/
#include <iostream>
#include "Functions.h"
#include <direct.h>
#include <io.h>
#include <string>
using namespace std;
/**************************************************************************//**
* @author Benjamin Kaiser
*
* @par Description:
* This is the main function of prog1.exe.  It is essentially a for loop to navigate directories
Professor Schrader provided the skeleton of this  loop in the assignment instructions.
*
* @param[in]      argc - counts the number of arguments entered on the command line
* @param[in]     argv[] - These are the arguments (directories) entered on the command line
* @param[out] buffer - stores a pointer to the current working directory so as to always return to it
* @param[in] i - counter for the for loop
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
*
*****************************************************************************/
int main ( int argc, char* argv[] )
{
    char* buffer;
    buffer = _getcwd ( NULL, 0 );
    
    for ( int i = 1; i < argc; i++ ) // for loop takes CLA directories and processes their contents
    {
        _chdir ( buffer );
        
        if ( _chdir ( argv[i] ) == 0 )
        {
            processDirectory();
        }
        else
        {
            cout << argv[i] << " is an invalid directory" << endl;
        }
        
    }
    
    return 0;
};