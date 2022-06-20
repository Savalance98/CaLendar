#pragma once
#include <iostream>
#include <vector>

class Month
{
public:
	static const int weekSize = 7;
	static const int amountOfStrings = 6;
	int days[weekSize][amountOfStrings];
private:
	const std::string YANUARY = "Январь";
	const std::string FEBRUARY = "Февраль";
	const std::string MARCH = "Март";
	const std::string APRIL = "Апрель";
	const std::string MAY = "Май";
	const std::string JUNE = "Июнь";
	const std::string JULY = "Июль";
	const std::string AUGUST = "Август";
	const std::string SEPTEMBER = "Сентябрь";
	const std::string OCTOBER = "Октябрь";
	const std::string NOVEMBER = "Ноябрь";
	const std::string DECEMBER = "Декабрь";

	int monthNumber;
	int amountOfDays;
	int monthCode;
	std::string name;

	void setName();
	void setAmountOfDays(int year);
	void setDays(int year);
	int getYearCode(int year);
	int getWeekDay(int day, int year, int yearCode);
public:
	Month();
	Month(int monthNumber, int year);

	int getAmountOfdays();
	std::string getName();
	int getMonthNumber();
	void addYearToName(int year);

	Month& operator=(const Month& other);

    std::vector<std::string> toString();
};

