/*
String.cpp
Copyright (C) 2022 Yusuf K. Hanoğlu

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
*/

#include "HCl.h"
#include "stdafx.h"

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "windows.h"
#include <string>
#include <sstream>
#include <strsafe.h>
#include <tchar.h>

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

String::String()
{
}
String::~String()
{
}
void String::print() {
	cout << this->string;
}
void String::println() {
	cout << this->string << endl;
}
String::String(LPCSTR str) {
	this->string = str;
}
String::String(std::string str) {
	this->string = str;
}
String::String(LPCWSTR str) {
	String st;
	st = str;
	this->string = st.string;
}
String::String(LPWSTR str) {
	String st;
	st = str;
	this->string = st.string;
}
String String::operator=(const String& str) {
	this->string = str.string;
	String str2 = *this;
	return str2;
}
String String::operator=(LPCSTR str) {
	this->string = str;
	String str2 = *this;
	return str2;
}
String String::operator=(std::string str) {
	this->string = str;
	String str2 = *this;
	return str2;
}
String String::operator=(LPCWSTR pwsz) {
	int cch = WideCharToMultiByte(NULL, 0, pwsz, -1, 0, 0, NULL, NULL);

	char* psz = new char[cch];

	WideCharToMultiByte(NULL, 0, pwsz, -1, psz, cch, NULL, NULL);

	std::string st(psz);
	delete[] psz;
	this->string = st;
	String str2 = *this;
	return str2;

}
String String::operator=(LPWSTR lpw) {
	wstring ws(lpw);
	const wchar_t *szlpw = ws.c_str();
	LPCWSTR pwsz = szlpw;
	int cch = WideCharToMultiByte(NULL, 0, pwsz, -1, 0, 0, NULL, NULL);

	char* psz = new char[cch];

	WideCharToMultiByte(NULL, 0, pwsz, -1, psz, cch, NULL, NULL);

	std::string st(psz);
	delete[] psz;
	this->string = st;
	String str2 = *this;
	return str2;
}
String String::operator+=(std::string str) {
	this->string = this->string + str;
	String str2 = *this;
	return str2;
}
String String::operator+=(LPCSTR str) {
	this->string = this->string + str;
	String str2 = *this;
	return str2;
}
String String::operator+=(const String& str) {
	this->string = this->string + str.string;
	String str2 = *this;
	return str2;
}
String String::operator+(const String& str) {
	String str2;
	str2.string = this->string + str.string;
	return str2;
}
String::operator LPCSTR() {
	return this->string.c_str();
}
String::operator LPCWSTR() {
	std::string s = this->string;
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	return sw;

}
String::operator std::string() {
	return this->string;
}
void String::convert(LPCWSTR pwsz) {
	int cch = WideCharToMultiByte(NULL, 0, pwsz, -1, 0, 0, NULL, NULL);

	char* psz = new char[cch];

	WideCharToMultiByte(NULL, 0, pwsz, -1, psz, cch, NULL, NULL);

	std::string st(psz);
	delete[] psz;
	this->string = st;
	return;
}
 
