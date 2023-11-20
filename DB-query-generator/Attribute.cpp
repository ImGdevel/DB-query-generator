#include "Attribute.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <iomanip>

Attribute::Attribute(string _name, bool _isUnique)
	: name(_name), isUnique(_isUnique) {}


AttributeNumber::AttributeNumber(string _name, int _rangeFirst, int _rangeLast, bool _isUnique)
	: Attribute(_name, _isUnique), rangeFirst(_rangeFirst), rangeLast(_rangeLast) {}

AttributeString::AttributeString(string _name, vector<string> _values, bool _isUnique)
	: Attribute(_name, _isUnique), values(_values) {}

AttributeDate::AttributeDate(string _name, int _startYear, bool _includeTime, bool _isUnique)
	: Attribute(_name, _isUnique), startYear(_startYear), includeTime(_includeTime) {}

string AttributeNumber::GenerateRandomValue() const {
    int randomValue = std::rand() % (rangeLast - rangeFirst + 1) + rangeFirst;
    return std::to_string(randomValue);
}

string AttributeString::GenerateRandomValue() const
{
    int randomIndex = std::rand() % values.size();
    return values[randomIndex];
}

string AttributeDate::GenerateRandomValue() const
{
    auto currentYear = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* timeinfo = std::localtime(&currentYear);
    int currentYearInt = timeinfo->tm_year + 1900;

    int randomYear = std::rand() % (currentYearInt - startYear + 1) + startYear;

    std::ostringstream dateValue;
    dateValue << std::setw(4) << std::setfill('0') << randomYear << "-";
    dateValue << std::setw(2) << std::setfill('0') << std::rand() % 12 + 1 << "-";
    dateValue << std::setw(2) << std::setfill('0') << std::rand() % 28 + 1;

    if (includeTime)
    {
        dateValue << " " << std::setw(2) << std::setfill('0') << std::rand() % 24 << ":"
            << std::setw(2) << std::setfill('0') << std::rand() % 60 << ":"
            << std::setw(2) << std::setfill('0') << std::rand() % 60;
    }

    return dateValue.str();
}

string AttributeNumber::GenerateUniqueValue() const 
{
    string temp;
    for (size_t i = 0; i < (rangeLast - rangeFirst - uniqueNumberCheck.size()); i++) {
        temp = GenerateRandomValue();
        if (uniqueNumberCheck.insert(temp).second) {
            return temp;
        }
    }
    std::cout << "(!) null값이 입력되었습니다." << std::endl;
    return "null";
}

string AttributeString::GenerateUniqueValue() const
{
    if (uniqueCheckIndex < values.size()) {
        return values[uniqueCheckIndex++];
    }
    std::cout << "(!) null값이 입력되었습니다." << std::endl;
    return "null";
}

string AttributeDate::GenerateUniqueValue() const
{
    return GenerateRandomValue();
}