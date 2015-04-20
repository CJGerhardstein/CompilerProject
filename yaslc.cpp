

//Dave A. Berque, Revised August 2014
//This driver program should be used to test the first part of the YASL
//compiler.

//This version tested in Visual Studio .NET 2014


#include "stdafx.h"  // A visual studio requirement

#include "scanner.h"
#include "filemngr.h"
#include "parser.h"

int main(int argc, char* argv[])
{   
	parserClass parser;

	parser.parseProgram();

	cout << "YASLC - CG has just compiled " << parser.numLinesProcessed() << " lines of code" << endl;

	cin.get();
	parser.closeSourceProgram();
    

	
    return (0);
}