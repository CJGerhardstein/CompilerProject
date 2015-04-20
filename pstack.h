
#ifndef _pstack
#define _pstack

#include "scanner.h"


class StackCell
{
public:
	int type;
	int subtype;

	StackCell *next;
	ItemCell *item;
};

class pStackClass
{
public:
	pStackClass();
	void push(tokenClass theToken);
	tokenClass pop();
	bool isTerminalOnTopOfStack();
	tokenClass topTerminalOnStack();
	tokenClass topOfStack();

	void dump();

private:
	StackCell *top;
};


#endif