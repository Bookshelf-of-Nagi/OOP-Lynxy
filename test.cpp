#include "Detect.h"
#include "similarity.h"
#include "HashFactory.h"
#include "Manual.h"

int main(int argc, char *argv[])
{
    Manual usage;
    usage.printInfo();
    std::cout<<std::endl<<std::endl;
    int numNtoken, numHash;
    std::cout<<"Please input a number of Ntoken to ensure how many words do you want to taken to use sherlock.(default value is 3)"<<std::endl;
    std::cin>>numNtoken;
    std::cout<<"Please input a number of the way to compute the value of hash."<<std::endl;
    HashFactory print;
    print.printInfo();
    std::cin>>numHash;
    Detect* p = new similarity(numNtoken, numHash);
    p -> startDetect(argc, argv);
    delete p;
    //Sherlock p;
    //p.startDetect(argc, argv);

    return 0;
}
