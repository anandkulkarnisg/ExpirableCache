#include<iostream>
#include<string>

#include "ThreadSafeCache.h"

using namespace std;

int main(int argc, char* argv[])
{
	ThreadSafeCache<string, string> sampleCache; 
	sampleCache.upsert(make_pair("Anand", "Apparao Kulkarni"));
	cout << sampleCache.get("Anand") << endl;
	return(0);	
}
