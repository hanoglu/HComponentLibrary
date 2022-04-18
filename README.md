# HComponentLibrary
HComponenLibrary is a lightweight UI component library for C++ which is highly inspired by Java Swing. <br>
Project aims to make it easy to convert __minimal__ Java Swing projects to native Windows application.
## Sample Applications
A java swing developer can easily understand how to use HComponentLibrary with these examples.
### "Hello World" Application
Here is an example of how to use library, its syntax hugely inspired by Swing.
```cpp
#include "windows.h"
#include "HCl.h";

// Starting point of application
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	ReportHINSTANCE(hInstance);//send hInstance to HCl to create frame with it
	
	// A frame created with title 'Hello World'
	HFrame frame = HFrame("Hello World");
	frame.setLocation(10, 10);
	frame.setSize(500, 500);
	frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);

	// A button created with label 'Click Me' and set an action listener
	HButton but = HButton("Click Me");
	but.setSize(100, 30);
	but.setLocation(30, 30);
	but.addActionListener([](ActionEvent)->int {//action listener as a lambda function
		PostQuitMessage(0);
		return 0;
	});

	// Add UI components to frame and set frame visible
	frame.add(&but);
	frame.setVisible(true);

	// Wait all frames to close
	return WaitAll();
}
```
### An Example With Combo Box
Slightly more complex application with combo box and text field.
```cpp
#include "HCl.h";
#include "windows.h"

HComboBox combo;
HTextField htf;
// Starting point of application
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	ReportHINSTANCE(hInstance);//send hInstance to HCl to create frame with it

	HFrame frame = HFrame("Example with HComboBox");
	frame.setLocation(50, 50);
	frame.setSize(400, 250);
	frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);

	htf = HTextField("");
	htf.setSize(170, 25);
	htf.setLocation(10, 10);

	HButton btnadd = HButton("Add");
	btnadd.setSize(100, 25);
	btnadd.setLocation(190,10);
	btnadd.addActionListener([](ActionEvent)->int{
		combo.addItem(htf.getText());
		return 0;
	});
	HButton btndel = HButton("Delete");
	btndel.setSize(100, 25);
	btndel.setLocation(190, 40);
	btndel.addActionListener([](ActionEvent)->int {
		combo.removeItemAt(combo.getSelectedIndex());
		return 0;
		});
	frame.add(&btndel);
	frame.add(&btnadd);
	frame.add(&htf);

	String str[] = {"Computer 1","Tablet 1","Tablet 2","Phone 1","Phone 2"};
	combo = HComboBox(str,5);
	String str2[] = {"a","b","c"};
	combo.setList(str2,3);
	combo.setSize(300, 400);
	combo.setLocation(50, 110);
	frame.add(&combo);

	HButton but = HButton("Selected Item");
	but.setSize(100, 25);
	but.setLocation(190, 70);
	but.addActionListener([](ActionEvent)->int {
		MessageBoxA(0,combo.getSelectedItem(),"You Selected",MB_OK);
		return 0;
		});

	frame.add(&but);
	frame.setVisible(true);

	combo.addItem("Added after creation");
	
	//Finish your app always with this function, it waits all frames to close
	return WaitAll();
}
```
## Classes
HComponentLibrary consist of classes below:
```
- ActionEvent
- ButtonGroup
- Component
- Dimension
- HButton
- HCheckBox
- HComboBox
- HFrame
- HInternalFrame
- HLabel
- HPanel
- HRadioButton
- HTextArea
- HTextField
- KeyEvent
- Point
- String
```
## How to Install
To use HCl library do this steps after copying HCl Component Library folder to C:\

	1. Open a Windows Desktop Application in Visual Studio
	2. This version of HCl is for only 32 bit(x86) programming (x64 comming soon) you should select x86 instead of x64 at the top bar
	3. Open property pages of project
	4. Select C/C++ -> General -> Additional Include Directories and add the location of the HCl.h file (C:\HCl Component Library\)
	5. Select Linker -> General -> Additional Library Directories and add the location of the HCl.lib file (C:\HCl Component Library\)
	6. Select Linker -> Input -> Additional Dependencies and add HCl.lib 
	7. Select Build Events -> Post-Build -> Command Line and add this:  xcopy /y /d "C:\HCl Component Library\HCl.dll" "$(OutDir)"
	Notes: Please be sure that project is created as Windows Desktop Application.
	       Please be sure that you have configured project settings for x86(32 bit) not only x64.

That's all, you can use H Component Library in your C++ project by using; #include "HCl.h";
## Build From Source
Just open HCl.sln file with Visual Studio, change source code and compile.
