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

// Returns 1 is versionA is newer, -1 if versionB is newer, and 0 if they are identical
int compare_version(struct Version *versionA, struct Version *versionB)

#endif