// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле


#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Error len";
	}
	else
	{
		bitLen = len;
		memLen = (bitLen / (8 * sizeof(TELEM))) + 1;
		pMem = new TELEM[memLen];
		for (int i = 0; i < memLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new TELEM[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;

	pMem = 0;
	memLen = 0;
	bitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= bitLen))
		throw "Error bit";
	else
	{
		return n / (8 * sizeof(TELEM));
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= bitLen))
		throw "Error bit";
	else
	{
		return 1 << ((n - 1) % (8 * sizeof(TELEM)));
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= bitLen))
		throw "Error bit";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= bitLen))
		throw "Error bit";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= bitLen))
		throw "Error bit";
	return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		bitLen = bf.bitLen;
		memLen = bf.memLen;
		pMem = new TELEM[memLen];
		for (int i = 0; i < memLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int rez = 1;
	if (bitLen != bf.bitLen)
		rez = 0;
	else
	{
		for (int i = 0; i < memLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				rez = 0;
				break;
			}
		}
	}
	return rez;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int rez = 1;
	if (*this == bf)
		rez = 0;
	return rez;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = bitLen;
	if (bf.bitLen > len)
		len = bf.bitLen;
	TBitField temp(len);
	for (i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.memLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = bitLen;
	if (bf.bitLen > len)
		len = bf.bitLen;
	TBitField temp(len);
	for (i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.memLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp = *this;
	for (int i = 0; i < temp.bitLen; i++)
	{
		if (temp.GetBit(i))
			temp.ClrBit(i);
		else
			temp.SetBit(i);
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string temp;
	istr >> temp;
	if (temp.size() != bf.GetLength())
		throw "Error len";
	else
	{
		for (int i = 0; i < bf.GetLength(); i++)
		{
			if (temp[i] == '0')
				bf.ClrBit(i);
			else
				if (temp[i] == '1')
					bf.SetBit(i);
				else
					throw "Error istream";
		}
		return istr;
	}
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << 1;
		else
			ostr << 0;
	}
	return ostr;
}