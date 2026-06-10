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
  char str_tmp[2];
  str_tmp[0] = node->letter;
  str_tmp[1] = '\0';
  char d[40];

  strcpy(d, s);
  strcat(d, str_tmp);

  if (node->endWord == true) {
    printf("%s ", d);
  } else {
    for (int j = 0; j < SIZE; j++) {
      Node *n = node->vet[j];
      if (n != NULL) {
        print(n, d);
      }
    }
  }
}
int main() {
  Trie *t = (Trie *)malloc(sizeof(Trie));
  t->root = newNode('\0');

  insert(t->root, "mar");
  insert(t->root, "milho");
  insert(t->root, "molho");

  print(t->root, "");
}
