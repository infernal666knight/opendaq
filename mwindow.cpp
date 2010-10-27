/*
    This file is part of OpenDAQ.   
    Copyright (C) Shapar Andrei (email: nkerah_w@mail.ru)

    OpenDAQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui>
#include "mwindow.h"

MWindow::MWindow (QWidget *parent) : QMainWindow (parent)
{
	setupUi (this);

	move (300,200);

	saver = new DSaver(this);
	config_dialog = new ConfigDialog (this);
	process_dialog = new ProcessDialog (this);

   	connect (config_dialog, SIGNAL (config_ready(DConfig *)), process_dialog, SLOT (set_config(DConfig *)));
	connect ( config_dialog, SIGNAL ( done () ), this, SLOT ( begin_measure() ));
	connect ( closeButton, SIGNAL ( clicked () ), this, SLOT ( close() ));
}

void MWindow::on_newButton_clicked () 
{
	config_dialog->renew();
	if (config_dialog->isHidden())
	{
		config_dialog->show();	
	}
	else 
	{
		config_dialog->activateWindow();
	}
}

void MWindow::begin_measure()
{
	process_dialog->renew();
	config_dialog->hide();
	if (process_dialog->isHidden())
	{
		process_dialog->show();
	}
	else
	{
			process_dialog->activateWindow();
	}
}

void MWindow::on_aboutButton_clicked ()
{
}
