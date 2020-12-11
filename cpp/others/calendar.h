#pragma once

#include "pnsei.h"

namespace _calendar {

struct datettime {};

class calendar {
  int id;
  string title;
};

struct event {
  // mandatory
  int id;
  string title;
  datettime startDT;
  datettime endDT;
  int duration; // unit: minutes

  // optional
  int creator;
  int organizer;
  string reminder;
  bool is_allday;
  bool is_private;
};

struct single_event : public event {};
struct recurring_event : public event {
  string rrule;
};

class user {
public:
  user() {
    // 1. create a primary calendar
  }
  int id;
  string email;
  vector<calendar> calendars;
  void createEvent(){
      // 1. add a new row in events table
      // 2. add 1/many new row in attendee_user, attendee_group
      // 3. send email to ask attendee users and groups for acceptance
  };
};

} // namespace _calendar