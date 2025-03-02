#include "snake.h"

// 设置控制台光标位置
void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 绘制游戏边界
void draw_border() {
    // 上下边界
    for (int i = 0; i <= WIDTH + 1; i++) {
        gotoxy(i, 0);           printf("#");
        gotoxy(i, HEIGHT + 1);  printf("#");
    }
    // 左右边界
    for (int i = 0; i <= HEIGHT + 1; i++) {
        gotoxy(0, i);           printf("#");
        gotoxy(WIDTH + 1, i);   printf("#");
    }
}

// 初始化蛇的位置（居中）以及起始方向（向右）
void init_game(Snake** head, int* dir) {
    *head = (Snake*)malloc(sizeof(Snake));
    (*head)->x = WIDTH / 2;
    (*head)->y = HEIGHT / 2;
    (*head)->next = NULL;
    *dir = 1; // 初始方向为右（0: 上, 1: 右, 2: 下, 3: 左）
}

// 移动蛇；grow 参数控制是否增长（吃到食物时不删除尾节点）
void move_snake(Snake** head, int dir, int grow) {
    // 新创建蛇头
    Snake* new_head = (Snake*)malloc(sizeof(Snake));
    new_head->x = (*head)->x;
    new_head->y = (*head)->y;
    
    switch (dir) {
        case 0: new_head->y--; break; // 上
        case 1: new_head->x++; break; // 右
        case 2: new_head->y++; break; // 下
        case 3: new_head->x--; break; // 左
        default: break;
    }
    
    new_head->next = *head;
    *head = new_head;
    
    // 显示新的蛇头
    gotoxy(new_head->x, new_head->y);
    printf("O");
    
    // 如果没有吃到食物，则移除尾节点
    if (!grow) {
        Snake* temp = *head;
        // 通过遍历找到倒数第二个节点
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        gotoxy(temp->next->x, temp->next->y);
        printf(" "); // 擦除尾部显示痕迹
        free(temp->next);
        temp->next = NULL;
    }
}

// 遍历蛇身，检查 (x, y) 坐标是否存在
int find_snake(Snake* head, int x, int y) {
    Snake* temp = head;
    while (temp) {
        if (temp->x == x && temp->y == y) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// 生成食物，确保食物位置不在蛇身上
void generate_food(int* food_x, int* food_y, Snake* head) {
    do {
        *food_x = rand() % WIDTH + 1;
        *food_y = rand() % HEIGHT + 1;
    } while (find_snake(head, *food_x, *food_y));
    gotoxy(*food_x, *food_y);
    printf("*");
}

// 碰撞检测：检查蛇头是否撞墙或者撞到自身
int check_collision(Snake* head) {
    // 撞墙检测：边界坐标为 0 和 WIDTH+1, HEIGHT+1
    if (head->x <= 0 || head->x >= WIDTH + 1 ||
        head->y <= 0 || head->y >= HEIGHT + 1) {
        return 1;
    }
    // 撞自身检测
    Snake* temp = head->next;
    while (temp) {
        if (head->x == temp->x && head->y == temp->y) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// 释放所有分配的蛇节点内存
void free_snake(Snake* head) {
    while (head) {
        Snake* temp = head;
        head = head->next;
        free(temp);
    }
}