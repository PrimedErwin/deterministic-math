#ifndef _CASES_H
#define _CASES_H

#define nan 0.0 / 0.0
#define inf 1.0 / 0.0

extern struct Case{
    double a;
    double b;
    char op;
} cases[];

extern const int CASES_COUNT;

#endif