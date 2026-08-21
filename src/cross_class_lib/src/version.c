#include "../includes/version.h"

#include <stdlib.h>
#include <stdbool.h>

const struct Version CURRENT_VERSION = {
    .major = 0,
    .minor = 0,
    .patch = 0,
};

struct Version get_current_version() { return CURRENT_VERSION; }

bool ensure_version_supported(struct Version *version) {
    const int majors[5] = { 1, 1, 0, 0, 0 }; //TEMPORARY
    const int minors[5] = { 1, 0, 1, 1, 0 }; //TEMPORARY
    const int patches[5] = { 1, 2, 2, 1, 1 }; //TEMPORARY

    for(int i = 0; i < sizeof(majors) / sizeof(majors[0]); i++){
        if(version->major != majors[i]){
            continue;
        }
        if(version->minor != minors[i]){
            continue;
        }
        if(version->patch != patches[i]){
            continue;
        }
        return true;
    }
    return false;
}