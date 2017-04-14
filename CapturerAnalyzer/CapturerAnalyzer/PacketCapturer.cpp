#include "stdafx.h"
#include "PacketCapturer.h"
#include "StatusBarEx.h"
#include "CapturerDlg.h"
/*
	const的使用，const对象只可以调用常成员函数
	成员函数只要是不改变对象，就加上const
	只要返回的指针或者引用，如果只需要访问对象数据就加const

*/

extern CPacketCapturer g_capturer;

DWORD WINAPI CPacketCapturer::ThreadProc(LPVOID lpParam)
{
	//printf("thread start!\n");
	Param* param = (Param*)lpParam;
	pcap_t* handle = param->handle;
	std::vector<CPacket>* packets = param->packet;
	int* nums = param->nums;
	bool* startFlag = param->startFlag;
	HANDLE mutex = param->mutex;
	CListCtrl* listctrl = param->listctrl;
	
	delete param;
	int retValue;
	struct pcap_pkthdr * packetHeader;
    const u_char       * packetData;
	//startFlag
	while (*startFlag)
    {
		retValue = pcap_next_ex(handle, &packetHeader, &packetData);
		if (retValue < 0)
		{
			perror("thread error, pcap_next_ex!\n");
			return -1;
		}
        // timeout elapsed if we reach this point

        if( retValue == 0 )

                continue;

        //打印捕获数据包的信息

		::WaitForSingleObject(mutex, INFINITE);	/* 锁 */

		CPacket tmp(packetHeader, packetData);
		(*packets).push_back(tmp);
		(*nums)++;

		wchar_t buf[32];
		wsprintf(buf, _T("%d"), *nums);
		listctrl->InsertItem(*nums - 1, buf);
		tm local;
		time_t sec = packetHeader->ts.tv_sec;
		localtime_s(&local, &sec);
		
		wsprintf(buf, _T("%d:%d:%d.%6d"), local.tm_hour, local.tm_min, local.tm_sec, packetHeader->ts.tv_usec);
		listctrl->SetItemText(*nums - 1, 1, buf);
		UINT64 len = packetHeader->len;
		wsprintf(buf, _T("%d"), len);
		listctrl->SetItemText(*nums - 1, 2, buf);

		
		::ReleaseMutex(mutex);					/* 放 */

	}
	return 0;
}



CPacketCapturer::CPacketCapturer(void)
{
	m_adapter_num = 0;
	m_nums = 0;
	m_read = 0;
	runFlag = false;
	startFlag = false;
	m_cur_adapter_index = -1;
	m_alldevs = NULL;
	strcpy_s(m_save_file, TMP_FILE);
	m_hThread = 0;
	m_hMutex = ::CreateMutex(NULL, false, NULL);
	m_listctrl = NULL;
}

CPacketCapturer::~CPacketCapturer(void)
{
	freeDevice();
	CloseHandle(m_hMutex);
}

bool CPacketCapturer::findHostAdapter()
{
	char errbuf[PCAP_ERRBUF_SIZE];
	int ret = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &m_alldevs, errbuf);
	if (ret == -1)
	{
		perror("can not find all devs!\n");
		perror(errbuf);
		return false;
	}
	pcap_if_t *tmp;
	for(tmp = m_alldevs; tmp != NULL; tmp = tmp->next)
    {
        m_adapter_num++;
		CAdapter adap(tmp);

		m_adapters.push_back(adap);
    }
	return true;
}

void CPacketCapturer::clearPacket()
{
	m_packets.clear();
	m_nums = 0;
}

bool CPacketCapturer::start(int adapter)
{
	// 单独启动一个线程读取数据
	
	if (m_hThread != 0)
	{
		perror("the thread is running!\n");
		return true;
	}
	g_capturer.reset();
	bool flag = openAdapter(adapter);
	if (flag == false)
	{
		MessageBox(NULL, _T("can not open adapter!"), _T("open adapter err"), IDOK);
		return false;
	}
	DWORD dwThreadId;
	
	Param* param = new Param;
	param->handle = m_adapters[m_cur_adapter_index].getHandle();
	param->nums = &m_nums;
	param->packet = &m_packets;
	param->startFlag = &startFlag;
	param->mutex = m_hMutex;
	param->listctrl = m_listctrl;


	m_hThread = ::CreateThread(NULL, NULL, ThreadProc, param, 0, &dwThreadId);
	if (m_hThread == NULL)
	{
		perror("start capture thread error!\n");
		return false;
	}
	
	startFlag = true;
	runFlag = true;
	
	return true;
}

bool CPacketCapturer::stop()
{
	if (startFlag == false)
	{
		perror("not start\n");
		return false;
	}
	startFlag = false;

	::CloseHandle(m_hThread);
	::WaitForSingleObject(m_hThread, INFINITE);	/* 等待子线程结束 */
	
	m_hThread = 0;
	runFlag = false;
	m_adapters[m_cur_adapter_index].close();
	m_cur_adapter_index = -1;
	return true;
}

bool CPacketCapturer::pause()
{
	if (startFlag == false)
	{
		perror("not start, first start capture!\n");
		return false;
	}
	// 挂起捕获线程
	//CloseHandle(m_hThread);

	::WaitForSingleObject(m_hMutex, INFINITE);

	runFlag = false;
	return true;
}

bool CPacketCapturer::conti()
{
	if (startFlag == false)
	{
		perror("not start, first start capture!\n");
		return false;
	}
	// 唤醒捕获线程
	::ReleaseMutex(m_hMutex);
	runFlag = true;
	return true;
}

void CPacketCapturer::freeDevice()
{
	if (m_alldevs != NULL)
		pcap_freealldevs(m_alldevs);
}

int CPacketCapturer::getAdapterNum()const
{
	return m_adapter_num;
}

const CAdapter& CPacketCapturer::getAdapter(int n)const
{
	return m_adapters[n];
}

bool CPacketCapturer::openAdapter(int n)
{
	if (n > m_adapter_num)
	{
		perror("no n adapter!\n");
		return false;
	}
	if (m_cur_adapter_index != -1)
	{
		m_adapters[m_cur_adapter_index].close();
		m_cur_adapter_index = -1;
	}
	bool flag = m_adapters[n].open();
	m_cur_adapter_index = n;
	if (flag = false)
	{
		return false;
		m_cur_adapter_index = -1;
	}
	return true;
}

const CPacket* CPacketCapturer::getNextPacket()
{
	if (m_read >= m_nums)
	{
		return NULL;
	}
	CPacket* res = &m_packets[m_read];
	m_read++;
	return res;
}

const std::vector<CPacket>& CPacketCapturer::getAllPacket(int* n)const
{
	*n = m_nums;
	return m_packets;
}

bool  CPacketCapturer::saveFile(const char*)
{
	return true;
}
void  CPacketCapturer::setFilterString(const char*ptr)
{
	m_filter.setFilterString(ptr);
}

void  CPacketCapturer::setFilterString(const std::string&str)
{
	m_filter.setFilterString(str);
}

bool CPacketCapturer::openFilter()
{
	// m_filter.complile()
	if (runFlag == true)
	{
		perror("can not set filter,the capturer is runing,pause first!\n");
		return false;
	}
	if (m_cur_adapter_index == -1)
	{
		perror("can not set filter,select adapter first!\n");
		return false;
	}
	m_adapters[m_cur_adapter_index].openFilter(&m_filter);
	//m_filter.setFilterString(str);
	return true;
}

bool CPacketCapturer::bindListCtrl(CListCtrl* listctrl)
{
	m_listctrl = listctrl;
	return true;
}

int CPacketCapturer::getPacketsNum()const
{
	return m_nums;
}

void CPacketCapturer::reset()
{
	runFlag = false;
	startFlag = false;
	clearPacket();
	m_read = 0;
	m_cur_adapter_index = -1;
	m_hThread = 0;					
	m_listctrl->DeleteAllItems();
}