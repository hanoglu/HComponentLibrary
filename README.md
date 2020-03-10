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
	2. Open property pages of project
	3. Select C/C++ -> General -> Additional Include Directories and add the location of the HCl.h file (C:\HCl Component Library\)
	4. Select Linker -> General -> Additional Library Directories and add the location of the HCl.lib file (C:\HCl Component Library\)
	5. Select Linker -> Input -> Additional Dependencies and add HCl.lib 
	6. Select Build Events -> Post-Build -> Command Line and add this:  xcopy /y /d "C:\HCl Component Library\HCl.dll" "$(OutDir)"


That's all, you can use H Component Library in your C++ project by using; #include "HCl.h";

*Source code of my library is preparing. 
Detailed explanations about usage will also be uploaded*
