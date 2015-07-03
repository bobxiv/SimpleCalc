#include "stdafx.h"

#pragma once

#include <cmath>
#include "ResolveSyntaxTree.h"
#include "SimbolTable.h"
#include "FunctionTable.h"


double ResolveSyntaxTree( Tree* pSyntaxTree )
	{
	return ResolveSyntaxTree( pSyntaxTree, pSyntaxTree->begin() );
	}

double ResolveSyntaxTree( Tree* pSyntaxTree, TreeIterator TreeIt )
	{
		//If NULL return 0
	if( TreeIt == pSyntaxTree->end() )
		return 0;
		
		//If leaf then return value
	if( ((*TreeIt).tag == TOKENTAG::NUM) || ((*TreeIt).tag == TOKENTAG::ID) )
		return ((*TreeIt).data->second);

	TreeIterator Left = TreeIt.left_child();
	TreeIterator Right = TreeIt.right_child();

	#pragma region Unary Operators
	if( Right == pSyntaxTree->end() )
		{
		switch( (*TreeIt).tag )
			{
			case TERMINALTAG::PLUS:
				{
				double a = ResolveSyntaxTree( pSyntaxTree, Left );
				return a;
				break;
				}
			case TERMINALTAG::MINUS:
				{
				double a = ResolveSyntaxTree( pSyntaxTree, Left );
				return ((-1)*a);
				break;
				}
			case TERMINALTAG::FUN:
				{
				double a = ResolveSyntaxTree( pSyntaxTree, Left );
				std::string name = (*TreeIt).data->first;
				return FunctionTable(name,a);
				break;
				}
			}
		return 0;
		}
	#pragma endregion

	#pragma region Binary Operators
	switch( (*TreeIt).tag )
		{
		case TERMINALTAG::PLUS:
			{
			double a = ResolveSyntaxTree( pSyntaxTree, Left );
			double b = ResolveSyntaxTree( pSyntaxTree, Right );
			return (a + b);
			break;
			}
		case TERMINALTAG::MINUS:
			{
			double a = ResolveSyntaxTree( pSyntaxTree, Left );
			double b = ResolveSyntaxTree( pSyntaxTree, Right );
			return (a - b);
			break;
			}
		case TERMINALTAG::PROD:
			{
			double a = ResolveSyntaxTree( pSyntaxTree, Left );
			double b = ResolveSyntaxTree( pSyntaxTree, Right );
			return (a * b);
			break;
			}
		case TERMINALTAG::DIV:
			{
			double a = ResolveSyntaxTree( pSyntaxTree, Left );
			double b = ResolveSyntaxTree( pSyntaxTree, Right );
			if( b == 0 )
				throw ArithmeticError(std::string("Division by 0\nans = Inf\n"));
			return (a / b);
			break;
			}
		case TERMINALTAG::POT:
			{
			double a = ResolveSyntaxTree( pSyntaxTree, Left );
			double b = ResolveSyntaxTree( pSyntaxTree, Right );
			if( (a==0) && (b==0) )
				throw ArithmeticError(std::string("0^0 is an Indetermination\nans = NAN\n"));
			return std::pow(a,b);
			break;
			}
		}
	return 0;
	#pragma endregion
	}
