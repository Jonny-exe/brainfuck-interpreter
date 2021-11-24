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
  int nest = 0;
  while ((c = fgetc(fp)) != EOF) {
    int com = CHARS[(int)c];

    if (com == -1) continue;
    if (com == 0) {
      printf("%c character is not defined in bf.", c);
      //TODO: dealoc
      break;
    } else if (com == 1) {
      // Previous byte
      ptr--;
    } else if (com == 2) {
      // Next byte
      ptr++;
    } else if (com == 3) {
      // Print byte
      printf("%c", *ptr);
    } else if (com == 6) {
      // Decrement byte
      (*ptr)--;
    } else if (com == 7) {
      // Increment byte
      (*ptr)++;
    }


  }
  printf("\n");
  return 0;
}

