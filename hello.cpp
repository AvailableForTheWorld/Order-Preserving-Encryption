#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

int main()
{
    ifstream file("result.txt");

    string line;
    int cnt = 0;
    const char *bspace = " ";

    while (getline(file, line, '\n'))
    {
        char *end, *tmp;
        const char *ch = line.c_str();
        double f = strtod(ch, &end);
        tmp = end;
        printf("%lf\n", f);
        f = strtod(tmp, &end);
        printf("%lf\n", f);
    }

    file.close();
    return 0;
}