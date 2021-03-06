
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

int main(int argc, char const *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') { // []与操作数的结合体的优先级比*和++高
        while (c = *++argv[0]) {    // 对指针argv[0]进行可自增运算
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number= 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
        if (argc != 1) {
            printf("Usage: find -x -n pattern\n");
        }else{
            while (getline(line, MAXLINE) > 0) {
                lineno++;
                if ((strstr(line, *argv) != NULL) != except) {
                    if (number) {
                        printf("%ld:", lineno);
                    }
                    printf("%s", line);
                    found++;
                }
            }
        }
    }
    return found;
}


int getline(char *s, int lim) {
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - t;
}
