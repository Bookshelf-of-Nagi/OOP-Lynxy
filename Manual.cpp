#include "Manual.h"

void Manual::printInfo()
{
    cout<<"usage: ";
    cout<<" file1 file2 ..."<<std::endl;
    cout<<"defaults:";
    cout<<" threshold=20%%";
    cout<<" zerobits=3";
    cout<<" chainlength=4";
}
