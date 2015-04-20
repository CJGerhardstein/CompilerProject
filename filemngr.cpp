//Chris Gerhardstein Last Edited 9/5/14

//this part of the code works! i got a 100 on the first project.  fingers crossed
//i won't need to change much later.

//This file contains implementations of the 
//fileManagerClass

//The class header is found in filemngr.h

#include "stdafx.h"  // Required for visual studio to work correctly

#include "filemngr.h"


fileManagerClass::fileManagerClass()
//Precondition: None.
//Postcondition: The constructor has opened the file which is to be
//               processed and has inialized the currentLineNumber to 0
{  char filename[MAXCELLSPERSTRING];

   cout << "Enter file name to compile: ";
   cin.getline (filename, MAXCELLSPERSTRING);
   fileToCompile.open(filename);

   if (fileToCompile.fail())
   {  cout << "Error, the source file: " << filename << " was not opened." << endl;
      cout << "Press return to end program." << endl;
      cin.get();
      exit(1);
   }  
  currentLineNumber = 0;
}

int fileManagerClass::getNextChar()
//Precondition:  The source file associated with the owning object has
//               been prepared for reading.
//Postcondition: The next character from the input file has been read and
//               returned by the function.  If another chacter could not
//               be read because END OF FILE was reached then EOF is
//               returned.
{

	int count = 0;
	if ((currentLineNumber == 0) ||
      (charToReadNext == strlen(currentLine)))
   {  if (fileToCompile.peek() == EOF) 
	{ 
		return (EOF);
	}
         
	  fileToCompile.getline(currentLine, MAXCELLSPERSTRING);
	  currentLineNumber++;
	  if (autoPrintStatus == true)
	  {
		  printCurrentLine();
	  }
	  strcat(currentLine, "\n");
      charToReadNext = 0;
   }
	return(currentLine[charToReadNext++]);
	
}

void fileManagerClass::pushBack()
{
	if (charToReadNext != 0)
		charToReadNext = charToReadNext - 1;
}

void fileManagerClass::printCurrentLine()
{
	cout << currentLineNumber << "- " << currentLine << endl;
}

void fileManagerClass::setPrinterStatus(bool newStatus)
{
	autoPrintStatus = newStatus;
}

//Returns the cumulative number of lines that have been processed
//(read to buffer) so far
int fileManagerClass::numLinesProcessed()
{
	return currentLineNumber;
}

void fileManagerClass::closeSourceProgram()
//Precondition:  The file belonging to the object owning this routine has
//               been opened.
//Postcondition: The file belonging to the object owning this routine has
//               been closed.
{  fileToCompile.close();
}
