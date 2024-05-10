#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>


#define ROW 8   // 8行
#define COL_ 38 // 扩大鱼塘，实现鱼尾巴出去，头再出来的游动效果
#define COL 32  // 32列


void pool(char str[ROW][COL_])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL_; j++)
        {
            str[i][j] = '~';
        }
    }
}

void fish(int n, char str[ROW][COL_], int X[], int Y[])
{
    // char fishbody[] = {'>', '<', '!', '!', '>', '^', '>', '0'}; //  ><(('>
    char fishbody[] = { '>', '<', '(', '(', '\'', '>' };

    for (int j = 0; j < n; j++)
    {
        if (X[j] == -1)
            continue;

        str[X[j]][Y[j] % 38] = '~';
        Y[j]++;
        for (int i = 0; i < 6; i++)
            str[X[j]][(Y[j] + i) % 38] = fishbody[i];
    }
}

int bait(int m, char str[ROW][COL_], int fishplaceX[], int fishplaceY[], int baitx[], int baity[], int* win)
{
    // char fishbody[] = {'>', '<', '!', '!', '>', '^', '>', '0'};
    char fishbody[] = { '>', '<', '(', '(', '\'', '>' }; //  ><(('>
    for (int i = 0; i < m; i++)
    {
        if (baitx[i] == -1)
            continue;

        str[baitx[i]][baity[i]] = '~';
        baitx[i]++;
        baity[i]--;
        if (baitx[i] == 8)
            baitx[i] = 0;
        if (baity[i] == -1)
            baity[i] = 31;
        for (int j = 0; j < 6; j++)
        {
            if (str[baitx[i]][baity[i]] == fishbody[j])
            {
                (*win)++;
                baitx[i] = -1;
                baity[i] = -1;
            }
        }
        if (str[baitx[i]][baity[i] - 1] == '>')
        {
            (*win)++;
            baitx[i] = -1;
            baity[i] = -1;
            str[baitx[i]][baity[i]] = '>';
        }
        str[baitx[i]][baity[i]] = '*';
    }
    fflush(stdin);
}

int hook(char str[ROW][COL_], int fishplaceX[ROW], int fishplaceY[COL], int* hookplaceX, int* hookplaceY, int* win2, int n)
{
    char fishbody[] = { '>', '<', '(', '(', '\'', '>' }; //  ><(('>
    char w = 0;
    
        if (_kbhit()) {
            w = _getch();
        /*    char take = _getch();*/
            if (w == 'a') {
                str[(*hookplaceX)][(*hookplaceY)] = '~';
                (*hookplaceY)--;
            }

            if (w == 'd') {
                str[(*hookplaceX)][(*hookplaceY)] = '~';
                (*hookplaceY)++;
            }
        }
    
    if (str[(*hookplaceX)][(*hookplaceY)] == 'J')
    {
        str[(*hookplaceX)][(*hookplaceY)] = '~';
    }

    static int flag_ = 0;

    // 若想要让鱼钩一直自下往上就解除注释，同时注释下面那段
    //  (*hookplaceX)--;
    //  if ((*hookplaceX) == 0)
    //      (*hookplaceX) = 7;

    // 上下循环
    if (flag_ == 0)
    {
        (*hookplaceX)--;
        if ((*hookplaceX) == 0)
        {
            flag_ = 1;
        }
    }
    else if (flag_ == 1)
    {
        (*hookplaceX)++;
        if ((*hookplaceX) == 7)
        {
            flag_ = 0;
        }
    }

    if (str[(*hookplaceX)][(*hookplaceY)] != '~' && str[(*hookplaceX)][(*hookplaceY)] != '*')
    {
        for (int i = 0; i < n; i++)
        {
            if ((*hookplaceX) == fishplaceX[i])
            {
                fishplaceX[i] = -1;
                break;
            }
        }
        (*win2)++;
        int flag = 0;
        int forward = (*hookplaceY) + 1;
        int backward = (*hookplaceY) - 1;
        if (str[(*hookplaceX)][(*hookplaceY)] == '>') // 鱼嘴或鱼尾
        {
            flag++;
        }
        while (flag < 2)
        {

            if (str[(*hookplaceX)][forward] != '~' && str[(*hookplaceX)][forward] != '*')
            {
                str[(*hookplaceX)][forward] = '~';
                forward++;
                if (str[(*hookplaceX)][forward] == '~' || str[(*hookplaceX)][forward] == '*')
                    flag++;
            }
            if (str[(*hookplaceX)][backward] != '~' && str[(*hookplaceX)][backward] != '*' && backward != -1)
            {
                str[(*hookplaceX)][backward] = '~';
                backward--;
                if (backward == -1)
                    flag++;
                if (backward != -1 && (str[(*hookplaceX)][backward] == '~' || str[(*hookplaceX)][backward] == '*'))
                    flag++;
            }
        }
    }
    str[(*hookplaceX)][(*hookplaceY)] = 'J';
}

void printpool(char str[ROW][COL_], int row, int col, int win, int win2,int num)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%c", str[i][j]);
        }
        printf("\n");
    }
    printf("\t\t\t小鱼吃鱼饵次数：%d", win);
    printf("\n\t\t\t钓到鱼的次数次数：%d", win2);
    printf("\n\t\t\t耗费时间：%.2fs", num*0.5);

}
