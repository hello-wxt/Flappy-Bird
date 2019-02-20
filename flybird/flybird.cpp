#include <graphics.h>
#include <conio.h>
#include <iostream>

// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

IMAGE img_bk, img_bd1, img_bd2, img_bar_up1, img_bar_up2, img_bar_down1, img_bar_down2,img_be; 
int bird_x;
int bird_y;
int bar_x_wide = 180;
int barup_y_wide = -300;
int bardown_y_wide =400;
int score;
char s1[] = "Author: 吴小同";
char s2[] = "Score:";
char s3[2];
//char s4[] = "GAME OVER";
TCHAR s[] = _T("GAME OVER");
int flag = 0;
void startup()
{
	initgraph(480, 360);
	loadimage(&img_be, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\begine.jpg");
	putimage(0, 0, &img_be);	// 显示背景
	Sleep(800);

	loadimage(&img_bk,"C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\background.jpg");
	loadimage(&img_bk,"C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\background.jpg");
	loadimage(&img_bd1, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\bird1.jpg");
	loadimage(&img_bd2, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\bird2.jpg");

	loadimage(&img_bar_up1, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\bar_up1.gif");
	loadimage(&img_bar_up2, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\bar_up2.gif");
	loadimage(&img_bar_down1, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\bar_down1.gif");
	loadimage(&img_bar_down2, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\bar_down2.gif");
	bird_x = 50;
	bird_y = 200;
	BeginBatchDraw();

	mciSendString("open res\\background.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
	initgraph(350, 600);
}

void show()
{ 

	putimage(0, 0, &img_bk);	// 显示背景	
	putimage(bar_x_wide, barup_y_wide, &img_bar_up1, NOTSRCERASE); // 显示上一半的障碍物
	putimage(bar_x_wide, barup_y_wide, &img_bar_up2, SRCINVERT);
	putimage(bar_x_wide, bardown_y_wide, &img_bar_down1, NOTSRCERASE); // 显示下一半的障碍物
	putimage(bar_x_wide, bardown_y_wide, &img_bar_down2, SRCINVERT);
	putimage(bird_x, bird_y, &img_bd1, NOTSRCERASE); // 显示小鸟	
	putimage(bird_x, bird_y, &img_bd2, SRCINVERT);
	outtextxy(10, 20, s1);
	outtextxy(10, 40, s2);
	sprintf(s3, "%d", score);
	outtextxy(30, 60, s3);

	
	FlushBatchDraw();
	Sleep(50);
}

void updateWithoutInput()
{	 
	if (bird_y<=600)
		bird_y = bird_y + 5;

	if (bar_x_wide < bird_x&&bird_x < bar_x_wide + 100)
	{
		if (bird_y<(600 + barup_y_wide) || bird_y >(700 + barup_y_wide))
		{
			mciSendString("close jpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open res\\over.mp3 alias jpmusic", NULL, 0, NULL); // 打开跳动音乐
			mciSendString("play jpmusic", NULL, 0, NULL); // 仅播放一次;
			Sleep(20);
			while (1)
			{
				outtextxy(30, 300, s);
				settextcolor(RED);
				settextstyle(30, 30, _T("黑体"));
				FlushBatchDraw();
				Sleep(50);
			}
		}

	}
	if (bird_x == bar_x_wide)
	{
		if ((600 + barup_y_wide) < bird_y && bird_y < (700 + barup_y_wide))
		{   
			
			score = score + 1;
			mciSendString("close jpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open res\\score.mp3 alias jpmusic", NULL, 0, NULL); // 打开跳动音乐
			mciSendString("play jpmusic", NULL, 0, NULL); // 仅播放一次
			Sleep(10);
			
			
		}	  
		else
		{ 
		//mciSendString("close res\\background.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
		mciSendString("close jpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open res\\over.mp3 alias jpmusic", NULL, 0, NULL); // 打开跳动音乐
		mciSendString("play jpmusic", NULL, 0, NULL); // 仅播放一次;
		Sleep(20);
	

		while (1)
		{
		outtextxy(30, 300, s);
		settextcolor(RED);
		settextstyle(30, 30,_T("黑体"));  
		FlushBatchDraw();
		Sleep(50);
		}
		
		}
	 
	} 

	bar_x_wide = bar_x_wide -2 ;

	if ((bar_x_wide+120) == 0)
	{
		bar_x_wide = 180;
		int a = ((rand() / 3000) - 5) * 50;

			bardown_y_wide = bardown_y_wide+a;
			if (bardown_y_wide<100 || bardown_y_wide>600)
				bardown_y_wide = 400;

			barup_y_wide = barup_y_wide + a;

			if (barup_y_wide<-600 || barup_y_wide>-100)
				barup_y_wide = -300;
	}

	 Sleep(2);
	
}

void updateWithInput()
{
	char input;
	if (kbhit())  // 判断是否有输入
	{
		input = getch();
		if (input == ' ' && bird_y>10)
		{
			bird_y = bird_y - 50;
			mciSendString("close jpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open res\\Jump.mp3 alias jpmusic", NULL, 0, NULL); // 打开跳动音乐
			mciSendString("play jpmusic", NULL, 0, NULL); // 仅播放一次
		}
	}
}

void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

int main()
{
	startup();  // 数据初始化	
	//if (MouseHit())
	//{
	//MOUSEMSG msg = GetMouseMsg();
    //msg.uMsg == WM_LBUTTONDOWN
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	gameover();     // 游戏结束、后续处理
	return 0;
}
