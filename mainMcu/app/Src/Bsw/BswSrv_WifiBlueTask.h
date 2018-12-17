#ifndef __BSWSRV_READWIFIBLUETASK_H__
#define __BSWSRV_READWIFIBLUETASK_H__


#define CKB_MAX_PKT_LEN	255


// #define DBG_WIFIBLUE	1 

enum {
	ENUM_WIFI_ZERO,
    ENUM_WIFI_IPD_I,
	ENUM_WIFI_IPD_P,
	ENUM_WIFI_IPD_D,
	ENUM_WIFI_IPD_COMMA,
	ENUM_WIFI_IPD_LENTH,
	ENUM_WIFI_IPD_COLON,
	ENUM_WIFI_WRITE_R,
	ENUM_WIFI_WRITE_I,
	ENUM_WIFI_WRITE_T,
	ENUM_WIFI_WRITE_E,
	ENUM_WIFI_WRITE_COLON,		//:
	ENUM_WIFI_WRITE_COMMA,		//,
	ENUM_WIFI_WRITE_LENTH,		//
	ENUM_WIFI_WRITE_DATA,
	ENUM_BLEDISCONN_L,
	ENUM_BLEDISCONN_E,
	ENUM_BLEDISCONN_D,
	ENUM_BLEDISCONN_I,
	ENUM_BLEDISCONN_S,
	ENUM_BLEDISCONN_C,
	ENUM_BLEDISCONN_O,
	ENUM_BLEDISCONN_N1,
	ENUM_BLEDISCONN_N2,
	ENUM_BLEDISCONN_COLON,
	ENUM_BLECONN_O,
	ENUM_BLECONN_N1,
	ENUM_BLECONN_N2,
	ENUM_BLECONN_COLON,
};



enum {
    BT_FIND_EE,
    BT_FIND_CMD,
    BT_FIND_LEN,
    BT_RX_DATA,
    BT_FIND_CHK,
    BT_FIND_END,
};


void WifiBlueTask(void);

#endif
