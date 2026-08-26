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

void delete_version_list(struct Version_List *list) {
  printf("Begin deleting - %d, %d, %d\n", &(list->data->major), &(list->data->minor), &(list->data->patch));
  while(list->prev != NULL){
    list = list->prev;
  }
  printf("Reached head of list - %d, %d, %d\n", &(list->data->major), &(list->data->minor), &(list->data->patch));

  while (list->next != NULL) {
    printf("%d, %d, %d\n", &(list->data->major), &(list->data->minor), &(list->data->patch));
    free(list->data);
    printf("DELETED DATA\n");
    list = list->next;
    free(list->prev);
    printf("DELETED PRIOR NODE\n");
  }

  printf("%d, %d, %d\n", &(list->data->major), &(list->data->minor), &(list->data->patch));
  free(list->data);
  printf("DELETED DATA\n");
  free(list);
  printf("DELETED PRIOR NODE\n");
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

  // Free up memory
  delete_version_list(supported_versions);

  return valid;
}