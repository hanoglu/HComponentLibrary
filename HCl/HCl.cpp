/*
HCl.cpp
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
#include <commctrl.h>
// #include <Commctrl.h>

using namespace std;

HFrame *frame_visible_ptr;

DWORD MAX_THREADS = 100;

int THREAD_COUT = 0;
thread thr[100];

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

DWORD WINAPI setVisibleA(LPVOID lpParam) {
	HFrame *hfr = frame_visible_ptr;
	//MessageBox(NULL, NULL, NULL, NULL);
	hfr->setVisible();
	return 0;
}
void setVisibleB(HFrame *fr) {
	fr->setVisible();
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
