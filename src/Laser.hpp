#ifndef LASER
#define LASER

class Laser
{
  private:
	uint8_t _pin;

  public:
	Laser(uint8_t pin)
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