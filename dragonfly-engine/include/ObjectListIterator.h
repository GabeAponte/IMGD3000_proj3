#pragma once
#include "Object.h"
#include "ObjectList.h"

namespace df {

	class ObjectList;	// Reference class to define pointers

	class ObjectListIterator {

	private:
		ObjectListIterator();		// Must be given list when created
		
		int m_index = 0;			// Index into list
		const ObjectList *m_p_list;	// List iterating over
		
	public:
		// Create iterator, over indicated list
		ObjectListIterator(const ObjectList *p_l);
		
		// Set iterator to first item in list
		void first();

		// Set iterator to next item in list
		void next();

		// Return true if at end of list
		bool isDone() const;
	
		// Return pointer to current Object, NULL if done / empty
		Object* currentObject() const;
	};
}