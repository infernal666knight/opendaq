#include <QtGui>
#include "mwindow.h"

MWindow::MWindow (QWidget *parent) : QMainWindow (parent)
{
	setupUi (this);

	move (300,200);

	saver = new DSaver(this);
	config_dialog = new ConfigDialog (this);
	process_dialog = new ProcessDialog (this);

   	connect (config_dialog, SIGNAL (config_ready(DConfig *)), process_dialog, SLOT (set_config(DConfig *)));
	connect ( config_dialog, SIGNAL ( done () ), this, SLOT ( begin_measure() ));
	connect ( closeButton, SIGNAL ( clicked () ), this, SLOT ( close() ));
}

void MWindow::on_newButton_clicked () 
{
	config_dialog->renew();
	if (config_dialog->isHidden())
	{
		config_dialog->show();	
	}
	else 
	{
		config_dialog->activateWindow();
	}
}

void MWindow::begin_measure()
{
	process_dialog->renew();
	config_dialog->hide();
	if (process_dialog->isHidden())
	{
		process_dialog->show();
	}
	else
	{
			process_dialog->activateWindow();
	}
}

void MWindow::on_aboutButton_clicked ()
{
}
