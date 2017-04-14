#pragma once
#include <pcap.h>

/* ���ݰ��ṹ */
class CPacket
{
public:
	/* ���캯����header����������ݰ�����Ϣ��pkt_data�����ݰ��ֽ� */
	CPacket(const struct pcap_pkthdr *header, const u_char *pkt_data);
	/* �����������ͷ��ڴ�ռ� */
	~CPacket();
	CPacket& operator =(const CPacket& packet);
	CPacket(const CPacket& packet);
	const struct pcap_pkthdr* getHeader()const;
	const u_char* getData()const;
private:
	/* ���ݰ���Ϣ m_header.len ���ݰ��ֽ��� m_header.ts ʱ��� */
	struct pcap_pkthdr m_header;
	/* ���ݰ� */
	u_char* m_data;
};