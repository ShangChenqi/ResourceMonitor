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
	if (rtn == ERROR_INSUFFICIENT_BUFFER)	//�����������ֵΪERROR_INSUFFICIENT_BUFFER��˵��m_pIfTable�Ĵ�С����
	{
		free(m_pIfTable);
		m_pIfTable = (MIB_IFTABLE *)malloc(m_dwSize);	//���µĴ�С���¿���һ���ڴ�
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
	//��ϵͳ��ȡ�ϴ�����
	//��ȡ��ǰ���е����ӣ������浽m_connections������
	GetIfTable(m_pIfTable, &m_dwSize, FALSE);
	GetAllIfTableInfo(m_connections, m_pIfTable);
	//��ȡȫ�����ӵ�����
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
	//��ϵͳ��ȡ��������
	
	//��ȡ��ǰ���е����ӣ������浽m_connections������
	GetIfTable(m_pIfTable, &m_dwSize, FALSE);
	GetAllIfTableInfo(m_connections, m_pIfTable);
	//��ȡȫ�����ӵ�����
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
	GetAdapterInfo(adapters_tmp);		//��ȡIP��ַ
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
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();		//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);		//�õ��ṹ���С,����GetAdaptersInfo����
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������

	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		delete pIpAdapterInfo;	//�ͷ�ԭ�����ڴ�ռ�
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];	//���������ڴ�ռ������洢����������Ϣ
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
	}

	PIP_ADAPTER_INFO pIpAdapterInfoHead = pIpAdapterInfo;	//����pIpAdapterInfo�����е�һ��Ԫ�صĵ�ַ
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
	//�ͷ��ڴ�ռ�
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