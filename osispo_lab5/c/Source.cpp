//Lab5_B, C, D
#include "windows.h" 
#include <stdlib.h> 
#include <stdio.h> 
#include <locale.h> 
#include <iostream> 
#include <tchar.h> 
#include <string>

using namespace std;

int main(int argc, char* argv[]) 
{

	HANDLE hReadyEvent, hAnswerCEvent, hStopEvent;
	setlocale(LC_ALL, "Rus");
	string outputstring;

	int k = 0;
	srand(time(NULL));
	hReadyEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"ReadyEvent");
	hAnswerCEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"AnswCEvent");
	hStopEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"StopEvent");

	puts("");
	fflush(stdout);

	SetEvent(hAnswerCEvent);
	
	outputstring = argv[1];
	outputstring += " ";

	WaitForSingleObject(hReadyEvent, INFINITE);


	int SingleObject;
	string outputstringmemory = outputstring;
	while (true)
	{
		outputstring = outputstringmemory + to_string(k);

		puts(outputstring.c_str());

		fflush(stdout);

		k++;

		Sleep(rand() % 5000);

	} 

	return 0;
}
