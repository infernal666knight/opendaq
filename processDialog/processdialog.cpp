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

#include "processdialog.h"
ProcessDialog::ProcessDialog (QWidget *parent) : QDialog (parent)
{
	setupUi (this);
	writeThread = new DThread;
	saver = new DSaver;
	aCurve = new DCurve;
	config = new DConfig;
	fprintf (stderr, "Objects initialized.\n");	
	zone_length = config->measure_num;
	zone_length_spin->setValue (zone_length);
	start_x = 0;
//	zone_length = 50;
//	start_x = 0;
//	end_x = zone_length;
	// ############## STANDART WIDGETS INITIALIZATION ############
	
	//zone_length_spin->setValue (static_cast<int>(aCurve->zone_length));
//	zone_length_spin->setValue (50);
//	QString scale_temp = QString::number (aCurve->maxX/zone_length, 'g', 4);
//	scale_value_label->setText (scale_temp); 
	saver->set_file_name ("default.dat");
	running = false;
	indicator_label->setText ("<font color=red> <b> NOT RUNNING </b> </font>");
	tabWidget->setTabText (0, "Diagram");
	tabWidget->setTabText (1, "Scheme");

	/*	Connections	*/
	connect (aCurve, SIGNAL ( pack_accepted () ), plot, SLOT ( replot() ));
	connect (aCurve, SIGNAL ( pack_accepted () ), this, SLOT (graph_next_frame()) );
	connect (writeThread, SIGNAL ( text_data (DPack *) ), this, SLOT ( process_pack (DPack *) ));
	connect (writeThread, SIGNAL ( chart_data (DPack *) ), aCurve, SLOT ( accept_data_pack (DPack *) ));
	connect (writeThread, SIGNAL ( save_data (DPack *) ), saver, SLOT (accept_data_pack (DPack *) ));
	connect (writeThread, SIGNAL ( done()), this, SLOT ( done()));
	connect (this, SIGNAL (rejected()), writeThread, SLOT (stop_thread()));
	// test routine
//	connect (this, SIGNAL (test_data_pack (DPack *)), this, SLOT ( process_pack (DPack *) ));
//	connect (this, SIGNAL (test_data_pack (DPack *)), aCurve, SLOT ( accept_data_pack (DPack *) ));
//	connect (this, SIGNAL (test_data_pack (DPack *)), saver, SLOT ( accept_data_pack (DPack *) ));
	/*	Properties	*/
	connect (channel1_box, SIGNAL (clicked()), this, SLOT (channel1_box_clicked()));
	connect (channel2_box, SIGNAL (clicked()), this, SLOT (channel2_box_clicked()));
	connect (channel3_box, SIGNAL (clicked()), this, SLOT (channel3_box_clicked()));
	connect (channel4_box, SIGNAL (clicked()), this, SLOT (channel4_box_clicked()));
	connect (channel5_box, SIGNAL (clicked()), this, SLOT (channel5_box_clicked()));
	connect (channel6_box, SIGNAL (clicked()), this, SLOT (channel6_box_clicked()));
	connect (zone_length_spin, SIGNAL (valueChanged (int)), this, SLOT (graph_update (int)));
	connect (this, SIGNAL (closed()), this, SLOT (renew()));
	
	fprintf (stderr, "Connections established,\n");
	// ###################  QwtPlot initialization ########################
       	for (int a = 0; a < 6; a ++)
	{
		QPen pen = QPen (config->colors[a]);
		pen.setWidth(2);
		aCurve->channel_curve[a]->setPen (pen);
        	aCurve->channel_curve[a]->attach (plot);
	}

        aCurve->setMaxX (config->measure_num); 
        aCurve->setStepX (config->chart_mod);
	fprintf (stderr, "ProcessDialog: stepx = config->chart_mod = %d.\n", config->chart_mod);

	QwtPlotGrid *grid = new QwtPlotGrid;
	
	grid->setMajPen (QPen (Qt::gray, 0, Qt::DotLine));
	grid->attach (plot);
	
	plot->setTitle ("Graphics diagram");
	plot->setCanvasBackground (Qt::white);
	plot->setAxisTitle (0,"Signal, V");
	plot->setAxisTitle (2,"Measure, num");
//	plot->setAxisScale (2, start_x, end_x, zone_length/10);		
	plot->setAxisScale (2, 0, config->measure_num, config->measure_num/10);
	//graph_update(zone_length);
	
	// ##################### TABLE INITIALIZATION #####################

	row = -1;
	display_table->setColumnCount (6);
	display_table->setRowCount(config->measure_num); 	
	for (int i = 0; i < 6; i++)
	{
		display_table->setColumnWidth (i, 40);
	}

	// ########### CHANNEL GROUP ######################

	QString temp = tr("<font color='%1'>%2</font>");
	QString text = "Ch1";
	channel1_label->setText (temp.arg (config->colors[0].name(), text));
	
	temp = tr("<font color='%1'>%2</font>");
	text = "Ch2";
	channel2_label->setText (temp.arg (config->colors[1].name(), text));
	
	temp = tr("<font color='%1'>%2</font>");
	text = "Ch3";
	channel3_label->setText (temp.arg (config->colors[2].name(), text));

	temp = tr("<font color='%1'>%2</font>");
	text = "Ch4";
	channel4_label->setText (temp.arg (config->colors[3].name(), text));

	temp = tr("<font color='%1'>%2</font>");
	text = "Ch5";
	channel5_label->setText (temp.arg (config->colors[4].name(), text));

	temp = tr("<font color='%1'>%2</font>");
	text = "Ch6";
	channel6_label->setText (temp.arg (config->colors[5].name(), text));

	fprintf (stderr, "ProcessDialog object created\n");
}

void ProcessDialog::graph_update(int new_length)
{
	zone_length = new_length;
	// TODO: реализовать смену start_x;
	graph_next_frame();
}

void ProcessDialog::graph_next_frame()
{
	if (aCurve->curX == start_x + zone_length)
	{
		start_x += zone_length; // или start_x = aCurve->curX;
		if (start_x + zone_length > config->measure_num)
			zone_length -= ((start_x + zone_length) - config->measure_num);
		if (start_x + zone_length != config->measure_num)
		plot->setAxisScale (2, start_x, start_x + zone_length, (start_x + zone_length)/10);	
		plot->replot();
	}
}

void ProcessDialog::renew()
{
	// Обнуление значений виджетов.
	display_table->clear();
	display_table->setRowCount (config->measure_num);
	aCurve->clear();		
	for (int i = 0; i < 6; i++)
        	aCurve->channel_curve[i]->attach (plot);
	plot->replot();
	row = -1;
}

void ProcessDialog::set_config (DConfig *cfg)
{
	renew();
	config = cfg;
	writeThread->set_config(cfg);
	saver->set_file_name (config->filename);
	switch (config->mode)
	{
		case SINGLE_MODE:
			aCurve->setMaxX (config->measure_num);
			//zone_length = aCurve->getMaxX();
			break;
		case CYCLED_MODE:
			aCurve->setMaxX (config->measure_num);
			//zone_length = aCurve->getMaxX();
			break;
		case SCHEDULED_MODE:
			aCurve->setMaxX (config->measure_num);
			//zone_length = aCurve->getMaxX();
			break;
	}
	aCurve->setStepX (config->chart_mod);
	//zone_length = config->measure_num;
	//zone_length = 50;
//	start_x = 0;
//	end_x = zone_length;
//	zone_length_spin->setValue (50);
	zone_length = config->measure_num;
	zone_length_spin->setValue (zone_length);
	start_x = 0;
	display_table->setRowCount (config->measure_num);
	plot->setAxisScale (2, 0, config->measure_num, config->measure_num/5);
//	graph_update(zone_length);
	plot->replot();
}

void ProcessDialog::process_pack (DPack *pack)
{
	row++;
	fprintf (stderr, "Row number %d:\n", row+1);
	for (int a = 0; a < 6; a++)
	{
		QString temp = pack->data[a];
		double dtemp = pack->data[a].toDouble();
		fprintf (stderr, "%f\n", dtemp);
		QTableWidgetItem *item = new QTableWidgetItem (temp);
		display_table->setItem (row, a, item);
	}	
	//if (aCurve->curX > end_x)
	//	emit graph_next_frame();	
}

void ProcessDialog::start_thread()
{
	writeThread->start();
}

void ProcessDialog::on_stopButton_clicked()
{
	QString sign = "S&top";
	QString indicator = "<font color=green> <b> RUNNING </b> </font>";
	if (running)
	{
		writeThread->stop_thread();
		writeThread->wait();
		emit stopped();
		sign = "S&tart";
		indicator = "<font color=red> <b> NOT RUNNING </b> </font>";
		running = false;
	}
	else
	{
		writeThread->start_thread();
		running = true;
	}
	indicator_label->setText (indicator);
	stopButton->setText (sign);
}

/*void ProcessDialog::on_testButton_clicked() 
{
	fprintf (stderr, "Creating test data pack.\n");
	for (int a = 0; a < 6; a++)
	{
		int d = rand() % 6;
		fprintf (stderr, "Random passed successfully.\n");
		test_pack.data[a].setNum (d);
		fprintf (stderr, "%d) %d\n", a, d);
	}	
	fprintf (stderr, "Test data pack created.\n");
	emit test_data_pack (&test_pack);
	fprintf (stderr, "Test data pack transmitted.\n");
}
*/
void ProcessDialog::channel1_box_clicked()
{
	if (channel1_box->isChecked())
	{
		aCurve->channel_curve[0]->attach(plot);
		plot->replot();
	}
	else
	{
		aCurve->channel_curve[0]->detach();
		plot->replot();
	}
}

void ProcessDialog::channel2_box_clicked()
{
	if (channel2_box->isChecked())
	{
		aCurve->channel_curve[1]->attach(plot);
		plot->replot();
	}
	else
	{
		aCurve->channel_curve[1]->detach();
		plot->replot();
	}

}
void ProcessDialog::channel3_box_clicked()
{
	if (channel3_box->isChecked())
	{
		aCurve->channel_curve[2]->attach(plot);
		plot->replot();
	}
	else
	{
		aCurve->channel_curve[2]->detach();
		plot->replot();
	}

}
void ProcessDialog::channel4_box_clicked()
{
	if (channel4_box->isChecked())
	{
		aCurve->channel_curve[3]->attach(plot);
		plot->replot();
	}
	else
	{
		aCurve->channel_curve[3]->detach();
		plot->replot();
	}

}
void ProcessDialog::channel5_box_clicked()
{
	if (channel5_box->isChecked())
	{
		aCurve->channel_curve[4]->attach(plot);
		plot->replot();
	}
	else
	{
		aCurve->channel_curve[4]->detach();
		plot->replot();
	}

}
void ProcessDialog::channel6_box_clicked()
{
	if (channel6_box->isChecked())
	{
		aCurve->channel_curve[5]->attach(plot);
		plot->replot();
	}
	else
	{
		aCurve->channel_curve[5]->detach();
		plot->replot();
	}
}

void ProcessDialog::done()
{
		writeThread->stop_thread();
		writeThread->wait();
		QString sign = "S&tart";
		running = false;
		stopButton->setText (sign);
		emit stopped();
}
