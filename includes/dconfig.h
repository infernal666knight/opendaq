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

#ifndef DCONFIG_H
#define DCONFIG_H

#include <QString>
#include <QColor>
#include <inttypes.h>
#include <stdio.h>
#define SINGLE_MODE 0
#define CYCLED_MODE 1
#define SCHEDULED_MODE 2

// Cycled mode definitions

#define CYCLE_INFINITE 1
#define CYCLE_NON_INFINITE 0

class DConfig
{
public:
	DConfig();
	unsigned int table_mod;
	unsigned int chart_mod;
	unsigned int measure_num;
	unsigned int measure_interval;
	QString filename;
	unsigned int mode;
	// cycle mode variables;
	short unsigned int cycle_mode;
	unsigned int cycle_num;
	unsigned int cycle_interval;
	// schedule mode variables;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	uint8_t repeat;
	unsigned int repeat_interval;
	QColor colors[6];	
};

#endif
