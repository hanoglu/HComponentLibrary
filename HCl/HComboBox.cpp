/*
HComboBox.cpp
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
 
