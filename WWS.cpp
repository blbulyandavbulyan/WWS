// WWS.cpp : Определяет экспортированные функции для приложения DLL.
//Данная библиотека предназначена для работы со строками
// Здесь будут функции для UNICODE и ASCII
#include "stdafx.h"
#include "WWS.h"
/****************************
******Unicode Version********
****************************/
/***********************************************************************
*Данные функции используются при обработке аргументов командной строки**
***********************************************************************/

WWSDLL_API WSTRINGARRAY WWS::BreakAStringIntoAnArrayOfStringsByCharacter(WSTRING StringToBreak, WCHAR CharacterToBreak) {// данная функция разбивает входную строку StringToBreak на массив строк по заданному символу CharacterToBreak
	WSTRING StringForProcessing = WWS::DeleteTwoCharactersInARow(StringToBreak, CharacterToBreak);
	WSTRINGARRAY TSA;
	if (StringToBreak == L"") {
		return TSA;
	}
	if (StringForProcessing[0] == CharacterToBreak) {
		StringForProcessing.erase(StringForProcessing.begin());
	}
	if (StringForProcessing[StringForProcessing.size() - 1] == CharacterToBreak) {
		StringForProcessing.erase(StringForProcessing.end());
	}
	WSTRING ts;
	size_t StringForProcessingSize = StringForProcessing.size(), StringForProcessingSizeSmallerByOne = StringForProcessingSize - 1;
	for (size_t i = 0; i < StringForProcessingSize; i++) {
		if ((StringForProcessing[i] == CharacterToBreak)) {
			TSA.push_back(ts);
			ts.clear();
		}
		else if (i == StringForProcessingSizeSmallerByOne) {
			ts += StringForProcessing[i];
			TSA.push_back(ts);
			ts.clear();
		}
		else {
			ts += StringForProcessing[i];
		}
	}
	return TSA;
}
WWSDLL_API WSTRING WWS::DeleteTwoCharactersInARow(WSTRING StringForDeleteTwoCharactersInARow, WCHAR SymbolForDelete) {// данная функция удаляет заданный дублирующийся символ
	WSTRING ResultString;
	size_t StringSize = StringForDeleteTwoCharactersInARow.size();
	ResultString += StringForDeleteTwoCharactersInARow[0];
	size_t Counter = 0;
	for (size_t i = 1; i < StringForDeleteTwoCharactersInARow.size(); i++) {
		if (ResultString[Counter] == StringForDeleteTwoCharactersInARow[i] == SymbolForDelete)continue;
		else {
			ResultString += StringForDeleteTwoCharactersInARow[i];
			Counter++;
		}
	}
	return ResultString;
}
/***********************************************************************
*Данные функции выводят диалоговое окно с текстом ошибки****************
***********************************************************************/
WWSDLL_API int WWS::MessageError(LPCWSTR ErrorText, LPCWSTR ErrorCaption, HWND hWnd) {//данная функция сама получает код ошибки с помощью GetLastError
	return MessageError(ErrorText, ErrorCaption, hWnd, GetLastError());
}
//данная функция требует код ошибки HRESULT
WWSDLL_API int WWS::MessageError(LPCWSTR ErrorText, LPCWSTR ErrorCaption, HWND hWnd, HRESULT hErrorCode) {
	int result = 0;
	LPWSTR BufferForFormatMessage = nullptr;
	DWORD FMResult = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, hErrorCode, LANG_USER_DEFAULT, (LPWSTR)&BufferForFormatMessage, NULL, nullptr);
	if (FMResult == 0) {
		WSTRING FormatedErrorMessage = ErrorText;
		FormatedErrorMessage += L"\nПричина ошибки: Не удалось узнать причину возникновения ошибки!";
		result = MessageBoxW(hWnd, FormatedErrorMessage.c_str(), ErrorCaption, MB_OK | MB_ICONERROR);
	}
	else {
		WSTRING FormatedErrorMessage = ErrorText;
		FormatedErrorMessage += L"\nПричина ошибки: ";
		FormatedErrorMessage += BufferForFormatMessage;
		result = MessageBoxW(hWnd, FormatedErrorMessage.c_str(), ErrorCaption, MB_OK | MB_ICONERROR);
	}
	if (HeapFree(GetProcessHeap(), NULL, BufferForFormatMessage) == NULL) {
		WSTRING HeapErrorMessage = L"Не удалось освободить буфуер при обработке предыдущей ошибки!\n";
		HeapErrorMessage += (L"Код ошибки: " + std::to_wstring(GetLastError()));
		result = MessageBoxW(hWnd, HeapErrorMessage.c_str(), L"Ошибка освобождения буфера!", MB_OK | MB_ICONERROR);
	}
	return result;
}
/****************************************************************
*данные функции выводят сообщение об ошибке в консоль отладчика**
*****************************************************************/
WWSDLL_API void WWS::MessageDebug(LPCWSTR ErrorText, LPCWSTR ErrorCaption) {//данная функция сама получает код ошибки с помощью GetLastError
	return WWS::MessageDebug(ErrorText, ErrorCaption, GetLastError());
}
//данная функция требует код ошибки HRESULT
WWSDLL_API void WWS::MessageDebug(LPCWSTR ErrorText, LPCWSTR ErrorCaption, HRESULT hErrorCode) {
	LPWSTR BufferForFormatMessage = nullptr;
	DWORD FMResult = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, hErrorCode, LANG_USER_DEFAULT, (LPWSTR)&BufferForFormatMessage, NULL, nullptr);
	if (FMResult == 0) {
		WSTRING FormatedErrorMessage = ErrorCaption;
		FormatedErrorMessage += L": ";
		FormatedErrorMessage += ErrorText;
		FormatedErrorMessage += L"\nПричина ошибки: Не удалось узнать причину возникновения ошибки!\n";
		OutputDebugStringW(FormatedErrorMessage.c_str());
	}
	else {
		WSTRING FormatedErrorMessage = ErrorCaption;
		FormatedErrorMessage += L": ";
		FormatedErrorMessage += ErrorText;
		FormatedErrorMessage += L"\nПричина ошибки: ";
		FormatedErrorMessage += BufferForFormatMessage;
		FormatedErrorMessage += L"\n";
		OutputDebugStringW(FormatedErrorMessage.c_str());
	}
	if (HeapFree(GetProcessHeap(), NULL, BufferForFormatMessage) == NULL) {
		WSTRING HeapErrorMessage = L"Не удалось освободить буфуер при обработке предыдущей ошибки!\n";
		HeapErrorMessage += (L"Код ошибки: " + std::to_wstring(GetLastError()) + L"\n");
		OutputDebugStringW(HeapErrorMessage.c_str());
	}
}

WWSDLL_API WSTRING WWS::ErrorString(LPCWSTR ErrorText, HRESULT hErrorCode) {
	WSTRING result;
	LPWSTR BufferForFormatMessage = nullptr;
	DWORD FMResult = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, hErrorCode, LANG_USER_DEFAULT, (LPWSTR)&BufferForFormatMessage, NULL, nullptr);
	if (FMResult == 0) {
		result = ErrorText;
		result += (L"\nКод Ошибки: " + std::to_wstring(hErrorCode));
		result += L"\nПричина ошибки: Не удалось узнать причину возникновения ошибки!";
	}
	else {
		result = ErrorText;
		result += (L"\nКод Ошибки: " + std::to_wstring(hErrorCode));
		result += L"\nПричина ошибки: ";
		result += BufferForFormatMessage;

	}
	if (HeapFree(GetProcessHeap(), NULL, BufferForFormatMessage) == NULL) {
		result += L"\nНе удалось освободить буфуер при обработке предыдущей ошибки!\n";
		result += (L"Код ошибки: " + std::to_wstring(GetLastError()));
	}
	return result;
}

WWSDLL_API WWS::WWS_ERROR_REPORT_STRUCTW WWS::ErrorString(LPCWSTR ErrorText) {
	WWS::WWS_ERROR_REPORT_STRUCTW result;
	result.ErrorCode = GetLastError();
	result.ErrorString = WWS::ErrorString(ErrorText, result.ErrorCode);
	return result;
}
//ASCII Version
/*
	 Функция будет работать ОООООчень медленно, по сравнению с Unicode  версией
	Да и вообще, эта библиотека используется только в Unicode проектах, современные версии Windows поддерживают Unicode
	Поэтому, по возможности, используйте Unicode версии функций
*/
WWSDLL_API ASTRINGARRAY WWS::BreakAStringIntoAnArrayOfStringsByCharacter(ASTRING StringToBreak, CHAR CharacterToBreak) {
	ASTRINGARRAY result;
	WSTRING StringToBreakW;
	WCHAR CharacterToBreakW = 0;
	WSTRINGARRAY wresult;
	if (WWS::AnsiToUnicode(StringToBreak.c_str(), StringToBreakW) == NOERROR) {
		if (MultiByteToWideChar(CP_ACP, 0, &CharacterToBreak, sizeof(CharacterToBreak), &CharacterToBreakW, 1) != 0) {
			wresult = WWS::BreakAStringIntoAnArrayOfStringsByCharacter(StringToBreakW, CharacterToBreakW);
			result.resize(wresult.size());
			for (size_t i = 0; i < wresult.size(); i++)WWS::UnicodeToAnsi(wresult[i].c_str(), result[i]);
		}
		else return result;//вернуть код ошибки
	}
	return result;
}
WWSDLL_API ASTRING WWS::DeleteTwoCharactersInARow(ASTRING StringForDeleteTwoCharactersInARow, CHAR SymbolForDelete){
	ASTRING result;
	WSTRING wresult;
	WCHAR wSymbolForDelete = 0;
	WSTRING wStringForDeleteTwoCharactersInARow;
	if (MultiByteToWideChar(CP_ACP, 0, &SymbolForDelete, sizeof(SymbolForDelete), &wSymbolForDelete, 1) != 0) {
		if (AnsiToUnicode(StringForDeleteTwoCharactersInARow.c_str(), wStringForDeleteTwoCharactersInARow) == NOERROR) {
			wresult = DeleteTwoCharactersInARow(wStringForDeleteTwoCharactersInARow, wSymbolForDelete);
			if (UnicodeToAnsi(wresult.c_str(), result) == NOERROR)return result;
			else WWS::MessageError(L"Ошибка в функции" __FUNCTION__ L" в библиотеке WWS, не удалось преобразовать Unicode строку в ASCII", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
		}
		else WWS::MessageError(L"Ошибка в функции" __FUNCTION__ L" в библиотеке WWS, не удалось преобразовать ASCII строку в Unicode", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
	}
	else WWS::MessageError(L"Ошибка в функции" __FUNCTION__ L" в библиотеке WWS, не удалось преобразовать SymbolForDelete в wSymbolForDelete.", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
	return result;
}
WWSDLL_API int WWS::MessageError(LPCSTR ErrorText, LPCSTR ErrorCaption, HWND hWnd){
	return  WWS::MessageError(ErrorText, ErrorCaption, hWnd, GetLastError());
}
WWSDLL_API int WWS::MessageError(LPCSTR ErrorText, LPCSTR ErrorCaption, HWND hWnd, HRESULT hErrorCode){
	WSTRING wErrorText, wErrorCaption;
	if (AnsiToUnicode(ErrorText, wErrorText) == NOERROR) {
		if (AnsiToUnicode(ErrorCaption, wErrorCaption) == NOERROR) {
			return WWS::MessageError(wErrorText.c_str(), wErrorCaption.c_str(), hWnd, hErrorCode);
		}
		else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorCaption в wErrorCaption!", L"Ошибка в функции " __FUNCTION__ L"!", hWnd);
	}
	else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorText в wErrorText!", L"Ошибка в функции " __FUNCTION__ L"!", hWnd);
	return NULL;
}
WWSDLL_API void WWS::MessageDebug(LPCSTR ErrorText, LPCSTR ErrorCaption)
{
	WSTRING wErrorText, wErrorCaption;
	if (AnsiToUnicode(ErrorText, wErrorText) == NOERROR) {
		if (AnsiToUnicode(ErrorCaption, wErrorCaption) == NOERROR)return WWS::MessageDebug(wErrorText.c_str(), wErrorCaption.c_str(), GetLastError());
		else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorCaption в wErrorCaption!", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
	}
	else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorText в wErrorText!", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
}
WWSDLL_API void WWS::MessageDebug(LPCSTR ErrorText, LPCSTR ErrorCaption, HRESULT hErrorCode) {
	WSTRING wErrorText, wErrorCaption;
	if (AnsiToUnicode(ErrorText, wErrorText) == NOERROR) {
		if (AnsiToUnicode(ErrorCaption, wErrorCaption) == NOERROR)MessageDebug(wErrorText.c_str(), wErrorCaption.c_str(), hErrorCode);
		else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorCaption в wErrorCaption!", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
	}
	else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorText в wErrorText!", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
}	
WWSDLL_API ASTRING WWS::ErrorString(LPCSTR ErrorText, HRESULT hErrorCode){
	ASTRING result;
	WSTRING wErrorText, wresult;
	if(AnsiToUnicode(ErrorText, wErrorText) == NOERROR){
		wresult = WWS::ErrorString(wErrorText.c_str(), hErrorCode);
		if (UnicodeToAnsi(wresult.c_str(), result) == NOERROR) {
			return result;
		}
		else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать wresult в result!", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
	}
	else WWS::MessageError(L"Ошибка в функции " __FUNCTION__ L" не удалось преобразовать ErrorText в wErrorText!", L"Ошибка в функции " __FUNCTION__ L"!", NULL);
	return result;
}
WWSDLL_API WWS::WWS_ERROR_REPORT_STRUCTA WWS::ErrorString(LPCSTR ErrorText){
	WWS_ERROR_REPORT_STRUCTA result;
	result.ErrorCode = GetLastError();
	result.ErrorString = WWS::ErrorString(ErrorText, result.ErrorCode);
	return  result;
}
HRESULT __fastcall WWS::AnsiToUnicode(LPCSTR aString, WSTRING& wString){
	DWORD dwError;
	// If input is null then just return the same.
	if (aString == NULL) {
		wString = L"";
		return NOERROR;
	}
	wString.resize(strlen(aString) + 1);
	// Covert to Unicode.
	if (0 == MultiByteToWideChar(CP_ACP, 0, aString, wString.size() + 1,
		(LPWSTR)wString.data(), wString.size() + 1)) {
		dwError = GetLastError();
		wString.clear();
		return HRESULT_FROM_WIN32(dwError);
	}
	return NOERROR;
} 
WWSDLL_API HRESULT __fastcall WWS::UnicodeToAnsi(LPCWSTR wString, ASTRING &aString){
	DWORD dwError;
	// If input is null then just return the same.
	if (wString == NULL){
		aString.clear();
		return NOERROR;
	}
	aString.resize(wcslen(wString) + 1);
	// Convert to ANSI.
	if (0 == WideCharToMultiByte(CP_ACP, 0, wString, (aString.size()+1), (LPSTR)aString.data(), (aString.size()+1), NULL, NULL)){
		dwError = GetLastError();
		aString.clear();
		return HRESULT_FROM_WIN32(dwError);
	}
	return NOERROR;
}