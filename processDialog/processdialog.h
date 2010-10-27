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


#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H
#include <QtGui>
#include <QDialog>
#include <qwt_plot_grid.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/dthread.h"
#include "../includes/dconfig.h"
#include "../includes/dcurve.h"
#include "../includes/dsaver.h"
#include "ui_processdialog.h"
#include "../includes/dpack.h"

class ProcessDialog : public QDialog, public Ui::processDialog
{
	Q_OBJECT
public:	
	ProcessDialog (QWidget *parent = 0);
	unsigned int zone_length, start_x, end_x;

public slots:
	void renew();
	void set_config (DConfig *cfg);
	void process_pack (DPack *pack);
	void start_thread();

signals:
	void stopped(); // ????????????????
	void test_data_pack (DPack *pack);
	
private slots:

	void graph_update(int new_length);
	void graph_next_frame();
	void on_stopButton_clicked();
//	void on_testButton_clicked();	
	void channel1_box_clicked();
	void channel2_box_clicked();
	void channel3_box_clicked();
	void channel4_box_clicked();
	void channel5_box_clicked();
	void channel6_box_clicked();
	void done();	

private:
	int row;
	bool running;
	DPack test_pack;
	DConfig *config;
	DCurve *aCurve;
	DSaver *saver;
	DThread *writeThread;
};

#endif
