/*
HTextArea.cpp
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
