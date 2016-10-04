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
	else throw "Bad bit";
}

// битовые операции

TBitField *TBitField::operator=(const TBitField &bf) // присваивание
{
	if (*this != bf)
	{
		if (BitLen >= bf.BitLen)
		{
			MemLen = bf.MemLen;
			BitLen = bf.BitLen;
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
		else
		{
			delete[] pMem;
			pMem = new TELEM[bf.BitLen];
			MemLen = bf.MemLen;
			BitLen = bf.BitLen;
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	}
	return this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int min = Min(MemLen, bf.MemLen);
	int max = Max1(MemLen, bf.MemLen);
	for (int i = 0; i < min; i++)
		if (pMem[i] != bf.pMem[i])
			return false;
	if (min != max) 
	{
		TELEM *maxField;
		if (MemLen > bf.MemLen)
			maxField = pMem;
		else maxField = bf.pMem;

		for (int i = min + 1; i < max; i++)
			if (maxField[i] != 0)
				return false;
	}
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int min = Min(MemLen, bf.MemLen);
	int max = Max1(MemLen, bf.MemLen);
	for (int i = 0; i < min; i++)
		if (pMem[i] != bf.pMem[i])
			return true;

	if (min != max) {
		TELEM *maxField;
		if (MemLen > bf.MemLen)
			maxField = pMem;
		else maxField = bf.pMem;

		for (int i = min + 1; i < max; i++)
			if (maxField[i] != 0)
				return true;
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
	for (int i = BitLen / LengthInt() + 1; i < MemLen; i++)
		tmp.pMem[i] = 0;
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	cout << "max nomber in bitfield ="<<bf.BitLen - 1<<endl;
	int count = 0;
	int bit;
	cin >> bit;
	while (count < bf.BitLen)
	{
		if (bf.GetBit(bit) == 0)
		{
			bf.SetBit(bit);
			count++;
		}
	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++)
		if (bf.pMem[i] != 0)
		{
			for (int j = 0; j < LengthInt(); j++)
				if (bf.pMem[i] & (1 << j))
					cout << j + i*LengthInt() << " ";
		}
	cout << endl;
	return ostr;
}

