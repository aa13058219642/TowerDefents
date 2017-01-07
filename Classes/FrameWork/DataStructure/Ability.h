#pragma once
#include <algorithm>
#include <string>
#include <list>

namespace cocosgalaxy
{

	template<typename _T>
	class _Ability_Value
	{
	public:
		_Ability_Value(){
			baseValue = _T();
			multiplier = _T(1);
			addend = _T(0);
		}

		_Ability_Value<_T>(const _T& value){
			baseValue = value;
			multiplier = _T(1);
			addend = _T(0);
		}

		operator _T(){ return getValue(); }
		const _Ability_Value& operator=(const _T& value){ baseValue = value; return *this; }
		template<typename _T2> _Ability_Value<_T>& operator+=(const _T2 &t2){ baseValue += t2; return *this; }
		template<typename _T2> _Ability_Value<_T>& operator-=(const _T2 &t2){ baseValue -= t2; return *this; }


		virtual _T getValue(){ return baseValue*multiplier + addend; }
		_T getBaseValue(){ return baseValue; }
		void setBaseValue(const _T& value){ baseValue = value; }
		virtual void clear(){ multiplier = _T(1); addend = _T(0); }
		void add(const _T& value, bool isReverse = false){ isReverse == false ? addend += value : addend -= value; }
		void mul(const _T& value, bool isReverse = false){ isReverse == false ? multiplier *= value : multiplier /= value; }

		_T clamp(_T value, _T min_inclusive, _T max_inclusive)
		{
			if (min_inclusive > max_inclusive) {
				//std::swap(min_inclusive, max_inclusive);
				min_inclusive = max_inclusive;
			}
			return value < min_inclusive ? min_inclusive : value < max_inclusive ? value : max_inclusive;
		}

		//protected:
		_T baseValue;
		_T multiplier;
		_T addend;
	};



	//Ability

	//非法定义
	template<typename _T> class Ability;

	//非法定义
	template<> class Ability < char >;

	template<>
	class Ability<short> : public _Ability_Value < short >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(short value) :_Ability_Value(value){}
	};

	template<>
	class Ability<int> : public _Ability_Value < int >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(int value) :_Ability_Value(value){}
	};

	template<>
	class Ability<long> : public _Ability_Value < long >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(long value) :_Ability_Value(value){}
	};

	template<>
	class Ability<float> : public _Ability_Value < float >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(float value) :_Ability_Value(value){}
	};

	template<> class Ability<double> : public _Ability_Value < double >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(double value) :_Ability_Value(value){}
	};
	
	template<>
	class Ability<unsigned short> : public _Ability_Value < unsigned short >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(unsigned short value) :_Ability_Value(value){}
	};
	
	template<>
	class Ability<unsigned int> : public _Ability_Value < unsigned int >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(unsigned int value) :_Ability_Value(value){}
	};
	
	template<>
	class Ability<unsigned long> : public _Ability_Value < unsigned long >
	{
	public:
		Ability() :_Ability_Value(){}
		Ability(unsigned long value) :_Ability_Value(value){}
	};
	
	
	template<typename _T>
	class _Ability_ValueEx : public _Ability_Value < _T >
	{
	public:
		Ability<_T> ValueMin;
		Ability<_T> ValueMax;
	
		_Ability_ValueEx(){ this->baseValue = 0; this->ValueMin = 0; this->ValueMax = 0x7fff; }
		_Ability_ValueEx(_T value, _T min, _T max){ this->baseValue = value; ValueMin.setBaseValue(min); ValueMax.setBaseValue(max); }
	
		operator _T(){ return getValue(); }
		const _Ability_ValueEx& operator=(const _T& value){ this->baseValue = value; return *this; }
	
		virtual _T getValue(){ return this->clamp(this->baseValue*this->multiplier + this->addend, ValueMin, ValueMax); }
		_T getRandmValue(){ return (rand() / (float)0x7fff) * (ValueMax - ValueMin + 1) + ValueMin; }
	
		virtual void clear(){ this->multiplier = _T(1); this->addend = _T(0); ValueMin.clear(); ValueMax.clear(); }
	};
	
	template<typename _T>
	class AbilityEx : public _Ability_Value < _T >
	{
	public:
		_Ability_ValueEx<_T> Min;
		_Ability_ValueEx<_T> Max;
	
		AbilityEx(){ this->baseValue = 0; this->Min = 0; this->Max = 0x7fff; }
		AbilityEx(_T value, _T min, _T max){ this->baseValue = value; Min.setBaseValue(min); Max.setBaseValue(max); }
	
		const AbilityEx& operator=(const _T& value){ this->baseValue = value; return *this; }
		template<typename _T2> AbilityEx<_T>& operator+=(const _T2 &t2){ this->baseValue += t2; if (this->baseValue > Max.getValue())this->baseValue = Max.getValue(); return *this; }
		template<typename _T2> AbilityEx<_T>& operator-=(const _T2 &t2){ this->baseValue -= t2; if (this->baseValue < Min.getValue())this->baseValue = Min.getValue(); return *this; }
	
		virtual _T getValue(){ return this->clamp(this->baseValue*this->multiplier + this->addend, Min, Max); }
		_T getRandmValue(){ return (rand() / (float)0x7fff) * (Max - Min + 1) + Min; }
	
		virtual void clear(){ this->multiplier = _T(1); this->addend = _T(0); Min.clear(); Max.clear(); }
	private:
	
	
	};
	
	//非法定义
	template<> class AbilityEx < std::string >;
	
	//######################################################################################
	
	template<typename _T>
	struct __Ability_Key_Data
	{
		int priority;
		_T value;
	
		__Ability_Key_Data()
	{
		priority = 0;
		value = _T();
	}
		__Ability_Key_Data(int priority, _T value){ this->priority = priority; this->value = value; }
		bool operator<(const __Ability_Key_Data<_T>& other)const { return this->priority < other.priority; }
		bool operator== (const __Ability_Key_Data<_T>& other) const { return this->priority == other.priority && this->value == other.value; }
		operator _T(){ return value; }
	};
	
	template<typename _T>
	class AbilityKey
	{
	public:
		AbilityKey() {}
		AbilityKey(int priority, _T value){ list.push_back(__Ability_Key_Data<_T>(priority, value)); }
	
		operator _T(){ return list.back(); }
		_T getValue(){ return list.back(); }
		void clear(){ list.clear(); list.push_back(base); }
		void add(const _T& value, int priority, bool isReverse = false)
		{
			if (isReverse == false)
			{
				list.push_back(__Ability_Key_Data<_T>(priority, value));
				list.sort();
			}
			else
			{
				list.erase(std::find(list.begin(), list.end(), __Ability_Key_Data<_T>(priority, value)));
			}
	
		}
	
		AbilityKey& operator=(const _T &value)
	{
		base.value = value;
		base.priority = 0;
		list.push_back(base);
		return *this;
	}
	
	
	private:
		__Ability_Key_Data<_T> base;
		std::list<__Ability_Key_Data<_T>> list;
	};
	
	////非法定义
//template<typename _T> class AbilityKey;
//
//template<>
//class AbilityKey<int> : public __Ability_Key<int>
//{
//public:
//	AbilityKey() :__Ability_Key(){}
//	AbilityKey(int priority, int value) :__Ability_Key(priority, value){}
//};
//
//template<>
//class AbilityKey<std::string> : public __Ability_Key<std::string>
//{
//public:
//	AbilityKey() :__Ability_Key(){}
//	AbilityKey(int priority, std::string value) :__Ability_Key(priority, value){}
//};
//
//template<>
//class AbilityKey<bool> : public __Ability_Key<bool>
//{
//public:
//	AbilityKey() :__Ability_Key(){}
//	AbilityKey(int priority, bool value) :__Ability_Key(priority, value){}
//};
	
}




