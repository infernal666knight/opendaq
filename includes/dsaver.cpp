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

#include "dsaver.h"

DSaver::DSaver (QWidget *parent):
	QObject (parent)
{
	connect (this, SIGNAL ( name_ready() ), this, SLOT ( read_string() ));
}

void DSaver::accept_string (QString data)
{
	QFile file (filename);
	if (file.exists()) {
		if (!file.open (QIODevice::Append))
		{
//			cerr << qPrintable (file.errorString());
			return;
		}
	}
	else
		if (!file.open (QIODevice::WriteOnly)){
			return;
		}

	QDataStream out (&file);
	out.setVersion (QDataStream::Qt_4_1);
	out << data;
	emit saved();
}	

void DSaver::read_string()
{
	QString data;
	QFile file (filename);
	if (file.exists())
	{
		if (!file.open (QIODevice::ReadOnly))
			return;
		QDataStream in (&file);
		in.setVersion (QDataStream::Qt_4_1);
		while (!file.atEnd())
		{
			in >> data;
			emit string_ready (data);
		}
	}
}

void DSaver::set_file_name (QString newName)
{
	filename = newName;
}

void DSaver::get_file_name ()
{
	QString newName = QFileDialog::getOpenFileName (NULL, tr("Open datafile"), "/home/nkerah/avr/daq/gusb01", tr("Datafiles (*.bgb)"));
	filename = newName;
	emit name_ready();
}

void DSaver::accept_data_pack (DPack *pack)
{
	QFile file (filename);
	if (file.exists())
	{
		if (!file.open (QIODevice::Append))
			return;
	}
	else
	if (!file.open (QIODevice::WriteOnly))
		return;
		
	QDataStream out (&file);
	out.setVersion (QDataStream::Qt_4_1);
	QString data_string ="";
	for (int a = 0; a < 6; a++)
	{
		data_string.append(pack->data[a]);
		data_string.append(" ");
	}
//	out << pack;
	out << data_string;
	emit pack_saved();
		
}

void DSaver::read_data_pack ()
{
	DPack pack;
	QFile file (filename);
	if (file.exists())
	{
		if (!file.open (QIODevice::ReadOnly))
			return;
		QDataStream in (&file);
		in.setVersion (QDataStream::Qt_4_1);
		QString data_string = "";
		while (!file.atEnd())
		{
			in >> data_string;
			// обработка полученной строки
			
			emit pack_ready (&pack);
		}
	}
}
