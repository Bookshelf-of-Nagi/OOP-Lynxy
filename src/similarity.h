#ifndef SHERLOCKDETECT_H
#define SHERLOCKDETECT_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Detect.h"
#include "Reader.h"
#include "HashFactory.h"
//stored the info of a file.
struct Sig
{
	int				Ntokenval;
	unsigned long	*value;
};
/*********************************************************
	This class can tell us the similarity of two file.
**********************************************************/
class similarity : public Detect
{
    char*			Progname;
    int	    		Ntoken;
    int	       		Zerobits;
    unsigned long	zeromask;
    int		   		ntoken;
    char**			token;
	int*    		typetoken;
    int		    	Thresh;

	HashFactory		Hash;
public:
	//set some value
    void set_Progname(char* _prog = (char*)"sherlock") {Progname = _prog;}
    void set_Zerobits(int num = 4) {Zerobits = num;}
    void set_ntoken(int num = 0) {ntoken = num;}
    void set_Thresh(int num = 20) {Thresh = num;}
	void set_Ntoken(int _Ntoken) {Ntoken = _Ntoken;}
	//constructor
    similarity(int numNtoken, int numHash);
	//compute
    void startDetect(int , char **);
	//use other interface to get all of the words in a file.
    std::vector<Token> get_word(std::string fileName);
	unsigned long ChoseHash(char *tok[], int* type);

	//init token
    void init_token_array(void);
	//stored the info of a file.
    Sig * signature(std::vector<Token> t);
	//compare the similarity.
    int compare(Sig *s0, Sig *s1);
};

int ulcmp(const void *p1, const void *p2);

#endif //SHERLOCKDETECT_H
