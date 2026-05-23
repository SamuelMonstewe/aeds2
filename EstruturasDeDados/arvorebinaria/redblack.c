#include <stdio.h>
#include <stdlib.h>

#define RED 'R'
#define BLACK 'B'

typedef struct Node {
  int key;
  char color;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
} Node;

typedef struct RedBlackTree {
  struct Node *root;
  struct Node *T_nil;

} RedBlackTree;

void rotate_for_left(RedBlackTree *T, Node *x) {
  Node *y = x->right;

  x->right = y->left;

  if (y->left != T->T_nil) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == T->T_nil) {
    T->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

void rotate_for_right(RedBlackTree *T, Node *x) {
  Node *y = x->left;

  x->left = y->right;

  if (y->right != T->T_nil) {
    y->right->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == T->T_nil) {
    T->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }

  y->right = x;
  x->parent = y;
}

void insert_fixup_RB(RedBlackTree *T, Node *z) {
  while (z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      Node *y = z->parent->parent->right;

      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotate_for_left(T, z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotate_for_right(T, z->parent->parent);
      }
    } else {
      Node *y = z->parent->parent->left;

      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotate_for_right(T, z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotate_for_left(T, z->parent->parent);
      }
    }
  }

  T->root->color = BLACK;
}
void insert_RB(RedBlackTree *T, Node *z) {
  Node *x = T->root;
  Node *y = T->T_nil;

  while (x != T->T_nil) {
    y = x;

    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  if (y == T->T_nil) {
    T->root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->parent = y;
  z->left = T->T_nil;
  z->right = T->T_nil;
  z->color = RED;

  insert_fixup_RB(T, z);
}

int heigth(RedBlackTree *T, Node *root) {
  if (root == T->T_nil || (root->left == T->T_nil && root->right == T->T_nil)) {
    return 0;
  }

  int hl = 1 + heigth(T, root->left);
  int hr = 1 + heigth(T, root->right);

  return (hl < hr) ? hr : hl;
}

void inorder_traversal(RedBlackTree *T, Node *root) {
  if (root != T->T_nil) {
    inorder_traversal(T, root->left);
    printf("%d ", root->key);
    inorder_traversal(T, root->right);
  }
}
int main() {
  RedBlackTree *T = (RedBlackTree *)malloc(sizeof(RedBlackTree));
  T->T_nil = (Node *)malloc(sizeof(Node));
  T->T_nil->color = BLACK;
  T->root = T->T_nil;
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int i = 0;

  while (i < 9) {
    Node *z = (Node *)malloc(sizeof(Node));
    z->key = A[i++];

    insert_RB(T, z);
  }
  inorder_traversal(T, T->root);
  printf("\n%d", heigth(T, T->root));
}
