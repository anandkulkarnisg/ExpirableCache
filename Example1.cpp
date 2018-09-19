#include<iostream>
#include<string>

#include "ExpirableCache.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Create a Cache and add an item.
	ExpirableCache<string, string> sampleCache; 
	sampleCache.upsert(make_pair("Anand", "Apparao Kulkarni"));

	// Try and get the item which is still there.	
	cout << sampleCache.get("Anand") << endl;

	// We have 2 secs left for the item to expire.
	this_thread::sleep_for(chrono::seconds(58));
	sampleCache.runEviction();

	// The item must exist here still.
	std::string result = sampleCache.get("Anand");

	// The item expires after below 2 secs for sure.
	this_thread::sleep_for(chrono::seconds(2));

	try
	{
		result = sampleCache.get("Anand");
	}
	catch(const std::string& e)
	{
		cout << e << endl;
	}
	return(0);	
}
