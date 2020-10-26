# HComponentLibrary
Lightweight Java like Windows GUI library for C++

H Componen Library(HCl) is a free to use lightweight Java like Windows GUI library for C++.
HCl classes:
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

*Source code of my library is preparing. 
Detailed explanations about usage will also be uploaded*
