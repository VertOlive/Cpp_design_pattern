#include <iostream>
#include "example_event.h"

int main(int argc, char const *argv[]) {
  /* Init */
  Event_convert uniq_event_convert;
  Event_count_deep uniq_event_count_deep;
  g_event_manager.add_event(std::move(uniq_event_convert));
  g_event_manager.add_event(std::move(uniq_event_count_deep));

  /* Call of entry point */
  g_event_manager.call_event("Event_convert", 0);

  return 0;
}
