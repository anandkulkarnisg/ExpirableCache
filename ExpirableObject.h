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
		ExpirableObject(const T& obj, const long& waitQuantity = 10, const TimeUnit& unit = TimeUnit::Seconds) : m_obj(obj) , Expirable(waitQuantity, unit) { }
		T get() const { return(m_obj); }
		friend bool operator==(const ExpirableObject<T>& first, const ExpirableObject<T>& second)
		{
			return(first.m_obj == second.m_obj);
		}	
};

#endif
