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

	HANDLE hReadyEvent, hAnswerBEvent, hStopEvent;////нужны для работы с каналом связи
	setlocale(LC_ALL, "Rus");//язык консоли
	string outputstring;//строка которую будем выводить
	
	int k = 0;
	srand(time(nullptr));//подключаем настоящий рандом
	hReadyEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"ReadyEvent");
	hAnswerBEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"AnswBEvent");
	hStopEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"StopEvent");

	//начальный отступ
	puts("");
	fflush(stdout);

	SetEvent(hAnswerBEvent);

	//argv[1]- имя процесса
	outputstring = argv[1];
	outputstring += " ";

	WaitForSingleObject(hReadyEvent, INFINITE);

	string outputstringmemory = outputstring;
	while (true)//бесконечный цикл выводящий в родительскую консоль сообщения
	{
		outputstring = outputstringmemory + to_string(k);

		puts(outputstring.c_str());
		
		fflush(stdout);

		k++;

		Sleep(rand() % 5000);
	} 

	return 0;
}
