#ifndef DCURVE_H
#define DCURVE_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <qwt_plot_curve.h>
#include <qwt_array.h>
#include "dpack.h"
#include <stdio.h>
#include <stdlib.h>

class CurveData
{
    // A container class for growing data
public:
	CurveData();
	void append(double *x, double *y, int count);
   	int count() const;
    	int size() const;
    	const double *x() const;
	const double *y() const;
	void clear();

private:
	int d_count;
	QwtArray<double> d_x;
	QwtArray<double> d_y;
};


/*	################ DCurve definition #############	*/

class DCurve : public QObject

{
	Q_OBJECT
public:
	DCurve (QWidget *parent = 0);
		
	QwtPlotCurve *channel_curve[6];

	void clear();
	
	double curX,maxX;	// x axis variables;
//	double start_x, end_x;	// frame borders;
//	double zone_length;
	double stepX; 

	double curY;

	double *bufX;		// pointer to curX;
	double *bufY;		// pointer to curY

	double getMaxX ();	// returns maxX;
	double getCurX ();	// returns curX;
	double getStepX ();	// returns stepX;

	void setMaxX (double x);
	void setCurX (double x);
	void setStepX (double x);
	

public slots:
	void accept_data_pack (DPack *pack);

signals:
	//void accepted ();
	void pack_accepted ();

private:
	CurveData *channel_data[6];
};

#endif
