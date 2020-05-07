#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <vector>
#include <memory>

template <typename T, typename U, typename V> class observer;

template <typename T, typename U, typename V>
class observable {
	private:
	// a vector of reference_warpper is better than a vector pointers.
	std::vector<std::reference_wrapper<observer<T, U, V> > > m_list_of_observer;
	
	public:
	void add_observer(observer<T, U, V>& obs);
	void delete_observer(observer<T, U, V>& obs);
	void notify(V value);

};

template <typename T, typename U, typename V>
class observer {
	public:
	// Let to user definition his .h file.
	virtual void update(V value) = 0;
};

template <typename T, typename U, typename V>
void observable<T, U, V>::add_observer(observer<T, U, V>& obs) {
	m_list_of_observer.push_back(obs);
}

template <typename T, typename U, typename V>
void observable<T, U, V>::delete_observer(observer<T, U, V>& observer) {
	for(int i = 0; i < m_list_of_observer.size(); i++) {
		// reference compared, work.
		if( m_list_of_observer[i] == observer) {
			m_list_of_observer.erase(
				m_list_of_observer.begin() + i);
		}
	}
}

template <typename T, typename U, typename V>
void observable<T, U, V>::notify(V value) {
	for(const auto observer: m_list_of_observer) {
		// get() is because of reference_warpper.
		observer.get().update(value);
	}
}

#endif /* OBSERVER_H */
