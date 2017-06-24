#include "HashFactory.h"

void HashFactory::addInfo(std::string _info)
{
    info.push_back(_info);
    return ;
}
void HashFactory::printInfo()
{
    int start = 1;
    for(auto i : info)
    {
        std::cout<<start++<<".Using "<<i<<" to ensure the value of hash."<<std::endl;
    }
}

unsigned long HashFactory::ChoseHash(char *tok[], int Ntoken, int* type)
{
    switch(numHash)
    {
        case 1:
            hash1(tok, Ntoken, type);
            break;
        case 2:
            hash2(tok, Ntoken, type);
            break;
        case 3:
            hash3(tok, Ntoken, type);
            break;
        default:
            std::cout<<"Don't have this number, please try again."<<std::endl;
            int num = 0;
            std::cin>>num;
            set_numHash(num);
            ChoseHash(tok, Ntoken, type);
            break;
    }
}
unsigned long HashFactory::hash1(char *tok[], int Ntoken, int* type)
{
    unsigned long h;
	unsigned char *s;

	h = 0;
	for (int i = 0; i < Ntoken; i++)
		for (s = (unsigned char*)tok[i]; *s; s++)
		{

            h = h*31 + *s;
        }
	return h;
}
unsigned long HashFactory::hash2(char *tok[], int Ntoken, int* type)
{
    int p = 16777619;
    int hash = (int)2166136261L;
    unsigned char *s;
    for(int i = 0;i < Ntoken; i++)
        for(s = (unsigned char*)tok[i]; *s; s++)
        hash = (hash ^ *s) * p;
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    return hash;
}
unsigned long HashFactory::hash3(char *tok[], int Ntoken, int* type)
{
    unsigned long hash = 0;
    unsigned char *s;
    for(int i = 0;i < Ntoken; i++)
        for(s = (unsigned char*)tok[i]; *s; s++)
             hash = *s + (hash << 6) + (hash << 16) - hash;
    return hash;
}
