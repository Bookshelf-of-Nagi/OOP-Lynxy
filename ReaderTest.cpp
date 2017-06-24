#include "Reader.h"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string fn = "data/01/49_38a.cpp";
    Reader tokker(fn);
    Token res;
	while((res = tokker.read_word()).type!=ENDOF){
		if(res.type!=EMPTY) cout << res << endl;
	}
    return 0;
}
