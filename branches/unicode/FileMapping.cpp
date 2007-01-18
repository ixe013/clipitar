// FileMapping.cpp: implementation of the CFileMapping class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileMapping.h"


//----------------------------------------------------------------------
// Name        : CFileMapping::CFileMapping
// Description : 
// Returns     : 
//----------------------------------------------------------------------
CFileMapping::CFileMapping()
: mMapping(0)
, mP(0)
{
}


//----------------------------------------------------------------------
// Name        : CFileMapping::~CFileMapping
// Description : 
// Returns     : 
//----------------------------------------------------------------------
CFileMapping::~CFileMapping()
{
	Unmap();
}


//----------------------------------------------------------------------
// Name        : *CFileMapping::Map
// Description : 
// Parametre   : [in,out] HANDLE file
// Returns     : void 
//----------------------------------------------------------------------
void *CFileMapping::Map(HANDLE file, DWORD protection)
{
	LARGE_INTEGER filesize;
    
	GetFileSizeEx(file, &filesize);

	mMapping = CreateFileMapping(file, 0, protection, filesize.HighPart, filesize.LowPart, 0);

	if(mMapping)
	{
		BYTE *p = (BYTE*)MapViewOfFile(mMapping, FILE_MAP_READ, 0, 0, 0);

		mP = p;
	}

	return mP;
}


//----------------------------------------------------------------------
// Name        : CFileMapping::Unmap
// Description : 
// Returns     : void 
//----------------------------------------------------------------------
void CFileMapping::Unmap()
{
	if(mP)
	{
		UnmapViewOfFile(mP);
		mP = 0;
	}

	if(mMapping)
	{
		CloseHandle(mMapping);
		mMapping = 0;
	}
}
