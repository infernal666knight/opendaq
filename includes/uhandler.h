#ifndef UHANDLER_H
#define UHANDLER_H
#include <QObject>
#include <QWidget>
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
//	QString string_data[6];
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
	int readbuf; // buffer's single byte
	int nbytes;  // byte counter

	int getString (usb_dev_handle *dev, int index, int langid, char *buf, int buflen);
	int openDevice (usb_dev_handle **device, int vendor, char *vendorName, int product, char *productName);
};

#endif
