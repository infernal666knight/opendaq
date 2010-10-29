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
#include "dcurve.h"

CurveData::CurveData():
    d_count(0)
{
//	double x = 0;
//	double y = 0;
//	append (&x, &y, 1);
}

void CurveData::append(double *x, double *y, int count)
{
    int newSize = ( (d_count + count) / 1000 + 1 ) * 1000;
    if ( newSize > size() )
    {
        d_x.resize(newSize);
        d_y.resize(newSize);
    }

    for ( register int i = 0; i < count; i++ )
    {
        d_x[d_count + i] = x[i];
        d_y[d_count + i] = y[i];
    }
    d_count += count;
}

int CurveData::count() const
{
    return d_count;
}

int CurveData::size() const
{
    return d_x.size();
}

const double *CurveData::x() const
{
    return d_x.data();
}

const double *CurveData::y() const
{
    return d_y.data();
}

void CurveData::clear()
{
	d_x.clear();
	d_y.clear();
}

/*	DCurve implementation		*/

DCurve::DCurve (QWidget *parent) : QObject (parent)//, d_data (NULL) 
{
//	curve = new QwtPlotCurve;
	for (int a = 0; a < 6; a++)
	{
		channel_curve[a] = new QwtPlotCurve;
		channel_data[a] = new CurveData;
	}

	curX = 0;
	maxX = 50;
	stepX = 1;
	curY = 0;

	bufX = &curX;
	bufY = &curY;
}

void DCurve::clear()
{
	curX = 0;
	maxX = 50;
	stepX = 1;
	curY = 0;
	for (int a = 0; a < 6; a++)
	{
		channel_data[a]->clear();
		channel_curve[a]->detach();
	}
}
/*
double DCurve::getMaxX()
{
	return maxX;
}

double DCurve::getCurX()
{
	return curX;
}

double DCurve::getStepX()
{
	return stepX;
}

void DCurve::setMaxX (double x)
{
	if ( (x != maxX) && (x > 0) )
		maxX = x;
}

void DCurve::setCurX (double x)
{		
	if ( (x != curX) && (x < maxX) && (x > -1) )
		curX = x;
}

void DCurve::setStepX (double x)
{
	if ( (x !=stepX) && (x < maxX) && (x > 0) )
		stepX = x;
}
*/
void DCurve::accept_data_pack (DPack *pack)
{
//	fprintf (stderr, "Accepting data pack.\n");
	curX += stepX;
	fprintf (stderr, "DCurve: stepX = %f; curX = %f.\n ", stepX, curX);
	for (int a = 0; a < 6; a++)
	{
		curY = pack->data[a].toDouble();
	//	fprintf (stderr, "toDouble() : %f.\n", curY);
		channel_data[a]->append (&curX, &curY, 1);
	//	fprintf (stderr, "Appended.\n");
		channel_curve[a]->setRawData (channel_data[a]->x(), channel_data[a]->y(), channel_data[a]->count());
	//	fprintf (stderr, "setRawData() done.\n");
	}
	emit pack_accepted();
//	fprintf (stderr, "DCurve: SIGNAL: pack_accepted.\n");
}
