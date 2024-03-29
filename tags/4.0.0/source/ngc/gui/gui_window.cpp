/****************************************************************************
 * Snes9x 1.51 Nintendo Wii/Gamecube Port
 *
 * Tantric February 2009
 *
 * gui_window.cpp
 *
 * GUI class definitions
 ***************************************************************************/

#include "gui.h"

GuiWindow::GuiWindow()
{
	width = 0;
	height = 0;
	focus = 0; // allow focus
}

GuiWindow::GuiWindow(int w, int h)
{
	width = w;
	height = h;
	focus = 0; // allow focus
}

GuiWindow::~GuiWindow()
{
}

void GuiWindow::Append(GuiElement* e)
{
	if (e == NULL)
		return;

	Remove(e);
	_elements.push_back(e);
	e->SetParent(this);
}

void GuiWindow::Insert(GuiElement* e, u32 index)
{
	if (e == NULL || index > (_elements.size() - 1))
		return;

	Remove(e);
	_elements.insert(_elements.begin()+index, e);
	e->SetParent(this);
}

void GuiWindow::Remove(GuiElement* e)
{
	if (e == NULL)
		return;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		if(e == _elements.at(i))
		{
			_elements.erase(_elements.begin()+i);
			break;
		}
	}
}

void GuiWindow::RemoveAll()
{
	_elements.clear();
}

GuiElement* GuiWindow::GetGuiElementAt(u32 index) const
{
	if (index >= _elements.size())
		return NULL;
	return _elements.at(index);
}

u32 GuiWindow::GetSize()
{
	return _elements.size();
}

void GuiWindow::Draw()
{
	if(_elements.size() == 0 || !this->IsVisible())
		return;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		try	{ _elements.at(i)->Draw(); }
		catch (exception& e) { }
	}

	this->UpdateEffects();

	if(parentElement && state == STATE_DISABLED)
		Menu_DrawRectangle(0,0,screenwidth,screenheight,(GXColor){0xbe, 0xca, 0xd5, 0x70},1);
}

void GuiWindow::ResetState()
{
	if(state != STATE_DISABLED)
		state = STATE_DEFAULT;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		try { _elements.at(i)->ResetState(); }
		catch (exception& e) { }
	}
}

void GuiWindow::SetState(int s)
{
	state = s;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		try { _elements.at(i)->SetState(s); }
		catch (exception& e) { }
	}
}

void GuiWindow::SetVisible(bool v)
{
	visible = v;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		try { _elements.at(i)->SetVisible(v); }
		catch (exception& e) { }
	}
}

void GuiWindow::SetFocus(int f)
{
	focus = f;

	if(f == 1)
		this->MoveSelectionVert(1);
	else
		this->ResetState();
}

void GuiWindow::ChangeFocus(GuiElement* e)
{
	if(parentElement)
		return; // this is only intended for the main window

	for (u8 i = 0; i < _elements.size(); i++)
	{
		if(e == _elements.at(i))
			_elements.at(i)->SetFocus(1);
		else if(_elements.at(i)->IsFocused() == 1)
			_elements.at(i)->SetFocus(0);
	}
}

void GuiWindow::ToggleFocus(GuiTrigger * t)
{
	if(parentElement)
		return; // this is only intended for the main window

	int found = -1;
	int newfocus = -1;
	u8 i;

	// look for currently in focus element
	for (i = 0; i < _elements.size(); i++)
	{
		try
		{
			if(_elements.at(i)->IsFocused() == 1)
			{
				found = i;
				break;
			}
		}
		catch (exception& e) { }
	}

	// element with focus not found, try to give focus
	if(found == -1)
	{
		for (i = 0; i < _elements.size(); i++)
		{
			try
			{
				if(_elements.at(i)->IsFocused() == 0 && _elements.at(i)->GetState() != STATE_DISABLED) // focus is possible (but not set)
				{
					_elements.at(i)->SetFocus(1); // give this element focus
					break;
				}
			}
			catch (exception& e) { }
		}
	}
	// change focus
	else if(t->wpad.btns_d & (WPAD_BUTTON_1 | WPAD_BUTTON_B | WPAD_CLASSIC_BUTTON_B)
		|| t->pad.btns_d & PAD_BUTTON_B)
	{
		for (i = found; i < _elements.size(); i++)
		{
			try
			{
				if(_elements.at(i)->IsFocused() == 0 && _elements.at(i)->GetState() != STATE_DISABLED) // focus is possible (but not set)
				{
					newfocus = i;
					_elements.at(i)->SetFocus(1); // give this element focus
					_elements.at(found)->SetFocus(0); // disable focus on other element
					break;
				}
			}
			catch (exception& e) { }
		}

		if(newfocus == -1)
		{
			for (i = 0; i < found; i++)
			{
				try
				{
					if(_elements.at(i)->IsFocused() == 0 && _elements.at(i)->GetState() != STATE_DISABLED) // focus is possible (but not set)
					{
						_elements.at(i)->SetFocus(1); // give this element focus
						_elements.at(found)->SetFocus(0); // disable focus on other element
						break;
					}
				}
				catch (exception& e) { }
			}
		}
	}
}

int GuiWindow::GetSelected()
{
	// find selected element
	int found = -1;
	for (u8 i = 0; i < _elements.size(); i++)
	{
		try
		{
			if(_elements.at(i)->GetState() == STATE_SELECTED)
			{
				found = i;
				break;
			}
		}
		catch (exception& e) { }
	}
	return found;
}

// set element to left/right as selected
// there's probably a more clever way to do this, but this way works
void GuiWindow::MoveSelectionHor(int dir)
{
	int found = -1;
	u16 left = 0;
	u16 top = 0;
	u8 i = 0;

	int selected = this->GetSelected();

	if(selected >= 0)
	{
		left = _elements.at(selected)->GetLeft();
		top = _elements.at(selected)->GetTop();
	}

	// look for a button on the same row, to the left/right
	for (i = 0; i < _elements.size(); i++)
	{
		try
		{
			if(_elements.at(i)->IsSelectable())
			{
				if(_elements.at(i)->GetLeft()*dir > left*dir && _elements.at(i)->GetTop() == top)
				{
					if(found == -1)
						found = i;
					else if(_elements.at(i)->GetLeft()*dir < _elements.at(found)->GetLeft()*dir)
						found = i; // this is a better match
				}
			}
		}
		catch (exception& e) { }
	}
	if(found >= 0)
		goto matchfound;

	// match still not found, let's try the first button in the next row
	for (i = 0; i < _elements.size(); i++)
	{
		try
		{
			if(_elements.at(i)->IsSelectable())
			{
				if(_elements.at(i)->GetTop()*dir > top*dir)
				{
					if(found == -1)
						found = i;
					else if(_elements.at(i)->GetTop()*dir < _elements.at(found)->GetTop()*dir)
						found = i; // this is a better match
					else if(_elements.at(i)->GetTop()*dir == _elements.at(found)->GetTop()*dir
						&&
						_elements.at(i)->GetLeft()*dir < _elements.at(found)->GetLeft()*dir)
						found = i; // this is a better match
				}
			}
		}
		catch (exception& e) { }
	}

	// match found
	matchfound:
	if(found >= 0)
	{
		_elements.at(found)->SetState(STATE_SELECTED);
		if(selected >= 0)
			_elements.at(selected)->ResetState();
	}
}

void GuiWindow::MoveSelectionVert(int dir)
{
	int found = -1;
	u16 left = 0;
	u16 top = 0;
	u8 i = 0;

	int selected = this->GetSelected();

	if(selected >= 0)
	{
		left = _elements.at(selected)->GetLeft();
		top = _elements.at(selected)->GetTop();
	}

	// look for a button above/below, with the least horizontal difference
	for (i = 0; i < _elements.size(); i++)
	{
		try
		{
			if(_elements.at(i)->IsSelectable())
			{
				if(_elements.at(i)->GetTop()*dir > top*dir)
				{
					if(found == -1)
						found = i;
					else if(_elements.at(i)->GetTop()*dir < _elements.at(found)->GetTop()*dir)
						found = i; // this is a better match
					else if(_elements.at(i)->GetTop()*dir == _elements.at(found)->GetTop()*dir
							&&
							abs(_elements.at(i)->GetLeft() - left) <
							abs(_elements.at(found)->GetLeft() - left))
						found = i;
				}
			}
		}
		catch (exception& e) { }
	}
	if(found >= 0)
		goto matchfound;

	// match found
	matchfound:
	if(found >= 0)
	{
		_elements.at(found)->SetState(STATE_SELECTED);
		if(selected >= 0)
			_elements.at(selected)->ResetState();
	}
}

void GuiWindow::Update(GuiTrigger * t)
{
	if(_elements.size() == 0 || (state == STATE_DISABLED && parentElement))
		return;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		try	{ _elements.at(i)->Update(t); }
		catch (exception& e) { }
	}

	this->ToggleFocus(t);

	if(focus) // only send actions to this window if it's in focus
	{
		// pad/joystick navigation
		if(t->Right())
			this->MoveSelectionHor(1);
		else if(t->Left())
			this->MoveSelectionHor(-1);
		else if(t->Down())
			this->MoveSelectionVert(1);
		else if(t->Up())
			this->MoveSelectionVert(-1);
	}

	if(updateCB)
		updateCB(this);
}
