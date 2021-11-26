#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1; 
  }

  char *filename = argv[1];
  printf("filename: %s\n", filename);

  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error with file");
    return 0;
  }

  int CHARS[127];

  for (int i = 0; i < 127; i++) CHARS[i] = 0;
  // <>.[]-+,
  // 60, 62, 46, 91, 93, 45, 43, 44
  // ACTIONS = 

  CHARS[60] = 1;
  CHARS[62] = 2;

  CHARS[46] = 3;
  CHARS[91] = 4;
  CHARS[93] = 5;
  CHARS[45] = 6;
  CHARS[43] = 7;
  CHARS[44] = 8;

  // New line
  CHARS[10] = -1;
  char c;

  int memc = 10;
  unsigned char *mem = malloc(memc);
  unsigned char *ptr = mem;

  struct Stack {
    int idx;
    int *stack;
    int size;
  };

  struct Stack stack;
  stack.idx = 0;
  stack.size = 5;
  stack.stack = malloc(sizeof(int) * stack.size);
  stack.stack[stack.idx] = 1;


  while ((c = fgetc(fp)) != EOF) {
    int com = CHARS[(int)c];
    if (stack.stack[stack.idx] == 0 && (com != 4 && com != 5)) continue;
    if (com == -1) continue;
    if (com == 0) {
      printf("\"%c\" character is not defined in bf.", c);
      break;
    } else if (com == 1) {
      // Previous byte
      if (ptr-1 < mem) {
        printf("Gone to far back in memory");
        break;
      }
      ptr--;
    } else if (com == 2) {
      // Next byte
      ptr++;
      if (ptr >= mem) {
        int pos = ptr - mem;
        mem = (unsigned char*)realloc(mem, memc+10);
        ptr = mem + pos;
      }
    } else if (com == 3) {
      // Print byte
      printf("%c", *ptr);
    } else if (com == 4) {
      // If open
      stack.idx++;
      if (stack.size <= stack.idx) {
        stack.size += 5;
        stack.stack = (int *)realloc(stack.stack, stack.size);
      }
      stack.stack[stack.idx] = (*ptr != 0);
    } else if (com == 5) {
      // If close
      stack.idx--;
    } else if (com == 6) {
      // Decrement byte
      (*ptr)--;
    } else if (com == 7) {
      // Increment byte
      (*ptr)++;
    } else if (com == 8) {
      // Input a byte
      scanf("%c", ptr);
    }
  }
  free(mem);
  free(stack.stack);
  printf("\n");
  return 0;
}

