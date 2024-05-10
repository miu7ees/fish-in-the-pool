#include "game.h"

int main()
{
    fflush(stdin);
    int n = 0, num = 0, m = 0;
    int win = 0, win2 = 0,time1=0;
    int flagg = 1;//记状态
    char str[ROW][COL_] = { 0 }; // 鱼塘大小

    // 鱼塘初始全为海浪
    pool(str);

    int hookplaceX = 8;
    int hookplaceY = 0;

    int* fishplaceX = NULL;
    int* fishplaceY = NULL;
    int* baitplaceX = NULL;
    int* baitplaceY = NULL;

    printf("这是一个鱼塘，您想要的鱼的数量为：\n");
    scanf_s("%d", &n);
    while (n >= 8) {
        printf("请重新输入，超出鱼塘限制8：\n");
        scanf_s("%d", &n);
    }
    printf("这是一个鱼塘，您想要的鱼饵的数量为：\n");
    scanf_s("%d", &m);
    printf("您设定捕鱼的时间为(单位：s)：\n");
    scanf_s("%d", &time1);

    fishplaceX = (int*)malloc(n * sizeof(int)); // 初始的横坐标的数组
    fishplaceY = (int*)malloc(n * sizeof(int)); // 初始的纵坐标的数组
    baitplaceX = (int*)malloc(m * sizeof(int)); // 初始鱼饵的纵坐标的数组
    baitplaceY = (int*)malloc(m * sizeof(int)); // 初始鱼饵的纵坐标的数组

    srand((unsigned int)time(NULL)); // 随机生成🐟的坐标
    int random_number = 0;           // 位置基
    int repetition[9] = { 0 };
    for (int k = 0; k < n; k++)
    {
        random_number = rand() % 32;
        fishplaceY[k] = random_number; // 列位置
        while (1)
        {
            int s = 0;
            random_number = rand() % 8;
            for (int j = 0; j < k; j++)
            {
                if (repetition[j] == random_number + 1)
                    s = 1;
            }
            if (s == 0)
                break;
        }
        repetition[k] = random_number + 1;
        fishplaceX[k] = random_number;
    }

    fish(n, str, fishplaceX, fishplaceY);

    for (int k = 0; k < m; k++)
    { // 随机生成鱼饵的坐标
        baitplaceX[k] = 0;
        baitplaceY[k] = rand() % 32;
        while (str[baitplaceX[k]][baitplaceY[k]] != '~')
        {
            baitplaceY[k] += 3;
            baitplaceY[k] %= 32;
        }
    }

    bait(m, str, fishplaceX, fishplaceY, baitplaceX, baitplaceY, &win);

    hookplaceY = rand() % 32;
    while (str[hookplaceX - 1][hookplaceY] != '~')
    {
        hookplaceY += 3;
        hookplaceY %= 32;
    }

    while (flagg)
    {
        system("cls");

        // 在随机位置放入🐟
        fish(n, str, fishplaceX, fishplaceY);

        bait(m, str, fishplaceX, fishplaceY, baitplaceX, baitplaceY, &win);


        hook(str, fishplaceX, fishplaceY, &hookplaceX, &hookplaceY, &win2, n);

        // 后更新鱼塘，现在是有鱼的鱼塘
        printpool(str, ROW, COL, win, win2,num);
        if (win2 == n) { 
            system("cls");
            printf("You win!  spend%.2fs", num * 0.5);
            flagg = 0;
        }
        if (num * 0.5 >= time1) {
            system("cls");
            printf("  Time is over^ ^\n  you have released %d fish",n-win2);
            flagg = 0;

        }
        num++; // 🐟往前游的次数    //小鱼游动  鱼饵也动

        Sleep(600);
        fflush(stdin);
    }
}
