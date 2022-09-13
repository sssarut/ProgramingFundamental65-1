#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

void    gotoxy(int x, int y)
{
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void    setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpcursor;
    lpcursor.bVisible = visible;
    lpcursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpcursor);
}
void    setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void    draw_bullet(int x, int y)
{
    setcolor(7, 0);
    gotoxy(x, y);
    printf("^");
}

void    erase_bullet(int x, int y)
{
    setcolor(7, 0);
    gotoxy(x, y);
    printf(" ");
}

void    erase_ship(int x, int y)
{
    setcolor(7, 0);
    gotoxy(x, y);
    printf("     ");
}

void    draw_ship(int x, int y)
{
    setcolor(2, 4);
    gotoxy(x, y);
    printf("<-0->");
}

int main(void)
{
    char    ch = ' ';
    int     x = 38, y = 20;
    int     flag = 0;
    int     i = 0, n = 0;
    int     bullet[10] = {999, 999, 999, 999, 999, 999, 999, 999, 999, 999};

    setcursor(0);
    draw_ship(x, y);
    do
    {
        if(i == 5)
            i = 0;
        if(n == 5)
            n = 0;
        while (n < 5)
        {
            if(bullet[(n * 2) + 1] <= 0)
            {
                erase_bullet(bullet[(n * 2)], bullet[(n * 2) + 1]);
                bullet[(n * 2)] = 999;
                bullet[(n * 2) + 1] = 999;
            }
            if(bullet[(n * 2)] != 999 || bullet[(n * 2) + 1] != 999)
            {
                erase_bullet(bullet[(n * 2)], bullet[(n * 2) + 1]);
                draw_bullet(bullet[(n * 2)], --bullet[(n * 2) + 1]);
            }
            n++;
        }
        if(flag == 1)
        {
            erase_ship(x, y);
            draw_ship(--x, y);
        }
        if(flag == 2)
        {
            erase_ship(x, y);
            draw_ship(++x, y);
        }
        if(x >= 80 || x <= 0 || y >= 80 || y <= 0)
        {
            flag = 0;
        }
        if(_kbhit())
        {
            ch = _getch();
            /*if(ch == 'a' && x != 0)
            {
                erase_ship(x, y);
                draw_ship(--x, y);
            }
            if(ch == 's' && y != 80)
            {
                erase_ship(x, y);
                draw_ship(x, ++y);
            }
            if(ch == 'w' && y != 0)
            {
                erase_ship(x, y);
                draw_ship(x, --y);
            }
            if(ch == 'd' && x != 80)
            {
                erase_ship(x, y);
                draw_ship(++x, y);
            }*/
            if(ch == 's' || x >= 80 || x <= 0 || y >= 80 || y <= 0)
            {
                flag = 0;
            }
            if(ch == 'a' && flag == 0)
            {
                flag = 1;
            }
            /*if(flag == 1)
            {
                erase_ship(x, y);
                draw_ship(--x, y);
            }*/
            if(ch == 'd' && flag == 0)
            {
                flag = 2;
            }
            /*if(flag == 2)
            {
                erase_ship(x, y);
                draw_ship(++x, y);
            }*/
            if(ch == ' ' && bullet[(i * 2)] == 999 && bullet[(i * 2) + 1] == 999)
            {
                bullet[(i * 2)] = x + 2;
                bullet[(i * 2) + 1] = y - 1;
                i++;
            }
            fflush(stdin);
        }
        Sleep(100);
    }
    while (ch != 'x');
    setcolor(7, 0);
    setcursor(1);
    return (0);
}