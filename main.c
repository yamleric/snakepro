#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

int main() {
    // 使用当前时间设置随机种子
    srand((unsigned)time(NULL));
    
    Snake* head = NULL;
    int dir, food_x, food_y, score = 0, grow = 0;
    
    init_game(&head, &dir);
    draw_border();
    generate_food(&food_x, &food_y, head);
    
    // 游戏主循环
    while (1) {
        // 检查键盘输入并更新方向6666
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                case 'w': if (dir != 2) dir = 0; break; // 上
                case 'd': if (dir != 3) dir = 1; break; // 右
                case 's': if (dir != 0) dir = 2; break; // 下
                case 'a': if (dir != 1) dir = 3; break; // 左
                default: break;
            }
        }
        
        // 判断是否吃到食物
        if (head->x == food_x && head->y == food_y) {
            score += 10;
            grow = 1; // 蛇体增长的标记
            generate_food(&food_x, &food_y, head);
        } else {
            grow = 0;
        }
        
        move_snake(&head, dir, grow);
        
        // 检测是否发生碰撞
        if (check_collision(head))
            break;
        
        Sleep(200); // 控制游戏刷新速度（200 毫秒一次）
    }
    
    // 游戏结束显示消息和得分
    gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
    printf("Game Over! Score: %d", score);
    
    free_snake(head);
    return 0;
}