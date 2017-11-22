/*
	LED Library - Senior Project - SJSU - 2015
	Alfredo Sandoval
	Source File
	
	V0.2 Update:
		Added ability to use the library for a software control. So that the library can be used for doing software timing or for use with things
		that require more complex on/off states such as a buzzer that requires OOK. the state() function can be used for masking or as a flag for more complex pin control
		
	V0.1 Update:
		Added ability for oneshot(), burst() mode, added state() function to provide the state of the LED
	
	*on() simply turns on the LED, will have to execute off() to turn it off
	*on(period, duty) does a non blocking blink of the LED, will have to call update() to ensure blinking continues
	*off() called to end on() or on(period, duty) state
	*oneshot(period) turns LED on for the specified duration. will have to call update() to ensure oneshot ends
		LED can be used with the 2 on() functions, or the oneshot function again
		off() disabled during oneshot process (to prevent early turn off of LED)
	*burst(period, duty, pulses) will blink the LED for the specified pulses (an on and an off), with a specified duty and period.
	*toggle() will invert the state of the LED
	
	Limitations:
		Can only do 256 bursts (can do more if you change the integer type of _brstcnt)
		Not good for frequencies above 10Hz+ due to having to constantly update the LED state.
*/
#include "Arduino.h"
#include "LED.h"

LED::LED()
{
	_hardware = 0;	//software timing
	_logic = 1;		//logic default to 1 for software
	_lock = 0; 		//not locked on startup
	off();			//auto turns off LEDs on startup
}

LED::LED(uint8_t pin, uint8_t logic)
{	
	_hardware = 1;
	_pin = pin;
	_logic = logic;
	_lock = 0; 				//not locked on startup
	pinMode(_pin, OUTPUT);
	off();			//auto turns off LEDs on startup

}
void LED::on()
{
	if(_lock == 0)
	{	
		if(_hardware == 1)
			digitalWrite(_pin, _logic);
		_period = 0;		//set to zero to means always on etc..
		_duty = 1;			//duty set to 1, doesnt matter since this overloaded function doesnt do PWM or freq
		_lock = 1;			//locks such that another call to on doesnt override anything
		_state = 1;			//gives the visual status of the LED (doesnt care about logic levels)
		_oneshot = 0;		//oneshot condition not true
		_burst = 0;			//burst condition not true
	}
}

void LED::on(int period, float duty)
{
	if(_lock == 0) //only executes upon turnoff of LED
	{
		if(_hardware == 1)
			digitalWrite(_pin, _logic);
		_timer1 = millis();
		_period = period;
		_duty = duty;
		_lock = 1;
		_state = 1;
		_oneshot = 0;
		_burst = 0;
	}
}

void LED::oneshot(int period)
{
	if(_lock == 0)
	{
		if(_hardware == 1)
			digitalWrite(_pin, _logic);
		_timer1 = millis();
		_period = period;
		_duty = 1;		//such that period = the on time of the oneshot input
		_lock = 1;
		_state = 1;
		_oneshot = 1;
		_burst = 0;
	}
}

void LED::burst(int period, float duty, uint8_t pulses)
{
	if(_lock == 0)
	{
		if(_hardware == 1)
			digitalWrite(_pin, _logic);
		_timer1 = millis();
		_period = period;
		_duty = duty;
		_lock = 1;
		_state = 1;
		
		_oneshot = 0;
		
		_burst = 1;		//enables burst mode
		_brstcnt = 0;	//reset burst count
		_pulses = pulses;
	}
		
}

void LED::off()
{
	if(_oneshot == 0 && _burst == 0)
	{
		if(_hardware == 1)
			digitalWrite(_pin, !_logic);
		_lock = 0;		//unlock the on function so it can be called again
		_state = 0;		//state of LED is visually off
	}
}

void LED::toggle()
{
	if(_logic == 1)			//if using logic high
	{
		if(_hardware == 1)
			digitalWrite(_pin, !_state);
	}
	if(_logic == 0)
	{
		if(_hardware == 1)
			digitalWrite(_pin, _state);
	}
	_state = !_state;
}

bool LED::state()
{
	return _state;
}

/*this function to be called every loop to 
recheck conditions and change LED appropriately
only needed if doing some fancy on and off stuff*/
void LED::update() 
{	
	if(_period != 0 && _lock == 1) 				//only fancy stuff done if period and duty specified && if off() was not executed
	{
		if( (millis() >= (_timer1 + _period * _duty) ) && (_state == 1) ) //if LED IS ON (independent of logic level)
		{	//turns off LED
			if(_oneshot == 0)
			{
				toggle(); 						//if not doing oneshot, then toggle LED to continue with pwm and freq mode of operation & to reset oneshot state
				_brstcnt++;
			}
			if(_oneshot == 1)
			{
				_oneshot = 0;					//set to zero to allow execution of off();
				off();							//if oneshot is true, then upon completion of a single trigger, go back to off state.
			}
			
			_timer1 = millis();
		}
		
		if( (millis() >= (_timer1 + _period * (1 - _duty) ) ) && (_state == 0) && (_oneshot == 0) && (_lock == 1)) 	//_oneshot == 0 prevents the turning on of LED after completion of shot
		{	//turns on LED																							//_lock == 1 prevents turn on of LED after completion of oneshot
			if( (_brstcnt != _pulses) )			//prevents transition to ON when final pulse of burst() complete
			{
			toggle();
			_timer1 = millis();
			}
			
			if((_brstcnt == _pulses) && (_burst == 1))	//ends burst mode upon completion of the last off state of burst(), this provides a smooth execution of back to back bursts()
			{
				_burst = 0;							//set to zero to allow execution of off();
				off();
			}
			
		}
	}
	
}