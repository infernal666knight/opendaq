#include "dconfig.h"
DConfig::DConfig()
{
	table_mod = 1;
	chart_mod = 1;
	measure_num = 50;
	measure_interval = 10;
	filename = "default.dat";
	mode = SINGLE_MODE;
	// cycled mode
	cycle_mode = CYCLE_NON_INFINITE;
	cycle_num = 3;
	cycle_interval = 10000;
	//scheduled mode
	hour = 0;
	minute = 0;
	second = 0;
	repeat = 0;
	repeat_interval = 90; 
	colors[0] = Qt::black;
	colors[1] = Qt::red;
	colors[2] = Qt::darkRed;
	colors[3] = Qt::darkGreen;
	colors[4] = Qt::blue;
	colors[5] = Qt::darkMagenta;
	fprintf (stderr, "DConfig class object created and initialized properly.\n");
}
