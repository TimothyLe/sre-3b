/*
	LED Library - Senior Project - SJSU - 2015
	Made By Alfredo Sandoval
	Header File
*/
#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED
{
	public:
		LED();
		LED(uint8_t pin, uint8_t logic);
		void on();
		void on(int period, float duty);
		void off();
		void toggle();
		void update();
		void oneshot(int period);
		void burst(int period, float duty, uint8_t pulses);
		bool state(); //useful for using as a mask
		
	private:
		uint8_t _hardware;	//used to specify if a hardware timer or software timer (for use with something like a buzzer that requires more than a simple on/off control i.e. OOK)
		uint8_t _pin;
		uint8_t _logic;
		uint8_t _brstcnt;//keep track of # of bursts
		uint8_t _pulses;//private varaible to save number of pulses
		bool _state;
		int _period;
		float _duty;
		long _timer1;	//used for general timing for oneshot and on w/ freq/duty
//		long _timer2; 	//used for burst timing
		bool _lock; 	//used to prevent updating of turned of led
		bool _oneshot; 	//used to identify a oneshot condition
		bool _burst;
};



#endif