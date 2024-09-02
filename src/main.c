#include "identifiers.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Posting {
  int docId;
  struct Posting *next;
  struct Posting *prev;
  struct Posting *last;
} Posting;

typedef struct InvertedIndex {
  char *token;
  Posting *postings;
} InvertedIndex;

int hash(char *str) {
  uint32_t hash = 5423;
  hash ^= 2166136261UL;
  const uint8_t *data = (const uint8_t *)str;
  for (int i = 0; data[i] != '\0'; ++i) {
    hash ^= data[i];
    hash *= 16777619;
  }
  return hash;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "\033[31;1;1mPlease provide a directory of documents for "
                    "indexing\033[0m\n");
    exit(EXIT_FAILURE);
  }
  char *directoryName = argv[1];
  size_t directoryNameLength = strlen(directoryName);

  errno = 0;
  DIR *directory = opendir(directoryName);

  if (NULL == directory) {
    perror("\033[31;1;1mOpen directory\033[0m");
    exit(EXIT_FAILURE);
  }

  struct dirent *dir;

  Identifiers *documents = initIdentifiers();

  while (NULL != (dir = readdir(directory))) {
    char *ext = strrchr(dir->d_name, '.');
    if (DT_REG == dir->d_type && NULL != ext && 0 == strcmp(ext + 1, "txt")) {
      errno = 0;
      char *name = calloc(dir->d_namlen + 1, sizeof(char));
      if (NULL == name) {
        perror("Allocating document identifier");
        exit(EXIT_FAILURE);
      }

      errno = 0;
      if (0 > sprintf(name, "%s", dir->d_name)) {
        perror("Error copying filename to identifiers");
        exit(EXIT_FAILURE);
      }

      addIdentifier(documents, name);
      printIdentifiers(documents);

      size_t qualifiedCharNameLength = dir->d_namlen + directoryNameLength + 1;
      char qualifiedCharName[qualifiedCharNameLength];

      errno = 0;
      if (0 > sprintf(qualifiedCharName, "%s/%s", directoryName, dir->d_name)) {
        perror("Concatenating directory and filename");
        exit(EXIT_FAILURE);
      }

      printf("Reading document %s\n", qualifiedCharName);

      errno = 0;
      FILE *file;
      if (NULL == (file = fopen(qualifiedCharName, "r"))) {
        perror("Open file");
        exit(EXIT_FAILURE);
      }

      char character = fgetc(file);
      while (EOF != character) {
        putchar(character);
        character = fgetc(file);
      }

      errno = 0;
      if (0 != fclose(file)) {
        perror("Closing file");
        exit(EXIT_FAILURE);
      }
    }
  }

  errno = 0;
  if (0 != closedir(directory)) {
    perror("\033[31;1;1mClose directory\033[0m");
    exit(EXIT_FAILURE);
  }

  printIdentifiers(documents);
  freeIdentifiers(documents);
  exit(EXIT_SUCCESS);
}
