// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower){}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()){}

TSet::operator TBitField()
{
	TBitField bit(BitField);
	return bit;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem <= MaxPower)
		if (BitField.GetBit(Elem))
			return true;
	return false;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem <= MaxPower)
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem <= MaxPower)
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
		if (BitField == s.BitField)
			return true;
	return false;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
		if (BitField == s.BitField)
			return false;
	return true;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	MaxPower = Max1(MaxPower, s.MaxPower);
	BitField = BitField | s.BitField;
	return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem <= MaxPower)
		BitField.SetBit(Elem);
	else throw ERROR;
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem <= MaxPower)
		BitField.ClrBit(Elem);
	else throw ERROR;
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	MaxPower = Max1(MaxPower, s.MaxPower);
	BitField = BitField & s.BitField;
	return *this;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << s.BitField;
	return ostr;
}
