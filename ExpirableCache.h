#include<iostream>
#include<string>
#include<shared_mutex>
#include<mutex>
#include<thread>
#include<vector>
#include<memory>
#include<map>
#include <boost/core/noncopyable.hpp>

#include "ExpirableObject.h"

using namespace std;

#ifndef ExpirableCache_H
#define ExpirableCache_H

template<typename T1, typename T2> class ExpirableCache : private boost::noncopyable
{
	private:
		std::map<T1, ExpirableObject<T2>> m_InternalExpirableCache;
		mutable std::shared_mutex m_readWriteMutex;

	public:
		ExpirableCache();													// Default constructor.	
		void runEviction();													// Method to evict expired cache items.
		bool upsert(const std::pair<T1, T2>&);							    // This method is used to update the cache , returns a status if update was successfull / fail.
		T2 get(const T1&);													// get an Item from cache in read only mode.
		size_t size() const;												// return the size of map.
};

#endif
