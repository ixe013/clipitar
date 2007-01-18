// clip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TemporaryFile.h"
#include "FileMapping.h"

//void NewLine(void); 
//void ScrollScreenBuffer(HANDLE, INT); 
 
//CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

void PrintError(DWORD err, const TCHAR *msg = _T("Error"))
{ 
	if(err)
	{
		LPVOID lpMsgBuf;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );

		MessageBox(GetConsoleWindow(), (LPTSTR)lpMsgBuf, msg, MB_ICONERROR); 
	 
		LocalFree(lpMsgBuf);
}
}

int _tmain(int argc, const TCHAR* argv[])
/*
{
	DWORD dummy = 0;
	DWORD cRead = 0;
	DWORD cWritten = 0;
	BOOL readResult = 0;
	TCHAR chBuffer[2048]; 
	TCHAR chDebugBuffer[2048]; 
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetLastError(0);
	readResult = PeekConsoleInput(hStdin, 0, 0, &dummy);
	PrintError(GetLastError(), _T("PeekConsoleInput"));

	SetLastError(0);

	if(!readResult)
	{
		readResult = ReadFile(hStdin, chBuffer, sizeof chBuffer / sizeof *chBuffer, &cRead, NULL);
	}
	else
	{
		readResult = ReadConsole(hStdin, chBuffer, sizeof chBuffer / sizeof *chBuffer, &cRead, NULL);
	}

	PrintError(GetLastError(), _T("Read"));

	_stprintf(chDebugBuffer, _T("readResult=%d\ncRead=%d\n"), readResult, cRead);
	MessageBox(GetConsoleWindow(), chDebugBuffer, _T("Debug"), MB_ICONINFORMATION); 

	HANDLE so = GetStdHandle(STD_OUTPUT_HANDLE);

	//DebugBreak();
	SetLastError(0);

	//WriteFile(so, chBuffer, cRead, &dummy, 0);
	WriteConsole(so, chBuffer, cRead, &dummy, 0);

	PrintError(GetLastError(), _T("Write"));
}
/*/
{
	bool input_redirected = false;

	HANDLE hStdout, hStdin; 

    hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

	fprintf(stderr, "Handles : stdin = 0x%08X  stdout = 0x%08X\n", hStdin, hStdout);

	if(!hStdin || !hStdout)
	{
		PrintError(GetLastError());
	}
    else if((hStdin != INVALID_HANDLE_VALUE) && (hStdout != INVALID_HANDLE_VALUE))
    {
		DWORD dummy = 0;
		input_redirected = !PeekConsoleInput(hStdin, 0, 0, &dummy);

		PrintError(GetLastError());

		if(input_redirected)
		{
			DWORD cRead = 0;
			DWORD cWritten = 0;
			BOOL readResult = 0;
			BYTE chBuffer[2048]; 

			CTemporaryFile tempfile;

			PrintError(tempfile.Create());

			do
			{ 
				readResult = ReadFile(hStdin, chBuffer, sizeof chBuffer, &cRead, NULL);

				fprintf(stderr, "readResult=%d\tcRead=%d\n", readResult, cRead);

				PrintError(GetLastError());

				if(cRead > 0)
				{
#ifdef _DEBUG
					//DebugBreak();
#endif
					//Le EOF risque d'etre proche de la fin
					//alors on cherche a l'envers.
					//int s=cRead;
					//while(s--) if(chBuffer[s] == 0x1A) { readResult = 0; cRead = s; }

					WriteFile(tempfile, chBuffer, cRead, &cWritten, 0);
				}
			
				fprintf(stderr, "rr=%d cr=0x%08X\n", readResult, cRead);
				
			} while (readResult && cRead);

			LARGE_INTEGER filesize;
    
			GetFileSizeEx(tempfile, &filesize);

			CFileMapping mapping;

			TCHAR *p = (TCHAR*)mapping.Map(tempfile);

			//Faire traitement sur le data ici au besoin
			//*
			if(filesize.LowPart && ::OpenClipboard(0))
			{
				HGLOBAL hglbCopy; 
        
				// Allocate a global memory object for the text. 
				hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (1 + filesize.LowPart) * sizeof(TCHAR)); 
        
				if (hglbCopy != NULL) 
				{ 
					LPTSTR  lptstrCopy; 
            
					// Lock the handle and copy the text to the buffer. 
					lptstrCopy = (LPTSTR)GlobalLock(hglbCopy); 
            
					StringCchCopy(lptstrCopy, (1+filesize.LowPart) * sizeof(TCHAR), p);
            
					GlobalUnlock(hglbCopy); 
            
					if(EmptyClipboard())
					{
						// Place the handle on the clipboard. 
						SetClipboardData(CF_UNICODETEXT, hglbCopy); 
					}
				}

				CloseClipboard();
			}
		}
		else
		{
			if(IsClipboardFormatAvailable(CF_UNICODETEXT) && OpenClipboard(0))
			{
				HANDLE hglbPaste = GetClipboardData(CF_UNICODETEXT);

				if(hglbPaste)
				{
					DWORD written = 0;
					DWORD towrite = 0;

					LPTSTR lptstr = (LPTSTR)GlobalLock(hglbPaste); 
					LPTSTR writtenupto = lptstr; 

					towrite = _tcslen(lptstr);

					

					do
					{
						//WriteFile(hStdout, writtenupto, towrite, &written, 0);
						WriteConsole(hStdout, writtenupto, towrite, &written, 0);

						towrite -= written;
						writtenupto += written;

					} while(towrite > 0);

					GlobalUnlock(lptstr);

				}
				else
				{
					PrintError(GetLastError());
				}

				CloseClipboard();
			}
		}
	}

	return 0;
}
//*/

