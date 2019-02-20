#include <graphics.h>
#include <conio.h>
#include <iostream>

// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

IMAGE img_bk, img_bd1, img_bd2, img_bar_up1, img_bar_up2, img_bar_down1, img_bar_down2,img_be; 
int bird_x;
int bird_y;
int bar_x_wide = 180;
int barup_y_wide = -300;
int bardown_y_wide =400;
int score;
char s1[] = "Author: ��Сͬ";
char s2[] = "Score:";
char s3[2];
//char s4[] = "GAME OVER";
TCHAR s[] = _T("GAME OVER");
int flag = 0;
void startup()
{
	initgraph(480, 360);
	loadimage(&img_be, "C:\\Users\\Administrator\\Downloads\\flybird\\flybird\\res\\begine.jpg");
	putimage(0, 0, &img_be);	// ��ʾ����
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

	mciSendString("open res\\background.mp3 alias bkmusic", NULL, 0, NULL);//�򿪱�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // ѭ������
	initgraph(350, 600);
}

void show()
{ 

	putimage(0, 0, &img_bk);	// ��ʾ����	
	putimage(bar_x_wide, barup_y_wide, &img_bar_up1, NOTSRCERASE); // ��ʾ��һ����ϰ���
	putimage(bar_x_wide, barup_y_wide, &img_bar_up2, SRCINVERT);
	putimage(bar_x_wide, bardown_y_wide, &img_bar_down1, NOTSRCERASE); // ��ʾ��һ����ϰ���
	putimage(bar_x_wide, bardown_y_wide, &img_bar_down2, SRCINVERT);
	putimage(bird_x, bird_y, &img_bd1, NOTSRCERASE); // ��ʾС��	
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
			mciSendString("close jpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open res\\over.mp3 alias jpmusic", NULL, 0, NULL); // ����������
			mciSendString("play jpmusic", NULL, 0, NULL); // ������һ��;
			Sleep(20);
			while (1)
			{
				outtextxy(30, 300, s);
				settextcolor(RED);
				settextstyle(30, 30, _T("����"));
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
			mciSendString("close jpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open res\\score.mp3 alias jpmusic", NULL, 0, NULL); // ����������
			mciSendString("play jpmusic", NULL, 0, NULL); // ������һ��
			Sleep(10);
			
			
		}	  
		else
		{ 
		//mciSendString("close res\\background.mp3 alias bkmusic", NULL, 0, NULL);//�򿪱�������
		mciSendString("close jpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString("open res\\over.mp3 alias jpmusic", NULL, 0, NULL); // ����������
		mciSendString("play jpmusic", NULL, 0, NULL); // ������һ��;
		Sleep(20);
	

		while (1)
		{
		outtextxy(30, 300, s);
		settextcolor(RED);
		settextstyle(30, 30,_T("����"));  
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
	if (kbhit())  // �ж��Ƿ�������
	{
		input = getch();
		if (input == ' ' && bird_y>10)
		{
			bird_y = bird_y - 50;
			mciSendString("close jpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open res\\Jump.mp3 alias jpmusic", NULL, 0, NULL); // ����������
			mciSendString("play jpmusic", NULL, 0, NULL); // ������һ��
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
	startup();  // ���ݳ�ʼ��	
	//if (MouseHit())
	//{
	//MOUSEMSG msg = GetMouseMsg();
    //msg.uMsg == WM_LBUTTONDOWN
	while (1)  //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();     // ���û������йصĸ���
	}
	gameover();     // ��Ϸ��������������
	return 0;
}
