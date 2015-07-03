#include "stdafx.h"

#pragma once
#include "parser.h"

#include <iostream>

//the definition of the ProductionTable
stdext::hash_map<int,std::pair<NonTerminal,Production>> ProductionTable;

using Lexical_Analysis::TOKENTAG;

void Initialize_ProductionTable()
	{
	// -------------------------------- factor -> NUM

		//The production of the head
	std::vector<Simbol*> tmpSimbolVector;//Be Aware that it is a pointer vector, so I dont have to delete any pointers!

		//The members of the production body
	Terminal* ptmpTerminal = new Terminal(TOKENTAG::NUM);
	tmpSimbolVector.push_back( ptmpTerminal );
		
		//forming the production
	Production tmpProd(tmpSimbolVector);

		//forming the nonterminal
	NonTerminal tmpNonTerm(NONTERMINALTAG::factor);

		//inserting the NonTerminal - Production
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(),std::pair<NonTerminal,Production> (tmpNonTerm,tmpProd))
		);

	tmpSimbolVector.clear();

		// -------------------------------- factor -> + NUM

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::PLUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::NUM);
	tmpSimbolVector.push_back( ptmpTerminal );
		
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the NonTerminal - Production
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(),std::pair<NonTerminal,Production> (tmpNonTerm,tmpProd))
		);

	tmpSimbolVector.clear();

			// -------------------------------- factor -> '(' expr ')'

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::LPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	NonTerminal* ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::RPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
		
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the NonTerminal - Production
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(),std::pair<NonTerminal,Production> (tmpNonTerm,tmpProd))
		);

	tmpSimbolVector.clear();

				// -------------------------------- factor -> + '(' expr ')'

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::PLUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::LPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::RPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
		
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the NonTerminal - Production
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(),std::pair<NonTerminal,Production> (tmpNonTerm,tmpProd))
		);

	tmpSimbolVector.clear();

			// -------------------------------- factor -> - '(' expr ')'

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::MINUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::LPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::RPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
		
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the NonTerminal - Production
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(),std::pair<NonTerminal,Production> (tmpNonTerm,tmpProd))
		);

	tmpSimbolVector.clear();

			// -------------------------------- factor -> - NUM

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::MINUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::NUM);
	tmpSimbolVector.push_back( ptmpTerminal );
		
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the NonTerminal - Production
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(),std::pair<NonTerminal,Production> (tmpNonTerm,tmpProd))
		);

	tmpSimbolVector.clear();

		// -------------------------------- factor -> + NUM ^ factor

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::PLUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::NUM);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::POT);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

	// -------------------------------- factor -> - NUM ^ factor

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::MINUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::NUM);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::POT);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

		// -------------------------------- factor -> NUM ^ factor

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::NUM);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::POT);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

		// -------------------------------- factor -> - '(' expr ')' ^ factor

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::MINUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::LPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::RPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::POT);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

			// -------------------------------- factor -> + '(' expr ')' ^ factor

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::PLUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::LPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::RPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::POT);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

			// -------------------------------- factor -> '(' expr ')' ^ factor

		//The members of the production body
	ptmpTerminal = new Terminal(TOKENTAG::LPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::RPAR);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::POT);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::factor);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

		// -------------------------------- term -> factor

		//The members of the production body
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::term);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

		tmpSimbolVector.clear();

		// -------------------------------- term -> factor * term

	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::PROD);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::term);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::term);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

		// -------------------------------- term -> factor / term

	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::factor);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::DIV);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::term);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::term);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

			// -------------------------------- expr -> term

	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::term);
	tmpSimbolVector.push_back( ptmpNonTerminal );
		
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::expr);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

			// -------------------------------- expr -> term + expr

	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::term);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::PLUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::expr);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

			// -------------------------------- expr -> term - expr

	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::term);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	ptmpTerminal = new Terminal(TOKENTAG::MINUS);
	tmpSimbolVector.push_back( ptmpTerminal );
	ptmpNonTerminal = new NonTerminal(NONTERMINALTAG::expr);
	tmpSimbolVector.push_back( ptmpNonTerminal );
	
		//forming the production
	tmpProd = Production(tmpSimbolVector);

		//forming the nonterminal
	tmpNonTerm = NonTerminal(NONTERMINALTAG::expr);

		//inserting the nonterminal
	ProductionTable.insert(
		std::pair<int,std::pair<NonTerminal,Production>>
		(ProductionTable.size(), std::pair<NonTerminal,Production>(tmpNonTerm,tmpProd)));

	tmpSimbolVector.clear();

	return;
	}


namespace Syntathic_Analysis
	{

	//Implementation notes:
	//~~~~~~~~~~~~~~ ~~~~~
	//
	//1) The syntax notations is made in BN notation with some few modifications, and also apart a production syntax
	//
	//2) Some syntax fixes and possibilities are not contempled by the production, but are taken care before
	//the the main call to expr, they are in the function ParseHeuristics
	//
	//3) The parse tree is made stricly following the production, with 1 exception the ^ problem with 
	//right associativity(it is explained next
	//
	//4) All the sintax is right associative, with the ^ that have to be left associative (2^3^4 is (2^3)^4 not 2^(3^4))
	//it is fixed, keeping the right associativity but making 2^(3*4) insted of (2^3)^4
		
	Tree* Parser::Analize() throw( BadSintax )
		{
		Tree* pSyntaxTree = new Tree();

		//It dosn't figure in the grammatics but an empty input will 
		//get an empty tree, this is a rule to apply before the parser
		if( TS.EndToken() )
			return pSyntaxTree;

		ParseHeuristics();

		//The Main NonTerminal
		expr(pSyntaxTree,pSyntaxTree->begin(),TS.TS.end());

		return pSyntaxTree;
		}

		inline void Parser::ParseHeuristics()
			{
			#pragma region If it start with operator (distinct from + and -) BadSintax
			if( (TS.GetCurrent().tag == TOKENTAG::PROD) || (TS.GetCurrent().tag == TOKENTAG::DIV) || 
				(TS.GetCurrent().tag == TOKENTAG::POT) )
				throw BadSintax("Check where you put the operators");
			#pragma endregion

			#pragma region If it end with operator BadSintax
			TS.pos = TS.TS.end();
			TS.PreviusToken();
			if( (TS.GetCurrent().tag == TOKENTAG::PLUS) || (TS.GetCurrent().tag == TOKENTAG::MINUS) ||
				(TS.GetCurrent().tag == TOKENTAG::PROD) || (TS.GetCurrent().tag == TOKENTAG::DIV) || 
				(TS.GetCurrent().tag == TOKENTAG::POT) )
				throw BadSintax("Check where you put the operators");
			TS.GoFirst();
			#pragma endregion

			#pragma region If there are parenthesis open but not close or vice versa BadSintax
			int lparCount=0;
			int rparCount=0;
			while( !TS.EndToken() )
				{
				if( TS.GetCurrent().tag == TOKENTAG::LPAR )
					++lparCount;
				if( TS.GetCurrent().tag == TOKENTAG::RPAR )
					++rparCount;
				TS.NextToken();
				}
			if( lparCount > rparCount)
				{
				#pragma region Make the error information and Launch
				int cant = lparCount-rparCount;
				char* zstrcant = new char[256];
				itoa(cant,zstrcant,10);
				char zstrtmp[256] = "You forgot close ";
				strcat(zstrtmp,zstrcant);
				delete[] zstrcant;
				char zstrpost[] = " left parenthesis\n";
				strcat(zstrtmp,zstrpost);
				throw BadSintax(zstrtmp);
				#pragma endregion
				}
			if( lparCount < rparCount)
				{
				#pragma region Make the error information and Launch
				int cant = rparCount-lparCount;
				char* zstrcant = new char[256];
				itoa(cant,zstrcant,10);
				char zstrtmp[256] = "You forgot close ";
				strcat(zstrtmp,zstrcant);
				delete[] zstrcant;
				char zstrpost[] = " right parenthesis\n";
				strcat(zstrtmp,zstrpost);
				throw BadSintax(zstrtmp);
				#pragma endregion
				}
			TS.GoFirst();
			#pragma endregion

			#pragma region 1++2 or 1--2 dosn´t make much sense so it is considered an syntax error
			while( !TS.EndToken() )
				{
				if( ((TS.GetCurrent().tag == TOKENTAG::PLUS) || (TS.GetCurrent().tag == TOKENTAG::MINUS)) && 
					(TS.pos != TS.TS.begin()) )
					{
					if( (*(TS.pos)).tag == (*(TS.pos-1)).tag )
						ThrowErrorWithHelp();
					}
				TS.NextToken();
				}
			TS.GoFirst();
			#pragma endregion

			#pragma region If NUM adjacent to ID
			TS.NextToken();
			while( !TS.EndToken() )
				{
				if( ((*(TS.pos-1)).tag == TOKENTAG::NUM) && (TS.GetCurrent().tag == TOKENTAG::ID) )
					ThrowErrorWithHelp();
				TS.NextToken();
				}
			TS.GoFirst();
			#pragma endregion
			}

	//
	//	function -> FUN '(' expr ')'	ó expresado distinto
	//												   function -> FUN
	//
	void Parser::Function( Tree* pSyntaxTree, TreeIterator it, TokenStream::position End ) throw( BadSintax )
		{
		it = pSyntaxTree->insert(it,TS.GetCurrent());

		TS.pos = TS.pos+2;
		expr(pSyntaxTree,it.left_child(),End);

		return;
		}

	TokenStream::position Parser::SeekFunctionEnd()
		{
		TokenStream::position funbeg = TS.pos;
		TS.NextToken();//advance to '('
		int lparcount = 1;
		int rparcount = 0;
		do
			{
			TS.NextToken();
			if( TS.GetCurrent().tag == TOKENTAG::LPAR )
				++lparcount;
			if( TS.GetCurrent().tag == TOKENTAG::RPAR )
				++rparcount;
			}while( (lparcount - rparcount) != 0 );
		TokenStream::position funend = TS.pos;
		TS.pos = funbeg;
		return funend;
		}

	//
	//	fact -> (+|-)? (NUM|ID|( '(' expr ')' )) [^ (+|-)? (NUM|( '(' expr ')' ))]*	
	//
	//													ó expresado distinto
	//
	//													fact -> NUM ^ fact
	//													fact -> ID ^ fact
	//													fact -> '(' expr ')' ^ fact
	//													fact -> (+|-) NUM ^ fact
	//													fact -> (+|-) ID ^ fact
	//													fact -> (+|-) '(' expr ')' ^ fact
	//													fact -> NUM
	//													fact -> ID
	//													fact -> '(' expr ')'
	//													fact -> (+|-) NUM
	//													fact -> (+|-) ID
	//													fact -> (+|-) '(' expr ')'
	//
	void Parser::Fact( Tree* pSyntaxTree, TreeIterator it, TokenStream::position End ) throw( BadSintax )
		{
		bool morethanfirst = 0;//see in fact -> (*|-)? (NUM|ID|'(' expr ')') ^ fact
							   //then all'll be clear
		while( true )
			{
			TokenStream::position beg = TS.pos;//keeps the last factor begining
											   //in case of factor -> (+|-)? NUM ^ factor, it is used to loop
			#pragma region Find next ^ until a +|- binary or *|/, over this level of (
				{
				int parCount = 0;//Counts '(' and ')', so we process only this level of parenthesis
				while( TS.pos != End )
					{
					if( TS.GetCurrent().tag == TOKENTAG::LPAR )
						++parCount;
					if( !parCount )
						{
						if( (TS.GetCurrent().tag == TOKENTAG::POT) )
							break;
						}
					if( TS.GetCurrent().tag == TOKENTAG::RPAR )
						--parCount;
					TS.NextToken();
					}
				}
			#pragma endregion

			#pragma region Check & Resolve factor -> (+|-)? (NUM|ID|'(' expr ')')
			//factor -> (+|-)? (NUM|'(' expr ')'|function)
			if( TS.pos == End )
				{
				TS.pos = beg;
				//factor -> (+|-) (NUM|'(' expr ')'|function)
				if( (TS.GetCurrent().tag == TOKENTAG::PLUS) || (TS.GetCurrent().tag == TOKENTAG::MINUS) )
					{
					it = pSyntaxTree->insert(it,TS.GetCurrent());
					TS.NextToken();
				if( (TS.GetCurrent().tag != TOKENTAG::NUM) && (TS.GetCurrent().tag != TOKENTAG::LPAR) &&
					(TS.GetCurrent().tag != TOKENTAG::ID) && (TS.GetCurrent().tag != TOKENTAG::FUN) )
					ThrowErrorWithHelp();
				if( (TS.GetCurrent().tag == TOKENTAG::NUM) || (TS.GetCurrent().tag == TOKENTAG::ID) )//factor -> (+|-) (NUM|ID)
					{
					pSyntaxTree->insert(it.left_child(),TS.GetCurrent());
					TS.NextToken();
					return;
					}else if( TS.GetCurrent().tag == TOKENTAG::FUN )//factor -> (+|-) function
					{	
						Function(pSyntaxTree,it,SeekFunctionEnd());
						return;
						}else										//factor -> (+|-) '(' expr ')'
						{
							TS.NextToken();
							//send's only expr!!!, not '(' expr ')'
							expr(pSyntaxTree,it,--End);
							TS.NextToken();
							return;
							}
					}
				// factor -> (NUM|ID|'(' expr ')'|function)
				if( (TS.GetCurrent().tag != TOKENTAG::NUM) && (TS.GetCurrent().tag != TOKENTAG::LPAR) &&
					(TS.GetCurrent().tag != TOKENTAG::ID) && (TS.GetCurrent().tag != TOKENTAG::FUN) )
					ThrowErrorWithHelp();
				if( (TS.GetCurrent().tag == TOKENTAG::NUM) || (TS.GetCurrent().tag == TOKENTAG::ID) )//factor -> (NUM|ID)
					{
					pSyntaxTree->insert(it,TS.GetCurrent());
					TS.NextToken();
					return;
					}else if( TS.GetCurrent().tag == TOKENTAG::FUN )//factor -> function
						{	
						Function(pSyntaxTree,it,SeekFunctionEnd());
						return;							  
						}else										//factor -> '(' expr ')'
						{
							TS.NextToken();
							//send's only expr!!!, not '(' expr ')'
							expr(pSyntaxTree,it,--End);
							TS.NextToken();
							return;
							}
				}
			#pragma endregion

			#pragma region Check & Resolve factor -> (+|-)? (NUM|ID|'('expr')'|function) ^ factor
			// factor -> (+|-)? (NUM|ID|'(' expr ')'|function) ^ factor
			if( morethanfirst )// 2^3^4 it is not 2^(3^4) !!!! it is (a) 2^(3*4) or (b) (2^3)^4, we resolve it like (a)
				it = pSyntaxTree->insert(it,Token(TOKENTAG::PROD,SimbolTable.end()));
			else
				it = pSyntaxTree->insert(it,TS.GetCurrent());
			TokenStream::position end = TS.pos;
			TS.pos = beg;
			//factor -> (+|-) (NUM|ID|'(' expr ')'|function) ^ fact
			if( (TS.GetCurrent().tag == TOKENTAG::PLUS) || (TS.GetCurrent().tag == TOKENTAG::MINUS) )
				{
				TreeIterator tmpit = it;
				it = pSyntaxTree->insert(it.left_child(),TS.GetCurrent());
				TS.NextToken();
				if( (TS.GetCurrent().tag != TOKENTAG::NUM) && (TS.GetCurrent().tag != TOKENTAG::LPAR) &&
					(TS.GetCurrent().tag != TOKENTAG::ID) && (TS.GetCurrent().tag != TOKENTAG::FUN) )
					ThrowErrorWithHelp();
				if( (TS.GetCurrent().tag == TOKENTAG::NUM) || (TS.GetCurrent().tag == TOKENTAG::ID) )//factor -> (+|-) (NUM|ID) ^ factor
					{
					pSyntaxTree->insert(it.left_child(),TS.GetCurrent());
					it = tmpit.right_child();
					}else if( TS.GetCurrent().tag == TOKENTAG::FUN )//factor -> (+|-) function ^ factor
						{	
						Function(pSyntaxTree,it,SeekFunctionEnd());
						it = tmpit.right_child();
						}else										//factor -> (+|-) '(' expr ')' ^ factor
						{
							TS.NextToken();
							//send's only expr!!!, not '(' expr ')'
							expr(pSyntaxTree,it.left_child(),--end);
							it = tmpit.right_child();
							}
				}else
				{
				//factor -> (NUM|ID|'(' expr ')') ^ fact
				if( (TS.GetCurrent().tag != TOKENTAG::NUM) && (TS.GetCurrent().tag != TOKENTAG::LPAR) &&
					(TS.GetCurrent().tag != TOKENTAG::ID) && (TS.GetCurrent().tag != TOKENTAG::FUN) )
					ThrowErrorWithHelp();
				if( (TS.GetCurrent().tag == TOKENTAG::NUM) || (TS.GetCurrent().tag == TOKENTAG::ID) )//factor -> (NUM|ID) ^ fact
					{
					pSyntaxTree->insert(it.left_child(),TS.GetCurrent());
					it = it.right_child();
					}else if( TS.GetCurrent().tag == TOKENTAG::FUN )//factor -> function ^ factor
						{	
						Function(pSyntaxTree,it,SeekFunctionEnd());
						it = it.right_child();
						}else										//factor -> '(' expr ')' ^ fact
						{
						TS.NextToken();
						//send's only expr!!!, not '(' expr ')'
						expr(pSyntaxTree,it.left_child(),--end);
						it = it.right_child();
							}
					}
				TS.NextToken();//here we are at the ^
				TS.NextToken();
				morethanfirst = 1;
			#pragma endregion
			}
		return;
		}

	//
	//	term -> factor [ (*|/) factor ]*	ó expresado distinto	term -> factor (*|/) term
	//																term -> factor
	//
	void Parser::Term( Tree* pSyntaxTree, TreeIterator it, TokenStream::position End ) throw( BadSintax )
		{
					 //BN grammar operator *
		while( true )// if it was a term -> factor (*|/) term		then loops
			{
			TokenStream::position beg = TS.pos;//keeps the last factor begining
											   //in case of term -> factor (*|/) term, it is used to loop
			#pragma region Find next *|/ until a +|- binary, over this level of (
				{
				int parCount = 0;//Counts '(' and ')', so we process only this level of parenthesis
				while( TS.pos != End )
					{
					if( TS.GetCurrent().tag == TOKENTAG::LPAR )
						++parCount;
					if( !parCount )
						{
						if( (TS.GetCurrent().tag == TOKENTAG::PROD) || 
							(TS.GetCurrent().tag == TOKENTAG::DIV) )
							break;
						}
					if( TS.GetCurrent().tag == TOKENTAG::RPAR )
						--parCount;
					TS.NextToken();
					}
				}
			#pragma endregion
				
			#pragma region Check & Resolve	term -> factor		production
			if( TS.pos == End ) // term -> factor
				{
				TS.pos = beg;
				Fact(pSyntaxTree,it,End);
				return;
				}
			#pragma endregion

			#pragma region Check & Resolve	term -> factor (*|/) term		production
			// term -> factor (*|/) term
			it = pSyntaxTree->insert(it,TS.GetCurrent());
			TokenStream::position end = TS.pos;
			TS.pos = beg;
			Fact(pSyntaxTree,it.left_child(),end);
			TS.NextToken();//I quit Fact in end(operator *|/)
			it= it.right_child();
			#pragma endregion
			}
		return;
		}

	//
	//	expr -> term [ (+|-) term ]*	ó expresado distinto	expr -> term (+|-) expr
	//															expr -> term
	//
	void Parser::expr( Tree* pSyntaxTree, TreeIterator it, TokenStream::position End) throw( BadSintax )
		{
					 //BN grammar operator *
		while( true )//if it was a expr -> term (+|-) expr		then loops
			{
			TokenStream::position beg = TS.pos;//keeps the last term begining
											   //in case of expr -> term (+|-) expr, it's used to loop
			#pragma region Find next +|- binary, over this level of (
			{
				int parCount = 0;//Counts '(' and ')', so we process only this level of parenthesis
				while( TS.pos != End )
					{
					if( TS.GetCurrent().tag == TOKENTAG::LPAR )
						++parCount;
					if( !parCount )//only if parCount == 0
						{
						if( ((TS.GetCurrent().tag == TOKENTAG::PLUS) || 
							(TS.GetCurrent().tag == TOKENTAG::MINUS)) && (TS.pos != beg) )
							{
							TS.PreviusToken();
							if( (TS.GetCurrent().tag == TOKENTAG::NUM) || (TS.GetCurrent().tag == TOKENTAG::ID)  )//if the sign isn't in a fact or term, then binary
								{
								TS.NextToken();
								break;
								}else
								{
								TS.NextToken();
									}
							}
						}
					if( TS.GetCurrent().tag == TOKENTAG::RPAR )
						--parCount;
					TS.NextToken();
					}
				}
			#pragma endregion

			#pragma region Check & Resolve expr -> term		production
			if( TS.pos == End )// expr -> term
				{
				TS.pos = beg;
				Term(pSyntaxTree,it,End);
				return;
				}
			#pragma endregion

			#pragma region Check & Resolve expr -> term (+|-) expr	production
			// expr -> term (+|-) expr
			it = pSyntaxTree->insert(it,TS.GetCurrent());
			TokenStream::position end = TS.pos;
			TS.pos = beg;
			Term(pSyntaxTree,it.left_child(),end);
			TS.NextToken();//I quit Term in end(operator +|-)
			it= it.right_child();
			#pragma endregion
			}
		return;
		}

	void Parser::ThrowErrorWithHelp()
		{
		TokenStream::position tmppos = TS.pos;
		TS.GoFirst();
		int offset=0;
		while( TS.pos != tmppos )
			{
			switch( TS.GetCurrent().tag )
				{
				case TOKENTAG::NUM:
					{
					char* zstrNum = new char[256];
					itoa( TS.GetCurrent().data->second, zstrNum, 10);
					offset += strlen(zstrNum);
					delete[] zstrNum;
					break;
					}
				case TOKENTAG::ID:
					{
					offset += (TS.GetCurrent().data->first).length();
					break;
					}
				default:
					{
					++offset;
					break;
					}
				}
			TS.NextToken();
			}
		throw BadSintax(offset);
		return;
		}

	}