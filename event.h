#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include <map>

template <typename T, typename U>
class Event;

/* All call back must have the same template type */
template <typename T, typename U>
class Callback {
public:
  U operator()(T args) {
    return *to_event(args);
  };
protected:
  std::shared_ptr<Event<T, U> > to_event;
};


template <typename T, typename U>
class Logic_event {
protected:
  U call(std::string callback_id, T args) {
    return to_callbacks[callback_id](args);
  }

  void add_callback(std::string id, Callback<T, U> callback){
    to_callbacks.insert(id, callback);
  }

  std::map<std::string ,Callback<T, U> > to_callbacks;
};

template<typename T, typename U>
struct Event {
  Logic_event<T,U> logic;
  Callback<T,U> callback;
};

#endif /* event.h */
