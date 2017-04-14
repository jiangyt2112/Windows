#pragma once
#include <pcap.h>

/* 数据包结构 */
class CPacket
{
public:
	/* 构造函数，header是与相关数据包的信息，pkt_data是数据包字节 */
	CPacket(const struct pcap_pkthdr *header, const u_char *pkt_data);
	/* 析构函数，释放内存空间 */
	~CPacket();
	CPacket& operator =(const CPacket& packet);
	CPacket(const CPacket& packet);
	const struct pcap_pkthdr* getHeader()const;
	const u_char* getData()const;
private:
	/* 数据包信息 m_header.len 数据包字节数 m_header.ts 时间戳 */
	struct pcap_pkthdr m_header;
	/* 数据包 */
	u_char* m_data;
};