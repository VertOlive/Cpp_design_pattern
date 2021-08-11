#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <memory>
#include <map>

template <typename T, typename U>
class Event;

/* All call back must have the same template type */
template <typename T, typename U>
class Next {
public:
  Next(auto event_ptr) : to_event(event), decorator([](T args) -> T {return args;}) {}
  Next(auto event_ptr, std::function<T(T)> dec) : to_event(event_ptr), decorator(dec) {}

  U operator()(T args, std::function<void(T)> callback) {
    callback(args);
    return *to_event(decorator(args));
  };
private:
  std::shared_ptr<Event<T, U> > to_event;
  std::function<T(T)> decorator;
};

template <typename T, typename U>
class Logic {virtual U operator()(T args) = 0;};

template <typename T, typename U>
class Logic_event {
public:
  Logic_event(std::map<std::string, Next<T,U>> &&next_map) {
    to_next = std::move(next_map);
  }
  virtual U operator()(T args) = 0;
protected:
  U call(int next_event_id, T args, std::function<void(T)> callback) {
    return to_next[next_event_id](args, callback(args));
  }

  void add_next(Next<T, U> next){
    to_next.push_back(next);
  }
private:
  std::vector<std::string ,Next<T, U> > to_next;
};

#endif /* event.h */
