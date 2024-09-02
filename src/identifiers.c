#include "identifiers.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SPACE 1

Identifiers *initIdentifiers(void) {
  errno = 0;
  char **texts = calloc(INITIAL_SPACE, sizeof(char *));
  if (NULL == texts) {
    perror("Allocating document identifiers");
    return NULL;
  }

  errno = 0;
  Identifiers *ids = calloc(1, sizeof(Identifiers));
  if (NULL == ids) {
    perror("Allocating ids");
    return NULL;
  }

  ids->arr = texts;
  ids->space = INITIAL_SPACE;
  ids->length = 0;
  return ids;
}

int addIdentifier(Identifiers *identifiers, char *name) {
  if (identifiers->length >= identifiers->space) {
    int newSpace = identifiers->space * 2;
    identifiers->space = newSpace;
    errno = 0;
    char **tmp = realloc(identifiers->arr, newSpace * sizeof(char *));
    if (NULL == tmp) {
      free(identifiers->arr);
      identifiers->arr = NULL;
      perror("Problem reallocating identifiers");
      exit(EXIT_FAILURE);
    } else if (identifiers->arr != tmp) {
      identifiers->arr = tmp;
    }
    tmp = NULL;
  }
  identifiers->arr[identifiers->length] = name;
  ++identifiers->length;
  return identifiers->length - 1;
}

void freeIdentifiers(Identifiers *ids) {
  for (int i = 0; i < (int)ids->length; ++i) {
    if (NULL != ids->arr[i]) {
      free(ids->arr[i]);
      ids->arr[i] = NULL;
    }
  }
  free(ids->arr);
  ids->arr = NULL;
  free(ids);
  ids = NULL;
}

void printIdentifiers(Identifiers *ids) {
  for (int i = 0; i < (int)ids->length; ++i) {
    printf("%d: %s\n", i, ids->arr[i]);
  }
}
