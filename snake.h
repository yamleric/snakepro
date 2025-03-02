#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20   // 游戏区域宽度
#define HEIGHT 20  // 游戏区域高度

// 定义蛇身节点结构体
typedef struct Snake {
    int x;              // x 坐标
    int y;              // y 坐标
    struct Snake* next; // 指向下一个节点的指针
} Snake;

// 函数声明
void gotoxy(int x, int y);                        // 设置光标位置
void draw_border();                               // 绘制游戏边界
void init_game(Snake** head, int* dir);           // 初始化游戏状态（蛇和方向）
void move_snake(Snake** head, int dir, int grow);  // 移动蛇，grow 为 1 时蛇体增长
int find_snake(Snake* head, int x, int y);          // 检查指定坐标是否在蛇身上
void generate_food(int* food_x, int* food_y, Snake* head); // 随机生成食物，并确保不与蛇重合
int check_collision(Snake* head);                 // 碰撞检测（撞墙或撞自身）
void free_snake(Snake* head);                     // 释放蛇身所占用的内存

#endif // SNAKE_H