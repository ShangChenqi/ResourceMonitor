#include "stdafx.h"
#include "Internet.h"
#include <string>
#include <iostream>
using namespace std;

Internet::Internet()
{
	m_dwSize = sizeof(MIB_IFTABLE);
	m_pIfTable = (MIB_IFTABLE *)malloc(m_dwSize);
	int rtn;
	rtn = GetIfTable(m_pIfTable, &m_dwSize, FALSE);
	if (rtn == ERROR_INSUFFICIENT_BUFFER)	//如果函数返回值为ERROR_INSUFFICIENT_BUFFER，说明m_pIfTable的大小不够
	{
		free(m_pIfTable);
		m_pIfTable = (MIB_IFTABLE *)malloc(m_dwSize);	//用新的大小重新开辟一块内存
	}
	typeName = "InternetInfo";
	description = "NULL";
	onSpeed = 0;
	downSpeed = 0;
}

void Internet::setTypeName(const std::string & na) {
	typeName = na;
}

void Internet::setDescription(const std::string & des) {
	description = des;
}

void Internet::setOnSpeed() {
	//从系统获取上传网速
	//获取当前所有的连接，并保存到m_connections容器中
	GetIfTable(m_pIfTable, &m_dwSize, FALSE);
	GetAllIfTableInfo(m_connections, m_pIfTable);
	//获取全部连接的网速
	m_out_bytes = 0;
	for (size_t i{}; i < m_connections.size(); i++)
	{
		m_out_bytes += m_pIfTable->table[m_connections[i].index].dwOutOctets;
	}

	if (m_out_bytes - m_last_out_bytes <= 1073741824)
		onSpeed = (m_out_bytes - m_last_out_bytes) / 1024.0;	
	else onSpeed = 0.0;
	m_last_out_bytes = m_out_bytes;
	m_connections.clear();
}

void Internet::setDownSpeed() {
	//从系统获取下载网速
	
	//获取当前所有的连接，并保存到m_connections容器中
	GetIfTable(m_pIfTable, &m_dwSize, FALSE);
	GetAllIfTableInfo(m_connections, m_pIfTable);
	//获取全部连接的网速
	m_in_bytes = 0;
	for (size_t i{}; i < m_connections.size(); i++)
	{
		m_in_bytes += m_pIfTable->table[m_connections[i].index].dwInOctets;
	}

	if (m_in_bytes - m_last_in_bytes <= 1073741824)
		downSpeed = (m_in_bytes - m_last_in_bytes) / 1024.0;
	else downSpeed = 0.0;
	m_last_in_bytes = m_in_bytes;
	m_connections.clear();
}

std::string Internet::getTypeName() const {
	return typeName;
}

std::string Internet::getDescription() const {
	return description;
}

double Internet::getOnSpeed() const {
	return onSpeed;
}

double Internet::getDownSpeed() const {
	return downSpeed;
}

Internet::~Internet()
{
}

void Internet::GetAllIfTableInfo(vector<NetWorkConection>& adapters, MIB_IFTABLE * pIfTable)
{
	vector<NetWorkConection> adapters_tmp;
	GetAdapterInfo(adapters_tmp);		//获取IP地址
	for (size_t i{}; i < pIfTable->dwNumEntries; i++)
	{
		NetWorkConection connection;
		connection.description = connection.description_2 = (const char*)pIfTable->table[i].bDescr;
		connection.index = i;
		connection.in_bytes = pIfTable->table[i].dwInOctets;
		connection.out_bytes = pIfTable->table[i].dwOutOctets;
		for (size_t j{}; j < adapters_tmp.size(); j++)
		{
			if (connection.description.find(adapters_tmp[j].description) != string::npos)
			{
				connection.ip_address = adapters_tmp[j].ip_address;
				connection.subnet_mask = adapters_tmp[j].subnet_mask;
				connection.default_gateway = adapters_tmp[j].default_gateway;
				break;
			}
		}
		adapters.push_back(connection);
	}
}

void Internet::GetAdapterInfo(vector<NetWorkConection>& adapters)
{
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();		//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);		//得到结构体大小,用于GetAdaptersInfo参数
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量

	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		delete pIpAdapterInfo;	//释放原来的内存空间
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];	//重新申请内存空间用来存储所有网卡信息
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
	}

	PIP_ADAPTER_INFO pIpAdapterInfoHead = pIpAdapterInfo;	//保存pIpAdapterInfo链表中第一个元素的地址
	if (ERROR_SUCCESS == nRel)
	{
		while (pIpAdapterInfo)
		{
			NetWorkConection connection;
			connection.description = pIpAdapterInfo->Description;
			connection.ip_address = StrToUnicode(pIpAdapterInfo->IpAddressList.IpAddress.String, false);
			connection.subnet_mask = StrToUnicode(pIpAdapterInfo->IpAddressList.IpMask.String, false);
			connection.default_gateway = StrToUnicode(pIpAdapterInfo->GatewayList.IpAddress.String, false);

			adapters.push_back(connection);
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	//释放内存空间
	if (pIpAdapterInfoHead)
	{
		delete pIpAdapterInfoHead;
	}
	if (adapters.empty())
	{
		NetWorkConection connection{};
		connection.description = UnicodeToStr(LoadText(L"<", IDS_NO_CONNECTION, L">"), L">");
		adapters.push_back(connection);
	}
}

wstring Internet::StrToUnicode(const char* str, bool utf8)
{
	wstring result;
	int size;
	size = MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, NULL, 0);
	if (size <= 0) return wstring();
	wchar_t* str_unicode = new wchar_t[size + 1];
	MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, str_unicode, size);
	result.assign(str_unicode);
	delete[] str_unicode;
	return result;
}

string Internet::UnicodeToStr(const wchar_t * wstr, bool utf8)
{
	string result;
	int size{ 0 };
	size = WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, NULL, 0, NULL, NULL);
	if (size <= 0) return string();
	char* str = new char[size + 1];
	WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, str, size, NULL, NULL);
	result.assign(str);
	delete[] str;
	return result;
}

CString Internet::LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str)
{
	CString str;
	str.LoadString(id);
	if (back_str != nullptr)
		str += back_str;
	if (front_str != nullptr)
		str = front_str + str;
	return str;
}

void Internet::display() const {
	cout << "-------------------------------------" << '\n';
	cout << "The information of Internet:\n"
		<< "Name:        " << typeName << '\n'
		<< "Description: " << description << '\n'
		<< "OnSpeed:     " << onSpeed << " KB/S" << '\n'
		<< "DownSpeed:   " << downSpeed << " KB/S" << '\n';
	cout << "-------------------------------------" << '\n';
}