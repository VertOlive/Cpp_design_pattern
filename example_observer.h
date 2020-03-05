#ifndef ACTS_H 
#define ACTS_H 

#include "observer.h"

class Brain : public observer<Brain, int> {
	private:
		int m_value = 0;
	public:
		void print_value() {
			std::cout << "Value x = " << m_value << std::endl;
		}
		void update(int value) override {			
			m_value = value;
		}

};

class Actionner : public observable<Brain, int> {
	private:
		int m_x;

	public:
		Actionner(int x) : m_x(x) { }
		void change_x_value(int x) {
			m_x = x;
			notify(m_x);

			return;
		}
};

#endif /* ACTS_H */
