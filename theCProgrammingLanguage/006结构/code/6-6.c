// 以本节介绍的函数为基础
// 编写一个适合C语言程序使用的#define处理器的简单版本（即无参数情况）
// 你会发现getch和ungetch函数非常有用

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct nlist {              // table entry
    struct nlist *next;     // next entry in the chain
    char *name;             // defined name
    char *defn;             // replacement text
};

void error(int, char *);
int getch(void);
void getdef(void);
int getword(char *, int);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
void skipblanks(void);
void undef(char *);
void ungetch(int);
void ungets(char *s);

// simple version of #define peocessor
int main(int argc, char const *argv[]) {
    char w[MAXWORD];
    struct nlist *p;

    while (getword(w, MAXWORD) != EOF) {
        if (strcmp(w, "#") == 0) {      // beginning of direct
            getdef();
        } else if (!isalpha(w[0])) {    
            printf("%s", w);            // cannot be defined
        } else if ((p = lookup(w)) == NULL) {
            printf("%s", w);            // not defined
        } else {
            ungets(p->defn);            // push definition
        }
    }
    return 0;
}

// get definition and install it
void getdef(void) {
    int c, i;
    char def[MAXWORD], dir[MAXWORD], name[MAXWORD];

    skipblanks();
    if (!isalpha(getword(dir, MAXWORD))) {
        error(dir[0], "getdef: expecting a directive after #");
    } else if (strcmp(dir, "define") == 0) {
        skipblanks();
        if (!isalpha(getword(name, MAXWORD))) {
            error(name[0], "getdef: non-alpha - name expexted");
        } else {
            skiplanks();
            for (i = 0; i < MAXWORD - 1; i++) {
                if ((def[i] = getch()) == EOF || def[i] == '\n') {
                    break;      // end of definition
                }
            }
            def[i] = '\0';
            if (i <= 0) {
                error('\n', "getdef: incomplete define");  // install definition
            } else {
                install(name, def);
            }
        }
    } else if (strcmp(dir, "undef") == 0) {
        skipblanks();
        if(!isalpha(getword(name, MAXWORD))) {
            error(name[0], "getdef: non-alpha in undef");
        } else {
            undef(name);
        }
    } else {
        error(dir[0], "getdef: expecting a direcice after #");
    }
}

// error: print error message and skip the rest of the line
void error(int c, char *s) {
    printf("error: %s\n", s);
    while (c != EOF && c != '\n') {
        c = getch();
    }
}

// skip blank and tab characters
void skipblanks(void) {
    int c;
    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }
    ungetch(c);
}





/*
    
*/