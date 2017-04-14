#include "stdafx.h"
#include "Packet.h"

CPacket::CPacket(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	m_header = *header;
	int len = header->len;
	m_data = new u_char[len];
	// 不能使用字符串拷贝，遇到全0就完蛋，使用内存拷贝
	// strcpy_s((char*)m_data, header->len, (char*)pkt_data);
	memcpy_s(m_data, header->len, pkt_data, header->len);
}

CPacket::~CPacket()
{
	delete[] m_data;
}

CPacket& CPacket::operator =(const CPacket& packet)
{
	m_header = packet.m_header;
	delete m_data;
	int len = packet.m_header.len + 1;
	m_data = new u_char[len];
	strcpy_s((char*)m_data, packet.m_header.len, (char*)packet.m_data);
	return *this;
}

CPacket::CPacket(const CPacket& packet)
{
	m_header = packet.m_header;
	int len = packet.m_header.len + 1;
	m_data = new u_char[len];
	strcpy_s((char*)m_data, packet.m_header.len, (char*)packet.m_data);
}

const struct pcap_pkthdr* CPacket::getHeader()const
{
	return &m_header;
}

const u_char* CPacket::getData()const
{
	return m_data;
}