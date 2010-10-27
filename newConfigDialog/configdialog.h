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
