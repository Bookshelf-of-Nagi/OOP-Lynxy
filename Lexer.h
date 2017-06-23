#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include 
enum TokenType{
	NUMBER, // int & float constants
	BOOLEAN, // true & false constants
	STRING, // string constants
	OPERATOR, 
	IDENTIFIER,
	KEYWORD
};
struct Token{
	TokenType type;
	std::string content;
};

class Lexer{
};

#endif
