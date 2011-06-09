/*
 *  libdioxin.c
 *  gprc5
 *
 *  Created by Kevin Bradley on 6/4/11.
 *  Copyright 2011 Chronic-Dev Team. All rights reserved.
 *
 */

#include "libdioxin.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

#include "firmware.h"

#include "libirecovery.h"

#include <IOKit/IOTypes.h>
#include <IOKit/IOCFBundle.h>
#include <IOKit/usb/IOUSBLib.h>
#include <IOKit/IOCFPlugIn.h>

#ifndef WIN32
#include <libusb-1.0/libusb.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <setupapi.h>
#endif
#define BUFFER_SIZE 0x1000

static libusb_context* libdioxin_context = NULL;

char * devices_to_xml(idevice_info_t **devices, int itemCount) {
	

	char *xmlData = NULL;
	uint32_t length = 0;
	int i;
	plist_t deviceList = plist_new_array();
	
	for (i = 0; i < itemCount; i++)
	{
		idevice_info_t *currentDevice = devices[i];
		plist_t currentDevicePlist = plist_new_dict();
		plist_dict_insert_item(currentDevicePlist, "ProductType", plist_new_string(currentDevice->productType));
		plist_dict_insert_item(currentDevicePlist, "ProductVersion", plist_new_string(currentDevice->productVersion));
		plist_dict_insert_item(currentDevicePlist, "BuildVersion", plist_new_string(currentDevice->buildVersion));
		plist_dict_insert_item(currentDevicePlist, "DeviceName", plist_new_string(currentDevice->deviceName));
		plist_dict_insert_item(currentDevicePlist, "HardwareModel", plist_new_string(currentDevice->hardwareModel));
		plist_dict_insert_item(currentDevicePlist, "HardwarePlatform", plist_new_string(currentDevice->hardwarePlatform));
		plist_dict_insert_item(currentDevicePlist, "UniqueDeviceID", plist_new_string(currentDevice->uniqueDeviceID));
		plist_dict_insert_item(currentDevicePlist, "UniqueChipID", plist_new_uint(currentDevice->uniqueChipID));
		if (currentDevice->URL != NULL)
			plist_dict_insert_item(currentDevicePlist, "URL", plist_new_string(currentDevice->URL));
		
		free(currentDevice);
		plist_array_append_item(deviceList, currentDevicePlist);
			//free(currentDevicePlist);
		
	}

	plist_to_xml(deviceList, &xmlData, &length);
	return xmlData;
	
}

char *urlForDevice(idevice_info_t *mobileDevice)
{
	plist_t thePlist = NULL;
	plist_from_xml(firmware_2_plist, firmware_2_plist_len, &thePlist);
	
	char *product = mobileDevice->productType;
	char *urlString = NULL;
	
	plist_t productNode = plist_dict_get_item(thePlist, mobileDevice->productType);
	plist_t versionNode = plist_dict_get_item(productNode, mobileDevice->productVersion);
	if (versionNode == NULL)
	{
		printf("version not found!!!\n");
		return NULL;
	}
	plist_t buildNode = plist_dict_get_item(versionNode, mobileDevice->buildVersion);
	plist_t urlNode = plist_dict_get_item(buildNode, "URL");
	plist_get_string_val(urlNode, &urlString);
	plist_free(urlNode);
	plist_free(buildNode);
	plist_free(versionNode);
	plist_free(productNode);
	plist_free(thePlist);
	return (urlString);
}

idevice_info_t * device_get_info(char *uuids) {
	
	lockdownd_client_t client = NULL;
	idevice_t phone = NULL;
	idevice_error_t ret = IDEVICE_E_UNKNOWN_ERROR;
	int simple = 0;
	char *domain = NULL;
	char *key = NULL;
	plist_t node = NULL;

	if (uuids != 0) {
		ret = idevice_new(&phone, uuids);
		if (ret != IDEVICE_E_SUCCESS) {
			printf("No device found with uuid %s, is it plugged in?\n", uuids);
			return -1;
		}
	}
	else
	{
		ret = idevice_new(&phone, NULL);
		if (ret != IDEVICE_E_SUCCESS) {
			printf("No device found, is it plugged in?\n");
			return -1;
		}
	}
	
	if (LOCKDOWN_E_SUCCESS != (simple ?
							   lockdownd_client_new(phone, &client, "libdioxin"):
							   lockdownd_client_new_with_handshake(phone, &client, "libdioxin"))) {
		idevice_free(phone);
		return -1;
	}
	
	idevice_info_t *device_info = malloc(sizeof(idevice_info_t));
	/* run query and output information */
	if(lockdownd_get_value(client, domain, key, &node) == LOCKDOWN_E_SUCCESS) {
		if (node) {
			
			char *xmlData = NULL;
			uint32_t length = 0;
			plist_to_xml(node, &xmlData, &length);
	
			
				//debug("plist: %s\n", xmlData);
			
			char *bv = NULL;
			char *pt = NULL;
			char *pv = NULL;
			char *dn = NULL;
			char *hm = NULL;
			char *hp = NULL;
			char *ud = NULL;
			uint64_t uc;
			
			plist_t bv_node = plist_dict_get_item(node, "BuildVersion");
			plist_get_string_val(bv_node, &bv);
			
			plist_t pt_node = plist_dict_get_item(node, "ProductType");
			plist_get_string_val(pt_node, &pt);
			
			plist_t pv_node = plist_dict_get_item(node, "ProductVersion");
			plist_get_string_val(pv_node, &pv);
			
			plist_t dn_node = plist_dict_get_item(node, "DeviceName");
			plist_get_string_val(dn_node, &dn);
			
			plist_t hm_node = plist_dict_get_item(node, "HardwareModel");
			plist_get_string_val(hm_node, &hm);
			
			plist_t hp_node = plist_dict_get_item(node, "HardwarePlatform");
			plist_get_string_val(hp_node, &hp);
			
			plist_t uuid_node = plist_dict_get_item(node, "UniqueDeviceID");
			plist_get_string_val(uuid_node, &ud);
			
			plist_t uchip_node = plist_dict_get_item(node, "UniqueChipID");
			plist_get_uint_val(uchip_node, &uc);
			
			device_info->buildVersion = bv;
			device_info->productType = pt;
			device_info->productVersion = pv;
			device_info->deviceName	= dn;
			device_info->hardwareModel = hm;
			device_info->hardwarePlatform = hp;
			device_info->uniqueDeviceID = ud;
			device_info->uniqueChipID = uc;

			
			char *url = urlForDevice(device_info);
			if (url != NULL)
				device_info->URL = url;
			else
				device_info->URL = "http://fix.firmware2.plist.n0w";
			
				//uint8_t* deviceAddress = getAddressFromUUID(ud);
			
				//fprintf(stderr, "deviceAddress: %s", deviceAddress);
			
			plist_free(bv_node);
			plist_free(pt_node);
			plist_free(pv_node);
			plist_free(dn_node);
			plist_free(hm_node);
			plist_free(hp_node);
			plist_free(uuid_node);
			plist_free(uchip_node);
			
			if (domain != NULL)
				free(domain);
			lockdownd_client_free(client);
			idevice_free(phone);
			
			return device_info;
			
			
		}
	}
	
	if (domain != NULL)
		free(domain);
	lockdownd_client_free(client);
	idevice_free(phone);
	
	return 0;
}

idevice_info_t ** get_attached_devices(int *deviceCount) {
	
	char **dev_list = NULL;
	
	int i;
	if (idevice_get_device_list(&dev_list, &i) < 0) {
		fprintf(stderr, "ERROR: Unable to retrieve device list!\n");
		return -1;
	}
	idevice_info_t** list = (idevice_info_t**)malloc((i+1)*sizeof(idevice_info_t*));
	for (i = 0; dev_list[i] != NULL; i++) {
			//printf("%s\n", dev_list[i]);
		list[i] = device_get_info(dev_list[i]);
	}
	idevice_device_list_free(dev_list);
	*deviceCount = i;
	return list;
}

char * get_attached_devices_xml(int *deviceCount) {
	
	int counts = 0;
	idevice_info_t **devices = get_attached_devices(&counts);
	char *xmlData = devices_to_xml(devices, counts);
		//fprintf(stderr, "print_device_xml: %s\n", xmlData);
	free(devices);
	return xmlData;
}


#pragma mark libusb hooey

uint8_t* getAddressFromUUID(char *uuid) {
	
	debug("get adddress for UUID: %s\n", uuid);
	uint8_t *address;
	libusb_init(&libdioxin_context);
	
	int i = 0;
	struct libusb_device* usb_device = NULL;
	struct libusb_device** usb_device_list = NULL;
	struct libusb_device_handle* usb_handle = NULL;
	struct libusb_device_descriptor usb_descriptor;
	
	irecv_client_t *pclient = NULL;
	
	
	irecv_error_t error = IRECV_E_SUCCESS;
	int usb_device_count = libusb_get_device_list(libdioxin_context, &usb_device_list);
	for (i = 0; i < usb_device_count; i++) {
		usb_device = usb_device_list[i];
		libusb_get_device_descriptor(usb_device, &usb_descriptor);
		if (usb_descriptor.idVendor == APPLE_VENDOR_ID) {
			fprintf(stderr, "apple vendor\n");
			/* verify this device is in a mode we understand */
			if (usb_descriptor.idProduct == 0x129e){
				
				
				debug("opening device %04x:%04x...\n", usb_descriptor.idVendor, usb_descriptor.idProduct);
				
				
				
				libusb_open(usb_device, &usb_handle);
				if (usb_handle == NULL) {
					libusb_free_device_list(usb_device_list, 1);
					libusb_close(usb_handle);
					libusb_exit(libdioxin_context);
					return NULL;
				}
				//libusb_free_device_list(usb_device_list, 1);
				
				irecv_client_t client = (irecv_client_t) malloc(sizeof(struct irecv_client));
				if (client == NULL) {
					libusb_close(usb_handle);
					libusb_exit(libdioxin_context);
					return NULL;
				}

				
				memset(client, '\0', sizeof(struct irecv_client));
				client->iface = 0;
				client->handle = usb_handle;
				client->mode = usb_descriptor.idProduct;

				error = irecv_set_configuration(client, 1);
				if (error != IRECV_E_SUCCESS) {
					fprintf(stderr, "set config fail!!!\n");
					return NULL;
				}
		
				error = irecv_set_interface(client, 0, 0);
				
					if (error != IRECV_E_SUCCESS) {
					
					
					fprintf(stderr, "set interface 0, 0 fail!!!\n");
						
					}
				
				error = irecv_set_interface(client, 1, 1);	
				
				
				if (error != IRECV_E_SUCCESS) {
					
					fprintf(stderr, "set interface 1,1 fail!!!\n");
					return NULL;
				}
				
				/* cache usb serial */
				irecv_get_string_descriptor_ascii(client, usb_descriptor.iSerialNumber, (unsigned char*) client->serial, 255);
					//debug("this far 3 %s?\n", client->serial);
				
				*address = libusb_get_device_address(usb_device);
				
					//debug("address: %s", address);
			//	if (!strcmp(client->serial, uuid))
//				{
//		
//					*address = libusb_get_device_address(usb_device);
//					
//					debug("address: %s", address);
//					printf("we got a match!\n");
//					*pclient = client;
//					return address;
//				}
					
		}
				printf("no luck!\n");
				
			
		}
	}
	
	return NULL;

}



#pragma mark print / debug


int print_device_xml()
{
	int counts = 0;
	idevice_info_t **devices = get_attached_devices(&counts);
	char *xmlData = devices_to_xml(devices, counts);
	fprintf(stderr, "print_device_xml: %s\n", xmlData);
	free(xmlData);
	free(devices);
	
}


int print_device_info()
{
	
	int i = 0;
	int counts = 0;
	idevice_info_t **devices = get_attached_devices(&counts);
	
	for (i = 0; i < counts; i++)
	{
		idevice_info_t *deviceInfo = devices[i];
		printf("device %i of %i uuid: %s\n\n", i+1, counts, deviceInfo->uniqueDeviceID);
		printf("%s hardware model: %s hardware platform: %s\n", deviceInfo->deviceName, deviceInfo->hardwareModel, deviceInfo->hardwarePlatform);
		printf("%s running %s (%s)\n\n", deviceInfo->productType, deviceInfo->productVersion, deviceInfo->buildVersion);
		free(deviceInfo);
	}

	free(devices);
	return 0;
}