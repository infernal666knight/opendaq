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

#ifndef DSAVER_H
#define DSAVER_H
#include <iostream>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include "dpack.h"

class DSaver : public QObject 
{
	Q_OBJECT

public:
	DSaver (QWidget *parent = 0);
	
public slots:

	void accept_string (QString data);
	void read_string ();
	void set_file_name (QString newName);
	void get_file_name ();
	void accept_data_pack (DPack *pack);
	void read_data_pack();	

signals:
	void saved();
	void pack_saved();
	void name_ready();
	void string_ready (QString data); 
	void pack_ready (DPack *pack);	

private:
	QString filename;	
};


#endif
