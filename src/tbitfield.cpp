// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (len / sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	memset(pMem, 0, MemLen * 4);
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
	delete pMem;
	cout << "Cработал деструктор";
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / sizeof(TELEM);
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
  return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[i] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int i = GetMemIndex(n);
	TELEM mask = ~GetMemMask(n);
	pMem[i] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{

	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	mask &= pMem[i];
    if (mask == 0) return 0;
	else return 1;
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
	for (int i = 0; i < MemLen; i++)
	{
		if (bf.pMem[i] != BitLen) return 0;
	}
	for (int i = BitLen - 1; i >= BitLen - BitLen % sizeof(TELEM); i--)
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
	for (int i = BitLen - 1; i >= BitLen - BitLen % sizeof(TELEM); i--)
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
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
