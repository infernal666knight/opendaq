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

#ifndef UHANDLER_H
#define UHANDLER_H
#include <QObject>
#include <QWidget>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <usb.h>
#include "dpack.h"

// defining the vendor and free shared PID
#define USBDEV_SHARED_VENDOR    0x16C0  /* VOTI */
#define USBDEV_SHARED_PRODUCT   0x05DC  /* Obdev's free shared PID */
//error messages :
#define USB_ERROR_NOTFOUND  1
#define USB_ERROR_ACCESS    2
#define USB_ERROR_IO        3

// Command_definitions
#define REPORT_VALUES 0
#define SET_CHANNEL 2
#define SET_REF 3
#define REPORT_ALL_CHANNELS 4
#define REPORT_SET_CHANNEL 5

// reference voltage selection
#define REF_INTERNAL 3
#define REF_EXTERNAL 4
#define REF_SUPPLY 5

class UHandler : public QObject
{
	Q_OBJECT

public:
	double ccof; // conversion coefficient;
	double results[6];
	DPack pack;
	UHandler (QWidget *parent = 0);	
	
public slots:
	void conversion_request();
	void set_ccof (double new_ccof);

signals:
	void data_ready (); // void readiness  flag (signal)
	void data_ready (DPack *datapack);
	void deviceError ();

private:
	usb_dev_handle *handle;
	unsigned char buffer[8];
	int nbytes;  // byte counter

	int getString (usb_dev_handle *dev, int index, int langid, char *buf, int buflen);
	int openDevice (usb_dev_handle **device, int vendor, char *vendorName, int product, char *productName);
};

#endif
