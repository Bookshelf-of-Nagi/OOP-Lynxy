#pragma once

#include <cstdlib>
#include <ctime>
#include <string>

const char legal_charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

unsigned int Rand(){
	static bool flag = false;
	if(!flag) std::srand(std::time(0)),flag=true;
	return std::rand();
}
std::string randString(int len = 6){
	std::string ret;
	for(int i=0;i<len;i++) ret.append(1,legal_charset[Rand()%62]);
	return ret;
}
