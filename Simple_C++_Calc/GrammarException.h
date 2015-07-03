#pragma once

#include <exception>
#include <string>

//This is thrown if an unexpected character is found in the lexical analysis
class UnExpextedSimbol: public std::exception
	{
	public:
		const char* what()const
			{
			return "While doing the lexical analisys an unextected simbol was found\n";
			}
	};

//This is thrown if the sintax is erronius, ie no production can be made
//Also it could aditionaly have and show information where the error is
class BadSintax: public std::exception
	{
	private:
		std::string ErrorMsj;
			//It contains the number of ' ' before the '^' pointing the error
			//It should be shown under the input, so '^' could point the error
			//A value of -1 means: "No avaiable information about the location of the error"
		int dwOffset;
	public:
		BadSintax(): ErrorMsj("While parsing the sintax was found erronius\n"), dwOffset(-1){}
		BadSintax(std::string msj): ErrorMsj(msj), dwOffset(-1){}
		BadSintax(int offset): ErrorMsj("While parsing the sintax was found erronius\n"), dwOffset(offset){}
		BadSintax(std::string msj, int offset): ErrorMsj(msj), dwOffset(offset){}
		const char* what()
			{
			if( dwOffset != -1 )
				{
				char* zstrMark = new char[dwOffset+3];
				for( int i=0;i < dwOffset;++i )
					zstrMark[i] = ' ';
				zstrMark[dwOffset] = '^';
				zstrMark[dwOffset+1] = '\n';
				zstrMark[dwOffset+2] = '\0';
				std::string aux = ErrorMsj;
				ErrorMsj = std::string(zstrMark);
				ErrorMsj += aux;
				delete[] zstrMark;
				}
			return ErrorMsj.c_str();
			}
		~BadSintax(){}

	};

//This is thrown if an unexpected character is found in the lexical analysis
class ArithmeticError: public std::exception
	{
	private:
		std::string Msj;
	public:
		ArithmeticError(std::string msj): Msj(msj) {}
		const char* what()const
			{
			return Msj.c_str();
			}
	};

