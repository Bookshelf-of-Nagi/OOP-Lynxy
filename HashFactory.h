#ifndef HASHFACTORY_H
#define HASHFACTORY_H

#include <vector>
#include <iostream>
#include <string>

//*******************************************************//
//      Use this class to print what we have about how //
//  to compute the hash value of the string.             //
//                                                       //
//*******************************************************//
class HashFactory
{
    std::vector<std::string> info;
    int numHash;                              //the label of hash method
public:
    //init
    HashFactory()
    {
        addInfo("multiply");
        addInfo("FNV");
        addInfo("SDBM");
    }
    //print tip
    void printInfo();
    //add new name of method
    void addInfo(std::string _info);

    //choose what we want to use
    unsigned long ChoseHash(char *tok[],  int Ntoken, int* type);
    //...
    unsigned long hash1(char *tok[], int Ntoken, int* type);
	unsigned long hash2(char *tok[], int Ntoken, int* type);
	unsigned long hash3(char *tok[], int Ntoken, int* type);

    void set_numHash(int num) {numHash = num;}
    int  get_numHash() {return numHash;}
};

#endif //HASHFACTORY_H
