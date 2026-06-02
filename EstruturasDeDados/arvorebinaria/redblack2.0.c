#include <stdio.h>
#include <stdlib.h>

#define RED 'R'
#define BLACK 'B'

typedef struct Node {
  int key;
  char color;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct RedBlackTree {
  struct Node *root;
  struct Node *T_nil;

} RedBlackTree;

Node *rotate_for_left(Node *x) {
  Node *y = x->right;
  x->right = y->left;
  y->left = x;

  return y;
}

Node *rotate_for_right(Node *x) {
  Node *y = x->left;
  x->left = y->right;
  y->right = x;

  return y;
}
Node *RB_insert(RedBlackTree *T, Node *root, Node *x) {
  if (root == T->T_nil) {
    return x;
  }

  // 4-node?
  if (root->left->color == RED && root->right->color == RED) {
    root->color = RED;
    root->left->color = BLACK;
    root->right->color = BLACK;
  }

  if (x->key < root->key) {
    root->left = RB_insert(T, root->left, x);
  } else
    root->right = RB_insert(T, root->right, x);

  if (root->left->color == RED) {

    if (root->left->right->color == RED) {
      root->left = rotate_for_left(root->left);
    }

    if (root->left->left->color == RED) {
      root->color = RED;
      root->left->color = BLACK;
      root = rotate_for_right(root);
    }
  }

  else if (root->right->color == RED) {
    if (root->right->left->color == RED) {
      root->right = rotate_for_right(root->right);
    }

    if (root->right->right->color == RED) {
      root->color = RED;
      root->right->color = BLACK;
      root = rotate_for_left(root);
    }
  }

  return root;
}
Node *RB_insert_wrapper(RedBlackTree *T, Node *x) {
  T->root = RB_insert(T, T->root, x);
  T->root->color = BLACK;

  return T->root;
}
void inorder_traversal(RedBlackTree *T, Node *root) {
  if (root != T->T_nil) {
    inorder_traversal(T, root->left);
    printf("%d ", root->key);
    inorder_traversal(T, root->right);
  }
}
int heigth(RedBlackTree *T, Node *root) {
  if (root == T->T_nil || (root->left == T->T_nil && root->right == T->T_nil)) {
    return 0;
  }

  int hl = 1 + heigth(T, root->left);
  int hr = 1 + heigth(T, root->right);

  return (hl < hr) ? hr : hl;
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
    z->color = RED;
    z->right = T->T_nil;
    z->left = T->T_nil;

    T->root = RB_insert_wrapper(T, z);
  }
  inorder_traversal(T, T->root);
  printf("\n%d", heigth(T, T->root));
}
