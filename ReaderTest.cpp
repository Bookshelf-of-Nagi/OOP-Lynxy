#include "Reader.h"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string fn = "__Processor.cpp";
    Reader tokker(fn);
    Token res;
	while((res = tokker.read_word()).type!=ENDOF){
		if(res.type!=EMPTY) cout << res << endl;
	}
    return 0;
}
