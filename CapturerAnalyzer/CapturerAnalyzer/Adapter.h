#pragma once
#include "stdafx.h"
#include <pcap.h>
/* 包含问题 */
#include <winsock2.h>
#include <string>
#include <vector>
#include <WS2TCPIP.H>

class CPacketFilter;

class CAddr
{
public:
	CAddr(pcap_addr_t *a);
	~CAddr();
// private:
	std::string type;
	std::string addr;
	std::string broadcast;
	std::string netmask;
	std::string destaddr;
	operator std::string()const;
};

class CAdapter
{
public:
	friend class CPacketCapturer;
	friend class CPacketFilter;
	std::string getName()const;
	std::string getDescription()const;
	bool isLoopBack()const;
	int getAddrNum()const;
	const CAddr& getAddrN(int n)const;
	const std::vector<CAddr>& getAllAddr()const;
	u_int getNetmask();
	/* 析构函数不可以私有 */
	~CAdapter(void);
	// std::string getInfo();
private:
	CAdapter(pcap_if_t* adapter);
	bool open();
	bool close();
	pcap_t* getHandle()const;
	bool openFilter(CPacketFilter*);
private:
	pcap_if_t* m_adapter;
	pcap_t* m_handle;
	int m_addr_num;
	std::vector<CAddr> m_addrs;
	CPacketFilter* m_filter;
};

