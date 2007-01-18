// TemporaryFile.cpp: implementation of the CTemporaryFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TemporaryFile.h"

//----------------------------------------------------------------------
// Name        : CTemporaryFile::CTemporaryFile
// Description : 
// Returns     : 
//----------------------------------------------------------------------
CTemporaryFile::CTemporaryFile()
: mHandle(INVALID_HANDLE_VALUE)
{

}


//----------------------------------------------------------------------
// Name        : CTemporaryFile::~CTemporaryFile
// Description : 
// Returns     : 
//----------------------------------------------------------------------
CTemporaryFile::~CTemporaryFile()
{
	Close();
}


//----------------------------------------------------------------------
// Name        : CTemporaryFile::Create
// Description : 
// Returns     : DWORD 
//----------------------------------------------------------------------
DWORD CTemporaryFile::Create(const TCHAR *prefix)
{
	DWORD result = E_FAIL;

	TCHAR szTempPath[MAX_PATH];
	TCHAR szTempName[MAX_PATH];
	
	// Create a temporary file. 
	if(GetTempPath(MAX_PATH, szTempPath))
	{
		if(GetTempFileName(szTempPath, prefix, 0, szTempName))
		{
			UINT olderrormode = SetErrorMode(SEM_FAILCRITICALERRORS);
			mHandle = CreateFile(szTempName, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY|FILE_ATTRIBUTE_NOT_CONTENT_INDEXED|FILE_FLAG_DELETE_ON_CLOSE, NULL);

			result = GetLastError();

			SetErrorMode(olderrormode);
		}
	}

	return result;
}
	

//----------------------------------------------------------------------
// Name        : CTemporaryFile::Close
// Description : 
// Returns     : DWORD 
//----------------------------------------------------------------------
DWORD CTemporaryFile::Close()
{
	if(mHandle != INVALID_HANDLE_VALUE)
	{
		if(CloseHandle(mHandle))
			mHandle = INVALID_HANDLE_VALUE;
	}

	return GetLastError();
}