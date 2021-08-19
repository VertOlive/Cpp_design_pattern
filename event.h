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
class Logic {
  virtual U operator()(T args) = 0;
};

template <typename T, typename U>
class Event_base {
public:
  virtual U call(T args) = 0;
};

template <typename U>
class Event_end {
  virtual U operator()() = 0;
};

template <typename T, typename U>
class Event : public Event_base<T,U> {
public:
  Logic_event(std::string id, Logic<T,U> logic) : c_id(id) {
    logic_event(logic);
    to_next = std::move(next_map);
  }
  virtual U operator()(T args){
    std::tuple<std::string next_id, T, std::function<void(T)> > ret = logic_event(T args);
    return call(std::get<0>(ret), std::get<1>(ret), std::get<2>(ret) );
  };
  std::string get_event_id(){return id;}

  U call(std::string next_event_id, T args, std::function<void(T)> callback ) override {
    for(size_t i = 0; i < to_next.size(); i++){
      if(to_next[i].*to_event.get_event_id() == next_event_id){
        return to_next[i](args, callback);
      }
    }
    std::cerr << "error calling event: no exesting event or event id" << std::endl;
    exit(EXIT_FAILLURE);
  }
  void add_next(Next<T, U> next) override {
    to_next.push_back(next);
  }
private:
  std::string c_id;
  Logic_event<T,U> logic_event;
  std::vector<Next<T,U> > to_next;
};

/* must review logic... The return type conflict with the argument
type ... */

/*
template <typename T, typename U>
class Event_manager {
private:
  Event<T, U> event;
protected:

public:
  Event_manager(){}

}; */

#endif /* event.h */
