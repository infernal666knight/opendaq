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

#include "uhandler.h"

UHandler::UHandler (QWidget *parent) : QObject (parent)
{
	// initializing public variables	
	ccof = 0.02;	// AD conversion coefficient.
	
	char boardID[] = "USBModuleV01";	// hardware ID
	char devprID[] = "www.bgb.netii.net";  // developer's ID

	usb_init ();
	if (!openDevice (&handle, USBDEV_SHARED_VENDOR, devprID, USBDEV_SHARED_PRODUCT, boardID)){
		emit deviceError();
		fprintf (stderr, "UHandler: Cannot open device.\n");
	}
//	fprintf (stderr, "UHandler: constructor did all successful.\n");
}

void UHandler::conversion_request()
{
	nbytes = usb_control_msg(
	handle,
	USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
	REPORT_ALL_CHANNELS,
	0,
	0,
	(char *) buffer,
	sizeof (buffer),
	1000);
	for (int a = 0; a < 6; a ++)
	{
		results[a] = buffer[a]*ccof;
	//	fprintf (stderr, "UHandler: result  %d = %f\n", a, results[a]);
		pack.data[a] = QString::number (results[a], 'g', 6);
		
	}
	emit data_ready ();
	emit data_ready (&pack);
}

void UHandler::set_ccof (double newCcof)
{
	if ( (newCcof > 0) && (newCcof <= 1))
	{
		ccof = newCcof;
	}
}

int UHandler::getString (usb_dev_handle *dev, int index, int langid, char *buf, int buflen)
{

char    buffer[256];
int     rval, i;

        if((rval = usb_control_msg(dev, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, langid, buffer, sizeof(buffer), 1000)) < 0)
        return rval;
    if(buffer[1] != USB_DT_STRING)
        return 0;
    if((unsigned char)buffer[0] < rval)
        rval = (unsigned char)buffer[0];
    rval /= 2;
    /* lossy conversion to ISO Latin1 */
    for(i=1;i<rval;i++){
        if(i > buflen)  /* destination buffer overflow */
            break;
        buf[i-1] = buffer[2 * i];
        if(buffer[2 * i + 1] != 0)  /* outside of ISO Latin1 range */
            buf[i-1] = '?';
    }
    buf[i-1] = 0;
    return i-1;

}

int UHandler::openDevice (usb_dev_handle **device, int vendor, char *vendorName, int product, char *productName)
{

	fprintf (stderr, "UHandler: opening device.\n");
struct usb_bus      *bus;  // busses
struct usb_device   *dev;  // devices
usb_dev_handle      *handle = NULL; // handle for detected device
int                 errorCode = USB_ERROR_NOTFOUND; // error code %)
static int          didUsbInit = 0; // just an initialization indicator 

    if(!didUsbInit){  
        didUsbInit = 1;
        usb_init();
    }
    usb_find_busses();
    usb_find_devices();
    for(bus=usb_get_busses(); bus; bus=bus->next){ // looking among all busses and devices
        for(dev=bus->devices; dev; dev=dev->next){
            if(dev->descriptor.idVendor == vendor && dev->descriptor.idProduct == product){ // if vendor and id are matching needed ones
                char    string[256];
                int     len;
                handle = usb_open(dev); /* we need to open the device in order to query strings */
                if(!handle){
                    errorCode = USB_ERROR_ACCESS;
                    fprintf(stderr, "Warning: cannot open USB device: %s\n", usb_strerror());
                    continue;
                }
                if(vendorName == NULL && productName == NULL){  /* name does not matter */
                    break;
                }
                /* now check whether the names match: */
                len = getString (handle, dev->descriptor.iManufacturer, 0x0409, string, sizeof(string));
                if(len < 0){
                    errorCode = USB_ERROR_IO;
                    fprintf(stderr, "Warning: cannot query manufacturer for device: %s\n", usb_strerror());
                }else{
                    errorCode = USB_ERROR_NOTFOUND;
                    fprintf(stderr, "seen device from vendor ->%s<-\n", string);
                    if(strcmp(string, vendorName) == 0){
                        len = getString (handle, dev->descriptor.iProduct, 0x0409, string, sizeof(string));
                        if(len < 0){
                            errorCode = USB_ERROR_IO;
                            fprintf(stderr, "Warning: cannot query product for device: %s\n", usb_strerror());
                        }else{
                            errorCode = USB_ERROR_NOTFOUND;
                            fprintf(stderr, "seen product ->%s<-\n", string);
                            if(strcmp(string, productName) == 0)
                                break;
                        }
                    }
                }
                usb_close(handle);
                handle = NULL;
            }
        }
        if(handle)
            break;
    }
    if(handle != NULL){
        errorCode = 0;
        *device = handle;
    }
    return errorCode;
}
