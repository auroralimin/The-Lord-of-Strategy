#include <ncurses.h>

int main(void)
{
	int mat[1000][1000], i, j, row = 0, col = 0, size_row, size_col;

	for (i = 0; i < 1000; i++)
		for (j = 0; j < 1000; j++)
			mat[i][j] = (j+i*2)%9;

	initscr();

	getmaxyx(stdscr, size_row, size_col);
	scrollok(stdscr,TRUE);

	while(1)
	{
		erase();
		move(0, 0);
		for (i = row; i < size_row + row; i++)
			for (j = col; j <size_col + col; j++)
				printw("%d", mat[i][j]);
		refresh();
		switch (getch())
		{
			case 'a':
				if (col != 0)
					col--;
				break;
			case 'd':
				if (col != size_col - 1)
					col++;
				break;
			case 'w':
				if (row != 0)
					row--;
				break;
			case 's':
				if (row != size_row - 1)
					row++;
				break;
			case 'k':
				endwin();
				return 0;
		}
	}

	endwin();
	return 0;
}
