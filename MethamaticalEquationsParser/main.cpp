#include <QCoreApplication>
#include <iostream>

#include "Globals.h"
#include "parser.h"

extern const int N;

using namespace std;

//From http://mindhalls.ru/symb-expr/.

int main() {


    tokens texpr, pexpr;
    Variables expvars;
    Massives expmasvars;
    string expr = "log(x)";
    CreateTokensFromExpression(expr, texpr);
    CreatePostfixFromTokens(texpr, pexpr);

    const int n=100;
    double x[n]{0.0};
    for(int i=0; i<n; ++i) x[i]=0.0+i * 100.0/(n-1);
    for(int i=0; i<n; ++i)
    {
        expvars["x"]=x[i];
        cout << "Result:" << endl;
        cout << ResultExpr(pexpr, expvars, expmasvars) << endl;
    }

    return 0;
}
