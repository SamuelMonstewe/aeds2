#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

typedef struct Node {
  struct Node *vet[SIZE];
  char letter;
  bool endWord;
} Node;

typedef struct Trie {
  Node *root;
} Trie;

Node *newNode(char letter) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->letter = letter;
  n->endWord = false;

  for (int i = 0; i < SIZE; i++) {
    n->vet[i] = NULL;
  }

  return n;
}
void insert(Node *node, char *word) {
  if (word[0] == '\0') {
    node->endWord = true;
    return;
  }

  int index = word[0] - 'a';

  if (node->vet[index] == NULL) {
    node->vet[index] = newNode(word[0]);
  }

  insert(node->vet[index], word + 1);
}
char *search(Node *node, char *s) {}

void print(Node *node, char *s) {
  if (node->endWord == true) {
    printf("%s\n", s);
  }

  for (int j = 0; j < SIZE; j++) {
    if (node->vet[j] != NULL) {
      char d[100];
      sprintf(d, "%s%c", s, node->vet[j]->letter);

      print(node->vet[j], d);
    }
  }
}
int main() {
  Trie *t = (Trie *)malloc(sizeof(Trie));
  t->root = newNode('\0');

  insert(t->root, "mar");
  insert(t->root, "milho");
  insert(t->root, "molho");
  insert(t->root, "marin");

  print(t->root, "");
}
