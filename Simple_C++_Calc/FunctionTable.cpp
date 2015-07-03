#include "stdafx.h"
#pragma once

#include "FunctionTable.h"
#include "GrammarException.h"

double FunctionTable(std::string name,double val)
	{
	if( name == "log" )
		return log10(val);
	if( name == "ln" )
		return log(val);
	if( name == "abs" )
		return abs(val);
	if( name == "sqrt" )
		return sqrt(val);
	if( name == "sin" )
		return sin(val);
	if( name == "cos" )
		return cos(val);
	if( name == "tan" )
		return tan(val);
	if( name == "sinh" )
		return sinh(val);
	if( name == "cosh" )
		return cosh(val);
	if( name == "tanh" )
		return tanh(val);

	throw ArithmeticError(std::string(std::string("Unknown function ")+ name+"\n"));
	
	return 0;
	}