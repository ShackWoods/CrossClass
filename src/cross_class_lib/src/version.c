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

// Auxiliary function to minimize space
void extend_supported_versions(struct Version_List **tail, int major, int minor, int patch) {
  (*tail)->next = malloc(sizeof(typeof(*((*tail)->next))));
  struct Version_List *new_version = (*tail)->next;
  new_version->data = malloc(sizeof(typeof((*new_version->data))));
  new_version->data->major = major;
  new_version->data->minor = minor;
  new_version->data->patch = patch;
  new_version->next = NULL;
  new_version->prev = *tail;
  *tail = new_version;
}

struct Version_List *get_supported_versions(){
  struct Version supported_version_data = get_current_version();

  struct Version_List *version_list =
    malloc(sizeof(typeof(*version_list)));
  version_list->data = &supported_version_data;
  version_list->next = NULL;
  version_list->prev = NULL;

  // Just list out all accepted versions
  // Note that tests must use one of these versions to pass
  extend_supported_versions(&version_list, 0, 0, 1);
  return version_list;
}

bool ensure_version_supported(struct Version *version) {
  struct Version_List *supported_versions = get_supported_versions();

  if(supported_versions == NULL){
    return false; // Error case/No versions are supported
  }

  bool valid = false;
  while(supported_versions->prev != NULL && !valid){
    if(version->major == supported_versions->data->major &&
      version->minor == supported_versions->data->minor &&
      version->patch == supported_versions->data->patch){
      valid = true;
    }
    supported_versions = supported_versions->prev; // As we did not wind back
  }
  // We may not have considered the head
  if(version->major == supported_versions->data->major &&
    version->minor == supported_versions->data->minor &&
    version->patch == supported_versions->data->patch){
    valid = true;
  }

  // Finish winding back
  while(supported_versions->prev != NULL){
    supported_versions = supported_versions->prev;
  }
    // Free up memory
  while(supported_versions->next != NULL){
    supported_versions = supported_versions->next;
    free(supported_versions->prev);
  }
  free(supported_versions);

  return valid;
}