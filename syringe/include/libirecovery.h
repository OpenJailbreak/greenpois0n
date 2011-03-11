/**
  * GreenPois0n Syringe - libirecovery.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2008-2011 Nicolas Haunold
  * Portions Copyright (C) 2010 Ricky Taylor
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef LIBIRECOVERY_H
#define LIBIRECOVERY_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WIN32
#include <libusb-1.0/libusb.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define sleep(n) Sleep(1000 * n)
#endif

#ifdef __cplusplus
#	define EXT_C extern "C"
#else
#	define EXT_C extern
#endif

#ifdef LIBSYRINGE_DYNAMIC
#	define LIBIRECOVERY_DYNAMIC 1
#endif

#ifdef _WIN32
#	ifdef LIBIRECOVERY_DYNAMIC
#		ifdef LIBIRECOVERY_EXPORTS
#			define LIBIRECOVERY_EXPORT EXT_C __declspec(dllexport)
#		else
#			define LIBIRECOVERY_EXPORT EXT_C __declspec(dllimport)
#		endif
#	else
#		define LIBIRECOVERY_EXPORT EXT_C
#	endif
#else
#	define LIBIRECOVERY_EXPORT EXT_C __attribute__((visibility("default")))
#endif

#define APPLE_VENDOR_ID 0x05AC

#define CPID_UNKNOWN         -1
#define CPID_IPHONE2G      8900
#define CPID_IPOD1G        8900
#define CPID_IPHONE3G      8900
#define CPID_IPOD2G        8720
#define CPID_IPHONE3GS     8920
#define CPID_IPOD3G        8922
#define CPID_IPAD1G        8930
#define CPID_IPHONE4       8930
#define CPID_IPOD4G        8930
#define CPID_APPLETV2G     8930
#define CPID_IPHONE42      8930
#define CPID_IPAD2G_WIFI   8940
#define CPID_IPAD2G_GSM    8940
#define CPID_IPAD2G_CDMA   8940

#define BDID_UNKNOWN        -1
#define BDID_IPHONE2G        0
#define BDID_IPOD1G          2
#define BDID_IPHONE3G        4
#define BDID_IPOD2G          0
#define BDID_IPHONE3GS       0
#define BDID_IPOD3G          2
#define BDID_IPAD1G          2
#define BDID_IPHONE4         0
#define BDID_IPOD4G          8
#define BDID_APPLETV2G       10
#define BDID_IPHONE42        6
#define BDID_IPAD2G_WIFI     0
#define BDID_IPAD2G_GSM      2
#define BDID_IPAD2G_CDMA     4

#define DEVICE_UNKNOWN      -1
#define DEVICE_IPHONE2G      0
#define DEVICE_IPOD1G        1
#define DEVICE_IPHONE3G      2
#define DEVICE_IPOD2G        3
#define DEVICE_IPHONE3GS     4
#define DEVICE_IPOD3G        5
#define DEVICE_IPAD1G        6
#define DEVICE_IPHONE4       7
#define DEVICE_IPOD4G        8
#define DEVICE_APPLETV2G     9
#define DEVICE_IPHONE42     10
#define DEVICE_IPAD2G_WIFI  11
#define DEVICE_IPAD2G_GSM   12
#define DEVICE_IPAD2G_CDMA  13

enum {
	kRecoveryMode1 = 0x1280,
	kRecoveryMode2 = 0x1281,
	kRecoveryMode3 = 0x1282,
	kRecoveryMode4 = 0x1283,
	kDfuMode = 0x1227
};

typedef enum {
	IRECV_E_SUCCESS = 0,
	IRECV_E_NO_DEVICE = -1,
	IRECV_E_OUT_OF_MEMORY = -2,
	IRECV_E_UNABLE_TO_CONNECT = -3,
	IRECV_E_INVALID_INPUT = -4,
	IRECV_E_FILE_NOT_FOUND = -5,
	IRECV_E_USB_UPLOAD = -6,
	IRECV_E_USB_STATUS = -7,
	IRECV_E_USB_INTERFACE = -8,
	IRECV_E_USB_CONFIGURATION = -9,
	IRECV_E_PIPE = -10,
	IRECV_E_TIMEOUT = -11,
	IRECV_E_UNKNOWN_ERROR = -255
} irecv_error_t;

typedef enum {
	IRECV_RECEIVED = 1,
	IRECV_PRECOMMAND = 2,
	IRECV_POSTCOMMAND = 3,
	IRECV_CONNECTED = 4,
	IRECV_DISCONNECTED = 5,
	IRECV_PROGRESS = 6
} irecv_event_type;

typedef struct {
	int size;
	const char* data;
	double progress;
	irecv_event_type type;
} irecv_event_t;

struct irecv_client;
typedef struct irecv_client* irecv_client_t;
typedef const struct irecv_device* irecv_device_t;
typedef int(*irecv_event_cb_t)(irecv_client_t client, const irecv_event_t* event);

struct irecv_client {
	int debug;
	int config;
	int iface;
	int alt_iface;
	unsigned short mode;
	char serial[256];
	
#ifndef _WIN32
	libusb_device_handle* handle;
#else
	HANDLE handle;
	HANDLE hDFU;
	HANDLE hIB;
	LPSTR iBootPath;
	LPSTR DfuPath;
#endif
	
	irecv_event_cb_t progress_callback;
	irecv_event_cb_t received_callback;
	irecv_event_cb_t connected_callback;
	irecv_event_cb_t precommand_callback;
	irecv_event_cb_t postcommand_callback;
	irecv_event_cb_t disconnected_callback;
};

struct irecv_device {
	int index;
	const char* product;
	const char* model;
	unsigned int board_id;
	unsigned int chip_id;
	const char* url;
};

static const struct irecv_device irecv_devices[] = {
	{  DEVICE_IPHONE2G,   "iPhone1,1",  "m68ap",   BDID_IPHONE2G,     CPID_IPHONE2G,
	"http://appldnld.apple.com.edgesuite.net/content.info.apple.com/iPhone/061-7481.20100202.4orot/iPhone1,1_3.1.3_7E18_Restore.ipsw" },
	{  DEVICE_IPOD1G,     "iPod1,1",    "n45ap",   BDID_IPOD1G,       CPID_IPOD1G,
	"http://appldnld.apple.com.edgesuite.net/content.info.apple.com/iPod/SBML/osx/bundles/061-4841.20080714.bgy8O/iPod1,1_1.1.5_4B1_Restore.ipsw" },
	{  DEVICE_IPHONE3G,   "iPhone1,2",  "n82ap",   BDID_IPHONE3G,     CPID_IPHONE3G,
	"http://appldnld.apple.com/iPhone4/061-9853.20101122.Vfgt5/iPhone1,2_4.2.1_8C148_Restore.ipsw" },
	{  DEVICE_IPOD2G,     "iPod2,1",    "n72ap",   BDID_IPOD2G,       CPID_IPOD2G,
	"http://appldnld.apple.com/iPhone4/061-9855.20101122.Lrft6/iPod2,1_4.2.1_8C148_Restore.ipsw" },
	{  DEVICE_IPHONE3GS,  "iPhone2,1",  "n88ap",   BDID_IPHONE3GS,    CPID_IPHONE3GS,
	"http://appldnld.apple.com/iPhone4/041-0328.20110311.Lkhy6/iPhone2,1_4.3_8F190_Restore.ipsw" },
	{  DEVICE_IPOD3G,     "iPod3,1",    "n18ap",   BDID_IPOD3G,       CPID_IPOD3G,
	"http://appldnld.apple.com/iPhone4/061-8366.20110311.Fr45t/iPod3,1_4.3_8F190_Restore.ipsw" },
	{  DEVICE_IPAD1G,     "iPad1,1",    "k48ap",   BDID_IPAD1G,       CPID_IPAD1G,
	"http://appldnld.apple.com/iPhone4/041-0329.20110311.Cvfre/iPad1,1_4.3_8F190_Restore.ipsw" },
	{  DEVICE_IPHONE4,    "iPhone3,1",  "n90ap",   BDID_IPHONE4,      CPID_IPHONE4,
	"http://appldnld.apple.com/iPhone4/041-0330.20110311.Cswe3/iPhone3,1_4.3_8F190_Restore.ipsw" },
	{  DEVICE_IPOD4G,     "iPod4,1",    "n81ap",   BDID_IPOD4G,       CPID_IPOD4G,
	"http://appldnld.apple.com/iPhone4/061-9588.20110311.GtP7y/iPod4,1_4.3_8F190_Restore.ipsw" },
	{  DEVICE_APPLETV2G,   "AppleTV2,1", "k66ap",   BDID_APPLETV2G,    CPID_APPLETV2G,
	"http://appldnld.apple.com/AppleTV/061-9584.20110308.Cxdew/AppleTV2,1_4.3_8F191m_Restore.ipsw" },
	{ DEVICE_IPHONE42,    "iPhone3,3",  "n92ap",   BDID_IPHONE42,     CPID_IPHONE42,
	"http://appldnld.apple.com/iPhone4/041-0177.20110131.Pyvrz/iPhone3,3_4.2.6_8E200_Restore.ipsw" },
	{ DEVICE_IPAD2G_WIFI, "iPad2,1",    "k93ap",   BDID_IPAD2G_WIFI,  CPID_IPAD2G_WIFI,
	"http://appldnld.apple.com/iPhone4/041-0368.20110311.SwtHr/iPad2,1_4.3_8F191_Restore.ipsw" },
	{ DEVICE_IPAD2G_GSM,  "iPad2,2",    "k94ap",   BDID_IPAD2G_GSM,   CPID_IPAD2G_GSM,
	"http://appldnld.apple.com/iPhone4/041-0369.20110311.Xzsew/iPad2,2_4.3_8F191_Restore.ipsw" },
	{ DEVICE_IPAD2G_CDMA, "iPad2,3",    "k95ap",   BDID_IPAD2G_CDMA,  CPID_IPAD2G_CDMA,
	"http://appldnld.apple.com/iPhone4/041-0334.20110311Plgt5/iPad2,3_4.3_8F191_Restore.ipsw" },
	{ -1,  NULL,        NULL,   -1,    -1,
	NULL }
};

LIBIRECOVERY_EXPORT void irecv_set_debug_level(int level);
LIBIRECOVERY_EXPORT const char* irecv_strerror(irecv_error_t error);
LIBIRECOVERY_EXPORT irecv_error_t irecv_open_attempts(irecv_client_t* pclient, int attempts);
LIBIRECOVERY_EXPORT irecv_error_t irecv_open(irecv_client_t* client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_reset(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_close(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_receive(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_send_exploit(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_execute_script(irecv_client_t client, const char* filename);
LIBIRECOVERY_EXPORT irecv_error_t irecv_set_configuration(irecv_client_t client, int configuration);

LIBIRECOVERY_EXPORT irecv_error_t irecv_event_subscribe(irecv_client_t client, irecv_event_type type, irecv_event_cb_t callback, void *user_data);
LIBIRECOVERY_EXPORT irecv_error_t irecv_event_unsubscribe(irecv_client_t client, irecv_event_type type);

LIBIRECOVERY_EXPORT irecv_error_t irecv_send_file(irecv_client_t client, const char* filename, int dfuNotifyFinished);
LIBIRECOVERY_EXPORT irecv_error_t irecv_send_command(irecv_client_t client, const char* command);
LIBIRECOVERY_EXPORT irecv_error_t irecv_send_buffer(irecv_client_t client, unsigned char* buffer, unsigned long length, int dfuNotifyFinished);

LIBIRECOVERY_EXPORT irecv_error_t irecv_saveenv(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_getret(irecv_client_t client, unsigned int* value);
LIBIRECOVERY_EXPORT irecv_error_t irecv_getenv(irecv_client_t client, const char* variable, char** value);
LIBIRECOVERY_EXPORT irecv_error_t irecv_setenv(irecv_client_t client, const char* variable, const char* value);
LIBIRECOVERY_EXPORT irecv_error_t irecv_set_interface(irecv_client_t client, int iface, int alt_iface);
LIBIRECOVERY_EXPORT irecv_error_t irecv_get_cpid(irecv_client_t client, unsigned int* cpid);
LIBIRECOVERY_EXPORT irecv_error_t irecv_get_bdid(irecv_client_t client, unsigned int* bdid);
LIBIRECOVERY_EXPORT irecv_error_t irecv_get_ecid(irecv_client_t client, unsigned long long* ecid);
LIBIRECOVERY_EXPORT irecv_error_t irecv_get_srnm(irecv_client_t client, unsigned char* srnm);
LIBIRECOVERY_EXPORT irecv_error_t irecv_get_imei(irecv_client_t client, unsigned char* imei);

LIBIRECOVERY_EXPORT void irecv_hexdump(unsigned char* buf, unsigned int len, unsigned int addr);

LIBIRECOVERY_EXPORT void irecv_init();
LIBIRECOVERY_EXPORT void irecv_exit();
LIBIRECOVERY_EXPORT irecv_client_t irecv_reconnect(irecv_client_t client, int initial_pause);
LIBIRECOVERY_EXPORT irecv_error_t irecv_reset_counters(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_finish_transfer(irecv_client_t client);
LIBIRECOVERY_EXPORT irecv_error_t irecv_recv_buffer(irecv_client_t client, char* buffer, unsigned long length);
LIBIRECOVERY_EXPORT irecv_error_t irecv_get_device(irecv_client_t client, irecv_device_t* device);

LIBIRECOVERY_EXPORT int irecv_control_transfer( irecv_client_t client,
							uint8_t bmRequestType,
							uint8_t bRequest,
							uint16_t wValue,
							uint16_t wIndex,
							unsigned char *data,
							uint16_t wLength,
							unsigned int timeout);

#ifdef __cplusplus
}
#endif

#endif
