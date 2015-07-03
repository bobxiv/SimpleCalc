#pragma once

#include "GrammarException.h"
#include <hash_map>
#include <vector>
#include <cctype>
#include <string>

//This is the declaration so I can make Parser friend of TokenStream, and touch directly pos
namespace Syntathic_Analysis
	{
	class Parser;
	}

//The SimbolTable that is used in all the translation process
extern stdext::hash_map<std::string,double, stdext::hash_compare<std::string, std::less<std::string> >>  SimbolTable;

namespace Lexical_Analysis
	{
	//My token tags:
	//~~ ~~~~~ ~~~~
	//
	//1) ID = (a..z|A..Z) [(a..z|A..Z|0..9)]*
	//2) NUM = [0..9)]*
	//3) PLUS = '+'
	//4) MINUS = '-'
	//5) PROD = '*'
	//6) DIV = '/'
	//7) POT = '^'
	//8) LPAR = '('
	//9) RPAR = ')'
	//10) FUN = [(a..z|A..Z)]* '('!		Aca FUN se crea solo si le sigue el '(', pero este no forma parte del token
enum TOKENTAG { ID = 256 , NUM = 257 , PLUS = 258 , MINUS = 259 , PROD = 260 , DIV = 261 , 
	POT = 262 , LPAR = 263 , RPAR = 264 , FUN = 265 };

//It have a tag and a pointer to the SimbolTable
struct Token
	{
	TOKENTAG tag;

	stdext::hash_map<std::string,double>::iterator data;

	Token(): tag(TOKENTAG::ID), data(SimbolTable.end()){}
	Token( TOKENTAG t, stdext::hash_map<std::string,double>::iterator it ):
		tag(t), data(it){} 
	};


class TokenStream
	{
	private:
			//TokenStream
		std::vector<Token> TS;
			//current position
		std::vector<Token>::iterator pos;
		typedef std::vector<Token>::iterator position;

	public:
		
			//This way the parser can access pos directly
		friend class Syntathic_Analysis::Parser;

		TokenStream(): TS(0), pos(TS.begin()) {}
		TokenStream(TokenStream& c): TS(c.TS), pos(c.pos) {}
			//Put Token in the Stream
		void PutToken( Token T){ TS.insert(TS.end(),T); }
			//Go to the first token
		void GoFirst(){ pos=TS.begin(); }
			//Give me the current token
		Token& GetCurrent(){ return *pos; }
			//Advance to the next token
		void NextToken(){ ++pos; }
			//Retroced to the previus token
		void PreviusToken(){ --pos; }
			//Are we in the end of the structure?
		bool EndToken(){ return (TS.end() == pos); }

	};

class Lexer
	{
	private:

			//Current input position read
		std::string::iterator peek;
			//Source of the data
		std::string& InputStream;

	public:

		Lexer(std::string& input): InputStream(input){ peek = InputStream.begin(); }
		
			//Make the analisis and get the TokenStream
		TokenStream* Analize() throw( UnExpextedSimbol );

	};

	}

