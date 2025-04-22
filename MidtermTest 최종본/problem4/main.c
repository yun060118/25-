#include <Windows.h>
#include <stdio.h>
#include <conio.h>

void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
    char ch = '0';
    int done = 0;
    printf("\033[40;94m              o\033[40;92m         o           \033[0m\n");
    printf("\033[40;97m              |         |           \033[0m\n");
    printf("\033[40;97m   ---------------------------------   \033[0m\n");
    printf("   |\033[45;97m\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\033[0m|\n");
    printf("   |\033[47;30m                               \033[0m|\n");
    printf("\033[40;97m   ---------------------------------   \033[0m\n");
    printf("\033[40;97m----------------------------------------\033[0m\n");
    printf("\033[45;97m|\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\033[0m|\n");
    printf("\033[47;30m|                                      \033[0m|\n");
    printf("\033[40;97m----------------------------------------\033[0m\n");

    while (done == 0) {
        ch = _getch();

        if (ch == 'n' || ch == 'N')
        {
            gotoxy(10, 30);
            printf("케이크 먹고싶다\n");
            done = 1;
        }
        else
        {
            if (ch == 'h' || ch == 'H')
            {
                int i = 0;
                while (i < 5)
                {
                    int j = 0;
                    gotoxy(30, 10 + i);
                    while (j < 22)
                    {
                        printf("\033[47;30m");
                        j = j + 1;
                    }
                    printf("\033[0m");
                    i = i + 1;
                }
                gotoxy(16, 4);
                printf("\033[47;30mHappy\033[0m");

                gotoxy(10, 30);

                done = 1;
            }
            else {
                gotoxy(15, 9);
                printf("\033[31mBirthday\033[0m");

            }
        }
    }
    printf("\n\n\n\n\n\n\n\m");

    return 0;
}