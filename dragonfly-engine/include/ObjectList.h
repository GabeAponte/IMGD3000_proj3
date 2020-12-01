#pragma once
#include "Object.h"
#include "ObjectListIterator.h"

const int MAX_OBJECTS = 5000;

namespace df {

	class ObjectList {

		friend class ObjectListIterator;

	private:
		std::vector<Object*> m_p_objects;

	public:
		ObjectList();
		~ObjectList();

		// Clear list
		void clear();

		// Insert object pointer in list
		// Return 0 if ok, else −1
		int insert(Object* p_obj);
		
		// Remove object pointer from list
		// Return 0 if found, else −1
		int remove(Object* p_obj);

		// Return count of number of objects in list
		int getCount() const;

		// Return true if list is empty, else false
		bool isEmpty() const;

		// Return true if list is full, else false
		bool isFull() const;
	};
}