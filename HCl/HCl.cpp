/*
HCl
Copyright (C) 2022 Yusuf K. Hanoğlu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "HCl.h"


#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "windows.h"
#include <string>
#include <sstream>
#include <strsafe.h>
#include <tchar.h>
#include <thread>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <Commctrl.h>


using namespace std;


LRESULT CALLBACK DefaultWindowProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI setVisibleA(LPVOID);
DWORD MAX_THREADS = 100;

int THREAD_COUT = 0;
thread thr[100];



typedef struct MyData {
	int val1;
	int val2;
}MYDATA, *PMYDATA;

HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
{
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
	SelectObject(hdcmem, hbitmap);

	int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
	for (int i = 0; i < item->rc.bottom - item->rc.top; i++)
	{
		RECT temp;
		int r, g, b;
		r = int(r1 + double(i * (r2 - r1) / item->rc.bottom - item->rc.top));
		g = int(g1 + double(i * (g2 - g1) / item->rc.bottom - item->rc.top));
		b = int(b1 + double(i * (b2 - b1) / item->rc.bottom - item->rc.top));
		Brush = CreateSolidBrush(RGB(r, g, b));
		temp.left = 0;
		temp.top = i;
		temp.right = item->rc.right - item->rc.left;
		temp.bottom = i + 1;
		FillRect(hdcmem, &temp, Brush);
		DeleteObject(Brush);
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);

	DeleteDC(hdcmem);
	DeleteObject(Brush);
	DeleteObject(hbitmap);

	return pattern;
}
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


Point::Point()
{

}
Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}
Point::~Point()
{
}




Dimension::Dimension()
{
}
Dimension::Dimension(int width, int height)
{
	this->width = width;
	this->height = height;
}
Dimension::~Dimension()
{
}


HINSTANCE hInstanceWindows;


KeyEvent::KeyEvent(HFrame *frame, char chr, MSG msg)
{
	this->component = frame;
	this->KeyCode = chr;
	this->msg = msg;
}
KeyEvent::~KeyEvent()
{
}
char KeyEvent::getKeyChar() {
	return KeyCode;
};
HFrame* KeyEvent::getComponent() {
	return component;
}



ActionEvent::ActionEvent(Component *frame, char chr, MSG msg)
{
	this->component = frame;
	this->KeyCode = chr;
	this->msg = msg;
}
ActionEvent::ActionEvent(Component *frame)
{
	this->component = frame;
}
ActionEvent::~ActionEvent()
{
}
Component* ActionEvent::getComponent() {
	return component;
}



void Component::setEnabled(bool enabled) {
	Enable = enabled;
	EnableWindow(this->hwnd, enabled);

};
bool Component::isEnabled() {
	return  Enable;
}
ButtonGroup* Component::getButtonGroup() {
	return buttongrp;
}
void Component::setButtonGroup(ButtonGroup* buttonGroup) {
	this->buttongrp = buttonGroup;
}

//****************************************BUTTON************************************************


LRESULT CALLBACK DefaultWindowProcForButton(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	//msg_dev(toString(uMsg));

	cout << uMsg << endl;
	switch (uMsg) {

	case WM_MOUSEMOVE:
		SetCursor(LoadCursor(NULL, IDC_HAND));
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_WINDOW + 100);
		EndPaint(hwnd, &ps);
	}return 0;

	case WM_LBUTTONDOWN:
		cout << "Clicked" << endl;



		break;

	default:
		DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
};

HButton::HButton()
{
	this->Type = "HBUTTON";
}
HButton::HButton(LPCSTR title)
{
	this->title = title;
	this->Type = "HBUTTON";
}
HButton::~HButton()
{
}
bool HButton::MakeButton(HWND hwndFrame) {

	this->hwnd = CreateWindowEx(
		0,
		L"BUTTON",
		NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);



	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	SetWindowTextA(this->hwnd, this->title);
	//SetWindowLong(this->hwnd, GWL_WNDPROC, (LONG_PTR) &DefaultWindowProcForButton);

	return true;
}
void HButton::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HButton::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HButton::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}

void HButton::addActionListener(int ActionListener(ActionEvent)) {
	this->ActionListener = ActionListener;
	this->ActionListenerAdded = true;
}


Point HButton::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HButton::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HButton::getText() {
	return this->title;
}


//********************************************CHECK BOX***********************************************


HCheckBox::HCheckBox()
{
	this->Type = "HCHECKBOX";

}
HCheckBox::HCheckBox(LPCSTR title)
{
	this->title = title;
	this->Type = "HCHECKBOX";
}
HCheckBox::~HCheckBox()
{
}
bool HCheckBox::MakeButton(HWND hwndFrame) {
	this->hwnd = CreateWindowEx(
		0,
		L"BUTTON",
		NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_CHECKBOX,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);
	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	SetWindowTextA(this->hwnd, this->title);
	return true;
}
void HCheckBox::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HCheckBox::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HCheckBox::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}
Point HCheckBox::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HCheckBox::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HCheckBox::getText() {
	return this->title;
}
void HCheckBox::addActionListener(int ActionListener(ActionEvent)) {
	this->ActionListener = ActionListener;
	this->ActionListenerAdded = true;
}
bool HCheckBox::isChecked() {
	return this->Checked;
}

//********************************************RADIO BUTTON***********************************************


HRadioButton::HRadioButton()
{
	this->Type = "HRADIOBUTTON";

}
HRadioButton::HRadioButton(LPCSTR title)
{
	this->title = title;
	this->Type = "HRADIOBUTTON";

}
HRadioButton::~HRadioButton()
{
}
bool HRadioButton::MakeButton(HWND hwndFrame) {
	this->hwnd = CreateWindowEx(
		0,
		L"BUTTON",
		NULL,
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_RADIOBUTTON,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);
	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	SetWindowTextA(this->hwnd, this->title);
	return true;
}
void HRadioButton::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HRadioButton::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HRadioButton::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}
Point HRadioButton::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HRadioButton::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HRadioButton::getText() {
	return this->title;
}
void HRadioButton::addActionListener(int ActionListener(ActionEvent)) {
	this->ActionListener = ActionListener;
	this->ActionListenerAdded = true;
}
bool HRadioButton::isChecked() {
	return this->Checked;
}
void HRadioButton::setChecked(bool checked) {
	if (checked)
		SendMessage(this->hwnd, BM_SETCHECK, BST_CHECKED, 0);
	else
		SendMessage(this->hwnd, BM_SETCHECK, BST_UNCHECKED, 0);

	this->Checked = checked;
}


//*********************************************BUTTON GROUP*******************************************


ButtonGroup::ButtonGroup()
{
}
ButtonGroup::~ButtonGroup()
{
}
void ButtonGroup::add(HRadioButton* RadioButton) {
	this->hbutton[this->BUTTON_COUT] = RadioButton;
	this->hbutton[this->BUTTON_COUT]->setButtonGroup(this);
	this->BUTTON_COUT++;
}
void ButtonGroup::AllUnsellected() {
	for (int i = 0; i < this->BUTTON_COUT; i++) {
		this->hbutton[i]->setChecked(false);
	}
}



//*********************************************TEXT FIELD******************************************************************************************


HTextField::HTextField()
{
	this->Type = "HTEXTFIELD";

}
HTextField::HTextField(LPCSTR title)
{
	this->title = title;
	this->Type = "HTEXTFIELD";
}
HTextField::~HTextField()
{
}
bool HTextField::MakeButton(HWND hwndFrame) {
	this->hwnd = CreateWindowEx(
		0,
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_BORDER | WS_CHILD | WS_TABSTOP,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);

	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	SetWindowTextA(this->hwnd, this->title);
	return true;
}
void HTextField::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HTextField::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HTextField::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}
Point HTextField::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HTextField::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HTextField::getText() {

	//TCHAR txt[1024];
	//GetWindowText(this->hwnd, txt, sizeof(txt));
	//wchar_t txt[1024];
	//GetWindowText(this->hwnd, txt, sizeof(txt));

	DWORD dwTextLength = GetWindowTextLength(this->hwnd) + 1;

	if (dwTextLength > 0)

	{

		DWORD dwBufferSize = dwTextLength + 1;

		LPWSTR pszText = (LPWSTR)GlobalAlloc(GPTR, dwBufferSize * sizeof(LPWSTR));

		if (pszText != NULL)

		{

			GetWindowText(this->hwnd, pszText, dwTextLength);

			SetWindowText(hwnd, pszText);
			String str = pszText;


			GlobalFree(pszText);
			return str;


		}
		String str = "NULL";
		return str;
	}


	String str = "";
	return str;
}
void HTextField::addActionListener(int ActionListener(ActionEvent)) {
	this->ActionListener = ActionListener;
	this->ActionListenerAdded = true;
}



//*********************************************TEXT AREA**************************************************************************************



HTextArea::HTextArea()
{
	this->Type = "HTEXTAREA";

}
HTextArea::HTextArea(LPCSTR title)
{
	this->title = title;
	this->Type = "HTEXTAREA";
}
HTextArea::~HTextArea()
{
}
bool HTextArea::MakeButton(HWND hwndFrame) {
	this->hwnd = CreateWindowEx(
		0,
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_BORDER | WS_CHILD | WS_TABSTOP |
		ES_LEFT | ES_AUTOVSCROLL | ES_AUTOHSCROLL |
		ES_MULTILINE | WS_VSCROLL | WS_HSCROLL,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);

	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	SetWindowTextA(this->hwnd, this->title);
	return true;
}
void HTextArea::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HTextArea::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HTextArea::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}
Point HTextArea::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HTextArea::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HTextArea::getText() {

	//TCHAR txt[1024];
	//GetWindowText(this->hwnd, txt, sizeof(txt));
	//wchar_t txt[1024];
	//GetWindowText(this->hwnd, txt, sizeof(txt));

	DWORD dwTextLength = GetWindowTextLength(this->hwnd) + 1;

	if (dwTextLength > 0)

	{

		DWORD dwBufferSize = dwTextLength + 1;

		LPWSTR pszText = (LPWSTR)GlobalAlloc(GPTR, dwBufferSize * sizeof(LPWSTR));

		if (pszText != NULL)

		{

			GetWindowText(this->hwnd, pszText, dwTextLength);

			SetWindowText(hwnd, pszText);
			String str = pszText;


			GlobalFree(pszText);
			return str;


		}
		String str = "NULL";
		return str;
	}


	String str = "";
	return str;
}
void HTextArea::addActionListener(int ActionListener(ActionEvent)) {
	this->ActionListener = ActionListener;
	this->ActionListenerAdded = true;
}






//*************************************************LABEL******************************************************************************************


HLabel::HLabel()
{
	this->Type = "HLABEL";
}
HLabel::HLabel(LPCSTR title)
{
	this->title = title;
	this->Type = "HLABEL";
}
HLabel::~HLabel()
{
}
bool HLabel::MakeButton(HWND hwndFrame) {

	this->hwnd = CreateWindowEx(
		0,
		L"STATIC",
		NULL,
		WS_VISIBLE | WS_CHILD,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);



	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	SetWindowTextA(this->hwnd, this->title);
	//SetWindowLong(this->hwnd, GWL_WNDPROC, (LONG_PTR) &DefaultWindowProcForButton);

	return true;
}
void HLabel::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HLabel::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HLabel::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)&rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}

Point HLabel::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HLabel::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HLabel::getText() {
	return this->title;
}

//*************************************************COMBOBOX******************************************************************************************



HComboBox::HComboBox()
{
	for (int i = 0; i < 200; i++)
		this->items[i] = "";
	this->title = "";
	this->Type = "HCOMBOBOX";
}

HComboBox::HComboBox(String list[],int length)
{
	for (int i = 0; i < 200; i++)
		this->items[i] = "";
	this->title = "";
	this->Type = "HCOMBOBOX";

			

		this->items_cout = length;
		for (int i = 0; i < length && i < 200; i++) {
			try {
				this->items[i] = "";
				this->items[i].string = list[i].string;
			}
			catch (int e) {

			}
		}
	

	

	
}
HComboBox::~HComboBox()
{
}
bool HComboBox::MakeButton(HWND hwndFrame) {

	this->hwnd = CreateWindowEx(
		0,
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
		this->x, this->y, this->wd, this->ht,
		hwndFrame,
		NULL,
		NULL,
		NULL
	);
	



	if (items_cout >-1) {
	
		
		
		for (int i = 0; i < this->items_cout; i++) {
			vector<TCHAR> buffer(items[i].string.begin(), items[i].string.end());
			buffer.push_back(_T('\0'));
			TCHAR* p = &buffer[0];
			
			SendMessage(this->hwnd, CB_ADDSTRING, 0, (LPARAM)p);
		}
			

		SendMessage(this->hwnd, CB_SETCURSEL, 0, 0);
	}

	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;
	//SetWindowTextA(this->hwnd, this->title);
	//SetWindowLong(this->hwnd, GWL_WNDPROC, (LONG_PTR) &DefaultWindowProcForButton);




	return true;
}

void HComboBox::setList(String list[], int length) {
	this->items_cout = length;
	for (int i = 0; i < length && i < 200; i++) {
		try {
			this->items[i] = "";
			this->items[i].string = list[i].string;
		}
		catch (int e) {

		}
	}
	if (this->ButtonCreated) {
		removeAllItems();
		if (items_cout > -1) {



			for (int i = 0; i < this->items_cout; i++) {
				vector<TCHAR> buffer(items[i].string.begin(), items[i].string.end());
				buffer.push_back(_T('\0'));
				TCHAR* p = &buffer[0];

				SendMessage(this->hwnd, CB_ADDSTRING, 0, (LPARAM)p);
			}


			SendMessage(this->hwnd, CB_SETCURSEL, 0, 0);
		}

	}
}
void HComboBox::removeAllItems() {

	if(ButtonCreated)
		SendMessage(this->hwnd, CB_RESETCONTENT, 0, 0);
	
	for(int i=0;i<items_cout;i++)
		this->items[i].string = "";
		this->items_cout = -1;



}
void HComboBox::addItem(String item) {

	this->items[items_cout] = "";
	this->items[items_cout].string = item.string;
	this->items_cout++;

	if (ButtonCreated) {
		vector<TCHAR> buffer(item.string.begin(), item.string.end());
		buffer.push_back(_T('\0'));
		TCHAR* p = &buffer[0];

		SendMessage(this->hwnd, CB_ADDSTRING, 0, (LPARAM)p);
	}
}
void HComboBox::removeItemAt(int zerobasedindex) {


	for (int i = zerobasedindex; i < this->items_cout; i++) {

		this->items[i].string = this->items[i + 1].string;
	}

	this->items_cout--;


	if (ButtonCreated) {
		SendMessage(this->hwnd, CB_DELETESTRING, zerobasedindex, 0);
	}





}
bool HComboBox::removeItem(String item) {
	int index = -1;
	for (int i = 0; i < 200; i++) {
		if (strcmp(this->items[i].string.c_str(), item.string.c_str())) {
			index = i;
			break;
		}

	}
	if (index != -1) {
		this->removeItemAt(index);
		return true;
	}
	else
		return false;
}
int HComboBox::getItemCount() {
	return (this->items_cout+1);
}
String HComboBox::getItemAt(int zerobasedindex) {
	if (zerobasedindex < 200)
		return this->items[zerobasedindex];
	else
		return "null";
}
int HComboBox::getSelectedIndex() {
	int index = SendMessage(this->hwnd, CB_GETCURSEL, 0, 0);
	return index;
}
String HComboBox::getSelectedItem() {

	return this->items[SendMessage(this->hwnd, CB_GETCURSEL, 0, 0)];


}


void HComboBox::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)& rect);
		this->wd = rect.right - rect.left;
		this->ht = rect.bottom - rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}

}
void HComboBox::setText(LPCSTR title) {
	this->title = title;
	if (ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
	}
}
void HComboBox::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (ButtonCreated) {
		RECT rect;
		GetWindowRect(hwnd, (LPRECT)& rect);
		this->x = rect.left;
		this->y = rect.top;
		SetWindowPos(this->hwnd, NULL, this->x, this->y, this->wd, this->ht, NULL);
	}
}

void HComboBox::addActionListener(int ActionListener(ActionEvent)) {
	this->ActionListener = ActionListener;
	this->ActionListenerAdded = true;
}


Point HComboBox::getLocation() {
	Point point = Point(this->x, this->y);
	return point;
}
Dimension HComboBox::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
String HComboBox::getText() {
	return this->title;
}



//**********************************************PANEL*************************************************************************************




HPanel::HPanel(LPCSTR title)//PCWSTR title
{
	this->Type = "HPANEL";
	this->title = title;
	setTitleBool = true;
	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;
}
HPanel::HPanel()
{
	this->Type = "HPANEL";
	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;

}
HPanel::~HPanel()
{
}
bool HPanel::addWindowProc(HINSTANCE hInstance, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM)) {
	if (!this->WindowProcAdded) {
		this->hInstance = hInstance;
		this->wc.lpszClassName = this->CLASS_NAME;
		this->wc.hInstance = this->hInstance;
		//RegisterClass(&this->wc);
		this->wc.lpfnWndProc = WindowProc;

		RegisterClass(&this->wc);
		this->WindowProcAdded = true;

		return true;
	}
	else
	{
		return false;
	}
}
void HPanel::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	this->setLocationBool = true;
}
void HPanel::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	setSizeBool = true;
}
void HPanel::setTitle(LPCSTR title) {
	this->title = title;
	this->setTitleBool = true;
}
bool HPanel::setDefaultCloseOperation(int operation) {
	if (operation > 9 && operation < 14) {
		this->CloseOperation = operation;
		return true;
	}
	return false;
}
int HPanel::getDefaultCloseOperation() {
	return this->CloseOperation;
}
Point HPanel::getLocation() {
	Point point = Point(this->x, this->y);

	return point;
}
LPCSTR HPanel::getTitle() {
	return title;
}
Dimension HPanel::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
void HPanel::add(Component *button) {
	this->hbutton[BUTTON_COUT] = button;
	this->hbutton[BUTTON_COUT]->ID_ON_PANEL = BUTTON_COUT;
	BUTTON_COUT++;
}
void HPanel::remove(Component *component) {

	if (component->ID_ON_PANEL >= 0) {
		if (this->hbutton[component->ID_ON_PANEL] == component) {
			ShowWindow(component->hwnd, SW_HIDE);
			for (int i = component->ID_ON_PANEL; i < (this->BUTTON_COUT - 1); i++) {
				this->hbutton[i] = this->hbutton[i + 1];
				this->hbutton[i]->ID_ON_PANEL = i;
			}
			this->hbutton[BUTTON_COUT - 1] = NULL;
			BUTTON_COUT -= 1;
			if (BUTTON_ADDED > 0)
				BUTTON_ADDED -= 1;

		}
	}
}
void HPanel::addKeyListener(int KeyListener(KeyEvent)) {
	this->KeyListener = KeyListener;
	this->KeyListenerAdded = true;
}
bool HPanel::MakeButton(HWND hwndFrame) {

	this->wc.lpszClassName = this->CLASS_NAME;
	this->wc.hInstance = this->hInstance;
	//RegisterClass(&this->wc);
	this->wc.lpfnWndProc = DefaultWindowProc;

	this->wc.style = CS_HREDRAW | CS_VREDRAW;
	this->wc.cbClsExtra = 0;
	this->wc.cbWndExtra = sizeof(long);
	this->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	this->wc.lpszMenuName = NULL;


	RegisterClass(&this->wc);


	this->hwnd = CreateWindow(
		this->CLASS_NAME,
		TEXT(""),
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
		this->x,
		this->y,
		this->wd,
		this->ht,
		hwndFrame,
		NULL,
		hInstance,
		NULL);


	for (int i = 0; i < BUTTON_COUT; i++) {
		this->hbutton[i]->MakeButton(this->hwnd);
		this->BUTTON_ADDED++;
	}

	SetTimer(hwnd,             // handle to main window 
		0,            // timer identifier 
		100,                 // 100-msecond interval 
		(TIMERPROC)NULL);     // no timer callback 

	ShowWindow(this->hwnd, 1);
	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;


	return true;
}

//**************************************************INTERNAL FRAME************************************************************



HInternalFrame::HInternalFrame(LPCSTR title)//PCWSTR title
{
	this->Type = "HINTERNALFRAME";
	this->title = title;
	setTitleBool = true;
	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;
}
HInternalFrame::HInternalFrame()
{
	this->Type = "HINTERNALFRAME";

	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;

}
HInternalFrame::~HInternalFrame()
{
}
bool HInternalFrame::addWindowProc(HINSTANCE hInstance, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM)) {
	if (!this->WindowProcAdded) {
		this->hInstance = hInstance;
		this->wc.lpszClassName = this->CLASS_NAME;
		this->wc.hInstance = this->hInstance;
		//RegisterClass(&this->wc);
		this->wc.lpfnWndProc = WindowProc;

		RegisterClass(&this->wc);
		this->WindowProcAdded = true;

		return true;
	}
	else
	{
		return false;
	}
}
void HInternalFrame::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	if (this->ButtonCreated)
		this->setLocationBool = true;

}
void HInternalFrame::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	if (this->ButtonCreated)
		setSizeBool = true;
}
void HInternalFrame::setTitle(LPCSTR title) {
	this->title = title;
	this->setTitleBool = true;
	if (this->ButtonCreated) {
		SetWindowTextA(this->hwnd, this->title);
		this->setTitleBool = false;
	}
}
bool HInternalFrame::setDefaultCloseOperation(int operation) {
	if (operation > 9 && operation < 14) {
		this->CloseOperation = operation;
		return true;
	}
	return false;
}
int HInternalFrame::getDefaultCloseOperation() {
	return this->CloseOperation;
}
Point HInternalFrame::getLocation() {
	Point point = Point(this->x, this->y);

	return point;
}
Point HInternalFrame::getLocationOnScreen() {
	Point point = Point(this->xsc, this->ysc);

	return point;
}

LPCSTR HInternalFrame::getTitle() {
	return title;
}
Dimension HInternalFrame::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
void HInternalFrame::add(Component *button) {
	this->hbutton[BUTTON_COUT] = button;
	this->hbutton[BUTTON_COUT]->ID_ON_PANEL = BUTTON_COUT;
	BUTTON_COUT++;
}
void HInternalFrame::remove(Component *component) {


	if (component->ID_ON_PANEL >= 0) {
		if (this->hbutton[component->ID_ON_PANEL] == component) {
			ShowWindow(component->hwnd, SW_HIDE);
			for (int i = component->ID_ON_PANEL; i < (this->BUTTON_COUT - 1); i++) {
				this->hbutton[i] = this->hbutton[i + 1];
				this->hbutton[i]->ID_ON_PANEL = i;
			}
			this->hbutton[BUTTON_COUT - 1] = NULL;
			BUTTON_COUT -= 1;
			if (BUTTON_ADDED > 0)
				BUTTON_ADDED -= 1;

		}
	}
}
void HInternalFrame::addKeyListener(int KeyListener(KeyEvent)) {
	this->KeyListener = KeyListener;
	this->KeyListenerAdded = true;
}
bool HInternalFrame::MakeButton(HWND hwndFrame) {

	this->wc.lpszClassName = this->CLASS_NAME;
	this->wc.hInstance = this->hInstance;
	//RegisterClass(&this->wc);
	this->wc.lpfnWndProc = DefaultWindowProc;

	this->wc.style = CS_HREDRAW | CS_VREDRAW;
	this->wc.cbClsExtra = 0;
	this->wc.cbWndExtra = sizeof(long);
	this->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	this->wc.lpszMenuName = NULL;


	RegisterClass(&this->wc);


	this->hwnd = CreateWindow(
		this->CLASS_NAME,
		NULL,
		WS_CHILDWINDOW | WS_VISIBLE | WS_CAPTION
		| WS_SYSMENU | WS_THICKFRAME | WS_TABSTOP
		| WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPSIBLINGS | WS_EX_CONTROLPARENT,
		this->x,
		this->y,
		this->wd,
		this->ht,
		hwndFrame,
		NULL,
		this->hInstance,
		NULL);


	SetWindowTextA(this->hwnd, this->title);




	for (int i = 0; i < BUTTON_COUT; i++) {
		this->hbutton[i]->MakeButton(this->hwnd);
		this->BUTTON_ADDED++;
	}

	SetTimer(hwnd,             // handle to main window 
		0,            // timer identifier 
		100,                 // 100-msecond interval 
		(TIMERPROC)NULL);     // no timer callback 

	ShowWindow(this->hwnd, 1);
	SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);
	ButtonCreated = true;


	return true;
}



//**********************************************FRAME****************************************************************************







void setVisibleB(HFrame*);


HFrame *frame_visible_ptr;
HFrame::HFrame(LPCSTR title)//PCWSTR title
{
	this->Type = "HFRAME";

	this->title = title;
	setTitleBool = true;

	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;
}
HFrame::HFrame()
{
	this->Type = "HFRAME";
	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;

}
HFrame::~HFrame()
{
}
bool WINAPI HFrame::setVisible(bool visible) {
	if (visible) {


		/*
				pDataArray = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));//HEAP_ZERO_MEMORY

				frame_visible_ptr = this;

				HANDLE thr[1];
				thr[0] = CreateThread(
					NULL,
					0,
					setVisibleA,
					pDataArray,
					0,
					&dwThreadId
				);

				if (thr[0] == NULL)
				{
					ExitProcess(3);
				}
			*/
			/*
				WaitForMultipleObjects(MAX_THREADS, thr, TRUE, INFINITE);

				for (int i = 0; i < MAX_THREADS; i++)
				{
					CloseHandle(thr[i]);
					if (pDataArray != NULL)
					{
						HeapFree(GetProcessHeap(), 0, pDataArray);
						pDataArray = NULL;    // Ensure address is not reused.
					}
				}
			*/

		PMYDATA pDataArray;
		DWORD dwThreadId;

		pDataArray = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MyData));//HEAP_ZERO_MEMORY

		frame_visible_ptr = this;

		HANDLE han = CreateThread(
			NULL,
			0,
			setVisibleA,
			pDataArray,
			0,
			&dwThreadId
		);
		if (han != NULL)
			THREAD_COUT++;

		Sleep(100);
		/*
		frame_visible_ptr = this;
		thr[THREAD_COUT] = thread(&setVisibleB, this);
		THREAD_COUT++;
		*/
	}
	else {
		return ShowWindow(this->hwnd, 0);
	}
}
bool HFrame::setVisible()
{
	if (this->WindowProcAdded || true) {



		this->wc.lpszClassName = this->CLASS_NAME;
		this->wc.hInstance = this->hInstance;
		//RegisterClass(&this->wc);
		this->wc.lpfnWndProc = DefaultWindowProc;

		this->wc.style = CS_HREDRAW | CS_VREDRAW;
		this->wc.cbClsExtra = 0;
		this->wc.cbWndExtra = sizeof(long);
		this->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		this->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		this->wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		this->wc.lpszMenuName = NULL;


		RegisterClass(&this->wc);


		this->hwnd = CreateWindowEx(
			0,
			this->CLASS_NAME,
			NULL,//this->title,
			WS_OVERLAPPEDWINDOW,
			this->x, this->y, this->wd, this->ht,
			NULL,
			NULL,
			this->hInstance,
			NULL
		);

		SetWindowTextA(this->hwnd, this->title);


		for (int i = 0; i < BUTTON_COUT; i++) {
			this->hbutton[i]->MakeButton(this->hwnd);
			this->BUTTON_ADDED++;
		}


		SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);



		SetTimer(hwnd,             // handle to main window 
			0,            // timer identifier 
			100,                 // 100-msecond interval 
			(TIMERPROC)NULL);     // no timer callback 

		ShowWindow(this->hwnd, 1);
		MSG msg = {};
		while (GetMessage(&msg, 0, NULL, NULL)) {
			if (msg.message != WM_TIMER) {
				//cout << msg.message << endl;
			}
			if (msg.message == WM_KEYDOWN) {
				if (this->KeyListenerAdded) {

					const char chr = LOWORD(msg.wParam);
					KeyEvent ke = KeyEvent(this, chr, msg);
					KeyListener(ke);
				}

			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		THREAD_COUT--;
		//return true;



	//return false;

	}
	else
		return false;
}
bool HFrame::addWindowProc(HINSTANCE hInstance, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM)) {
	if (!this->WindowProcAdded) {
		this->hInstance = hInstance;
		this->wc.lpszClassName = this->CLASS_NAME;
		this->wc.hInstance = this->hInstance;
		//RegisterClass(&this->wc);
		this->wc.lpfnWndProc = WindowProc;

		RegisterClass(&this->wc);
		this->WindowProcAdded = true;

		return true;
	}
	else
	{
		return false;
	}
}
void HFrame::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	this->setLocationBool = true;
}
void HFrame::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	setSizeBool = true;
}
void HFrame::setTitle(LPCSTR title) {
	this->title = title;
	this->setTitleBool = true;
	SetWindowTextA(this->hwnd, this->title);
	this->setTitleBool = false;

}
DWORD WINAPI setVisibleA(LPVOID lpParam) {
	HFrame *hfr = frame_visible_ptr;
	//MessageBox(NULL, NULL, NULL, NULL);
	hfr->setVisible();
	return 0;
}
void setVisibleB(HFrame *fr) {
	fr->setVisible();
}

bool HFrame::setDefaultCloseOperation(int operation) {
	if (operation > 9 && operation < 14) {
		this->CloseOperation = operation;
		return true;
	}
	return false;
}
int HFrame::getDefaultCloseOperation() {
	return this->CloseOperation;
}
Point HFrame::getLocation() {
	Point point = Point(this->x, this->y);

	return point;
}
LPCSTR HFrame::getTitle() {
	return title;
}
Dimension HFrame::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
void HFrame::add(Component *button) {
	this->hbutton[BUTTON_COUT] = button;
	this->hbutton[BUTTON_COUT]->ID_ON_PANEL = BUTTON_COUT;
	BUTTON_COUT++;
}
void HFrame::remove(Component *component) {

	if (component->ID_ON_PANEL >= 0) {
		if (this->hbutton[component->ID_ON_PANEL] == component) {
			ShowWindow(component->hwnd, SW_HIDE);
			for (int i = component->ID_ON_PANEL; i < (this->BUTTON_COUT - 1); i++) {
				this->hbutton[i] = this->hbutton[i + 1];
				this->hbutton[i]->ID_ON_PANEL = i;
			}
			this->hbutton[BUTTON_COUT - 1] = NULL;
			BUTTON_COUT -= 1;
			if (BUTTON_ADDED > 0)
				BUTTON_ADDED -= 1;

		}
	}
}
void HFrame::addKeyListener(int KeyListener(KeyEvent)) {
	this->KeyListener = KeyListener;
	this->KeyListenerAdded = true;
}

//std::error_code DefaultWindowProc(std::nothrow_t) noexcept;

static COLORREF bgColor = RGB(0, 255, 0);






LRESULT CALLBACK DefaultWindowProc(HWND hWin, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static HBRUSH defaultbrush = NULL;
	static HBRUSH hotbrush = NULL;
	static HBRUSH selectbrush = NULL;
	static HBRUSH push_uncheckedbrush = NULL;
	static HBRUSH push_checkedbrush = NULL;
	static HBRUSH push_hotbrush1 = NULL;
	static HBRUSH push_hotbrush2 = NULL;



	switch (uMsg) {
	case WM_TIMER: {

		LONG_PTR lpUserData = GetWindowLongPtr(hWin, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		if (ObjectPtr->Type == "HFRAME") {

			if (ObjectPtr->setSizeBool) {
				ObjectPtr->setSizeBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				ObjectPtr->x = rect.left; ObjectPtr->y = rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}
			else if (ObjectPtr->setLocationBool) {
				ObjectPtr->setLocationBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				ObjectPtr->wd = rect.right - rect.left;
				ObjectPtr->ht = rect.bottom - rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}


			RECT rect;
			GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
			ObjectPtr->wd = rect.right - rect.left;
			ObjectPtr->ht = rect.bottom - rect.top;
			ObjectPtr->x = rect.left;
			ObjectPtr->y = rect.top;
		}
		if (ObjectPtr->Type == "HINTERNALFRAME") {

			if (ObjectPtr->setSizeBool) {
				ObjectPtr->setSizeBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				MapWindowPoints(HWND_DESKTOP, GetParent(ObjectPtr->hwnd), (LPPOINT)&rect, 2);
				ObjectPtr->x = rect.left; ObjectPtr->y = rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}
			else if (ObjectPtr->setLocationBool) {
				ObjectPtr->setLocationBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				MapWindowPoints(HWND_DESKTOP, GetParent(ObjectPtr->hwnd), (LPPOINT)&rect, 2);
				ObjectPtr->wd = rect.right - rect.left;
				ObjectPtr->ht = rect.bottom - rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}

			RECT rect;
			GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
			ObjectPtr->xsc = rect.left;
			ObjectPtr->ysc = rect.top;

			MapWindowPoints(HWND_DESKTOP, GetParent(ObjectPtr->hwnd), (LPPOINT)&rect, 2);
			ObjectPtr->wd = rect.right - rect.left;
			ObjectPtr->ht = rect.bottom - rect.top;
			ObjectPtr->x = rect.left;
			ObjectPtr->y = rect.top;

		}
		if (ObjectPtr->BUTTON_ADDED < ObjectPtr->BUTTON_COUT) {

			ObjectPtr->hbutton[ObjectPtr->BUTTON_ADDED]->MakeButton(ObjectPtr->hwnd);
			ObjectPtr->BUTTON_ADDED++;

		}

	}
				   return 0;
	case WM_DESTROY: {

		LONG_PTR lpUserData = GetWindowLongPtr(hWin, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		int closeOperation = ObjectPtr->getDefaultCloseOperation();

		if (closeOperation == 10)
			PostQuitMessage(0);
		else if (closeOperation == 11) {
			ObjectPtr->setVisible(false);
			break;
		}
		else if (closeOperation == 12) {}
		else if (closeOperation == 13) {
			break;
		}

	}
					 return 0;
	case WM_CLOSE: {

		LONG_PTR lpUserData = GetWindowLongPtr(hWin, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		int closeOperation = ObjectPtr->getDefaultCloseOperation();

		if (closeOperation == 10)
			PostQuitMessage(0);
		else if (closeOperation == 11) {
			ObjectPtr->setVisible(false);
			break;
		}
		else if (closeOperation == 12) {}
		else if (closeOperation == 13) {
			break;
		}

		return DefWindowProc(hWin, uMsg, wParam, lParam);

	}
				   return 0;



	case WM_LBUTTONDOWN: {



	}
						 return 0;

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWin, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_WINDOW + 100);
		EndPaint(hWin, &ps);

	}return 0;


	case WM_COMMAND: {
		//cout << wParam << endl;

		LONG_PTR lpUserData = GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		if (ObjectPtr->Type == "HCHECKBOX") {
			if (!ObjectPtr->Checked) {
				SendMessage(ObjectPtr->hwnd, BM_SETCHECK, BST_CHECKED, 0);
				ObjectPtr->Checked = !ObjectPtr->Checked;
			}
			else {
				SendMessage(ObjectPtr->hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
				ObjectPtr->Checked = !ObjectPtr->Checked;
			}
		}
		if (ObjectPtr->Type == "HRADIOBUTTON") {

			if (ObjectPtr->getButtonGroup() != NULL) {
				ObjectPtr->getButtonGroup()->AllUnsellected();
			}

			SendMessage(ObjectPtr->hwnd, BM_SETCHECK, BST_CHECKED, 0);
			ObjectPtr->Checked = 1;

		}
		if (ObjectPtr->Type == "HCOMBOBOX") {
		
			
		
		
		}


		if (ObjectPtr->ActionListenerAdded&&ObjectPtr->isEnabled()) {
			ActionEvent ke = ActionEvent(NULL);
			ObjectPtr->ActionListener(ke);
		}
		




		//if((HWND)lParam){}
		//HButton btn = &GetWindowLong((HWND)lParam, GWL_USERDATA);
		//cout << hWin << endl;

	}return 0;

	case WM_CTLCOLORBTN: {


		LONG_PTR lpUserData = GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		/*DWORD button_id = (DWORD)GetMenu((HWND)lParam);
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		return (LRESULT)brush;*/

		RECT crect;
		HBRUSH brush;
		COLORREF background_color = RGB(255, 0, 0);
		HDC hdc = (HDC)wParam;
		HWND button_handle = (HWND)lParam;

		GetClientRect(button_handle, &crect);
		SetBkColor(hdc, background_color);
		SetTextColor(hdc, RGB(255, 255, 255));


		std::wstring stemp = s2ws(ObjectPtr->getText().string);
		LPCWSTR result = stemp.c_str();

		DrawText(hdc, result, ObjectPtr->getText().string.size(), &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		brush = CreateSolidBrush(background_color);

		return (HRESULT)brush;



		} break;

	case WM_DRAWITEM: {

		/*
		const DRAWITEMSTRUCT& dis = *(DRAWITEMSTRUCT*)lParam;
		if (dis.itemAction & ODA_DRAWENTIRE) {
			// Render the control
			// ...

			// If the control has the input focus...
			if (dis.itemState & ODS_FOCUS) {
				// Render the focus rectangle
				DrawFocusRect(dis.hDC, &dis.rcItem);
			}
		}
		*/

		/*
		DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
		RECT rect;

		LONG_PTR lpUserData = GetWindowLongPtr(dis->hwndItem, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;




		GetClientRect(dis->hwndItem, &rect); // get the size of the button.

		SetBkColor(dis->hDC, RGB(255, 0, 0));         // set text background to match button’s background.
		SetTextColor(dis->hDC, RGB(255, 255, 255));

		std::wstring stemp = s2ws(ObjectPtr->getText().string);
		LPCWSTR result = stemp.c_str();

		DrawText(dis->hDC, result, ObjectPtr->getText().string.size(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		*/



		//DrawText(dis->hDC, L"BTN", _countof(L"BTN") - 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	} return 0;
	/*case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (true)//some_item->code == NM_CUSTOMDRAW
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

			if (item->uItemState & CDIS_SELECTED)
			{
				//Select our color when the button is selected
				if (selectbrush == NULL)
					selectbrush = CreateGradientBrush(RGB(180, 0, 0), RGB(255, 180, 0), item);

				//Create pen for button border
				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				//Select our brush into hDC
				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, selectbrush);

				//If you want rounded button, then use this, otherwise use FillRect().
				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				//Clean up
				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				//Now, I don't want to do anything else myself (draw text) so I use this value for return:
				return CDRF_DODEFAULT;
				//Let's say I wanted to draw text and stuff, then I would have to do it before return with
				//DrawText() or other function and return CDRF_SKIPDEFAULT
			}
			else
			{
				if (item->uItemState & CDIS_HOT) //Our mouse is over the button
				{
					//Select our color when the mouse hovers our button
					if (hotbrush == NULL)
						hotbrush = CreateGradientBrush(RGB(255, 230, 0), RGB(245, 0, 0), item);

					HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

					HGDIOBJ old_pen = SelectObject(item->hdc, pen);
					HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

					RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

					SelectObject(item->hdc, old_pen);
					SelectObject(item->hdc, old_brush);
					DeleteObject(pen);

					return CDRF_DODEFAULT;
				}

				//Select our color when our button is doing nothing
				if (defaultbrush == NULL)
					defaultbrush = CreateGradientBrush(RGB(255, 180, 0), RGB(180, 0, 0), item);

				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}
		}
		return CDRF_DODEFAULT;



	}
	break;
	*/
	default:
		return DefWindowProc(hWin, uMsg, wParam, lParam);
	}

}



bool WaitAll() {
	/*for (int i=THREAD_COUT-1; i >= 0; i--) {
		thr[i].join();
	}*/
	while (THREAD_COUT) {

	}

	return true;
}
void ReportHINSTANCE(HINSTANCE hInstance) {
	hInstanceWindows = hInstance;

}
