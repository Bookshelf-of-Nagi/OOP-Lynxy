#include "Reader.h"
#include "funcs.hpp"
#include <bits/stdc++.h>

using namespace std;

const char *TokenTypeMapper[] = {
	"NUMBER","STRING","CHAR","BOOLEAN","OPERATOR","IDENTIFIER","EMPTY","ENDOF","ANY"
};
std::ostream & operator<<(std::ostream & out, Token tt){
	return out << "(" << TokenTypeMapper[tt.type] << "," << tt.content <<  ")";
}

void Reader :: preprocess(){
    ifstream fin(fn);
    fstream tempfile;
	string ttpfn=fn+randString()+".cpp";
	//cerr << ttpfn << endl;
	tempfile.open(ttpfn,ios_base::out | ios_base::trunc);

	string line;
	regex f_include("^\\s*#\\s*include.*[\n\r]*");
	while(1){
		getline(fin,line);
		if(!regex_match(line,f_include))
			tempfile << line << endl;
		if(fin.eof()) break;
	}

	tempfile.close();
	tpfn = fn+randString()+".cpp";
	system(("g++ -E "+ttpfn+" -o "+tpfn).c_str());
//	remove(ttpfn.c_str());
}

Token Reader :: read_word(){
    ch=cr.next_char();
    //cerr << ch << endl;
    if(ch==EOF) return Token(ENDOF,"");
    else if(ch=='\''){
        ret="";
        while(1){
            ret+=ch;
            if(ch=='\\'){
                ret+=cr.next_char();
            }
            if(cr.glimpse()=='\''){
                ret+=cr.next_char();
                return Token(CHAR,ret);
            }
            ch=cr.next_char();
        }
    }
    else if(ch=='\"'){
        ret="";
        while(1){
            ret+=ch;
            if(ch=='\\'){
                ret+=cr.next_char();
            }
            if(cr.glimpse()=='\"'){
                ret+=cr.next_char();
                return Token(STRING,ret);
            }
            ch=cr.next_char();
        }
    }
    else{
        ret=ch;
        return Token(ANY,ret);
    }
}

Reader :: Reader(std::string _fn) : ret(""), fn(_fn), ch(0){
    preprocess();
    cr.init(tpfn);
}

Reader :: ~Reader(){
    cr.close();
    remove(tpfn.c_str());
}