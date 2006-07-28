// clip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TemporaryFile.h"
#include "FileMapping.h"

void NewLine(void); 
void ScrollScreenBuffer(HANDLE, INT); 
 
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

int main(int argc, char* argv[])
{
	bool input_redirected = false;

	HANDLE hStdout, hStdin; 

    hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

    if((hStdin != INVALID_HANDLE_VALUE) && (hStdout != INVALID_HANDLE_VALUE))
    {
		DWORD dummy = 0;
		input_redirected = !PeekConsoleInput(hStdin, 0, 0, &dummy);

		if(input_redirected)
		{
			UINT code_page = GetConsoleCP();

			DWORD cRead = 0;
			DWORD cWritten = 0;
			BOOL readResult = 0;
			TCHAR chBuffer[2048]; 

			CTemporaryFile tempfile;

			tempfile.Create();

			do
			{ 
				readResult = ReadFile(hStdin, chBuffer, sizeof chBuffer / sizeof *chBuffer, &cRead, NULL);
				if(cRead > 0)
				{
					//Le EOF risque d'etre proche de la fin
					//alors on cherche a l'envers.
					int s=cRead;

					while(s--)
					{
						if(chBuffer[s] == 0x1A) //EOF
						{
							readResult = 0;
							cRead = s;
						}
					}

					WriteFile(tempfile, chBuffer, cRead, &cWritten, 0);
				}
			
				//fprintf(stderr, "rr=%d cr=0x%08X\n", readResult, cRead);
				
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
				hglbCopy = GlobalAlloc(GMEM_MOVEABLE, 1 + filesize.LowPart * sizeof(TCHAR)); 
        
				if (hglbCopy != NULL) 
				{ 
					LPTSTR  lptstrCopy; 
            
					// Lock the handle and copy the text to the buffer. 
					lptstrCopy = (LPTSTR)GlobalLock(hglbCopy); 
            
					StringCchCopy(lptstrCopy, 1+filesize.LowPart * sizeof(TCHAR), p);
            
					GlobalUnlock(hglbCopy); 
            
					if(EmptyClipboard())
					{
						// Place the handle on the clipboard. 
						SetClipboardData(CF_OEMTEXT, hglbCopy); 
					}
				}

				CloseClipboard();
			}
		}
		else
		{
			if(IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard(0))
			{
				DWORD written = 0;

				HANDLE hglbPaste = GetClipboardData(CF_TEXT);

				LPSTR lptstr = (char*)GlobalLock(hglbPaste); 

				WriteFile(hStdout, lptstr, _tcslen(lptstr), &written, 0);

				CloseClipboard();
			}
		}
	}

	return 0;
}

