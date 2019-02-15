#ifndef RESULT
#define RESULT

#include<Arduino.h>

class Result
{
private:
	String _name;
	unsigned long _record;
	
public:
	Result(String name = "", unsigned long record = 0)
	{
		_name = name;
		_record = record;
	}
	Result (const Result &source)
	{
		_name = source._name;
		_record = source._record;
	}

	String getName() { return _name; }
	unsigned long getRecord() { return _record; }
	static String recordString(unsigned long time) 
	{ 
		String ret = "";
		if (time >= 60000)
			ret += String(time / 60000) + " min ";
		ret += String((time / 1000)%60);
		if (time < 60000)
			ret += "." + String(time % 1000);
		ret += " sec";
		return ret;
	}

	static int compare(Result &a, Result &b)
	{
		if (a._record > b._record)
			return 1;
		return -1;
	}
};


#endif