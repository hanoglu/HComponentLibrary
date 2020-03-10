01.02.2019
HCl library notes;
Version 1.1

This library provides you create and use windows gui components in your app.
This library created by Yusuf K. Hanoðlu.


To use HCl library do this steps:
	Copy HCl Component Library folder to C:\

	1. Open a Windows Desktop Application in Visual Studio
	2. Open property pages of project
	3. Select C/C++ -> General -> Additional Include Directories and add the location of the HCl.h file (C:\HCl Component Library\)
	4. Select Linker -> General -> Additional Library Directories and add the location of the HCl.lib file (C:\HCl Component Library\)
	5. Select Linker -> Input -> Additional Dependencies and add HCl.lib 
	6. Select Build Events -> Post-Build -> Command Line and add this:  xcopy /y /d "C:\HCl Component Library\HCl.dll" "$(OutDir)"


That's all, you can use H Component Library in your C++ project by using;
			#include "HCl.h";



An Example:

#include "windows.h"
#include "HCl.h";



//starting point wWinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	ReportHINSTANCE(hInstance);//send hInstance to HCl to create frame with it
	
	HFrame frame = HFrame("Hello World");
	frame.setLocation(10, 10);
	frame.setSize(500, 500);
	frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);

	HButton but = HButton("Click Me");
	but.setSize(100, 30);
	but.setLocation(30, 30);
	but.addActionListener([](ActionEvent)->int {//action listener as a lambda function
		PostQuitMessage(0);
		return 0;
	});

	frame.add(&but);
	frame.setVisible(true);

	return WaitAll();//finish your app always with this function, it waits all frames to close
}



//important note: if you get an error in your project even you do all of the steps listed above, create Windows Desktop Aplication intsead of Empty Project