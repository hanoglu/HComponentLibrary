/*
HLabel.cpp
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
