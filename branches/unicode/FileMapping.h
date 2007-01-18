// FileMapping.h: interface for the CFileMapping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMAPPING_H__B3F90251_75E3_4148_AC92_2F70A10AC4F9__INCLUDED_)
#define AFX_FILEMAPPING_H__B3F90251_75E3_4148_AC92_2F70A10AC4F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileMapping  
{
protected:
	HANDLE mMapping;
	void *mP;

public:
	CFileMapping();
	virtual ~CFileMapping();

	void *Map(HANDLE file, DWORD protection=PAGE_READWRITE);
	void Unmap();

	operator void*() { return mP; }
};

#endif // !defined(AFX_FILEMAPPING_H__B3F90251_75E3_4148_AC92_2F70A10AC4F9__INCLUDED_)
