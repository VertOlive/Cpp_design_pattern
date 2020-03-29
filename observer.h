#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <vector>
#include <memory>

template <typename T, typename U, typename V> class observer;

template <typename T, typename U, typename V>
class observable {
	private:
	std::vector<observer<T, U, V>*> m_list_of_observer;
	
	public:
	void add_observer(observer<T, U, V>* obs);
	void delete_observer(observer<T, U, V>* obs);
	void notify(V value);

};

template <typename T, typename U, typename V>
class observer {
	public:
	virtual void update(V value) {};
};

template <typename T, typename U, typename V>
void observable<T, U, V>::add_observer(observer<T, U, V>* obs) {
	m_list_of_observer.push_back(obs);
}

template <typename T, typename U, typename V>
void observable<T, U, V>::delete_observer(observer<T, U, V>* observer) {
	for(int i = 0; i < m_list_of_observer.size(); i++) {
		if( m_list_of_observer[i] == observer) {
			m_list_of_observer.erase(
				m_list_of_observer.begin() + i);
		}
	}
}

template <typename T, typename U, typename V>
void observable<T, U, V>::notify(V value) {
	for(auto &observer: m_list_of_observer) {
		observer->update(value);
	}
}

#endif /* OBSERVER_H */
