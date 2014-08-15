/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "menusettingfile.h"

#include "delegate.h"
#include "filedialog.h"
#include "gmenu2x.h"
#include "iconbutton.h"

using std::string;
using std::unique_ptr;
using std::move;

MenuSettingFile::MenuSettingFile(
		GMenu2X *gmenu2x, Touchscreen &ts_,
		const string &name, const string &description,
		string *value, const string &filter_)
	: MenuSettingStringBase(gmenu2x, name, description, value)
	, ts(ts_)
	, filter(filter_)
{
	unique_ptr<IconButton> btnClear(new IconButton(
		gmenu2x, ts, "skin:imgs/buttons/cancel.png", gmenu2x->tr["Clear"]));
	btnClear->setAction(BIND(&MenuSettingFile::clear));
	buttonBox.add(move(btnClear));

	unique_ptr<IconButton> btnSelect(new IconButton(
		gmenu2x, ts, "skin:imgs/buttons/accept.png", gmenu2x->tr["Select"]));
	btnSelect->setAction(BIND(&MenuSettingFile::edit));
	buttonBox.add(move(btnSelect));
}

void MenuSettingFile::edit()
{
	FileDialog fd(gmenu2x, ts, description, filter, value());
	if (fd.exec()) {
		setValue(fd.getPath() + "/" + fd.getFile());
	}
}
