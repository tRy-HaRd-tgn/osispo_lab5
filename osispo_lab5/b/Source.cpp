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

	HANDLE hReadyEvent, hAnswerBEvent, hStopEvent;////����� ��� ������ � ������� �����
	setlocale(LC_ALL, "Rus");//���� �������
	string outputstring;//������ ������� ����� ��������
	
	int k = 0;
	srand(time(nullptr));//���������� ��������� ������
	hReadyEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"ReadyEvent");
	hAnswerBEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"AnswBEvent");
	hStopEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"StopEvent");

	//��������� ������
	puts("");
	fflush(stdout);

	SetEvent(hAnswerBEvent);

	//argv[1]- ��� ��������
	outputstring = argv[1];
	outputstring += " ";

	WaitForSingleObject(hReadyEvent, INFINITE);

	string outputstringmemory = outputstring;
	while (true)//����������� ���� ��������� � ������������ ������� ���������
	{
		outputstring = outputstringmemory + to_string(k);

		puts(outputstring.c_str());
		
		fflush(stdout);

		k++;

		Sleep(rand() % 5000);
	} 

	return 0;
}
