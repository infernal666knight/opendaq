#ifndef DSAVER_H
#define DSAVER_H
#include <iostream>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include "dpack.h"

class DSaver : public QObject 
{
	Q_OBJECT

public:
	DSaver (QWidget *parent = 0);
	
public slots:

	void accept_string (QString data);
	void read_string ();
	void set_file_name (QString newName);
	void get_file_name ();
	void accept_data_pack (DPack *pack);
	void read_data_pack();	

signals:
	void saved();
	void pack_saved();
	void name_ready();
	void string_ready (QString data); 
	void pack_ready (DPack *pack);	

private:
	QString filename;	
};


#endif
