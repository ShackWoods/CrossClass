#ifndef VERSION
#define VERSION

#include <stdbool.h>
#include "./linked_list.h"

struct Version {
  int major;
  int minor;
  int patch;
};

LIST_NODE(Version_List, Version);

struct Version get_current_version();

bool ensure_version_supported(struct Version *version);

#endif