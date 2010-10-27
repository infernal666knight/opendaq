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
