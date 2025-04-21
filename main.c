#include <Windows.h>
#include <stdio.h>
#include <conio.h>

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    char ch = '0';
    int done = 0;
    printf("                       ,-,\n");
    printf("                     ,' /\n");
    printf("                   ,'  (          _          _\n");
    printf("           __...--'     `-....__,'(      _,-'/\n");
    printf("  _,---''''                     ````-._,'  ,'\n");
    printf(",'  o                                  `  <\n");
    printf("`.____  )))                          ...'  \\\n");
    printf("   `--..._        .   .__....----''''   `-. \\\n");
    printf("          ```7--i-`.  \\                    `-`\n");
    printf("             `.(    `-.`.\n");
    printf("               `'      `' \n");
    gotoxy(28, 11);
    printf("\033[45;32mrrrrrrr\033[0m");

    while (done == 0) {
        ch = _getch();

        if (ch == 'n' || ch == 'N') {
            gotoxy(10, 30); 
            printf("프로그램이 종료됩니다...\n");
            done = 1;
        }
        else {
            if (ch == 'y' || ch == 'Y') {
                int i = 0;
                while (i < 5) {
                    int j = 0;
                    gotoxy(30, 10 + i);
                    while (j < 22) {
                        printf("\033[44m ");
                        j = j + 1;
                    }
                    printf("\033[0m");
                    i = i + 1;
                }
                gotoxy(32, 12);
                printf("\033[44;33mrrrrrrr!\033[0m");

                gotoxy(10, 30); // 종료 메시지 겹치지 않게 출력
    
                done = 1;
            }
            else {
                gotoxy(30, 17);
                printf("\033[31mrrrrrrrrrrr!!!\033[0m");
              
            }
        }
    }
    printf("\n\n\n\n\n\n\n\m");

    return 0;
}