#include "stdafx.h"
#include "SimbolTable.h"

stdext::hash_map<std::string,double, stdext::hash_compare<std::string, std::less<std::string> >> SimbolTable;

void Initializing_SimbolTable()
	{
	SimbolTable.insert(std::pair<std::string,double>("pi",3.14));
	SimbolTable.insert(std::pair<std::string,double>("e",2.73));
	SimbolTable.insert(std::pair<std::string,double>("true",1));
	SimbolTable.insert(std::pair<std::string,double>("false",0));

	//the functions are resolve using the function FuncitonTable
	//and add to the SimbolTable in runtime, but only compute 
	//if they exist in the Functiontable
		
	return;
	}