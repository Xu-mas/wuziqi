#include "game.h"
#include "framebuffer.h"
#include <stdio.h>

#define RED   0xFFFF94BC
#define GREEN 0x0000FF00
#define BLUE  0x000000FF
#define BLACK 0x00000000
#define WHITE 0x00FFFBFD
#define YELLOW 0x00FFFF00
#define PINKISH 0xFFFFF0F7
#define PINK 0xFFFF94BC
#define RUBY 0xFFFF9FB3

//棋盘横向起始位置的偏移量
#define BROAD_X_START 150
//棋盘纵向起始位置的偏移量
#define BROAD_Y_START 80

//棋盘横向位置个数
#define BROAD_X_CNT 20
//棋盘纵向位置个数
#define BROAD_Y_CNT 20
//棋盘单个格子的宽度
#define BROAD_W_ONE 25

#define WHITE_CHESS 1
#define BLACK_CHESS -1

//当前光标所在的位置
int posx_g = BROAD_X_START;
int posy_g = BROAD_Y_START;

int win_flag = 0;

int chess_g[BROAD_Y_CNT][BROAD_X_CNT] = {0};

void show_chess_broad()
{
	draw_clear(PINKISH);
	
	for (int i = 0; i < BROAD_Y_CNT; ++i)
	{
		draw_h_line(BROAD_X_START, BROAD_Y_START+i*BROAD_W_ONE, (BROAD_X_CNT-1)*BROAD_W_ONE,PINK);
	}
	
	for (int i = 0; i < BROAD_X_CNT; ++i)
	{
		draw_s_line(BROAD_X_START+i*BROAD_W_ONE, BROAD_Y_START, (BROAD_Y_CNT-1)*BROAD_W_ONE, PINK);
	}
	
    draw_full_rect(posx_g-5, posy_g-5, 10, 10, RED);
	
	for (int i = 0; i < BROAD_Y_CNT; ++i)
	{
		for (int j = 0; j < BROAD_X_CNT; ++j)
		{
			if (WHITE_CHESS == chess_g[i][j])
			{
				draw_circle(j*BROAD_W_ONE+BROAD_X_START, i*BROAD_W_ONE + BROAD_Y_START,10, WHITE);
			}
			else if (BLACK_CHESS == chess_g[i][j])
			{
				draw_circle(j*BROAD_W_ONE+BROAD_X_START, i*BROAD_W_ONE + BROAD_Y_START,10, RUBY);
			}
		}
	}
	
}

void begin_game()
{
	char choose = 0;
    int flag = 0;

	while (1)
	{
		choose = getchar();
		if ('w' == choose)
		{
			if (posy_g > BROAD_Y_START)
			{
				posy_g -= BROAD_W_ONE;
			}
		}
		else if ('a' == choose)
		{
            if(posx_g > BROAD_X_START)
            {
                posx_g -= BROAD_W_ONE;
		    }
        }
		else if ('s' == choose)
		{
			if (posy_g < BROAD_Y_START + (BROAD_Y_CNT-1)*BROAD_W_ONE)
			{
				posy_g += BROAD_W_ONE;
			}
		}
		else if ('d' == choose)
		{//draw_circle(posx_g, posy_g, 10, WHITE);	
		    if(posx_g < BROAD_X_START + (BROAD_X_CNT-1)*BROAD_W_ONE)
            {
                posx_g += BROAD_W_ONE;
            }
		}
		else if (' ' == choose)
		{
            if(chess_g[(posy_g-BROAD_Y_START)/BROAD_W_ONE][(posx_g-BROAD_X_START)/BROAD_W_ONE] != 0)
            {
                continue;
            }
            if(flag == 0)
            {
			    chess_g[(posy_g-BROAD_Y_START)/BROAD_W_ONE][(posx_g-BROAD_X_START)/BROAD_W_ONE] = -1; // -1
                flag = -1;
            }
			else if(flag == -1)
            {
                chess_g[(posy_g-BROAD_Y_START)/BROAD_W_ONE][(posx_g-BROAD_X_START)/BROAD_W_ONE] = 1; // -1
		        flag = 0;
            }
        }

		show_chess_broad();
        if(judge_succes()==1)
        {
            if(win_flag==1)
            {
                draw_bmp(245,200,"white.bmp");
            }
            else if(win_flag==-1)
            {
                draw_bmp(245,200,"black.bmp");
            }
            break;
        }
	}
}
int judge_succes()
{
    for(int i = 0;i<BROAD_Y_CNT;++i)
    {
        for(int j = 0;j<BROAD_X_CNT;++j)
        {
            int cur = chess_g[i][j];
            if(cur==0)
            {
                continue;
            }
            int count = 1;
            for(int k = 1;k <=4; ++k)
            {
                if(j+k<BROAD_X_CNT && cur == chess_g[i][j+k])
                {
                    ++count;
                }
                else
                {
                    break;
                }
            }
            if(count>=5)
            {
                if(cur==1)
                {
                    win_flag=1;
                }
                else if(cur==-1)
                {
                    win_flag=-1;
                }
                return 1;
            }
            count = 1;
            for(int k = 1;k <= 4;++k)
            {
                if(i+k<BROAD_Y_CNT && cur == chess_g[i+k][j])
                {
                    ++count;
                }
                else
                {
                    break;
                }
            }
            if(count>=5)
            {
                if(cur==1)
                {
                    win_flag=1;
                }
                else if(cur==-1)
                {
                    win_flag=-1;
                }
                return 1;
            }
            count = 1;
            for(int k = 1;k<=4;++k)
            {
                if(i+k<BROAD_Y_CNT && j+k<BROAD_X_CNT && cur==chess_g[i+k][j+k])
                {
                    ++count;
                }
                else
                {
                    break;
                }
            }
            if(count>=5)
            {
                if(cur==1)
                {
                    win_flag=1;
                }
                else if(cur==-1)
                {
                    win_flag=-1;
                }
                return 1;
            }
            count = 1;
            for(int k = 1;k<=4;++k)
            {
                if(i-k<BROAD_Y_CNT && j+k<BROAD_X_CNT && cur ==chess_g[i-k][j+k])
                {
                    ++count;
                }
                else
                {
                    break;
                }
            }
            if(count >= 5)
            {
                if(cur==1)
                {
                    win_flag=1;
                }
                else if(cur==-1)
                {
                    win_flag=-1;
                }
                return 1;
            }
        }
    }
    return 0;
}

