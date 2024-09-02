#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

typedef struct Identifiers {
  int length;
  int space;
  char **arr;
} Identifiers;

Identifiers *initIdentifiers(void);
int addIdentifier(Identifiers *identifiers, char *name);
void freeIdentifiers(Identifiers *ids);
void printIdentifiers(Identifiers *ids);
#endif
