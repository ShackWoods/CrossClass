#ifndef VERSION
#define VERSION

#include <stdbool.h>
#include "./linked_list.h"

struct Version {
  int major;
  int minor;
  int patch;
};

struct Version get_current_version();

#endif