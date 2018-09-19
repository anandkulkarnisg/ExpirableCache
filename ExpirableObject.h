#include<iostream>
#include<string>

#include "Expirable.h"

#ifndef ExpirableObject_H
#define ExpirableObject_H

template<typename T> class ExpirableObject : public Expirable
{
	private:
		T m_obj;

	public:
		ExpirableObject() : Expirable(1, TimeUnit::Minutes) 
	{ 
		std::cout << "iamhere1" << std::endl; 
	}
		ExpirableObject(const T& obj, const long& waitQuantity=1, const TimeUnit& unit=TimeUnit::Minutes) : m_obj(obj) , Expirable(waitQuantity, unit) 
	{ 
		std::cout << "iamhere2" << std::endl; 
	}
		ExpirableObject(const ExpirableObject& copyItem) : Expirable(0, TimeUnit::MilliSeconds) 
	{ std::cout << "iamhere3" << std::endl; m_obj = copyItem.m_obj; setWaitCount(copyItem.getWaitCount()); }
		ExpirableObject& operator=(const ExpirableObject& assignItem) { this->m_obj = assignItem.m_obj; return(*this); }
		T get() const { return(m_obj); }
		friend bool operator==(const ExpirableObject<T>& first, const ExpirableObject<T>& second)
		{
			return(first.m_obj == second.m_obj);
		}	
};

template class ExpirableObject<std::string>;

#endif
