#pragma once
#include <pcap.h>
#include <string>
class CAdapter;

class CPacketFilter
{
public:
	CPacketFilter(void);
	~CPacketFilter(void);
	void setFilterString(const std::string& str);
	void setFilterString(const char* ptr);
	bool complie(CAdapter* adapter);
	struct bpf_program getFCode()const;
	// friend class CAdapter;
private:
	struct bpf_program m_fcode;
	std::string m_filter_string; 
};
