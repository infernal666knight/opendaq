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

#include "dconfig.h"
DConfig::DConfig()
{
	table_mod = 1;
	chart_mod = 1;
	measure_num = 50;
	measure_interval = 10;
	filename = "default.dat";
	mode = SINGLE_MODE;
	// cycled mode
	cycle_mode = CYCLE_NON_INFINITE;
	cycle_num = 3;
	cycle_interval = 10000;
	//scheduled mode
	hour = 0;
	minute = 0;
	second = 0;
	repeat = 0;
	repeat_interval = 90; 
	colors[0] = Qt::black;
	colors[1] = Qt::red;
	colors[2] = Qt::darkRed;
	colors[3] = Qt::darkGreen;
	colors[4] = Qt::blue;
	colors[5] = Qt::darkMagenta;
	fprintf (stderr, "DConfig class object created and initialized properly.\n");
}
