/*
HRadioButton.cpp
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

