/*
HFrame.cpp
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

//**********************************************FRAME****************************************************************************


HFrame::HFrame(LPCSTR title)//PCWSTR title
{
	this->Type = "HFRAME";

	this->title = title;
	setTitleBool = true;

	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;
}
HFrame::HFrame()
{
	this->Type = "HFRAME";
	this->hInstance = hInstanceWindows;
	this->WindowProcAdded = true;

}
HFrame::~HFrame()
{
}
bool WINAPI HFrame::setVisible(bool visible) {
	if (visible) {


		/*
				pDataArray = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));//HEAP_ZERO_MEMORY

				frame_visible_ptr = this;

				HANDLE thr[1];
				thr[0] = CreateThread(
					NULL,
					0,
					setVisibleA,
					pDataArray,
					0,
					&dwThreadId
				);

				if (thr[0] == NULL)
				{
					ExitProcess(3);
				}
			*/
			/*
				WaitForMultipleObjects(MAX_THREADS, thr, TRUE, INFINITE);

				for (int i = 0; i < MAX_THREADS; i++)
				{
					CloseHandle(thr[i]);
					if (pDataArray != NULL)
					{
						HeapFree(GetProcessHeap(), 0, pDataArray);
						pDataArray = NULL;    // Ensure address is not reused.
					}
				}
			*/

		PMYDATA pDataArray;
		DWORD dwThreadId;

		pDataArray = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MyData));//HEAP_ZERO_MEMORY

		frame_visible_ptr = this;

		HANDLE han = CreateThread(
			NULL,
			0,
			setVisibleA,
			pDataArray,
			0,
			&dwThreadId
		);
		if (han != NULL)
			THREAD_COUT++;

		Sleep(100);
		/*
		frame_visible_ptr = this;
		thr[THREAD_COUT] = thread(&setVisibleB, this);
		THREAD_COUT++;
		*/
	}
	else {
		return ShowWindow(this->hwnd, 0);
	}
}
bool HFrame::setVisible()
{
	if (this->WindowProcAdded || true) {



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


		this->hwnd = CreateWindowEx(
			0,
			this->CLASS_NAME,
			NULL,//this->title,
			WS_OVERLAPPEDWINDOW,
			this->x, this->y, this->wd, this->ht,
			NULL,
			NULL,
			this->hInstance,
			NULL
		);

		SetWindowTextA(this->hwnd, this->title);


		for (int i = 0; i < BUTTON_COUT; i++) {
			this->hbutton[i]->MakeButton(this->hwnd);
			this->BUTTON_ADDED++;
		}


		SetWindowLongPtr(this->hwnd, GWLP_USERDATA, (LONG_PTR)this);



		SetTimer(hwnd,             // handle to main window 
			0,            // timer identifier 
			100,                 // 100-msecond interval 
			(TIMERPROC)NULL);     // no timer callback 

		ShowWindow(this->hwnd, 1);
		MSG msg = {};
		while (GetMessage(&msg, 0, NULL, NULL)) {
			if (msg.message != WM_TIMER) {
				//cout << msg.message << endl;
			}
			if (msg.message == WM_KEYDOWN) {
				if (this->KeyListenerAdded) {

					const char chr = LOWORD(msg.wParam);
					KeyEvent ke = KeyEvent(this, chr, msg);
					KeyListener(ke);
				}

			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		THREAD_COUT--;
		//return true;



	//return false;

	}
	else
		return false;
}
bool HFrame::addWindowProc(HINSTANCE hInstance, LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM)) {
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
void HFrame::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
	this->setLocationBool = true;
}
void HFrame::setSize(int wd, int ht) {
	this->wd = wd;
	this->ht = ht;
	setSizeBool = true;
}
void HFrame::setTitle(LPCSTR title) {
	this->title = title;
	this->setTitleBool = true;
	SetWindowTextA(this->hwnd, this->title);
	this->setTitleBool = false;

}


bool HFrame::setDefaultCloseOperation(int operation) {
	if (operation > 9 && operation < 14) {
		this->CloseOperation = operation;
		return true;
	}
	return false;
}
int HFrame::getDefaultCloseOperation() {
	return this->CloseOperation;
}
Point HFrame::getLocation() {
	Point point = Point(this->x, this->y);

	return point;
}
LPCSTR HFrame::getTitle() {
	return title;
}
Dimension HFrame::getSize() {
	Dimension dim = Dimension(this->wd, this->ht);
	return dim;
}
void HFrame::add(Component *button) {
	this->hbutton[BUTTON_COUT] = button;
	this->hbutton[BUTTON_COUT]->ID_ON_PANEL = BUTTON_COUT;
	BUTTON_COUT++;
}
void HFrame::remove(Component *component) {

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
void HFrame::addKeyListener(int KeyListener(KeyEvent)) {
	this->KeyListener = KeyListener;
	this->KeyListenerAdded = true;
}

//std::error_code DefaultWindowProc(std::nothrow_t) noexcept;

static COLORREF bgColor = RGB(0, 255, 0);






LRESULT CALLBACK DefaultWindowProc(HWND hWin, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static HBRUSH defaultbrush = NULL;
	static HBRUSH hotbrush = NULL;
	static HBRUSH selectbrush = NULL;
	static HBRUSH push_uncheckedbrush = NULL;
	static HBRUSH push_checkedbrush = NULL;
	static HBRUSH push_hotbrush1 = NULL;
	static HBRUSH push_hotbrush2 = NULL;



	switch (uMsg) {
	case WM_TIMER: {

		LONG_PTR lpUserData = GetWindowLongPtr(hWin, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		if (ObjectPtr->Type == "HFRAME") {

			if (ObjectPtr->setSizeBool) {
				ObjectPtr->setSizeBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				ObjectPtr->x = rect.left; ObjectPtr->y = rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}
			else if (ObjectPtr->setLocationBool) {
				ObjectPtr->setLocationBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				ObjectPtr->wd = rect.right - rect.left;
				ObjectPtr->ht = rect.bottom - rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}


			RECT rect;
			GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
			ObjectPtr->wd = rect.right - rect.left;
			ObjectPtr->ht = rect.bottom - rect.top;
			ObjectPtr->x = rect.left;
			ObjectPtr->y = rect.top;
		}
		if (ObjectPtr->Type == "HINTERNALFRAME") {

			if (ObjectPtr->setSizeBool) {
				ObjectPtr->setSizeBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				MapWindowPoints(HWND_DESKTOP, GetParent(ObjectPtr->hwnd), (LPPOINT)&rect, 2);
				ObjectPtr->x = rect.left; ObjectPtr->y = rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}
			else if (ObjectPtr->setLocationBool) {
				ObjectPtr->setLocationBool = false;
				RECT rect;
				GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
				MapWindowPoints(HWND_DESKTOP, GetParent(ObjectPtr->hwnd), (LPPOINT)&rect, 2);
				ObjectPtr->wd = rect.right - rect.left;
				ObjectPtr->ht = rect.bottom - rect.top;
				SetWindowPos(ObjectPtr->hwnd, NULL, ObjectPtr->x, ObjectPtr->y, ObjectPtr->wd, ObjectPtr->ht, NULL);
			}

			RECT rect;
			GetWindowRect(ObjectPtr->hwnd, (LPRECT)&rect);
			ObjectPtr->xsc = rect.left;
			ObjectPtr->ysc = rect.top;

			MapWindowPoints(HWND_DESKTOP, GetParent(ObjectPtr->hwnd), (LPPOINT)&rect, 2);
			ObjectPtr->wd = rect.right - rect.left;
			ObjectPtr->ht = rect.bottom - rect.top;
			ObjectPtr->x = rect.left;
			ObjectPtr->y = rect.top;

		}
		if (ObjectPtr->BUTTON_ADDED < ObjectPtr->BUTTON_COUT) {

			ObjectPtr->hbutton[ObjectPtr->BUTTON_ADDED]->MakeButton(ObjectPtr->hwnd);
			ObjectPtr->BUTTON_ADDED++;

		}

	}
				   return 0;
	case WM_DESTROY: {

		LONG_PTR lpUserData = GetWindowLongPtr(hWin, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		int closeOperation = ObjectPtr->getDefaultCloseOperation();

		if (closeOperation == 10)
			PostQuitMessage(0);
		else if (closeOperation == 11) {
			ObjectPtr->setVisible(false);
			break;
		}
		else if (closeOperation == 12) {}
		else if (closeOperation == 13) {
			break;
		}

	}
					 return 0;
	case WM_CLOSE: {

		LONG_PTR lpUserData = GetWindowLongPtr(hWin, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		int closeOperation = ObjectPtr->getDefaultCloseOperation();

		if (closeOperation == 10)
			PostQuitMessage(0);
		else if (closeOperation == 11) {
			ObjectPtr->setVisible(false);
			break;
		}
		else if (closeOperation == 12) {}
		else if (closeOperation == 13) {
			break;
		}

		return DefWindowProc(hWin, uMsg, wParam, lParam);

	}
				   return 0;



	case WM_LBUTTONDOWN: {



	}
						 return 0;

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWin, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_WINDOW + 100);
		EndPaint(hWin, &ps);

	}return 0;


	case WM_COMMAND: {
		//cout << wParam << endl;

		LONG_PTR lpUserData = GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		if (ObjectPtr->Type == "HCHECKBOX") {
			if (!ObjectPtr->Checked) {
				SendMessage(ObjectPtr->hwnd, BM_SETCHECK, BST_CHECKED, 0);
				ObjectPtr->Checked = !ObjectPtr->Checked;
			}
			else {
				SendMessage(ObjectPtr->hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
				ObjectPtr->Checked = !ObjectPtr->Checked;
			}
		}
		if (ObjectPtr->Type == "HRADIOBUTTON") {

			if (ObjectPtr->getButtonGroup() != NULL) {
				ObjectPtr->getButtonGroup()->AllUnsellected();
			}

			SendMessage(ObjectPtr->hwnd, BM_SETCHECK, BST_CHECKED, 0);
			ObjectPtr->Checked = 1;

		}
		if (ObjectPtr->Type == "HCOMBOBOX") {
		
			
		
		
		}


		if (ObjectPtr->ActionListenerAdded&&ObjectPtr->isEnabled()) {
			ActionEvent ke = ActionEvent(NULL);
			ObjectPtr->ActionListener(ke);
		}
		




		//if((HWND)lParam){}
		//HButton btn = &GetWindowLong((HWND)lParam, GWL_USERDATA);
		//cout << hWin << endl;

	}return 0;
/* Paint all buttons to red color
	case WM_CTLCOLORBTN: {


		LONG_PTR lpUserData = GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;

		//DWORD button_id = (DWORD)GetMenu((HWND)lParam);
		//HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		//return (LRESULT)brush;

		RECT crect;
		HBRUSH brush;
		COLORREF background_color = RGB(255, 0, 0);
		HDC hdc = (HDC)wParam;
		HWND button_handle = (HWND)lParam;

		GetClientRect(button_handle, &crect);
		SetBkColor(hdc, background_color);
		SetTextColor(hdc, RGB(255, 255, 255));


		std::wstring stemp = s2ws(ObjectPtr->getText().string);
		LPCWSTR result = stemp.c_str();

		DrawText(hdc, result, ObjectPtr->getText().string.size(), &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		brush = CreateSolidBrush(background_color);

		return (HRESULT)brush;



		} break;*/
/*
	case WM_DRAWITEM: {

		
		const DRAWITEMSTRUCT& dis = *(DRAWITEMSTRUCT*)lParam;
		if (dis.itemAction & ODA_DRAWENTIRE) {
			// Render the control
			// ...

			// If the control has the input focus...
			if (dis.itemState & ODS_FOCUS) {
				// Render the focus rectangle
				DrawFocusRect(dis.hDC, &dis.rcItem);
			}
		}
		*/

		/*
		DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
		RECT rect;

		LONG_PTR lpUserData = GetWindowLongPtr(dis->hwndItem, GWLP_USERDATA);
		Component* ObjectPtr = (Component*)lpUserData;




		GetClientRect(dis->hwndItem, &rect); // get the size of the button.

		SetBkColor(dis->hDC, RGB(255, 0, 0));         // set text background to match button’s background.
		SetTextColor(dis->hDC, RGB(255, 255, 255));

		std::wstring stemp = s2ws(ObjectPtr->getText().string);
		LPCWSTR result = stemp.c_str();

		DrawText(dis->hDC, result, ObjectPtr->getText().string.size(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		



		//DrawText(dis->hDC, L"BTN", _countof(L"BTN") - 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	} return 0;*/
	/*case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (true)//some_item->code == NM_CUSTOMDRAW
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

			if (item->uItemState & CDIS_SELECTED)
			{
				//Select our color when the button is selected
				if (selectbrush == NULL)
					selectbrush = CreateGradientBrush(RGB(180, 0, 0), RGB(255, 180, 0), item);

				//Create pen for button border
				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				//Select our brush into hDC
				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, selectbrush);

				//If you want rounded button, then use this, otherwise use FillRect().
				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				//Clean up
				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				//Now, I don't want to do anything else myself (draw text) so I use this value for return:
				return CDRF_DODEFAULT;
				//Let's say I wanted to draw text and stuff, then I would have to do it before return with
				//DrawText() or other function and return CDRF_SKIPDEFAULT
			}
			else
			{
				if (item->uItemState & CDIS_HOT) //Our mouse is over the button
				{
					//Select our color when the mouse hovers our button
					if (hotbrush == NULL)
						hotbrush = CreateGradientBrush(RGB(255, 230, 0), RGB(245, 0, 0), item);

					HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

					HGDIOBJ old_pen = SelectObject(item->hdc, pen);
					HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

					RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

					SelectObject(item->hdc, old_pen);
					SelectObject(item->hdc, old_brush);
					DeleteObject(pen);

					return CDRF_DODEFAULT;
				}

				//Select our color when our button is doing nothing
				if (defaultbrush == NULL)
					defaultbrush = CreateGradientBrush(RGB(255, 180, 0), RGB(180, 0, 0), item);

				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}
		}
		return CDRF_DODEFAULT;



	}
	break;
	*/
	default:
		return DefWindowProc(hWin, uMsg, wParam, lParam);
	}

}

