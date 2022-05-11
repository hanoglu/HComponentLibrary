/*
HInternalFrame.cpp
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
