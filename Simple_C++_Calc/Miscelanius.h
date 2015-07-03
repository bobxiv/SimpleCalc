#pragma once

#include "Lexer.h"
#include "Parser.h"
using namespace Lexical_Analysis;
using namespace Syntathic_Analysis;

//This is so we can output the Tokens quickly
template<class _Elem, class _Tr>
std::basic_ostream<_Elem, _Tr>& operator<<(std::basic_ostream<_Elem, _Tr>& _Ostr, const Token& t)
	{
	switch(t.tag)
		{
		case TOKENTAG::ID:
			return _Ostr<<"ID ";
			break;
		case TOKENTAG::DIV:
			return _Ostr<<"DIV ";
			break;
		case TOKENTAG::MINUS:
			return _Ostr<<"MINUS ";
			break;
		case TOKENTAG::NUM:
			return _Ostr<<"NUM ";
			break;
		case TOKENTAG::PLUS:
			return _Ostr<<"PLUS ";
			break;
		case TOKENTAG::PROD:
			return _Ostr<<"PROD ";
			break;
		case TOKENTAG::POT:
			_Ostr<<"POT ";
			break;
		case TOKENTAG::RPAR:
			_Ostr<<"RPAR ";
			break;
		case TOKENTAG::LPAR:
			_Ostr<<"LPAR ";
			break;
		case TOKENTAG::FUN:
			_Ostr<<"FUN ";
			break;
		}
	}

//This is so we can output the pairs quickly
template<class _Elem, class _Tr>
std::basic_ostream<_Elem, _Tr>& operator<<(std::basic_ostream<_Elem, _Tr>& _Ostr, const std::pair<std::string,double>& t)
	{
	return _Ostr<<t.first<<'\t'<<'\t'<<t.second<<'\n';
	}

//This is so we can output the NonTerminals quickly
template<class _Elem, class _Tr>
std::basic_ostream<_Elem, _Tr>& operator<<(std::basic_ostream<_Elem, _Tr>& _Ostr, const NonTerminal& nont)
	{
	switch( nont.NTtag )
		{
		case NONTERMINALTAG::factor:
			return _Ostr<<"factor";
			break;
		case NONTERMINALTAG::term:
			return _Ostr<<"term";
			break;
		case NONTERMINALTAG::expr:
			return _Ostr<<"expr";
			break;
		}
	}

//This is so we can output the Production quickly
template<class _Elem, class _Tr>
std::basic_ostream<_Elem, _Tr>& operator<<(std::basic_ostream<_Elem, _Tr>& _Ostr, Production& prod)
	{
	prod.GoFirst();
	while( !prod.EndSimbol() )
		{
		if( dynamic_cast<Terminal*>(prod.GetCurrent()) )
			{
				switch( static_cast<Terminal*>(prod.GetCurrent())->Ttag )
					{
					case TOKENTAG::ID:
						_Ostr<<"ID ";
						break;
					case TOKENTAG::DIV:
						_Ostr<<"DIV ";
						break;
					case TOKENTAG::MINUS:
						_Ostr<<"MINUS ";
						break;
					case TOKENTAG::NUM:
						_Ostr<<"NUM ";
						break;
					case TOKENTAG::PLUS:
						_Ostr<<"PLUS ";
						break;
					case TOKENTAG::PROD:
						_Ostr<<"PROD ";
						break;
					case TOKENTAG::POT:
						_Ostr<<"POT ";
						break;
					case TOKENTAG::RPAR:
						_Ostr<<"RPAR ";
						break;
					case TOKENTAG::LPAR:
						_Ostr<<"LPAR ";
						break;
					case TOKENTAG::FUN:
						_Ostr<<"FUN ";
						break;
					}
			}else
			{
			switch( static_cast<NonTerminal*>(prod.GetCurrent())->NTtag )
				{
				case NONTERMINALTAG::factor:
					_Ostr<<"factor ";
					break;
					case NONTERMINALTAG::term:
					_Ostr<<"term ";
					break;
					case NONTERMINALTAG::expr:
					_Ostr<<"expr ";
					break;
				}
			}
		prod.NextSimbol();
		}
	return _Ostr;
	}


