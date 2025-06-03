#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int WIDTH = 20;
const int HEIGHT = 20;
const int NUM_POOPS = 5;
const int MAX_HP = 3;

int playerX;
int hp = MAX_HP;
int score = 0;
bool gameOver = false;

struct Poop {
    int x, y;
};

vector<Poop> poops;

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = { 100, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// UI 출력
void drawUI() {
    cout << "HP: ";
    for (int i = 0; i < hp; i = i + 1) cout << "♥ ";
    for (int i = hp; i < MAX_HP; i = i + 1) cout << "♡ ";
    cout << "   Score: " << score << "\n";
}

// 게임 그리기
void draw() {
    system("cls");
    drawUI();
    for (int y = 0; y < HEIGHT; y = y + 1) {
        for (int x = 0; x < WIDTH; x = x + 1) {
            bool printed = false;

            for (int j = 0; j < (int)poops.size(); j = j + 1) {
                if (poops[j].x == x && poops[j].y == y) {
                    cout << "●";
                    printed = true;
                    break;
                }
            }

            if (!printed) {
                if (y == HEIGHT - 1 && x == playerX)
                    cout << "▲";
                else
                    cout << " ";
            }
        }
        cout << "\n";
    }
}

// 키 입력 처리
void input(bool& leftPressed, bool& rightPressed) {
    if (_kbhit()) {
        char key = _getch();
        if (key == -32) {
            key = _getch();
            if (key == 75) leftPressed = true;
            else if (key == 77) rightPressed = true;
        } else if (key == 27) {
            gameOver = true;
        }
    }

    if (GetAsyncKeyState(VK_LEFT) >= 0) leftPressed = false;
    if (GetAsyncKeyState(VK_RIGHT) >= 0) rightPressed = false;
}

// 게임 로직
void logic() {
    for (int i = 0; i < (int)poops.size(); i = i + 1) {
        poops[i].y = poops[i].y + 1;

        if (poops[i].y >= HEIGHT - 1) {
            if (poops[i].x == playerX) {
                hp = hp - 1;
                if (hp <= 0) {
                    gameOver = true;
                    return;
                }
            } else {
                score = score + 10;
            }

            // 똥 초기화
            poops[i].y = 0;
            poops[i].x = rand() % WIDTH;
        }
    }
}

// 메뉴 화면 출력 및 입력 처리
bool showMenu() {
    int selected = 0;
    const int MENU_SIZE = 2;
    string menuItems[MENU_SIZE] = { "게임 시작", "종료" };

    while (true) {
        system("cls");
        cout << "==============================\n";
        cout << "       똥 피하기 게임\n";
        cout << "==============================\n\n";

        for (int i = 0; i < MENU_SIZE; i = i + 1) {
            if (i == selected)
                cout << " > " << menuItems[i] << "\n";
            else
                cout << "   " << menuItems[i] << "\n";
        }

        cout << "\n(방향키 ↑↓로 선택, Enter로 결정, ESC로 종료)\n";

        if (_kbhit()) {
            char key = _getch();
            if (key == -32) {
                key = _getch();
                if (key == 72) { // 위 방향키
                    selected = (selected - 1 + MENU_SIZE) % MENU_SIZE;
                } else if (key == 80) { // 아래 방향키
                    selected = (selected + 1) % MENU_SIZE;
                }
            } else if (key == 13) { // Enter
                if (selected == 0) {
                    return true; // 게임 시작
                } else {
                    return false; // 종료
                }
            } else if (key == 27) { // ESC
                return false;
            }
        }
        Sleep(100);
    }
}

int main() {
    srand((unsigned)time(0));
    hideCursor();

    while (true) {
        bool startGame = showMenu();
        if (!startGame) break;

        // 게임 초기화
        hp = MAX_HP;
        score = 0;
        playerX = WIDTH / 2;
        poops.clear();
        for (int i = 0; i < NUM_POOPS; i = i + 1) {
            poops.push_back({ rand() % WIDTH, rand() % (HEIGHT / 2) });
        }
        gameOver = false;

        auto startTime = steady_clock::now();

        // 게임 루프
        bool leftPressed = false, rightPressed = false;
        while (!gameOver) {
            draw();
            input(leftPressed, rightPressed);

            if (leftPressed && playerX > 0) playerX = playerX - 1;
            if (rightPressed && playerX < WIDTH - 1) playerX = playerX + 1;

            logic();
            Sleep(100);
        }

        auto endTime = steady_clock::now();
        auto duration = duration_cast<seconds>(endTime - startTime).count();
        int minutes = duration / 60;
        int seconds = duration % 60;

        system("cls");
        cout << "\n\n\t게임 오버!\n";
        cout << "\t점수: " << score << "\n";
        cout << "\t경과 시간: " << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << "\n";
        cout << "\t당신은 똥을 3번 맞았습니다!\n\n";
        cout << "\t아무 키나 눌러 메뉴로 돌아갑니다...\n";
        _getch();
    }

    system("cls");
    cout << "게임을 종료합니다. 감사합니다!\n";
    return 0;
}
