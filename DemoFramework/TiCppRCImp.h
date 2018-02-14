#pragma once

#include <vector>
#include "ticpprc.h"

class TiCppRCImp
{
private:

	int m_count;		/**< Holds reference count to me, and to the node I point to */

	TiCppRC* m_tiCppRC;	/**< Holds pointer to an object inheriting TiCppRC */

public:

	/**
	Initializes m_tiCppRC pointer, and set reference count to 1
	*/
	TiCppRCImp( TiCppRC* tiCppRC );

	/**
	Allows the TiCppRC object to set the pointer to itself ( m_tiCppRc ) to NULL when the TiCppRC object is deleted
	*/
	void Nullify();

	/**
	Increment Reference Count
	*/
	void IncRef();

	/**
	Decrement Reference Count
	*/
	void DecRef();

	/**
	Set Reference Count to 1 - dangerous! - Use only if you are sure of the consequences
	*/
	void InitRef();

	/**
	Get internal pointer to the TiCppRC object - not reference counted, use at your own risk
	*/
	TiCppRC* Get();

	/**
	Returns state of internal pointer - will be null if the object was deleted
	*/
	bool IsNull();
};
