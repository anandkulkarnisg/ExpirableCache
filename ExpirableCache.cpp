#include<iostream>
#include<string>

#include "ExpirableCache.h"

using namespace std;

// Constructor implementation.
template<typename T1, typename T2> ExpirableCache<T1,T2>::ExpirableCache()
{

}

// Get Function to get an item from the ExpirableCache. returns the value of a key if this is present in the cache.
template<typename T1, typename T2> T2 ExpirableCache<T1,T2>::get(const T1& keyItem)
{
	// Take a read only lock and then try to identify if the item is present in the cache.
	std::shared_lock<std::shared_mutex> lock(m_readWriteMutex);	

	auto iter = m_InternalExpirableCache.find(keyItem);
	if( iter != m_InternalExpirableCache.end())
	{
		lock.unlock();
		if(!iter->second.isExpired())
			return(iter->second.get());
		else
			throw std::string("The item has expired!");
	}
}

// Method that does the cache update with a given item.
template<typename T1, typename T2> bool ExpirableCache<T1,T2>::upsert(const std::pair<T1, T2>& upsertItem)
{
	// Attempt to insert the item into the cache. If the key is found then check the value. If both are same then reject. If the value is updated/new then accept and update the cache.
	// First of all check if the cache has the item and if the value is also same. Else only proceed.

	bool updateRequired = false;	

	// First take a read only lock and check if the item is present and if they kev/value are same. Then decide to take exclusive lock and update the item.
	std::shared_lock<std::shared_mutex> lock(m_readWriteMutex);

	auto iter = m_InternalExpirableCache.find(upsertItem.first);
	if( iter == m_InternalExpirableCache.end())
	{
		updateRequired = true;	
	}
	else
	{
		ExpirableObject<T2> valueItem(upsertItem.second);
		if(!(iter->first == upsertItem.first && iter->second == valueItem))
		{
			updateRequired = true;
		} 
	}

	lock.unlock();

	// Attempt an exclusive write lock now to update the content only if the updateRequired is true.
	if(updateRequired)
	{
		std::unique_lock<std::shared_mutex> writeLock(m_readWriteMutex);
		ExpirableObject<T2> valueItem(upsertItem.second);
		m_InternalExpirableCache[upsertItem.first] = valueItem;
	}	

	return(updateRequired);
}

template<typename T1, typename T2> size_t ExpirableCache<T1,T2>::size() const
{
	std::shared_lock<std::shared_mutex> lock(m_readWriteMutex);
	return(m_InternalExpirableCache.size());	
}

template<typename T1, typename T2> void ExpirableCache<T1,T2>::runEviction() 
{
	std::unique_lock<std::shared_mutex> writeLock(m_readWriteMutex);
	for(auto& iter : m_InternalExpirableCache)
	{
		if(iter.second.isExpired())
			m_InternalExpirableCache.erase(iter.first);
	}	
}

template class ExpirableCache<std::string, std::string>;
