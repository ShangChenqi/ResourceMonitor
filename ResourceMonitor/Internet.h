#pragma once
#ifndef INTERNET_H
#define INTERNET_H
#include <string>
#include <vector>
#include <atlstr.h>
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#define IDS_NO_CONNECTION 289


//保存一个网络连接信息
struct NetWorkConection
{
	int index{};			//该连接在MIB_IFTABLE中的索引
	std::string description;		//网络描述（获取自GetAdapterInfo）
	std::string description_2;	//网络描述（获取自GetIfTable）
	unsigned int in_bytes;	//初始时已接收字节数
	unsigned int out_bytes;	//初始时已发送字节数
	std::wstring ip_address{ L"-.-.-.-" };	//IP地址
	std::wstring subnet_mask{ L"-.-.-.-" };	//子网掩码
	std::wstring default_gateway{ L"-.-.-.-" };	//默认网关
};

class Internet
{
private:
	std::string typeName;
	std::string description;
	double onSpeed;
	double downSpeed;

	unsigned __int64 m_in_bytes;		//当前已接收的字节数
	unsigned __int64 m_out_bytes;	//当前已发送的字节数

	unsigned __int64 m_last_in_bytes{};	//上次已接收的字节数
	unsigned __int64 m_last_out_bytes{};	//上次已发送的字节数

	std::vector<NetWorkConection> m_connections;
	MIB_IFTABLE* m_pIfTable;
	DWORD m_dwSize{};	//m_pIfTable的大小

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