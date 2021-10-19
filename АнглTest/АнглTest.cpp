#include "Application.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Application test;

    test.run();

    _getch();
    return 0;
}