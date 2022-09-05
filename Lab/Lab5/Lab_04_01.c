#include <stdio.h>
#include <windows.h>

void	gotoxy(int x, int y)
{
	COORD c = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void	draw_ship(void)
{
	printf("<-0->");
}

int		main(void)
{
	int	n;
	n = 0;
	y = 10
	while (n < 20)
	{
		gotoxy(n, y)
		drawship();
		sleep(1);
		n++;
	}
	return (0);
}
