#ifndef DECORATOR_H
#define DECORATOR_H

#include <functional>

template <typename T, typename ... Args>
class decorator {
	public:
		decorator(std::function<T(T)> at_exit) : 
						c_at_exit(at_exit) {
		}
		
		std::function<T(Args ...)> make_decorator(std::function<T(Args...)> callable) {
			return  [=](Args ... args) { return c_at_exit(callable(args...)); };
		}

	private:
		std::function<T(T)> c_at_exit;
};

#endif /* DECORATOR_H */
