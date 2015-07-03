#pragma once

#include <hash_map>
#include <string>

//The All Migthy SimbolTable!!!
extern stdext::hash_map<std::string,double, stdext::hash_compare<std::string, std::less<std::string> >> SimbolTable;
typedef stdext::hash_map<std::string,double, stdext::hash_compare<std::string, std::less<std::string> >>::iterator
															SimbolIterator;

void Initializing_SimbolTable();
