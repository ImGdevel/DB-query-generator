#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <string>
#include <unordered_set>
using std::vector;
using std::string;
using std::unordered_set;

class Attribute
{
public:
    string name;
    bool isUnique;
    Attribute(string _name, bool _isUnique = false);
    virtual ~Attribute() = default;

    virtual string GenerateRandomValue() const = 0;
    virtual string GenerateUniqueValue() const = 0;
    
};

class AttributeNumber : public Attribute
{
public:
    AttributeNumber(string _name, int _rangeFirst, int _rangeLast, bool _isUnique = false);

    string GenerateRandomValue() const override;
    string GenerateUniqueValue() const override;

private:
    int rangeFirst;
    int rangeLast;
    mutable unordered_set<string> uniqueNumberCheck;
};

class AttributeString : public Attribute
{
public:
    AttributeString(string _name, vector<string> _values, bool _isUnique = false);

    string GenerateRandomValue() const override;
    string GenerateUniqueValue() const override;
private:
    vector<string> values;
    mutable size_t uniqueCheckIndex = 0;
};

class AttributeDate : public Attribute
{
public:
    AttributeDate(string _name, int _startYear, bool _includeTime, bool _isUnique = false);

    string GenerateRandomValue() const override;
    string GenerateUniqueValue() const override;

private:
    int startYear;
    bool includeTime;
};