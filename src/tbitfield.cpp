// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>
#include<iostream>
using namespace std;

TBitField::TBitField(int len)
{
	if (len > 0) {
		BitLen = len;
		MemLen = (len / (sizeof(TELEM) * 8 )) + 1;
		pMem = new TELEM[MemLen];
		memset(pMem, 0, MemLen * 32);
	}
	else throw len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	memcpy(pMem, bf.pMem, MemLen * 4);
}

TBitField::~TBitField()
{
	delete[] pMem;
	cout << "Cработал деструктор";
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / sizeof(TELEM) + 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM a;
	a = 1;
	a << (n % sizeof(TELEM));
	return a;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ( (n >= 0) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		pMem[i] |= mask;
	}
	else throw n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		TELEM mask = ~GetMemMask(n);
		pMem[i] &= mask;
	}
	else throw n;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		mask &= pMem[i];
		if (mask == 0) return 0;
		else return 1;
	}
	else throw n;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen)
	{
		delete[] pMem;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	memcpy(pMem, bf.pMem, MemLen * 4);
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bf.BitLen != BitLen) return 0;
	for (int i = 0; i < MemLen - 1 ; i++)
	{
		if (bf.pMem[i] != BitLen) return 0;
	}
	for (int i = BitLen - 1; i >= BitLen - BitLen % (sizeof(TELEM) * 8); i--)
	{
		if (bf.GetBit(i) != GetBit(i)) return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{

	if (bf.BitLen != BitLen) return 1;
	for (int i = 0; i < MemLen; i++)
	{
		if (bf.pMem[i] != BitLen) return 1;
	}
	for (int i = BitLen - 1; i >= BitLen - BitLen % (sizeof(TELEM)*8); i--)
	{
		if (bf.GetBit(i) != GetBit(i)) return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int bl;
	if (BitLen > bf.BitLen) bl = BitLen;
	else bl = bf.BitLen;
	TBitField tmp(bl);

	int minml,maxml;
	if (MemLen > bf.MemLen)
	{
		minml = bf.MemLen;
		maxml = MemLen;
		for (int i = minml; i < maxml; i++) tmp.pMem[i] = pMem[i];
	}
	else
	{
		minml = MemLen;
		maxml = bf.MemLen;
		for (int i = minml; i < maxml; i++) tmp.pMem[i] = bf.pMem[i];
	}
	
	for (int i = 0; i < minml; i++) tmp.pMem[i] = pMem[i] | bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

	int bl;
	if (BitLen < bf.BitLen) bl = BitLen;
	else bl = bf.BitLen;
	TBitField tmp(bl);

	int minml;
	if (MemLen > bf.MemLen)		minml = bf.MemLen;
	else	minml = MemLen;
	

	for (int i = 0; i < minml; i++) tmp.pMem[i] = pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++) tmp.pMem[i] = ~ pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string st;
	istr >> st;
	for (int i = 0; i < st.size(); i++)
	{
		if ((st[i] != '0') && (st[i] != '1')) break;
		else {
			if (st[i] = '1') bf.SetBit(i);
			else bf.ClrBit(i);
		}
	}
		return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0; i < bf.GetLength(); i++)
	{
		if (bf.GetBit(i)) ostr << i; else return ostr;
	}
}
