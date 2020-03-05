#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <vector>
#include <memory>

template <typename T, typename U> class observer;

template <typename T, typename U>
class observable {
	private:
	std::vector<observer<T, U>*> m_list_of_observer;
	
	public:
	void add_observer(observer<T, U>* obs);
	void delete_observer(observer<T, U>* obs);
	void notify(U value);

};

template <typename T, typename U>
class observer {
	public:
	virtual void update(U value) {};
};

template <typename T, typename U>
void observable<T, U>::add_observer(observer<T, U>* obs) {
	m_list_of_observer.push_back(obs);
}

template <typename T, typename U>
void observable<T, U>::delete_observer(observer<T, U>* observer) {
	for(int i = 0; i < m_list_of_observer.size(); i++) {
		if( m_list_of_observer[i] == observer) {
			m_list_of_observer.erase(
				m_list_of_observer.begin() + i);
		}
	}
}

template <typename T, typename U>
void observable<T, U>::notify(U value) {
	for(auto &observer: m_list_of_observer) {
		observer->update(value);
	}
}

#endif /* OBSERVER_H */
