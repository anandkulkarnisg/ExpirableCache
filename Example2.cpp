#include<iostream>
#include<string>

#include "ExpirableCache.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Create a Cache and add an item.
	ExpirableCache<string, string> sampleCache(10, TimeUnit::Seconds); 
	sampleCache.upsert(make_pair("Anand", "Apparao Kulkarni"));

	// Try and get the item which is still there.	
	cout << sampleCache.get("Anand") << endl;

	// We have 2 secs left for the item to expire.
	this_thread::sleep_for(chrono::seconds(11));

	try
	{
		string result = sampleCache.get("Anand");
		cout << result << endl;
	}
	catch(const std::string& e)
	{
		cout << e << endl;
	}
	return(0);	
}
