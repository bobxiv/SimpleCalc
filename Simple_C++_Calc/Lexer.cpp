#include "stdafx.h"

#pragma once

#include "Lexer.h"

namespace Lexical_Analysis
	{

	TokenStream* Lexer::Analize() throw( UnExpextedSimbol )
	{
	TokenStream* pTS = new TokenStream();

	while( peek != InputStream.end() )
		{

		#pragma region NUM
			//the numbers
		if( isdigit(*peek) )
			{
			int tmp_val =0;
			do
				{
					tmp_val = tmp_val * 10 + (*peek - '0');
				}while( ++peek != InputStream.end() && isdigit(*peek) );
				
				char lexeme[255]; itoa(tmp_val,lexeme,10);//temporary buffer
				std::pair<stdext::hash_map<std::string,double>::iterator,bool> simbolpos = 
					SimbolTable.insert(std::pair<std::string,double>(lexeme,tmp_val));
				pTS->PutToken( Token(TOKENTAG::NUM,simbolpos.first) );
			}

		if( peek == InputStream.end() ) break;
		#pragma endregion This part computes the numbers and get the NUM token 

		#pragma region ID and FUN 
		std::string tmp_id_or_fun;
			//the fun
		if( isalpha(*peek) )
			{
				do
				{	
					tmp_id_or_fun.insert(tmp_id_or_fun.end(),*peek);

				}while( ++peek != InputStream.end() && isalpha(*peek) );
				
				if( peek != InputStream.end() && *peek == '(' )//it is really a fun?
					{
					stdext::hash_map<std::string,double>::iterator simbolpos = SimbolTable.find( tmp_id_or_fun );
					if( simbolpos == SimbolTable.end() )
						{
						std::pair<stdext::hash_map<std::string,double>::iterator,bool> insertpos;
						insertpos = SimbolTable.insert(std::pair<std::string,double>(tmp_id_or_fun,0));
						simbolpos = insertpos.first;
						}

					//if it was already there then we don't touch the simboltable
					pTS->PutToken( Token(TOKENTAG::FUN,simbolpos) );
					//the '(' is nesesary for FUN, but not part of the expression
					continue;
					}

				//the ids
			if( peek != InputStream.end() && isdigit(*peek) )
				{
					do
					{	
						tmp_id_or_fun.insert(tmp_id_or_fun.end(),*peek);

					}while( ++peek != InputStream.end() && isdigit(*peek) );
				}

				stdext::hash_map<std::string,double>::iterator simbolpos = SimbolTable.find( tmp_id_or_fun );
				if( simbolpos == SimbolTable.end() )//then it was't in the simboltable let's add it
					{
					std::pair<stdext::hash_map<std::string,double>::iterator,bool> insertpos;
					insertpos = SimbolTable.insert(std::pair<std::string,double>(tmp_id_or_fun,0));
					simbolpos = insertpos.first;
					}
				
				//if it was already there then we don't touch the simboltable
				pTS->PutToken( Token(TOKENTAG::ID,simbolpos) );
					
			}
					
			//It could be that the ids and numbers get analysed and then it ends, so i need to 
			//take care of this posibility
		if( peek == InputStream.end() ) break;
		#pragma endregion This part computes the ids and funs and get the ID or FUN token

		#pragma region OPERATORS
			//the operators
		if(*peek == '+') {pTS->PutToken( Token(TOKENTAG::PLUS, SimbolTable.end()) ); ++peek; continue; }
		if(*peek == '-') {pTS->PutToken( Token(TOKENTAG::MINUS, SimbolTable.end()) ); ++peek; continue; }		
		if(*peek == '*') {pTS->PutToken( Token(TOKENTAG::PROD, SimbolTable.end()) ); ++peek; continue; }
		if(*peek == '/') {pTS->PutToken( Token(TOKENTAG::DIV, SimbolTable.end()) ); ++peek; continue; }
		if(*peek == '^') {pTS->PutToken( Token(TOKENTAG::POT, SimbolTable.end()) ); ++peek; continue; }
		if(*peek == '(') {pTS->PutToken( Token(TOKENTAG::LPAR, SimbolTable.end()) ); ++peek; continue; }
		if(*peek == ')') {pTS->PutToken( Token(TOKENTAG::RPAR, SimbolTable.end()) ); ++peek; continue; }
		#pragma endregion This part computes the arithmetics operators and get the corresponding token

		#pragma region WITHESPACE AND LF
			//the spaces and end of line
		if(*peek == ' ') {++peek; continue; }
		if(*peek == '\n') {++peek; continue; }
		#pragma endregion This part filter the unimportant characters

			//If it does't recognize a token then the InputStream had an error
		throw UnExpextedSimbol();

		}

	return pTS;
	}

	}