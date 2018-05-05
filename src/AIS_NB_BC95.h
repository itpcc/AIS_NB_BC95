/*!
 * @file AIS_NB_BC95.h
 *
 * This is part of AIS's NB-IoT module (Quectel BC95) driver for the Arduino platform.  It is
 * designed specifically to work with the AIS DEVIO NB-SHIELD I.
 *
 */

#ifndef AIS_NB_BC95_h
#define AIS_NB_BC95_h

#define ATLSOFTSERIAL 1

#include <Arduino.h>
#include <Stream.h>

#define MODE_STRING 0
#define MODE_STRING_HEX 1

#if ATLSOFTSERIAL 
	#include "AltSoftSerial.h"
#endif

#define AIS_NB_BC95_CEREG_STATUS_UNKNOW 0xFF

struct AIS_NB_BC95_RES
{
	unsigned char status;
	String data;
	String temp;
};

struct signal
{
	String csq;
	String rssi;
	String ber;
};

struct UDPSend
{
	bool status;
	String strsend;
	unsigned char socket;
	unsigned int length;
};

struct UDPReceive
{
	unsigned char socket;
	String ip_address;
	unsigned int port;
	unsigned int length;
	String data;
	unsigned int remaining_length;
};
struct pingRESP
{
	bool status;
	String addr;
	String ttl;
	String rtt;
};
/**
 * @brief EPS Network Registration Status.
 *
 * For more information, Read Quectel's BC95 AT Command Doument, section 3.7. 
 * AT+CEREG EPS Network Registration Status.
 */
struct AIS_NB_BC95_CEREG{
	unsigned char status; /**< Type of network registration and location information unsolicited result code */
	unsigned char EPS_status; /**<  EPS registration status */
	unsigned int TAC; /**< tracking area code */
	unsigned long ECI; /**< E-UTRAN cell ID */
	unsigned char AcT; /**< access technology */
};

class AIS_NB_BC95
{
public:
	AIS_NB_BC95();
	bool debug;

	void (*Event_debug)(char *data);
	void reset();
	void rebootModule();
	bool waitReady();
	bool setPhoneFunction(unsigned char mode);

	//General
	String getFirmwareVersion();
	String getIMEI();
	String getIMSI();
	pingRESP pingIP(String IP);

	//Network
	bool setAutoConnectOn();
	bool setAutoConnectOff();
	String getAutoConnect();
	String getNetworkStatus();
	AIS_NB_BC95_CEREG getEPSNetworkStatus();
	String getPLMN();
	//bool setAPN(String apn);
	String getAPN();


	bool cgatt(unsigned char mode);
	bool getNBConnect();
	
	void setupDeviceWithoutAttachNB();
	void setupDevice(String serverPort);
	bool attachNB(String serverPort);
	bool detachNB();

	String getDeviceIP();
	signal getSignal();

	void createUDPSocket(String port);

	UDPSend sendUDPmsg(String addressI,String port,String data);
	UDPSend sendUDPmsg(String addressI,String port,unsigned int len,char *data,unsigned char send_mode);
	UDPSend sendUDPmsgStr(String addressI,String port,String data);
	
	bool closeUDPSocket();

	UDPReceive waitResponse();

	void printHEX(char *str);
	String toString(String dat);
	String str2HexStr(String strin);
	char char_to_byte(char c);
	
	void receive_UDP(UDPReceive rx);

private:
	AIS_NB_BC95_RES wait_rx_bc(long tout,String str_wait);
	AIS_NB_BC95_CEREG parseEPSNetworkStatus(char *buffer);

protected:
	Stream *_Serial;
};

#endif