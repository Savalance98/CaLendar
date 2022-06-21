#include "Month.h"
#include <cmath>
#include <string>
#include <vector>
/**
 * Функция вычисляет длину строки
 * @param str
 * @return длина строки
 */
size_t strlen(std::string str) {
    size_t size = 0;
    for (auto byte : str) {
        size += (((byte & 0x80) == 0) || ((byte & 0xC0) == 0xC0));
    }
    return size;
}
/**
 *Класс Месяц
 * @param monthNumber номер месяца
 * @param year год
 */
Month::Month(int monthNumber, int year) {
	this->monthNumber = monthNumber;
	setAmountOfDays(year);
	setName();
	setDays(year);
    addYearToName(year);
}
/**
 *Добавляет год  к строке name
 * @param year год
 */
void Month::addYearToName(int year) {
	name += " ";
	name += std::to_string(year);
}
/**
 *Узнает век
 * @param year год
 * @return код года
 */
int Month::getYearCode(int year) {
	int century = year / 100;
	return ((6 - (century % 4) * 2)+year%100+(year%100)/4)%7;
}
/**
 *Узнает день недели
 * @param day день
 * @param year год
 * @param yearCode год
 * @return номер дня недели
 */
int Month::getWeekDay(int day, int year, int yearCode){
	int ans = (day + monthCode + yearCode)%7-2;
	if (ans < 0)
		ans += 7;
	if (year % 4 == 0 && monthNumber <= 2)
		ans--;
	return ans;
}
/**
 *Расположение дня в календаре
 * @param year год
 */
void Month::setDays(int year) {
	for (int i = 0; i < amountOfStrings; i++) {
		for (int j = 0; j < weekSize; j++) {
			days[j][i] = 0;
		}
	}
	int first = getWeekDay(1, year, getYearCode(year));
	int daysCounter = 1;
	for (int i = 0; i < amountOfStrings; i++) {
		for (int j = first; j < weekSize && daysCounter <= amountOfDays; j++) {
			days[j][i] = daysCounter;
			daysCounter++;
		}
		first = 0;
	}
}
/**
 *Вычисляет количество дней
 * @param year год
 */
void Month::setAmountOfDays(int year) {
	this->amountOfDays = 28 + ((int)(monthNumber + floor(monthNumber / 8)) % 2) 
		+ 2 % monthNumber + floor((1 + (1 - (year % 4 + 2) % (year % 4 + 1)) * ((year % 100 + 2) % (year % 100 + 1))
		+ (1 - (year % 400 + 2) % (year % 400 + 1))) / monthNumber) + floor(1 / monthNumber) 
		- floor(((1 - (year % 4 + 2) % (year % 4 + 1)) * ((year % 100 + 2) % (year % 100 + 1))
			+ (1 - (year % 400 + 2) % (year % 400 + 1))) / monthNumber);
}
/**
 *Перезагрузка оператора = для переопредления месяца
 * @param other
 * @return
 */
Month& Month::operator=(const Month& other) {
	if (this != &other) {
		monthNumber = other.monthNumber;
		amountOfDays = other.amountOfDays;
		name = other.name;
	}
	return *this;
}

void Month::setName() {
	switch(monthNumber) {
		case 1:
			name = YANUARY;
			monthCode = 1;
			break;
		case 2:
			name = FEBRUARY;
			monthCode = 4;
			break;
		case 3:
			name = MARCH;
			monthCode = 4;
			break;
		case 4:
			name = APRIL;
			monthCode = 0;
			break;
		case 5:
			name = MAY;
			monthCode = 2;
			break;
		case 6:
			name = JUNE;
			monthCode = 5;
			break;
		case 7:
			name = JULY;
			monthCode = 0;
			break;
		case 8:
			name = AUGUST;
			monthCode = 3;
			break;
		case 9:
			name = SEPTEMBER;
			monthCode = 6;
			break;
		case 10:
			name = OCTOBER;
			monthCode = 1;
			break;
		case 11:
			name = NOVEMBER;
			monthCode = 4;
			break;
		case 12:
			name = DECEMBER;
			monthCode = 6;
			break;

	}
}

int Month::getAmountOfdays() {
	return amountOfDays;
}

std::string Month::getName() {
	return name;
}

int Month::getMonthNumber() {
	return monthNumber;
}


std::vector<std::string> Month::toString(){
    std::vector<std::string> monthStrings;
    int len = strlen(getName());
    int amountOfSpaces = (8*3 - len)/2;
    monthStrings.emplace_back("");
    for (int i = 0; i < amountOfSpaces; i++)
        monthStrings[0].append(" ");

    monthStrings[0].append(getName());

    for(int i = 0; i < amountOfSpaces; i++)
        monthStrings[0].append(" ");
    monthStrings.emplace_back("");
    monthStrings[1].append("ПН ВТ СР ЧТ ПТ СБ ВС ");
    monthStrings.emplace_back("");
    for(int j =0; j < Month::amountOfStrings; j++) {
        for (int z = 0; z < Month::weekSize; z++) {
            if (days[z][j] == 0)
                monthStrings[2+j].append("   ");
            else if (days[z][j] / 10 >= 1) {
                monthStrings[2+j].append(std::to_string(days[z][j]));
                monthStrings[2+j].append(" ");
            } else {
                monthStrings[2+j].append(std::to_string(days[z][j]));
                monthStrings[2+j].append("  ");
            }
        }
        monthStrings.emplace_back("");
    }
    return monthStrings;
}
