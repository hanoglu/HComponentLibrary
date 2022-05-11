/*
ButtonGroup.cpp
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

//*********************************************BUTTON GROUP*******************************************


ButtonGroup::ButtonGroup()
{
}
ButtonGroup::~ButtonGroup()
{
}
void ButtonGroup::add(HRadioButton* RadioButton) {
	this->hbutton[this->BUTTON_COUT] = RadioButton;
	this->hbutton[this->BUTTON_COUT]->setButtonGroup(this);
	this->BUTTON_COUT++;
}
void ButtonGroup::AllUnsellected() {
	for (int i = 0; i < this->BUTTON_COUT; i++) {
		this->hbutton[i]->setChecked(false);
	}
}




