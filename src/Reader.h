#ifndef __READER_H__
#define __READER_H__

#include <string>
#include <deque>
#include <fstream>
#include <iostream>

enum TokenType{
	NUMBER, // int & float constants
	STRING,
	CHAR,
	BOOLEAN,
	OPERATOR,
	IDENTIFIER,
	EMPTY,
	ENDOF,
	ANY
};

struct Token{
	TokenType type;
	std::string content;
	Token() : type(EMPTY), content("") {}
	Token(TokenType _type, const std::string _content) : type(_type), content(_content) {}
};

std::ostream & operator<<(std::ostream & , Token );
class Charbuf{
	std::deque<char> q;
	std::ifstream fin;
	bool fill_buf(){
		bool ret = false;
		std::string buf;
		fail:;
		if(!std::getline(fin,buf).eof()){
			if(buf[0]=='#' || !buf.length()) goto fail;
			for(auto p : buf) q.push_back(p);
			ret = true;
		}
		return ret;
	}
public:
	Charbuf(){}
	Charbuf(const std::string fn) : fin(fn) {}
	~Charbuf(){fin.close();}
	Charbuf(const Charbuf &) = delete;
	Charbuf & operator=(const Charbuf &) = delete;
	void init(const std::string fn){
		fin.close();fin.open(fn);
	}
	void close(){fin.close();}
	int next_char(){
		if(!q.empty() || fill_buf()){
			char ret=q.front();
			q.pop_front();
			return ret;
		}
		else return EOF;
	}
	int glimpse(){
		if(!q.empty() || fill_buf()) return q.front();
		return EOF;
	}
};

class Reader{
private:
	Charbuf cr;
	std::string ret,fn,tpfn;
	int ch;
	void preprocess();
public:
	Reader(std::string );
	Reader(const Reader &) = delete;
	Reader & operator= (const Reader &) = delete;
	Token read_word();
	~Reader();
};

#endif
