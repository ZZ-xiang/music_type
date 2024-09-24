#ifndef __LCD_H__
#define __LCD_H__
extern int lcdfd;
extern int* ld;
int initlcd();
void uninitlcd();
/*
*/
void DrawPoint(int x,int y,int color);
/**/
void ClearPoint(int color);

void lcd_draw_word(int x0,int y0,char ch[], int len, int w, int color);

void myexit();

void login();

void my_exit_huace();

//void my_music_play();
#endif
