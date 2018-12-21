// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
	maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
	maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
	maxPower = bitField.GetLength();
}

TSet::operator TBitField()
{
	return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return maxPower;
}

int TSet::IsMember(const int elem) const // элемент множества
{
	if ((elem < 0) || (elem >= maxPower))
		throw "Error len";
	return bitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
	if ((elem < 0) || (elem >= maxPower))
		throw "Error elem";
	bitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
	if ((elem < 0) || (elem >= maxPower))
		throw "Error elem";
	bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		maxPower = s.maxPower;
		bitField = s.bitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (maxPower != s.maxPower)
		return 0;
	else
		if (bitField != s.bitField)
			return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s)
		return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int len = maxPower;
	if (s.maxPower >= maxPower)
		len = s.maxPower;
	TSet temp(len);
	temp.bitField = bitField | s.bitField;
	return temp;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
	if ((elem < 0) || (elem >= maxPower))
		throw "Error elem";
	TSet temp(maxPower);
	temp = *this;
	if (temp.bitField.GetBit(elem) != 1)
		temp.bitField.SetBit(elem);
	return temp;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
	if ((elem < 0) || (elem >= maxPower))
		throw "Error elem";
	TSet temp(maxPower);
	temp = *this;
	if (temp.bitField.GetBit(elem) == 1)
		temp.bitField.ClrBit(elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int len = maxPower;
	if (s.maxPower >= maxPower)
		len = s.maxPower;
	TSet temp(len);
	temp.bitField = bitField & s.bitField;
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp = *this;
	temp.bitField = ~temp.bitField;
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	cin >> i;
	for (; (i > -1) && (i < s.maxPower); cin >> i)
	{
		s.bitField.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.bitField << ' ';
	return ostr;
}