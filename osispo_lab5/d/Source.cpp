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

	HANDLE hReadyEvent, hAnswerDEvent, hStopEvent;
	setlocale(LC_ALL, "Rus");
	string outputstring;
	
	int k = 0;
	srand(time(NULL));
	hReadyEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"ReadyEvent");
	hAnswerDEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"AnswDEvent");
	hStopEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"StopEvent");

	puts("");
	fflush(stdout);


	SetEvent(hAnswerDEvent);
	
	outputstring = argv[1];
	outputstring += " ";

	WaitForSingleObject(hReadyEvent, INFINITE);


	int SingleObject;
	string outputstringmemory = outputstring;
	while(true) 
	{
		outputstring = outputstringmemory + to_string(k);

		puts(outputstring.c_str());

		fflush(stdout);

		k++;
		Sleep(rand() % 5000);

	} 

	return 0;
}
