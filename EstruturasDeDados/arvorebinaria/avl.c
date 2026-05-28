#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef struct Node {
  int h;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
  int key;
} Node;

typedef struct AVL {
  Node *root;
} AVL;

Node *newNode(int x) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->key = x;
  node->h = 0;

  return node;
}

AVL *newAVL() {
  AVL *T = (AVL *)malloc(sizeof(AVL));
  T->root = NULL;

  return T;
}

int getHeight(Node *x) {
  if (x == NULL) {
    return -1;
  }

  int height_l = (x->left != NULL) ? x->left->h : -1;
  int height_r = (x->right != NULL) ? x->right->h : -1;
  return 1 + MAX(height_l, height_r);
}
void rotate_for_right(AVL *T, Node *x) {
  Node *y = x->left;
  x->left = y->right;

  if (y->right != NULL) {
    y->right->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == NULL) {
    T->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else
    x->parent->right = y;

  y->right = x;
  x->parent = y;

  x->h = getHeight(x);
  y->h = getHeight(y);
}
void rotate_for_left(AVL *T, Node *x) {
  Node *y = x->right;
  x->right = y->left;

  if (y->left != NULL) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == NULL) {
    T->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else
    x->parent->left = y;

  y->left = x;
  x->parent = y;

  x->h = getHeight(x);
  y->h = getHeight(y);
}

Node *balance(AVL *T, Node *x) {

  int factor_x = getHeight(x->left) - getHeight(x->right);

  if (factor_x >= -1 && factor_x <= 1) {
    x->h = getHeight(x);
    return x;
  } else if (factor_x == 2) {
    int factor_left = getHeight(x->left->left) - getHeight(x->left->right);

    if (factor_left < 0) {
      rotate_for_left(T, x->left);
    }

    rotate_for_right(T, x);

    x = x->parent;
  } else {
    int factor_right = getHeight(x->right->left) - getHeight(x->right->right);
    // printf("%d ", x->key);
    if (factor_right > 0) {
      rotate_for_right(T, x->right);
    }

    rotate_for_left(T, x);
    x = x->parent;
  }

  return x;
}
Node *insert(AVL *T, Node *root, int x) {
  if (root == NULL) {
    return newNode(x);
  } else if (x < root->key) {
    root->left = insert(T, root->left, x);

    if (root->left->parent == NULL) {
      root->left->parent = root;
    }
  } else if (x > root->key) {
    root->right = insert(T, root->right, x);

    if (root->right->parent == NULL) {
      root->right->parent = root;
    }
  }

  return balance(T, root);
}

void transplate(AVL *T, Node *u, Node *v) {
  if (u->parent == NULL) {
    T->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  if (v != NULL) {
    v->parent = u->parent;
  }
}
Node *minimo(Node *root) {
  Node *y = root;

  while (y->left != NULL) {
    y = y->left;
  }

  return y;
}
Node *maximo(Node *root) {
  Node *y = root;

  while (y->right != NULL) {
    y = y->right;
  }

  return y;
}
Node *remover(AVL *T, Node *x) {
  Node *y = NULL;
  Node *node_to_balance = NULL;

  if (x->left == NULL) {
    node_to_balance = x->parent;
    transplate(T, x, x->right);
  } else if (x->right == NULL) {
    node_to_balance = x->parent;
    transplate(T, x, x->left);
  } else {
    y = minimo(x->right);

    if (y != x->right) {
      node_to_balance = y->parent;
      transplate(T, y, y->right);
      y->right = x->right;
      y->right->parent = y;
    } else {
      node_to_balance = y;
    }

    transplate(T, x, y);
    y->left = x->left; // y receive left subtree of x
    y->left->parent = y;
  }

  free(x);
  Node *z = node_to_balance;
  while (z != NULL) {
    balance(T, z);
    z = z->parent;
  }

  return y;
}

Node *search(Node *root, int x) {
  if (root == NULL || root->key == x) {
    return root;
  }
  if (x < root->key) {
    return search(root->left, x);
  } else
    return search(root->right, x);
}
void inorder_traversal(Node *root) {
  if (root != NULL) {
    inorder_traversal(root->left);
    printf("%d ", root->key);
    inorder_traversal(root->right);
  }
}
int height(Node *root) { return root->h; }
int main() {
  AVL *T = newAVL();

  int A[] = {1, 2, 3, 4, 5, 6};

  for (int i = 0; i < 6; i++) {
    T->root = insert(T, T->root, A[i]);
  }
  Node *x = search(T->root, 4);
  remover(T, x);
  // inorder_traversal(T->root);
}
