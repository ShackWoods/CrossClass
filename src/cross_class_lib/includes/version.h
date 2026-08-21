#ifndef VERSION
#define VERSION

#include <stdbool.h>

struct Version {
  int major;
  int minor;
  int patch;
};

struct Version get_current_version();

bool ensure_version_supported(struct Version *version);

#endif