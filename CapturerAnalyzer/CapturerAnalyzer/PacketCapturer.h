#pragma once

#include "stdafx.h"
#include <vector>
#include <pcap.h>
#include "Packet.h"
#include "Adapter.h"
#include "PacketFilter.h"
#include "windows.h"
#include "StatusBarEx.h"

#define TMP_FILE "tmpfile.dump"
// char tmp_dump[16] = TMP_FILE;
class CCapturerDlg;

typedef struct Param
{
	pcap_t* handle;
	std::vector<CPacket>* packet;
	int *nums;
	bool *startFlag;
	HANDLE mutex;
	CListCtrl* listctrl;
}Param;

/* 捕获器 */
class CPacketCapturer
{
public:
	/* 构造函数 */
	CPacketCapturer(void);
	/* 析构函数 */
	~CPacketCapturer(void);
	bool start(int adapter);
	bool pause();
	bool conti();
	bool stop();
	void clearPacket();
	const CPacket* getNextPacket();
	const std::vector<CPacket>& getAllPacket(int* n)const;
	const CAdapter& getAdapter(int n)const;
	int getAdapterNum()const;
	bool saveFile(const char*);
	void setFilterString(const char*);
	void setFilterString(const std::string&);
	bool openFilter();
	bool findHostAdapter();
	bool bindListCtrl(CListCtrl*);
	int getPacketsNum()const;
	void reset();
private:
public:
	static DWORD WINAPI CPacketCapturer::ThreadProc(LPVOID lpParam);
	//bool setFilter();
	// bool useFilter();
	// friend class CAdapter;
private:
	bool openAdapter(int n);
	void freeDevice();
	void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
private:
	bool runFlag;
	bool startFlag;
	std::vector<CPacket> m_packets;
	int m_nums;
	int m_read;
	pcap_if_t* m_alldevs;
	std::vector<CAdapter> m_adapters;
	int m_adapter_num;
	int m_cur_adapter_index;
	char m_save_file[36];
	CPacketFilter m_filter;
	HANDLE m_hThread;					/* 线程句柄 */
	HANDLE m_hMutex;					/* 读写互斥锁 */
	CListCtrl* m_listctrl;				// 列表指针
};

