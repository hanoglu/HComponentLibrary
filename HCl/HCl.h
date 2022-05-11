/*
HCl.h
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
#pragma once

#ifdef HCL_EXPORTS
#define HCL_API __declspec(dllexport)
#else
#define HCL_API __declspec(dllimport)
#endif

#include "windows.h"
#include <string>
#include <sstream>
#include <tchar.h>
#include <strsafe.h>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;

class HFrame;
class Component;
class HCheckBox;
class HRadioButton;
class HTextField;
class ButtonGroup;
class HInternalFrame;
class HPanel;

class HButton;
class HComboBox;


class String;

class HCL_API Point
{
public:
	int x = 0;
	int y = 0;
	Point();
	Point(int, int);
	~Point();

private:

};
class HCL_API String
{
public:
	String();
	String(LPCSTR str);
	String(string str);
	String(LPCWSTR str);
	String(LPWSTR str);
	~String();
	String operator=(const String& str);
	String operator=(LPCSTR str);
	String operator=(string str);
	String operator=(LPCWSTR pwsz);
	String operator=(LPWSTR lpw);
	String operator+=(string str);
	String operator+=(LPCSTR str);
	String operator+=(const String& str);
	String operator+(const String& str);


	operator LPCSTR();
	operator LPCWSTR();
	operator string();
	void convert(LPCWSTR pwsz);
	void print();
	void println();
	string string = "null";

private:

};
class HCL_API Dimension
{
public:
	int width = 0;
	int height = 0;
	Dimension();
	Dimension(int, int);
	~Dimension();

private:

};
class HCL_API KeyEvent
{
public:
	KeyEvent(HFrame*, char, MSG);
	~KeyEvent();
	char getKeyChar();
	HFrame* getComponent();
private:
	char KeyCode = 0;
	MSG msg;
	HFrame *component;
};
class HCL_API ActionEvent
{
public:
	ActionEvent(Component*, char, MSG);
	ActionEvent(Component*);
	~ActionEvent();

	Component* getComponent();
private:
	char KeyCode = 0;
	MSG msg;
	Component *component;
};

class HCL_API Component
{
public:
	HWND hwnd;
	int ID_ON_PANEL = -1;
	LPCSTR Type = "NOT DEFINED";
	bool ActionListenerAdded = 0;
	virtual String getText() = 0;
	virtual bool MakeButton(HWND) = 0;
	virtual int getDefaultCloseOperation() = 0;
	virtual bool WINAPI setVisible(bool visible) = 0;
	virtual void setSize(int, int) = 0;
	virtual Dimension getSize() = 0;
	virtual Point getLocation() = 0;
	virtual void setLocation(int, int) = 0;


	LPCSTR title = "NO TITLED";

	void setEnabled(bool enabled);
	bool isEnabled();

	int(*KeyListener)(KeyEvent);
	int(*ActionListener)(ActionEvent);

	bool Checked = false;
	ButtonGroup* getButtonGroup();
	void setButtonGroup(ButtonGroup* buttonGroup);

	bool setSizeBool = false;
	bool WindowProcAdded = false;
	bool setLocationBool = false;
	bool setTitleBool = false;
	bool KeyListenerAdded = false;


	Component *hbutton[2000];
	int BUTTON_COUT = 0; int BUTTON_ADDED = 0;

	int x = 0, y = 0, wd = 100, ht = 100;
	int xsc = 0, ysc = 0, wdsc = 100, htsc = 100;


private:
	ButtonGroup* buttongrp = NULL;
	bool Enable = true;
};
class HCL_API HButton :public Component
{
public:
	HButton();
	HButton(LPCSTR);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);


	//void addKeyListener(int KeyListener(KeyEvent)); yapilandirilmadi
	void addActionListener(int ActionListener(ActionEvent));

	Point getLocation();
	Dimension getSize();
	String getText();
	~HButton();


private:

	int getDefaultCloseOperation() { return 0; };
	bool WINAPI setVisible(bool visible) { return 0; };
	bool ButtonCreated = false;
	LPCSTR title = "NO TITLED BUTTON";
};
class HCL_API HCheckBox :public Component
{
public:
	HCheckBox();
	HCheckBox(LPCSTR);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);

	Point getLocation();
	Dimension getSize();
	String getText();
	~HCheckBox();

	bool isChecked();

	//void addKeyListener(int KeyListener(KeyEvent)); yapilandirilmadi
	void addActionListener(int ActionListener(ActionEvent));



private:
	bool WINAPI setVisible(bool visible) { return 0; };
	int getDefaultCloseOperation() { return 0; };
	bool ButtonCreated = false;
	LPCSTR title = "NO TITLED CHECK BOX";
};
class HCL_API HRadioButton :public Component
{
public:
	HRadioButton();
	HRadioButton(LPCSTR);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);
	void setChecked(bool);

	Point getLocation();
	Dimension getSize();
	String getText();
	~HRadioButton();

	bool isChecked();

	//void addKeyListener(int KeyListener(KeyEvent)); yapilandirilmadi
	void addActionListener(int ActionListener(ActionEvent));



private:
	int getDefaultCloseOperation() { return 0; };
	bool WINAPI setVisible(bool visible) { return 0; };
	bool ButtonCreated = false;
	LPCSTR title = "NO TITLED RADIO BUTTON";
};
class HCL_API ButtonGroup
{
public:
	ButtonGroup();
	~ButtonGroup();
	void add(HRadioButton*);
	void AllUnsellected();

private:
	HRadioButton *hbutton[2000];
	int BUTTON_COUT = 0;

};
class HCL_API HTextField :public Component
{
public:
	HTextField();
	HTextField(LPCSTR);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);

	Point getLocation();
	Dimension getSize();
	String getText();
	~HTextField();

	//void addKeyListener(int KeyListener(KeyEvent)); yapilandirilmadi
	void addActionListener(int ActionListener(ActionEvent));



private:
	bool WINAPI setVisible(bool visible) { return 0; };
	int getDefaultCloseOperation() { return 0; };
	bool ButtonCreated = false;
	LPCSTR title = "NO TITLED TEXT FIELD";
};
class HCL_API HTextArea :public Component
{
public:
	HTextArea();
	HTextArea(LPCSTR);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);

	Point getLocation();
	Dimension getSize();
	String getText();
	~HTextArea();

	//void addKeyListener(int KeyListener(KeyEvent)); yapilandirilmadi
	void addActionListener(int ActionListener(ActionEvent));



private:
	bool WINAPI setVisible(bool visible) { return 0; };
	int getDefaultCloseOperation() { return 0; };
	bool ButtonCreated = false;
	LPCSTR title = "NO TITLED TEXT FIELD";
};
class HCL_API HLabel :public Component
{
public:
	HLabel();
	HLabel(LPCSTR);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);

	Point getLocation();
	Dimension getSize();
	String getText();
	~HLabel();


private:

	int getDefaultCloseOperation() { return 0; };
	bool WINAPI setVisible(bool visible) { return 0; };
	bool ButtonCreated = false;
	LPCSTR title = "NO TITLED LABEL";
};
class HCL_API HComboBox :public Component
{
public:
	HComboBox();
	
	HComboBox(String[],int);
	bool MakeButton(HWND);
	void setLocation(int, int);
	void setText(LPCSTR);
	void setSize(int, int);
	void setList(String[],int);
	void addItem(String);
	void removeItemAt(int);
	void removeAllItems();
	bool removeItem(String);
	int getItemCount();
	String getItemAt(int);
	int getSelectedIndex();
	String getSelectedItem();


	//void addKeyListener(int KeyListener(KeyEvent)); yapilandirilmadi
	void addActionListener(int ActionListener(ActionEvent));

	Point getLocation();
	Dimension getSize();
	String getText();
	~HComboBox();
	

private:

	int getDefaultCloseOperation() { return 0; };
	bool WINAPI setVisible(bool visible) { return 0; };
	bool ButtonCreated = false;

	String items[200];
	int items_cout = -1;

	LPCSTR title = "NO TITLED COMBO BOX";

};


class HCL_API HPanel :public Component
{
public:
	static const int EXIT_ON_CLOSE = 10;
	static const int HIDE_ON_CLOSE = 11;
	static const int DISPOSE_ON_CLOSE = 12;
	static const int DO_NOTHING_ON_CLOSE = 13;

	HPanel(LPCSTR);//PCWSTR
	HPanel();
	~HPanel();
	Point getLocation();
	LPCSTR getTitle();
	Dimension getSize();
	int getDefaultCloseOperation();
	void setLocation(int, int);
	void setTitle(LPCSTR);
	void setSize(int, int);
	bool setDefaultCloseOperation(int);
	bool WINAPI setVisible(bool visible) { return ShowWindow(this->hwnd, 0); }
	void addKeyListener(int KeyListener(KeyEvent));
	void add(Component*);
	void remove(Component*);
	bool addWindowProc(HINSTANCE, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM));
	WNDCLASS wc = {};

	String getText() { return ""; };
	bool MakeButton(HWND);

private:
	int CloseOperation = 11;
	bool ButtonCreated = false;



	HINSTANCE hInstance = NULL;
	//PCWSTR title = L"NO TITLED H COMPONENT";
	int(*KeyListener)(KeyEvent);

	const wchar_t CLASS_NAME[14] = L"H PANEL CLASS";

};
class HCL_API HInternalFrame :public Component
{
public:
	static const int EXIT_ON_CLOSE = 10;
	static const int HIDE_ON_CLOSE = 11;
	static const int DISPOSE_ON_CLOSE = 12;
	static const int DO_NOTHING_ON_CLOSE = 13;

	HInternalFrame(LPCSTR);//PCWSTR
	HInternalFrame();
	~HInternalFrame();
	Point getLocation();
	LPCSTR getTitle();
	Dimension getSize();
	Point getLocationOnScreen();
	int getDefaultCloseOperation();
	void setLocation(int, int);
	void setTitle(LPCSTR);
	void setSize(int, int);
	bool setDefaultCloseOperation(int);
	bool WINAPI setVisible(bool visible) { return ShowWindow(this->hwnd, 0); }
	void addKeyListener(int KeyListener(KeyEvent));
	void add(Component*);
	void remove(Component*);
	bool addWindowProc(HINSTANCE, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM));
	WNDCLASS wc = {};

	String getText() { return ""; };
	bool MakeButton(HWND);

private:
	int CloseOperation = 11;
	bool ButtonCreated = false;



	HINSTANCE hInstance = NULL;
	//PCWSTR title = L"NO TITLED H COMPONENT";
	int(*KeyListener)(KeyEvent);

	const wchar_t CLASS_NAME[14] = L"H PANEL CLASS";

};
class HCL_API HFrame : public Component
{
public:
	static const int EXIT_ON_CLOSE = 10;
	static const int HIDE_ON_CLOSE = 11;
	static const int DISPOSE_ON_CLOSE = 12;
	static const int DO_NOTHING_ON_CLOSE = 13;




	HFrame(LPCSTR);//PCWSTR
	HFrame();
	~HFrame();
	bool WINAPI setVisible(bool);
	Point getLocation();
	LPCSTR getTitle();
	Dimension getSize();
	int getDefaultCloseOperation();
	void setLocation(int, int);
	void setTitle(LPCSTR);
	void setSize(int, int);
	bool setDefaultCloseOperation(int);
	void addKeyListener(int KeyListener(KeyEvent));
	void add(Component*);
	void remove(Component*);
	bool addWindowProc(HINSTANCE, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM));
	WNDCLASS wc = {};

	bool setVisible();


private:

	int CloseOperation = 11;

	HINSTANCE hInstance = NULL;
	//PCWSTR title = L"NO TITLED H COMPONENT";
	int(*KeyListener)(KeyEvent);

	const wchar_t CLASS_NAME[22] = L"H COMPONENT CLASS 1.2";



	String getText() { return ""; };
	bool MakeButton(HWND) { return 0; };


};

    typedef struct MyData {
        int val1;
        int val2;
    }MYDATA, *PMYDATA;
    LRESULT CALLBACK DefaultWindowProc(HWND, UINT, WPARAM, LPARAM);
    DWORD WINAPI setVisibleA(LPVOID);
    void setVisibleB(HFrame*);
    
    extern HINSTANCE hInstanceWindows;
    extern HFrame *frame_visible_ptr;
    extern int THREAD_COUT;



	//extern "C" HCL_API class Point;
	//extern HButton HButtonExt;
	extern "C" HCL_API void ReportHINSTANCE(HINSTANCE);
	extern "C" HCL_API bool WaitAll();
	static const string HCL_INFO = "H Component Library Version: 1.2 Created By: Yusuf K. Hanoglu";;
