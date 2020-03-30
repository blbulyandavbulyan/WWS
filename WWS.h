#pragma once
#ifdef WWS_EXPORTS
#define WWSDLL_API __declspec(dllexport)
#include "stdafx.h"
#else
#define WWSDLL_API __declspec(dllimport)
#include "types.h"
#endif
namespace WWS {
	/*****************************************************
	**��������� ����������� ��� ������ ������� � ��� DLL**
	*****************************************************/
	//Unicode Version
	struct WWS_ERROR_REPORT_STRUCTW {//������ ��������� ����� ��� ������ Unicode ������ ������� ErrorString
		WSTRING ErrorString;//������ � �������
		WSTRING ErrorCaption;//��������� ������
		DWORD ErrorCode;// ��� ������
	};
	WWSDLL_API WSTRINGARRAY BreakAStringIntoAnArrayOfStringsByCharacter(WSTRING StringToBreak, WCHAR CharacterToBreak);// ������� ��������� ������ �� ������ ����� �� ������� CharacterToBreak
	WWSDLL_API WSTRING DeleteTwoCharactersInARow(WSTRING StringForDeleteTwoCharactersInARow, WCHAR SymbolForDelete);//������� ������� ������������� ������ (��������� ������ ���� ��� �����)
	WWSDLL_API int MessageError(LPCWSTR ErrorText, LPCWSTR ErrorCaption, HWND hWnd);// ������� ������� ���������� ���� � ������� (������� �������� ��� ������ � ������� GetLastError)
	WWSDLL_API int MessageError(LPCWSTR ErrorText, LPCWSTR ErrorCaption, HWND hWnd, HRESULT hErrorCode);//������� ������� ���������� ���� � ������� �� ��������� hErrorCode
	WWSDLL_API void MessageDebug(LPCWSTR ErrorText, LPCWSTR ErrorCaption);//������� ������� ��������� �� ������ � ������� ��������� (���� �������� ��� ������ � ������� GetLastError)
	WWSDLL_API void MessageDebug(LPCWSTR ErrorText, LPCWSTR ErrorCaption, HRESULT hErrorCode);//������� ������� ��������� �� ������ � ������� ��������� (������� ��� ������ HRESULT)
	WWSDLL_API WSTRING ErrorString(LPCWSTR ErrorText, HRESULT hErrorCode);//������� ��������� ��������� �� ������ �� ��������� HRESULT � �������� ��� � ��������� WWS_ERROR_REPORT_STRUCTW 
	WWSDLL_API WWS_ERROR_REPORT_STRUCTW ErrorString(LPCWSTR ErrorText);//������� ��������� ��������� �� ������ (���� �������� ��� ������) � �������� ��� � ��������� WWS_ERROR_REPORT_STRUCTW 
	/*
		��������! ANSI ������� �������� ��������� �� Unicode ��������, ����� ����, � ANSI �������� ��� ����������� ������ � Unicode, � �������� Unicode � ANSI
	*/
	//ANSI Version
	struct WWS_ERROR_REPORT_STRUCTA {
		ASTRING ErrorString;//������ � �������
		ASTRING ErrorCaption;//��������� ������
		DWORD ErrorCode;// ��� ������
	};
	WWSDLL_API ASTRINGARRAY BreakAStringIntoAnArrayOfStringsByCharacter(ASTRING StringToBreak, CHAR CharacterToBreak);// ������� ��������� ������ �� ������ ����� �� ������� CharacterToBreak
	WWSDLL_API ASTRING DeleteTwoCharactersInARow(ASTRING StringForDeleteTwoCharactersInARow, CHAR SymbolForDelete);//������� ������� ������������� ������ (��������� ������ ���� ��� �����)
	WWSDLL_API int MessageError(LPCSTR ErrorText, LPCSTR ErrorCaption, HWND hWnd);// ������� ������� ���������� ���� � ������� (������� �������� ��� ������ � ������� GetLastError)
	WWSDLL_API int MessageError(LPCSTR ErrorText, LPCSTR ErrorCaption, HWND hWnd, HRESULT hErrorCode);//������� ������� ���������� ���� � ������� �� ��������� hErrorCode
	WWSDLL_API void MessageDebug(LPCSTR ErrorText, LPCSTR ErrorCaption);//������� ������� ��������� �� ������ � ������� ��������� (���� �������� ��� ������ � ������� GetLastError)
	WWSDLL_API void MessageDebug(LPCSTR ErrorText, LPCSTR ErrorCaption, HRESULT hErrorCode);//������� ������� ��������� �� ������ � ������� ��������� (������� ��� ������ HRESULT)
	WWSDLL_API ASTRING ErrorString(LPCSTR ErrorText, HRESULT hErrorCode);//������� ��������� ��������� �� ������ �� ��������� HRESULT � �������� ��� � ��������� WWS_ERROR_REPORT_STRUCTW 
	WWSDLL_API WWS_ERROR_REPORT_STRUCTA ErrorString(LPCSTR ErrorText);//������� ��������� ��������� �� ������ (���� �������� ��� ������) � �������� ��� � ��������� WWS_ERROR_REPORT_STRUCTW 	
	WWSDLL_API HRESULT __fastcall AnsiToUnicode(LPCSTR aString, WSTRING& wString);//������� ��������� ANSI � Unicode
	WWSDLL_API HRESULT __fastcall UnicodeToAnsi(LPCWSTR wString, ASTRING& aString);	//������� ��������� Unicode � ANSI
}