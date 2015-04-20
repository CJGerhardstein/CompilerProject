//Dave A. Berque, Revised August 2014
//This file contains some general constant definitions that will
//be useful in several parts of the compiler.  Feel free to add
//additional definitions here.

#ifndef _general
#define _general

const int MAXCELLSPERSTRING = 82;  //80 characters as well as \n plus \0.

// below are states that are not final states.


const int RELOP_T = 0;
const int ADDOP_T = 1;
const int MULOP_T = 2;
const int OPENP_T = 3;
const int CLOSEP_T = 4;
const int IDENT_T = 5;
const int DIGIT_T = 6;
const int TRUE_T = 7;
const int FALSE_T = 8;
const int SEMICOLON_T = 9;
const int OTHER = 10;



const int OPENBRACKET_T = 13;


// Below are Final States that requre only 
// one character to reach.
const int PLUS_ST = 14;
const int MINUS_ST = 15;
const int TIMES_ST = 16;

const int PERIOD_T = 19;

const int COMMA_T = 21;
const int AMPERSAND_T = 22;

const int ERROR_T = 23;
const int COMMENT_NONTOKEN = 24;

const int COMPDIRECTIVE_T = 25;
const int ERROR2_T = 27;
const int STRING_T = 28;
const int EQUAL_T = 34;
const int ISEQUAL_ST = 35;
const int LESS_ST = 36;
const int INSERT_T = 37; // >>

const int NOTEQ_ST = 38;
const int LESSEQ_ST = 39;
const int GREATER_ST = 40;
const int SWAP_T = 41;

const int EXTRACT_T = 42; // <<
const int GREATEREQ_ST = 43;
const int EOF_T = 45;


const int NONE_ST = 50;
const int PRINT_ST = 51;
const int ERRORCOMPDIR_ST = 52;

const int PROGRAM_T = 100;
const int FUNCTION_T = 101;
const int BEGIN_T = 102;
const int END_T = 103;
const int IF_T = 104;
const int THEN_T = 105;
const int ELSE_T = 106;
const int WHILE_T = 107;
const int DO_T = 108;
const int COUT_T = 109;
const int CIN_T = 110;
const int ENDL_T = 111;
const int OR_ST = 112;
const int AND_ST = 113;
const int DIV_ST = 114;
const int MOD_ST = 115;
const int INT_T = 116;
const int BOOLEAN_T = 117;
const int EQUAL_ST = 118;

const int LT = 200;
const int GT = 201;
const int EQ = 202;
const int ER = 202;

const int E_T = 203;





#endif