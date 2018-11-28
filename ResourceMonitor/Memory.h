#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <string>

class Memory
{
private:
	std::string typeName;
	std::string description;
	double totalUsage;
	double availbleUsage;
	double usePercent;

public:
	Memory();
	Memory(const std::string & na, const std::string & des, double tusage = 0, double ausage = 0, double up = 0) { 
		typeName = na; 
		description = des; 
		totalUsage = tusage; 
		availbleUsage = ausage; 
		usePercent = up;
	}

	void setTypeName(const std::string & na);
	void setDescription(const std::string & des);
	void setTotalUsage();
	void setAvailableUsage();
	void setUsePercent();

	std::string getTypeName() const;
	std::string getDescription() const;
	double getTotalUsage() const;
	double getAvailableUsage() const;
	double getUsePercent() const;

	~Memory();
};

#endif // !MEMORY_H