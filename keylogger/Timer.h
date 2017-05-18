#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer {

	//PRIVATE ATTRIBUTES AND METHODS
	std::thread Thread; //thread for asynchronous execution
	bool Alive = false; //is the process alive?
	long CallNumber = -1L; //determines how many times to call a function
	long repeat_count = -1L; //counts the amount of times a function has been called
	std::chrono::milliseconds interval = std::chrono::milliseconds(0); //interval between function calls
	std::function<void(void)> funct = nullptr; //a pointer to a function (initialized as null)

	void SleepAndRun(){
    	std::this_thread::sleep_for(interval);
    	if(Alive)
        	Function()();
	}

	void ThreadFunc(){
    	if(CallNumber == Infinite)
        	while(Alive)
            	SleepAndRun();
    	else
        	while(repeat_count--)
            	SleepAndRun();
	}

	public:

    	//PUBLIC ATTRIBUTES
    	static const long Infinite = -1L;

    	Timer(){} //constructor for Time

    	Timer(const std::function<void(void)> &f) : funct (f) {}

    	Timer(const std::function<void(void)> &f,
          	const unsigned long &i, const long repeat = Timer::Infinite) : funct (f),
          	interval(std::chrono::milliseconds(i)), CallNumber(repeat) {}

    	//starts the timer
    	void Start(bool Async = true){
        	if(IsAlive())
            	return;
        	Alive = true;
        	repeat_count = CallNumber;
        	if(Async)
            	Thread = std::thread( [this] { this->ThreadFunc(); });
        	else
            	this->ThreadFunc();
    	}

    	//stops the timer
    	void Stop(){
        	Alive = false;
        	Thread.join(); //joins threads together to stop concurrent execution on main thread, stops timer
    	}

    	//GETTERS AND SETTERS
    	bool IsAlive() const {return Alive;} //getter
    	void RepeatCount(const long r){ //setter for number of repeats
        	if(Alive)
            	return;
        	CallNumber = r;
    	}
    	void SetFunction(const std::function<void(void)> &f){funct = f;} //setter for functions
    	long GetLeftCount() const {return repeat_count;} //returns number of calls left
    	long RepeatCount() const {return CallNumber;} //returns number of repeats
    	void SetInterval(const unsigned long &i){ //sets interval value
        	if(Alive)
            	return;
        	interval = std::chrono::milliseconds(i);
    	}
    	unsigned long Interval() const {return interval.count();} //gets interval value
    	const std::function<void(void)> &Function() const {return funct;} //gets funct

}; //closing bracket of Timer class

#endif // TIMER_H
