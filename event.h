#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <memory>
#include <map>

template <typename T>
class Event {
public:
  friend Event_manager<T>::call_event(std::string id, T args);
  virtual void operator()(T args) = 0;

  std::string get_event_id(){return id;}
private:
  std::string c_id;
};

template <typename T>
class Event_manager {
public:
  Event_manager() {}
  void call_event(std::string id, T args) {    /* test if exist */
    auto it = to_next.find(id)
    if(it != to_next.end() ) {
      std::async(std::launch::async, to_next.at(args.next_id)(args));
    }
    else {
      std::cout << "End of event chain or no reference to next event." << std::endl;
    }
  }

  void add_event(Event<T>&& event) {
    const std::lock_guard<std::mutex> lock(mutex);
    to_next.insert(event);
  }

protected:
  std::mutex mutex;
  std::map<Event<T> > to_next;
private:
  std::string id;
};


#endif /* event.h */
