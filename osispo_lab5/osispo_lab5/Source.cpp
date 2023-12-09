
#include "windows.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <locale.h> 
#include <io.h> 
#include <Fcntl.h> 
#include <string>
#include <iostream>

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::string str1; std::string str2; std::string str3;

	//������ �������� ���������
	std::cout << "������� 3 ������(����� ������� �� �������� ���������)\n";
	std::cin >> str1 >> str2 >> str3;
	//���������� ��������� � �������
	str1 = "Tread " + str1;
	str2 = "Tread " + str2;
	str3 = "Tread " + str3;

	//�������������� ����� 1
	std::wstring widestr1 = std::wstring(str1.begin(), str1.end());
	std::wstring widestr2 = std::wstring(str2.begin(), str2.end());
	std::wstring widestr3 = std::wstring(str3.begin(), str3.end());

	//�������������� ����� 2
	const wchar_t*  cstr1 = widestr1.c_str();
	const wchar_t*  cstr2 = widestr2.c_str();
	const wchar_t*  cstr3 = widestr3.c_str();
	/*
		�������������� ����� ���������� ��-�� ���� ���������� � ������� CreateProcess
	*/
	LPWSTR Name1 = (LPWSTR)cstr1;
	LPWSTR Name2 = (LPWSTR)cstr2;
	LPWSTR Name3 = (LPWSTR)cstr3;

	LPWSTR NAMES[] = { Name1, Name2, Name3 };

	//���� ��� exe ������ ���������
	const wchar_t name1[] = L"C:\\Users\\User\\source\\repos\\osispo_lab5\\x64\\Debug\\b.exe";
	const wchar_t name2[] = L"C:\\Users\\User\\source\\repos\\osispo_lab5\\x64\\Debug\\c.exe";
	const wchar_t name3[] = L"C:\\Users\\User\\source\\repos\\osispo_lab5\\x64\\Debug\\d.exe";
	const wchar_t* NAMES1[] = { name1, name2, name3 };
	

	BOOL strBRuns = FALSE, strCRuns = FALSE, strDRuns = FALSE;//������� ���������� ��� ������������ ������� ���������
	BOOL RUNS[3] = { strBRuns, strCRuns, strDRuns };

	HANDLE hReadPipe, hWritePipe, hAnswerBEvent, hAnswerCEvent, hAnswerDEvent, hStopEvent, hReadyEvent;	//����� ��� ������ � ������� �����
	FILE* readPipeFile;	//����� ��� ������
	STARTUPINFO startInfo = { sizeof(startInfo) };//������������� ��������� startupinfo - ��� ����� ��� �������� ��������
	PROCESS_INFORMATION strInfo;
	SECURITY_ATTRIBUTES pipeAttributes = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	SetWindowText(GetForegroundWindow(), (LPCWSTR)(L"Process A"));


	hReadyEvent   =	CreateEvent(NULL, TRUE, FALSE,	(LPCWSTR)("ReadyEvent"));
	hAnswerBEvent = CreateEvent(NULL, FALSE, FALSE, (LPCWSTR)("AnswBEvent"));
	hAnswerCEvent = CreateEvent(NULL, FALSE, FALSE, (LPCWSTR)("AnswCEvent"));
	hAnswerDEvent = CreateEvent(NULL, FALSE, FALSE, (LPCWSTR)("AnswDEvent"));
	hStopEvent    =	CreateEvent(NULL, TRUE, FALSE,	(LPCWSTR)("StopEvent"));


	CreatePipe(&hReadPipe, &hWritePipe, &pipeAttributes, 0);//�������� ���������� ������������� ������

	readPipeFile = _fdopen((HFILE)_open_osfhandle((intptr_t)hReadPipe, _O_TEXT | _O_RDONLY), "rt");//��������� �������� ��������� ��� ������ �� ������������ ������
	startInfo.dwFlags = STARTF_USESTDHANDLES;
	startInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	startInfo.hStdOutput = hWritePipe;
	startInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	for (int i = 0; i < 3; i++) //������ ��������� �������� �������� � ��������� ������ �� ���� ���������.
	{
		startInfo.lpTitle = (LPWSTR)NAMES[i];

		RUNS[i] = CreateProcess(NAMES1[i], NAMES[i], NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &startInfo, &strInfo);
	}
	CloseHandle(hWritePipe);//��������� ���������� ������ � ������ ����� � ������� ������� �� ������� �� ���������� ��������� B, C � D
	WaitForSingleObject(hAnswerBEvent, INFINITE);
	WaitForSingleObject(hAnswerCEvent, INFINITE);
	WaitForSingleObject(hAnswerDEvent, INFINITE);
	SetEvent(hReadyEvent);
	char temp[400];
	fgets(temp, 400, readPipeFile);
	int i = 0;
	while (i < 10000) //������ ������ ������ �� ������ � ������� �� �� �����.
	{
		fgets(temp, 200, readPipeFile);
		temp[strlen(temp) - 1] = '\0';
		std::cout << std::endl << temp;
		i++;
	}
	return 0;
}
