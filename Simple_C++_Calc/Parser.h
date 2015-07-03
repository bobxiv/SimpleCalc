#pragma once

#include "GrammarException.h"
#include "Lexer.h"
#include <hash_map>
#include "Dash_Tree.h"
#include "Dash_BTree.h"


namespace Syntathic_Analysis
	{

		//The classes defined in Lexical_Analisys used here
	using Lexical_Analysis::TokenStream;
	using Lexical_Analysis::Token;
	using Lexical_Analysis::TOKENTAG;

		//The tags for the nonterminal
	enum NONTERMINALTAG{ factor = 1 , term = 2 , expr = 3 };
		//The tags for the terminals are equal to the TokenTags
	typedef TOKENTAG TERMINALTAG;

		//Base for Terminal and NonTerminal
	struct Simbol
		{
		private:
			virtual void Who(){return;}//just to justify the polimorphism
		};

		//Basicaly a stream of Terminals and NonTerminals
	class Production
		{
		private:
				//SimbolStream
			std::vector<Simbol*> SS;
				//Current position
			std::vector<Simbol*>::iterator pos;

		public:

			Production(std::vector<Simbol*>& myS): SS(myS), pos(SS.begin()){}
				//Go to the first simbol
			void GoFirst(){ pos=SS.begin();}
				//Give me the current Simbol
			Simbol* GetCurrent(){ return *pos; }
				//Advance to the next simbol
			void NextSimbol(){ ++pos; }
				//Are we at the end of the structure?
			bool EndSimbol(){ return (SS.end() == pos); }

			void operator=( const Production& B )
				{	
				this->SS = B.SS;
				this->pos = B.pos;
				return;
				}
		};

		//Terminal simbol, it is almost equal to Token but without pointer to SimbolTable
	struct Terminal: public Simbol
		{
		TERMINALTAG Ttag;
		Terminal(TERMINALTAG t): Ttag(t){}
		};

		//NonTerminal simbol
	struct NonTerminal: public Simbol
		{
		NONTERMINALTAG NTtag;
		NonTerminal(NONTERMINALTAG t): NTtag(t){}
		};

		//My precius tree, you just call it tree
	typedef Dash_Structures::DBTree<Token> Tree;
	typedef Dash_Structures::DBTree<Token>::iterator TreeIterator;
	
	class Parser
		{
		private:
				//TokenStream
			TokenStream& TS;
				//The last Token read
			Token lookahead;

				//This function throw an exception with information inside it
				//to show the user where the error was found in the expression
			void ThrowErrorWithHelp() throw( BadSintax );

				//It resolve some issues before the main call to expr
			void ParseHeuristics();

				//It should be called when TS.pos is over a FUN, 
				//and it return the pos of the ')' that ends the function
			TokenStream::position SeekFunctionEnd();
			
			void expr( Tree*, TreeIterator, TokenStream::position ) throw( BadSintax );

			void Term( Tree*, TreeIterator, TokenStream::position ) throw( BadSintax );

			void Fact( Tree*, TreeIterator, TokenStream::position ) throw( BadSintax );

			void Function( Tree*, TreeIterator, TokenStream::position ) throw( BadSintax );

		public:
			Parser( TokenStream& t): TS(t), lookahead(){}
			
				//Make the analisis and get the ParseTree
			Tree* Analize() throw( BadSintax );

		};



	}

using Syntathic_Analysis::Simbol;
using Syntathic_Analysis::Terminal;
using Syntathic_Analysis::NonTerminal;
using Syntathic_Analysis::NONTERMINALTAG;
using Syntathic_Analysis::Production;
	
//The All Great ProductionTable!!!
extern stdext::hash_map<int,std::pair<NonTerminal,Production>> ProductionTable;

void Initialize_ProductionTable();