#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define WIDTH 640
#define HEIGHT 480
#define SNAKE_LEN 100

typedef struct {
    int x, y;
} Point;

Point snake[SNAKE_LEN];
int snakeLength = 1;
int foodX, foodY;
int direction = 'R'; // 默认向右

void drawSnake() {
    for (int i = 0; i < snakeLength; i++) {
        rectangle(snake[i].x, snake[i].y, snake[i].x + 10, snake[i].y + 10);
    }
}

void drawFood() {
    setfillstyle(SOLID_FILL, RED);
    floodfill(foodX + 5, foodY + 5, WHITE);
}

void generateFood() {
    foodX = (rand() % (WIDTH / 10)) * 10;
    foodY = (rand() % (HEIGHT / 10)) * 10;
}

void updateSnake() {
    for (int i = snakeLength; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case 'U': snake[0].y -= 10; break;
        case 'D': snake[0].y += 10; break;
        case 'L': snake[0].x -= 10; break;
        case 'R': snake[0].x += 10; break;
    }
}

int checkCollision() {
    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1; // 碰撞
        }
    }
    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
        return 1; // 碰撞边界
    }
    return 0; // 无碰撞
}

int main() {
    initwindow(WIDTH, HEIGHT);
    srand(time(0));

    snake[0].x = 100;
    snake[0].y = 100;

    generateFood();

    while (1) {
        if (kbhit()) {
            switch (getch()) {
                case 'w': direction = 'U'; break;
                case 's': direction = 'D'; break;
                case 'a': direction = 'L'; break;
                case 'd': direction = 'R'; break;
                case 'q': closegraph(); return 0; // 退出
            }
        }

        updateSnake();

        if (snake[0].x == foodX && snake[0].y == foodY) {
            if (snakeLength < SNAKE_LEN) {
                snakeLength++;
            }
            generateFood();
        }

        if (checkCollision()) {
            break; // 游戏结束
        }

        cleardevice();
        drawFood();
        drawSnake();
        delay(100);
    }

    closegraph();
    return 0;
}
