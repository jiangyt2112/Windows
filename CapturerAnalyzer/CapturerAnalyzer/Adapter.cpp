#include "stdafx.h"
#include "Adapter.h"

#include "PacketFilter.h"

#define IPTOSBUFFERS 12

// ip4地址数值到字符串
char *iptos(u_long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    _snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

// ip6地址数值到字符串
char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
    socklen_t sockaddrlen;

    sockaddrlen = sizeof(struct sockaddr_in6);

    if(getnameinfo(sockaddr, 
        sockaddrlen, 
        address, 
        addrlen, 
        NULL, 
        0, 
        NI_NUMERICHOST) != 0) address = NULL;

    return address;
}

CAddr::CAddr(pcap_addr_t *a)
{
	char ip6str[128];
	switch(a->addr->sa_family)
    {
      case AF_INET:
        type = "AF_INET";
        if (a->addr)
			addr = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
        if (a->netmask)
			netmask = iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr);
        if (a->broadaddr)
          broadcast = iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr);
        if (a->dstaddr)
          destaddr = iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr);
        break;

      case AF_INET6:
        type = "AF_INET6";
        if (a->addr)
			addr = ip6tos(a->addr, ip6str, sizeof(ip6str));
       break;

      default:
        break;
    }
}

CAddr::~CAddr()
{
	;
}

CAddr::operator std::string()const
{
	std::string ret;
	ret += "type:" + type;
	ret += std::string("\n");
	ret += "addr:" + addr;
	ret += std::string("\n");
	ret += "broadcast:" + broadcast;
	ret += std::string("\n");
	ret += "netmask:" + netmask;
	ret += std::string("\n");
	ret += "destaddr:" + destaddr;
	ret += std::string("\n");
	return ret;
}

CAdapter::CAdapter(pcap_if_t * adapter)
{
	pcap_addr_t *a;
	m_adapter = adapter;
	// m_adapter.next = NULL;
	m_addr_num = 0;
	for(a = m_adapter->addresses; a; a=a->next)
	{
		m_addr_num++;
		CAddr addr(a);
		m_addrs.push_back(addr);
	}
	m_handle = NULL;
	//m_filter = NULL;
}


CAdapter::~CAdapter(void)
{
	;
}

std::string CAdapter::getName()const
{
	return std::string(m_adapter->name);
}

std::string CAdapter::getDescription()const
{
	return std::string(m_adapter->description);
}

int CAdapter::getAddrNum()const
{
	return m_addr_num;
}

const CAddr& CAdapter::getAddrN(int n)const
{
	return m_addrs[n];
}

const std::vector<CAddr>& CAdapter::getAllAddr()const
{
	return m_addrs;
}

bool CAdapter::open()
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* handle = pcap_open(	m_adapter->name,				// name of the device
								65536,							// portion of the packet to capture
                                                // 65536 guarantees that the whole packet will be captured on all the link layers
								PCAP_OPENFLAG_PROMISCUOUS,		// promiscuous mode
								1000,							// read timeout
								NULL,							// authentication on the remote machine
								errbuf							// error buffer
							);
	if (handle == NULL)
	{
		perror("can not open adapter!");
		perror(errbuf);
		return false;
	}
	m_handle = handle;
	return true;
}

bool CAdapter::close()
{
	if (m_handle != NULL)
	{
		pcap_close(m_handle);
		m_handle = NULL;
	}
	return true;
}

pcap_t* CAdapter::getHandle()const
{
	return m_handle;
}

bool CAdapter::isLoopBack()const
{
	return (m_adapter->flags & PCAP_IF_LOOPBACK) ? true : false;
}

u_int CAdapter::getNetmask()
{
	u_int netmask;
	if(m_adapter->addresses != NULL)
        /* Retrieve the mask of the first address of the interface */
        netmask=((struct sockaddr_in *)(m_adapter->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        /* If the interface is without addresses we suppose to be in a C class network */
        netmask=0xffffff; 
	return netmask;
}

bool CAdapter::openFilter(CPacketFilter* fil)
{
	CPacketFilter*m_filter = fil;
	m_filter->complie(this);
	bpf_program fcode = m_filter->getFCode();
	if (pcap_setfilter(m_handle, &fcode)<0)
    {
        perror("can not set filter!\n");
        return false;
    }
	return true;
}

