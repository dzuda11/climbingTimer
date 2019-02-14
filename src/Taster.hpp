#ifndef TASTER
#define TASTER

class Taster
{
private:
	uint8_t _pin;
public:
	Taster(uint8_t pin)
	{
		_pin = pin;
		pinMode(_pin, INPUT);
	}
	
	bool on()
	{
		return digitalRead(_pin);
	}
};

#endif