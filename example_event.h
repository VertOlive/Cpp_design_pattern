#ifndef EXAMPLE_EVENT_H
#define EXAMPLE_EVENT_H

struct cartesian_data;

Event_manager g_event_manager;

struct cartesian_data {
  float x = 0;
  float y = 0;
};

class global_catesian_var {
private:
  std::mutex mutex;
  cartesian_data coord = {0,0};
public:
  void write_cartesian(cartesian_data new_coord){
    const std::lock_guard<std::mutex> lock(mutex);
    coord = new_coord;
  }
  cartesian_data read_cartesian(){
    const std::lock_guard<std::mutex> lock(mutex);
    return coord;
  }
};
global_catesian_var gm_coord;

/* make a modular railroad for conditionnal, don't forget to suppress */
class Event_convert : public Event<int>  {
public:
  Event_convert() : c_id("Event_convert") {}

  void operator()(int deep) override {
    deep++;
    std::cout << "In event convert." << std::endl;
    auto coord = read_cartesian()
    write_cartesian(coord.x + 0.5, coord.y);

    float angle = std::atan2(gm_coord.x, gm_coord.y);
    float radius = (gm_coord.x*gm_coord.x + gm_coord.y*gm_coord.y);

    std::cout << "angle:" << angle << "radius:" << radius << std::endl;

    if (radius > 2) {
      g_event_manager.call_event("event_count_deep", deep);
    }
    else {
      g_event_manager.call_event("Event_convert", deep);
      g_event_manager.call_event("Event_count_deep", deep);
    }
  }
};

class Event_count_deep : public Event<int> {
  Event_count_deep() : c_id("Event_count_deep") {}

  void operator()(int deep) override {
    std::cout << "Event deep: " << deep << std::endl;
  }
}

#endif /* example_event.h */
