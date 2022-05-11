# HComponentLibrary
HComponenLibrary is a lightweight UI component library for C++ which is highly inspired by Java Swing's syntax.
## Why Should I Use HCl
* HCl directly uses Win32 API, so it has minimal dependencies and maximum performance
* Its syntax is similar to Java Swing so it can be learned easily
* It can be used to convert __minimal__ Java Swing projects to native Windows applications
* It has minimal classes which are necessary to create a GUI application
* Size of the DLL file is so small (Around 230KiB)
* LGPL licensed so it can also be used in dynamically linked proprietary applications
## Classes
HComponentLibrary consist of classes below:
|Classes|Explanation|
|-------|-----------|
|ActionEvent|Contains an action event for action listeners|
|ButtonGroup|Groups radio buttons to be sure only one button selected simultaneously|
|Component|Parent class of UI components|
|Dimension|Contains width and height values|
|HButton|Creates a clickable button|
|HCheckBox|Creates a checkbox|
|HComboBox|Creates a dropdown list|
|HFrame|Creates an application window which can be main window|
|HInternalFrame|Creates a window which can be displayed inside panels|
|HLabel|Displays a text|
|HPanel|Can contain UI elements|
|HRadioButton|Creates a radio button|
|HTextArea|Displays an editable multiple line text|
|HTextField|Displays an editable one line text|
|KeyEvent|Stores data for key listeners|
|Point|Contains x and y axis|
|String|Performs cast operations|

## Sample Applications
A Java Swing developer can easily understand how to use HComponentLibrary with these examples.
### "Hello World" Application
Here is an example of how to use library, its syntax hugely inspired by Swing.
```cpp
#include "windows.h"
#include "HCl.h"

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
#include "HCl.h"
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
### Windows
Just open HCl.sln file with Visual Studio, change source code and compile.<br>
You can also compile the project with CMake with similar steps in Linux section.
### Linux
HCl uses Windows api and cannot be natively compiled on Linux distros. But it can be cross compiled and run with MinGW and Wine projects.<br>
These steps for RHEL based distros can also be applied other Linux based operating systems easily.
### RHEL Based Distros
#### Compiling With CMake
Install necessary packages by
```bash
sudo dnf install mingw64-gcc mingw64-gcc-c++ mingw64-headers mingw64-filesystem
```
or to compile for 32 bit architecture use
```bash
sudo dnf install mingw32-gcc mingw32-gcc-c++ mingw32-headers mingw32-filesystem
```
Then open project root directory and
```bash
mkdir build
mingw64-cmake ..
mingw64-make
```
for 32 bit
```bash
mkdir build
mingw32-cmake ..
mingw32-make
```
Then libHCL.dll and libHCL.dll.a files can be found at build/HCL directory. libHCL.dll.a can be renamed to HCL.lib.
#### Testing With Wine
Be sure Wine64 is installed properly.<br>
Copy any of the examples above and paste it to Test.cpp file.<br>
Copy libHCL.dll and HCl.h files to the same directory with Test.cpp<br>
Copy HCL.lib to /home/$USER/HCl (Any directory can be used)<br>
Run following code to compile application with HCl
```bash
x86_64-w64-mingw64-g++ Test.cpp -lHCl -L/home/$USER/HCl -municode -o Test.exe
```
For 32 bit
```bash
x86_64-w64-mingw64-g++ Test.cpp -lHCl -L/home/$USER/HCl -municode -o Test.exe
```
Before run the compiled application all necessary dll files of MinGW should either be copied to same directory with appliction or included to WINEPATH environment variable properly.
|DLL Files|Can Be Found At (x64)|Can Be Found At (x32)|
|---------|---------------------|---------------------|
|libgcc_s_seh-1.dll|/usr/x86_64-w64-mingw32/sys-root/mingw/bin|-|
|libstdc++-6.dll|/usr/x86_64-w64-mingw32/sys-root/mingw/bin|/usr/i686-w64-mingw32/sys-root/mingw/bin|

WINEPATH environment variable can be initialized by
```bash
export WINEPATH="/usr/x86_64-w64-mingw32/sys-root/mingw/bin"
```
For 32 bit
```bash
export WINEPATH="/usr/i686-w64-mingw32/sys-root/mingw/bin"
```
_Note: In every individual terminal session this export command should be run._<br><br>
Finally compiled application can be run by following command
```bash
wine64 Test.exe
```
For 32 bit
```bash
wine Test.exe
```
## Gallery
<img width="236" alt="example" src="https://user-images.githubusercontent.com/56837349/167948174-7914d48f-7323-4bf5-8fcd-6ccc1161d7b9.png">
