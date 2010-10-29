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
#include "configdialog.h"

ConfigDialog::ConfigDialog (QWidget *parent) : QDialog (parent)
{
	setupUi (this);
	config = new DConfig;
	connect (single_button, SIGNAL ( clicked() ), this, SLOT (single_button_clicked()) );
	connect (cycled_button, SIGNAL ( clicked() ), this, SLOT (cycled_button_clicked()) );
	connect (scheduled_button, SIGNAL ( clicked() ), this, SLOT (scheduled_button_clicked()) );
	connect (schedule_repeat, SIGNAL ( clicked() ), this, SLOT (schedule_repeat_clicked()) );
	connect (cycle_infinite, SIGNAL ( clicked() ), this, SLOT (cycle_infinite_button_clicked()));
	connect (filename_button, SIGNAL ( clicked() ), this, SLOT (filename_button_clicked()) );

	connect (color_button1, SIGNAL ( clicked() ), this, SLOT (color_button1_clicked()));
	connect (color_button2, SIGNAL ( clicked() ), this, SLOT (color_button2_clicked()));
	connect (color_button3, SIGNAL ( clicked() ), this, SLOT (color_button3_clicked()));
	connect (color_button4, SIGNAL ( clicked() ), this, SLOT (color_button4_clicked()));
	connect (color_button5, SIGNAL ( clicked() ), this, SLOT (color_button5_clicked()));
	connect (color_button6, SIGNAL ( clicked() ), this, SLOT (color_button6_clicked()));

	connect (proceed_button, SIGNAL ( clicked() ), this, SLOT (make_config()));

	connect (interval_slider, SIGNAL (valueChanged(int)), this, SLOT (calculate_time()));
	connect (measure_slider, SIGNAL (valueChanged(int)), this, SLOT (calculate_time()));

// displaying default settings

	table_spin->setValue (config->table_mod);
	chart_spin->setValue (config->chart_mod);
	measure_spin->setValue (config->measure_num);
	interval_spin->setValue (config->measure_interval);
	// schedule values
	hours_box->setValue (config->hour);
	minutes_box->setValue (config->minute);
	seconds_box->setValue (config->second);

	// TODO: обработка байта Repeat
	
	switch (config->cycle_mode) 
	{
		case CYCLE_INFINITE:
			cycle_infinite->setChecked (true);
			break;
		
		case CYCLE_NON_INFINITE:
			cycle_number_slider->setValue (config->cycle_num);
			break;
	}
	
	cycle_interval_slider->setValue (config->cycle_interval);	

	filename_edit->setText (config->filename);

	QString temp = tr("<font color='%1'>%2</font>");
	QString text = "Channel1";
	color_label1->setText (temp.arg (config->colors[0].name(), text));

	temp = tr("<font color='%1'>%2</font>");
	text = "Channel2";
	color_label2->setText (temp.arg (config->colors[1].name(), text));
	
	temp = tr("<font color='%1'>%2</font>");
	text = "Channel3";
	color_label3->setText (temp.arg (config->colors[2].name(), text));
	
	temp = tr("<font color='%1'>%2</font>");
	text = "Channel4";
	color_label4->setText (temp.arg (config->colors[3].name(), text));
	
	temp = tr("<font color='%1'>%2</font>");
	text = "Channel5";
	color_label5->setText (temp.arg (config->colors[4].name(), text));
	
	temp = tr("<font color='%1'>%2</font>");
	text = "Channel6";
	color_label6->setText (temp.arg (config->colors[5].name(), text));
}

void ConfigDialog::renew()
{
        config->table_mod = 1;
        config->chart_mod = 1;
        config->measure_num = 50;
        config->measure_interval = 10;
        config->filename = "default.dat";
        config->mode = SINGLE_MODE;
        config->hour = 0;
        config->minute = 0;
        config->second = 0;
        config->repeat = 0;
        config->repeat_interval = 90; 

	config->cycle_mode = CYCLE_NON_INFINITE;
	config->cycle_num = 3;
	config->cycle_interval = 10000;
	
        config->colors[0] = Qt::black;
        config->colors[1] = Qt::red;
        config->colors[2] = Qt::darkRed;
        config->colors[3] = Qt::darkGreen;
        config->colors[4] = Qt::blue;
        config->colors[5] = Qt::darkMagenta;
        fprintf (stderr, "ConfigDialog: config renewed.\n");
	table_spin->setValue (config->table_mod);
        chart_spin->setValue (config->chart_mod);
        measure_spin->setValue (config->measure_num);
        interval_spin->setValue (config->measure_interval);
        filename_edit->setText (config->filename);

	hours_box->setValue (config->hour);
        minutes_box->setValue (config->minute);
        seconds_box->setValue (config->second);

        // TODO: обработка байта Repeat

        switch (config->cycle_mode)
        {
                case CYCLE_INFINITE:
                        cycle_infinite->setChecked (true);
                        break;

                case CYCLE_NON_INFINITE:
                        cycle_number_slider->setValue (config->cycle_num);
                        break;
        }

        cycle_interval_slider->setValue (config->cycle_interval);
        

	QString temp = tr("<font color='%1'>%2</font>");
        QString text = "Channel1";
        color_label1->setText (temp.arg (config->colors[0].name(), text));
        temp = tr("<font color='%1'>%2</font>");
        text = "Channel2";
        color_label2->setText (temp.arg (config->colors[1].name(), text));
        temp = tr("<font color='%1'>%2</font>");
        text = "Channel3";
        color_label3->setText (temp.arg (config->colors[2].name(), text));
        temp = tr("<font color='%1'>%2</font>");
        text = "Channel4";
        color_label4->setText (temp.arg (config->colors[3].name(), text));
        temp = tr("<font color='%1'>%2</font>");
        text = "Channel5";
        color_label5->setText (temp.arg (config->colors[4].name(), text));
        temp = tr("<font color='%1'>%2</font>");
        text = "Channel6";
        color_label6->setText (temp.arg (config->colors[5].name(), text));
	fprintf (stderr, "ConfigDialog renewed.\n");
}

void ConfigDialog::make_config()
{
	config->table_mod = table_spin->value();
	fprintf (stderr, "ConfigDialog::make_config: table_mod : %d  \n", config->table_mod);
	config->chart_mod = chart_spin->value();
	fprintf (stderr, "ConfigDialog::make_config: chart_mod : %d  \n", config->chart_mod);
	config->measure_num = measure_spin->value();
	fprintf (stderr, "ConfigDialog::make_config: measure_num : %d  \n", config->measure_num);
	config->measure_interval = interval_spin->value();
	fprintf (stderr, "ConfigDialog::make_config: measure_interval :%d  \n", config->measure_interval);
	config->filename = filename_edit->text();

	if (cycled_button->isChecked())
	{
		config->mode = CYCLED_MODE;
		if (cycle_infinite->isChecked())
		{
			config->cycle_mode = CYCLE_INFINITE;	
			config->cycle_num = 1;
		}		
		else 
		{
			config->cycle_mode = CYCLE_NON_INFINITE;
			config->cycle_num = cycle_number_spin->value();
		}

		config->cycle_interval = cycle_interval_spin->value();
	}

	if (scheduled_button->isChecked())
	{
		config->mode = SCHEDULED_MODE;
		config->hour = 3600*hours_box->value();
		config->minute = 60*minutes_box->value();
		config->second = seconds_box->value();
		
		if (mn_box->isChecked())
			config->repeat |= (1 << 0);
		else 
			config->repeat ^= config->repeat&(1 << 0);

		if (tue_box->isChecked())
			config->repeat |= (1 << 1);
		else 
			config->repeat ^= config->repeat&(1 << 0);
	
		if (wd_box->isChecked())
			config->repeat |= (1 << 2);		
		else 
			config->repeat ^= config->repeat&(1 << 0);

		if (th_box->isChecked())
			config->repeat |= (1 << 3);
		else 
			config->repeat ^= config->repeat&(1 << 0);
	
		if (fr_box->isChecked())
			config->repeat |= (1 << 4);
		else 
			config->repeat ^= config->repeat&(1 << 0);

		if (sat_box->isChecked())
			config->repeat |= (1 << 5);
		else 
			config->repeat ^= config->repeat&(1 << 0);

		if (sd_box->isChecked())	
			config->repeat |= (1 << 6);
		else 
			config->repeat ^= config->repeat&(1 << 0);
	}
	emit config_ready (config);
	emit done();
}

void ConfigDialog::single_button_clicked() 
{
	cycle_box->setDisabled (true);
	schedule_box->setDisabled (true);
	config->mode = SINGLE_MODE;
}

void ConfigDialog::cycled_button_clicked()
{
	schedule_box->setDisabled (true);
	cycle_box->setEnabled (true);
	config->mode = CYCLED_MODE;
}

void ConfigDialog::cycle_infinite_button_clicked()
{
	if (cycle_infinite->isChecked())
	{
		cycle_number_slider->setDisabled (true);
		cycle_number_spin->setDisabled (true);
		cycle_number_label->setDisabled (true);
	}
	else
	{
		cycle_number_slider->setEnabled (true);
		cycle_number_spin->setEnabled (true);
		cycle_number_label->setEnabled (true);
	}	
}

void ConfigDialog::scheduled_button_clicked()
{	
	schedule_box->setEnabled (true);
	cycle_box->setDisabled (true);
	config->mode = SCHEDULED_MODE;
}

void ConfigDialog::schedule_repeat_clicked()
{
	if (schedule_repeat->isChecked())
	{
		mn_box->setEnabled (true);
		sd_box->setEnabled (true);
		tue_box->setEnabled (true);
		wd_box->setEnabled (true);
		th_box->setEnabled (true);
		sat_box->setEnabled (true);
		fr_box->setEnabled (true);
	}
	else 
	{
		mn_box->setDisabled (true);
		sd_box->setDisabled (true);
		tue_box->setDisabled (true);
		wd_box->setDisabled (true);
		th_box->setDisabled (true);
		sat_box->setDisabled (true);
		fr_box->setDisabled (true);
	}
}

void ConfigDialog::filename_button_clicked()
{
	QFileDialog::Options options;
	QString selectedFilter = "";
	QString fileName = QFileDialog::getSaveFileName (this,
						tr("QFileDialog::getSaveFileName()"),
						filename_edit->text(),
						tr("Monitoring data files (*.dat)"),
						&selectedFilter,
						options);
	if (!fileName.isEmpty())
	{
		fileName += ".dat";
		filename_edit->setText (fileName);
	}
}

void ConfigDialog::calculate_time()
{
	int meas = measure_spin->value();
	int interval = interval_spin->value();
	int time = meas*interval;
	QString temp;
	temp.setNum(time);
	series_time_edit->setText (temp);
}

void ConfigDialog::color_button1_clicked()
{
	QColor color  = QColorDialog::getColor(Qt::green, this);
		QString temp = tr("<font color='%1'>%2</font>");
		QString text = "Channel1";
		color_label1->setText (temp.arg (color.name(), text));
		config->colors[1] = color;
}

void ConfigDialog::color_button2_clicked()
{
	QColor color  = QColorDialog::getColor(Qt::green, this);
		QString temp = tr("<font color='%1'>%2</font>");
		QString text = "Channel2";
		color_label2->setText (temp.arg (color.name(), text));
		config->colors[2] = color;
}

void ConfigDialog::color_button3_clicked()
{
	QColor color  = QColorDialog::getColor(Qt::green, this);
		QString temp = tr("<font color='%1'>%2</font>");
		QString text = "Channel3";
		color_label3->setText (temp.arg (color.name(), text));
		config->colors[3] = color;
}

void ConfigDialog::color_button4_clicked()
{
	QColor color  = QColorDialog::getColor(Qt::green, this);
		QString temp = tr("<font color='%1'>%2</font>");
		QString text = "Channel4";
		color_label4->setText (temp.arg (color.name(), text));
		config->colors[4] = color;
}

void ConfigDialog::color_button5_clicked()
{
	QColor color  = QColorDialog::getColor(Qt::green, this);
		QString temp = tr("<font color='%1'>%2</font>");
		QString text = "Channel5";
		color_label5->setText (temp.arg (color.name(), text));
		config->colors[5] = color;
}

void ConfigDialog::color_button6_clicked()
{
	QColor color  = QColorDialog::getColor(Qt::green, this);
		QString temp = tr("<font color='%1'>%2</font>");
		QString text = "Channel6";
		color_label6->setText (temp.arg (color.name(), text));
		config->colors[6] = color;
}
