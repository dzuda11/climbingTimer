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

	bool hold(unsigned int duration)
	{
		unsigned int timeHold = 0, startHold = millis();
		do
		{
			timeHold = millis() - startHold;
		} while (on() && timeHold < duration);

		if (timeHold >= duration)
			return true;
		else
			return false;
	}
};

#endif