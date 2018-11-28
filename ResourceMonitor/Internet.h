#pragma once
#ifndef INTERNET_H
#define INTERNET_H
#include <string>
#include <vector>
#include <atlstr.h>
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#define IDS_NO_CONNECTION 289


//����һ������������Ϣ
struct NetWorkConection
{
	int index{};			//��������MIB_IFTABLE�е�����
	std::string description;		//������������ȡ��GetAdapterInfo��
	std::string description_2;	//������������ȡ��GetIfTable��
	unsigned int in_bytes;	//��ʼʱ�ѽ����ֽ���
	unsigned int out_bytes;	//��ʼʱ�ѷ����ֽ���
	std::wstring ip_address{ L"-.-.-.-" };	//IP��ַ
	std::wstring subnet_mask{ L"-.-.-.-" };	//��������
	std::wstring default_gateway{ L"-.-.-.-" };	//Ĭ������
};

class Internet
{
private:
	std::string typeName;
	std::string description;
	double onSpeed;
	double downSpeed;

	unsigned __int64 m_in_bytes;		//��ǰ�ѽ��յ��ֽ���
	unsigned __int64 m_out_bytes;	//��ǰ�ѷ��͵��ֽ���

	unsigned __int64 m_last_in_bytes{};	//�ϴ��ѽ��յ��ֽ���
	unsigned __int64 m_last_out_bytes{};	//�ϴ��ѷ��͵��ֽ���

	std::vector<NetWorkConection> m_connections;
	MIB_IFTABLE* m_pIfTable;
	DWORD m_dwSize{};	//m_pIfTable�Ĵ�С

	void GetAllIfTableInfo(std::vector<NetWorkConection>& adapters, MIB_IFTABLE * pIfTable);
	void GetAdapterInfo(std::vector<NetWorkConection>& adapters);
	std::wstring StrToUnicode(const char* str, bool utf8);
	std::string UnicodeToStr(const wchar_t * wstr, bool utf8 = false);
	CString LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str);

public:
	Internet();
	Internet(const std::string & na, const std::string & des, double os = 0, double ds = 0) {
		typeName = na;
		description = des;
		onSpeed = os;
		downSpeed = ds;
	}

	void setTypeName(const std::string & na);
	void setDescription(const std::string & des);
	void setOnSpeed();
	void setDownSpeed();

	std::string getTypeName() const;
	std::string getDescription() const;
	double getOnSpeed() const;
	double getDownSpeed() const;
	
	void display() const;

	~Internet();
};

#endif // !INTERNET_H