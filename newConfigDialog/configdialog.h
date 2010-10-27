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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include "ui_configdialog.h"
#include "../includes/dconfig.h"

class ConfigDialog : public QDialog, public Ui::Dialog
{
	Q_OBJECT
public:
	ConfigDialog (QWidget *parent = 0);
	DConfig *config;	

public slots:
	void renew();
	void make_config();

private slots:
	void single_button_clicked();
	void cycled_button_clicked();
	void cycle_infinite_button_clicked();
	void scheduled_button_clicked();
	void schedule_repeat_clicked();
	void filename_button_clicked();
	

	void calculate_time();

	void color_button1_clicked();
	void color_button2_clicked();
	void color_button3_clicked();
	void color_button4_clicked();
	void color_button5_clicked();
	void color_button6_clicked();

signals:
	void config_ready (DConfig *config);
	void done();
};
#endif
