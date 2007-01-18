// TemporaryFile.h: interface for the CTemporaryFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPORARYFILE_H__B3E46053_8CD4_4DB6_BB6D_34B153EBE8EF__INCLUDED_)
#define AFX_TEMPORARYFILE_H__B3E46053_8CD4_4DB6_BB6D_34B153EBE8EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTemporaryFile  
{
protected:
	HANDLE mHandle;

public:
	CTemporaryFile();
	virtual ~CTemporaryFile();

	DWORD Create(const TCHAR *prefix = _T("_$_"));
	DWORD Close();

	operator HANDLE() { return mHandle; }
};

#endif // !defined(AFX_TEMPORARYFILE_H__B3E46053_8CD4_4DB6_BB6D_34B153EBE8EF__INCLUDED_)
