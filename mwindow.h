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

#ifndef MWINDOW_H
#define MWINDOW_H
#include <QWidget>
#include "processDialog/processdialog.h"
#include "newConfigDialog/configdialog.h"
#include "includes/dthread.h"
#include "includes/dsaver.h"
#include "ui_mainwindow.h"

class MWindow :public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:
	MWindow (QWidget *parent = 0);

private slots:
	void on_newButton_clicked ();	
	void on_aboutButton_clicked ();
	void begin_measure ();

private:
	ProcessDialog *process_dialog;
	ConfigDialog *config_dialog;
	DSaver *saver;	
};

#endif
