#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  NAME_ONLY = 0,
  MAJOR_AND_NAME = 1,
  YEAR_AND_NAME = 2,
  YEARS_LEFT_AND_NAME = 3
} Mode;

typedef struct {
  char *first_name;
  char *last_name;
  char *major;
  int year;

} Student;

void print_student(Mode m, Student s) {
  switch (m) {
    case NAME_ONLY:
      printf("%s %s\n", s.first_name, s.last_name);
      break;
    case MAJOR_AND_NAME:
      printf("%s %s %s\n", s.major, s.first_name, s.last_name);
      break;
    case YEAR_AND_NAME:
      printf("%d %s %s\n", s.year, s.first_name, s.last_name);
      break;
    case YEARS_LEFT_AND_NAME:
      printf("%d %s %s\n", (s.year - 2017), s.first_name, s.last_name);
      break;
    default:
      printf("Error\n");
  }
}

int main(int argc, char *argv[]) {
  
  char *filename = argv[1];
  FILE *fp = fopen(filename, "r"); 
  char buffer[256];
  Student students[256];
  

  if (fp == NULL) {
    printf("Could not open %s\n", filename);
    return -1;
  }

  int i = 0;
  while (fgets(buffer, 255, fp) != NULL) {
    Student s;

    size_t length = strlen(buffer);
    size_t length_bytes = (length+1) * sizeof(char);
    s.first_name = malloc(length_bytes);
    s.last_name = malloc(length_bytes);
    s.major = malloc(length_bytes);

    sscanf(buffer, "%s %s %s %d", s.first_name, s.last_name, s.major, &s.year);

    students[i] = s;
    i++;


  }
  fclose(fp);
  
  int index, mode;
  while (1) {
    fscanf(stdin, "%d %d", &index, &mode);
    print_student(mode, students[index]);
  }

  
  
  return 0;
}

