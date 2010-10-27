#ifndef DCONFIG_H
#define DCONFIG_H

#include <QString>
#include <QColor>
#include <inttypes.h>
#include <stdio.h>
#define SINGLE_MODE 0
#define CYCLED_MODE 1
#define SCHEDULED_MODE 2

// Cycled mode definitions

#define CYCLE_INFINITE 1
#define CYCLE_NON_INFINITE 0

class DConfig
{
public:
	DConfig();
	unsigned int table_mod;
	unsigned int chart_mod;
	unsigned int measure_num;
	unsigned int measure_interval;
	QString filename;
	unsigned int mode;
	// cycle mode variables;
	short unsigned int cycle_mode;
	unsigned int cycle_num;
	unsigned int cycle_interval;
	// schedule mode variables;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	uint8_t repeat;
	unsigned int repeat_interval;
	QColor colors[6];	
};

#endif
