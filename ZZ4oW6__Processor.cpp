# 1 "v7Fcwn__Processor.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "v7Fcwn__Processor.cpp"

using namespace std;


const char legal_charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

string fn,tpfn;
fstream tempfile;

unsigned int Rand(){
 static bool flag = false;
 if(!flag) srand(time(0)),flag=true;
 return rand();
}
string randString(int len = 6){
 string ret;
 for(int i=0;i<len;i++) ret.append(1,legal_charset[Rand()%62]);
 return ret;
}

void preprocess(){
 ifstream fin(fn);
 string ttpfn=randString()+fn;
 cerr << ttpfn << endl;
 tempfile.open(ttpfn,ios_base::out | ios_base::trunc);

 static char line[300];
 regex f_include("^\\s*#\\s*include.*[\n\r]*");
 while(fin.getline(line,256)){
  cerr << strlen(line) << ":" << line << endl;
  if(!regex_match(line,f_include))
   tempfile << line << endl;
 }

 tempfile.close();
 tpfn = randString()+fn;
 system(("g++ -E "+ttpfn+" -o "+tpfn).c_str());
 remove(ttpfn.c_str());
}

class Charbuf{
 deque<char> q;
 ifstream fin;
 bool fill_buf(){
  bool ret = false;
  string buf;
  fail:;
  if(!getline(fin,buf).eof()){
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

enum TokenType{
 NUMBER,
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
static const char *TokenTypeMapper[] = {
 "NUMBER","STRING","CHAR","BOOLEAN","OPERATOR","IDENTIFIER","EMPTY","ENDOF","ANY"
};
inline friend ostream & operator<<(ostream & out, Token tt){
 return out << "(" << TokenTypeMapper[tt.type] << "," << tt.content << ")";
}
class Tokenizer{
 Charbuf cr;
 string ret,_fn;
 int ch;






public:
 Tokenizer(const std::string fn) : cr(fn), ret(""), _fn(fn), ch(0) {}
 Token next_token(){
  ch=cr.next_char();
  cerr << ch << endl;
  if(ch==EOF) return Token(ENDOF,"");
  else if(ch=='\''){
   ret="";
   while(1){
    ret+=ch;
    if(cr.glimpse()=='\'' && ch!='\\'){
     ret+='\'';cr.next_char();
     return Token(CHAR,ret);
    }
    ch=cr.next_char();
   }
  }
  else if(ch=='\"'){
   ret="";
   while(1){
    ret+=ch;
    if(cr.glimpse()=='\"' && ch!='\\'){
     ret+='\"';cr.next_char();
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
 ~Tokenizer(){
  cr.close();
  remove(_fn.c_str());
 }
};
int main()
{
 fn = "sherlockDetect.cpp";
 preprocess();
 Token res;
 Tokenizer tokker(tpfn);
 while((res = tokker.next_token()).type!=ENDOF){
  if(res.type!=EMPTY) cout << res << endl;
 }
 return 0;
}
