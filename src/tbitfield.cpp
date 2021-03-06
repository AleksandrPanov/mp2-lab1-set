// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#define LENGTHBYTE 8
#define ERROR 0
inline int LengthInt()
{
	return sizeof(int)*LENGTHBYTE;
}

#include "tbitfield.h"
	TBitField::TBitField(int len)
	{
		try
		{
		if (len > 0 && len < UINT_MAX)
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
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return 0;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 0;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	TBitField a(1);
	return a;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	return 0;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return 0;
}

TBitField TBitField::operator~(void) // отрицание
{
	return 0;
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
