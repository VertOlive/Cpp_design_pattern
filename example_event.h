#ifndef EXAMPLE_EVENT_H
#define EXAMPLE_EVENT_H

struct cartesian_data {
  float x = 0;
  float y = 0;
};

struct polar_data {
  float angle = 0;
  float radius_sqr = 0;
};

class global_polar_var {
private:
  std::mutex mutex;
  polar_data polar = {0,0};
public:
  void write_polar(cartesian_data pol){
    const std::lock_guard<std::mutex> lock(mutex);
    polar = pol;
  }
  cartesian_data read_polar(){
    const std::lock_guard<std::mutex> lock(mutex);
    return polar;
  }
};

global_catesian_var var;


/* make a modular railroad for conditionnal, don't forget to suppress */
class Conc_logic_convert : public Logic<cartesian_data> {
protected:
  /* TODO */
  std::tuple<std::string, cartesian_data, std::function<void(T)> > railroad();
public:
  auto operator()(cartesian_data args) override {
    std::cout << "In event convert." << std::endl;

    polar_data = polar;
    polar.angle = std::atan2(args.x, args.y);
    polar.radius = (args.x*args.x + args.y*args.y);

    if((polar.angle%306) > 90)
      return std::make_tuple("add_1", args, var.write_polar(polar));
    return std::make_tuple("add_2", args, var.write_polar(polar));
  }

  polar_data get_polar(){return polar;}
};

template <int I>
class Conc_logic_add : public Logic<cartesian_data, bool> {
public:
  bool operator()(cartesian_data args) override {
    args.x = args.x + 1.;
    args.y = args.y + 1.;

    return std::make_tuple("convert")
  }
};

class Conc_event_end_true : public Event_end<bool> {
  bool operator()() {return true;}
};

class Conc_logic_end_false : public Event_end<bool> {
  bool operator()() {return false;}
};


#endif /* example_event.h */
