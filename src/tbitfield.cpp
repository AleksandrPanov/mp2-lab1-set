// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#define LENGTHBYTE 8
#define BitInByte 3
#define ERROR 0
# define OffsetToLeft(num,n) (num << n)
inline int LengthInt()
{
	return sizeof(int)*LENGTHBYTE;
}

#include "tbitfield.h"
	TBitField::TBitField(int len)
	{
		try
		{
		if (len >= 0 && len < UINT_MAX)
		{
			BitLen = len;
			MemLen = (len - 1) / sizeof(int) + 1;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
		}
		else
			throw ERROR;
	}
		catch (int error)
		{
			cout << "you print " << len;
			throw ERROR;
		}

	}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0 && n < BitLen)
		return OffsetToLeft(n, n / LengthInt());
	else throw ERROR;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return OffsetToLeft(1,n % LengthInt());
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
		pMem[n / LengthInt()] = pMem[n / LengthInt()] | (1 << n % LengthInt());

	else throw ERROR;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
		pMem[n / LengthInt()] = pMem[n / LengthInt()] & (~(1 << n % LengthInt()));
	else
		throw ERROR;
}

int TBitField::GetBit(const int n) const // получить значение бита
{

	if (n >= 0 && n < BitLen)
		return (pMem[n / LengthInt()] & (1 << n % LengthInt()));
	else throw ERROR;
}

// битовые операции

TBitField *TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen >= bf.BitLen) 
	{
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
		return this;
	}
	else throw ERROR;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen || BitLen == bf.BitLen)
	{
		for (int i = 0; i < BitLen/LengthInt(); i++)
		{
			if (pMem[i] != bf.pMem[i])
				return false;
		}
	return true;
	}
	return false;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen || BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return true;
		return false;
	}
	return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
		if (bf.MemLen >= MemLen) 
		{
			TBitField tmp(bf);
			for (int i = 0; i < MemLen; i++)
				tmp.pMem[i] = tmp.pMem[i] | pMem[i];
			return tmp;
		}
		else
		{
			TBitField tmp(MemLen);
			for (int i = 0; i < bf.MemLen; i++)
				tmp.pMem[i] = pMem[i] | bf.pMem[i];

			for (int i = bf.MemLen; i < MemLen; i++)
				tmp.pMem[i] = pMem[i];
			return tmp;
		}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (bf.MemLen >= MemLen)
	{
		TBitField tmp(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		return tmp;
	}
	else
	{
		TBitField tmp(BitLen);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	tmp.pMem[BitLen /LengthInt()] = tmp.pMem[BitLen / LengthInt()] & (UINT_MAX >> (LengthInt()-BitLen%LengthInt()) );
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
