#include <stdio.h>

int main() {
  char v[50];
  fgets(v, sizeof(v), stdin);

  while (!(v[0] == 'F' && v[1] == 'I' && v[2] == 'M')) {
    int end = 0;
    for (int i = 0; v[i] != '\0'; i++) {
      end++;
    }
    end = end - 2;
    int temp;

    for (int i = 0; i < end + 1; i++, end--) {
      temp = v[i];
      v[i] = v[end];
      v[end] = temp;
    }

    printf("%s", v);
    fgets(v, sizeof(v), stdin);
  }
}
