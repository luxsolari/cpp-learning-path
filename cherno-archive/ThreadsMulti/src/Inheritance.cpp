#include "pch.h"

class Person {
protected:
	int realAge; // the one that girls don't like to say
public: 
	int age;  // the one that girls will tell you
};

class Woman : public Person {
private:
	int breastSize; // something very private to girls ;)
public:
	Woman () {
		age = 20;			// this is ok. can give consent for sex 
		realAge = 25;		// she's older than she looks. But man she is hot!
		breastSize = 90;
	}
	int getAge () {
		return age;		// this is ok. age is public in the base class
	}

	int getRealAge() {
		return realAge; // they only tell this to other girls... or maybe their boyfriend.
	}
};

int reallyNotmainAgain () {
	Woman w {};
	w.age = 20;

	Person p {};
	p.age = 20;

	
	return 0;

}
