#include "stdafx.h"
#include "PacketFilter.h"

#include "Adapter.h"

CPacketFilter::CPacketFilter(void)
{
	;
}


CPacketFilter::~CPacketFilter(void)
{
	;
}

void CPacketFilter::setFilterString(const std::string& str)
{
	m_filter_string = str;
}

void CPacketFilter::setFilterString(const char* ptr)
{
	m_filter_string = ptr;
}

bool CPacketFilter::complie(CAdapter* adapter)
{
	//compile the filter
	pcap_t* handle = adapter->getHandle();
	u_int netmask = adapter->getNetmask();
    if (pcap_compile(handle, &m_fcode, m_filter_string.c_str(), 1, netmask) <0 )
    {
        perror("can not complie the filter,check the filter syntax!\n");
        return false;
    }
	return true;
}

struct bpf_program CPacketFilter::getFCode()const
{
	return m_fcode;
}