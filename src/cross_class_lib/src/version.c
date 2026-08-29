#include "../includes/version.h"

#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

const struct Version CURRENT_VERSION = {
    .major = 0,
    .minor = 0,
    .patch = 0,
};

struct Version get_current_version() { return CURRENT_VERSION; }

// Returns 1 is versionA is newer, -1 if versionB is newer, and 0 if they are identical
int compare_version(struct Version *versionA, struct Version *versionB){
    if(versionA->major > versionB->major){
        return 1;
    }
    if(versionA->major < versionB->major){
        return -1;
    }
    return 0;
}