#pragma warning (disable:4996)
#if _MSC_VER>=1900
#include <stdio.h>
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE* __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif

#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
int main()
{
	bool testmode = false;
returnpage:
	char command[100] = { '\0' };
	printf("Welcome to JFCA Defender by code004!\n\nPlease Input Command:\nexit = stop this program\nstart = start defending\nsetpwd = set password\nsetgu = set luogu auto lock\n\nWarning: Please set password and luogu auto lock before you choose to start defending!\n\n>");
	scanf("%s", command);
	if (strcmp(command, _T("exit")) == 0)
	{
		return 0;
	}
	else if (strcmp(command, _T("setpwd")) == 0)
	{
		char messageput1[1000] = { '\0' };
		char oldpass[100] = { '\0' };
		FILE *passwd = NULL;
		if (fopen("passwd.jfca", "r") == NULL)
		{
			goto skipcheck;
		}
		passwd = fopen("passwd.jfca", "r");
		fscanf(passwd, "%s", oldpass);
		fclose(passwd);
		sprintf(messageput1, "Old Password:%s\nDo you want to change it?", oldpass);
		int messagereply = MessageBox(NULL, messageput1, _T("JFCA Defender"), MB_YESNO | MB_ICONINFORMATION);
		if (messagereply == IDNO)
		{
			goto returnpage;
		}
	skipcheck:
		char newpass[100] = { '\0' };
		printf("\nEnter New Password:");
		scanf("%s", newpass);
		passwd = fopen("passwd.jfca", "w+");
		fprintf(passwd, "%s", newpass);
		char messageput2[1000] = { '\0' };
		sprintf(messageput2, "Changed successfully!\nCurrent password:%s\nPlease restart JFCA-Defender as soon as possible!\n\n", newpass);
		MessageBox(NULL, messageput2, _T("JFCA Defender"), MB_OK | MB_ICONINFORMATION);
		goto returnpage;
	}
	else if (strcmp(command, _T("setgu")) == 0)
	{
		int luoguid = 0;
		printf("\nEnter your luogu ID:");
		scanf("%d", &luoguid);
		FILE *lgid = NULL;
		lgid = fopen("luoguid.jfca", "w+");
		fprintf(lgid, "%d", luoguid);
		fclose(lgid);
	}
	else if (strcmp(command, _T("start")) != 0)
	{
		printf("\nERROR: Such command doesn't exist.\n\n");
		goto returnpage;
	}
	int answer2 = MessageBox(NULL, _T("温馨提示：\n请您在更换密码后进行一次测试，以防程序BUG导致电脑无法开机！\n如果您现在希望进行测试，请点击“是”，否则请点击“否”"), _T("JFCA Defender"), MB_YESNO | MB_ICONWARNING);
	if (answer2 == IDYES)
	{
		system("cls");
		printf("\n\n温馨提示：\n此程序可以实现的效果：在鼠标移动后（即机惨者开始行动时）30秒重启，程序禁止关闭，禁止最小化，占满整个屏幕，杀掉explorer\n在测试模式中，程序将不会开启30秒重启，也不会杀掉explorer\n如果您认为密码系统等设置有问题，请通过explorer将程序关闭后再次设置，谢谢。");
		printf("\nStarting test mode in 5000ms...");
		testmode = true;
		Sleep(5000);
	}
	int tx, ty, countdown = 3000;
	POINT p;
	IMAGE img1;
	loadimage(&img1, _T("AD.png"));
	if (!testmode)
	{
		system("taskkill /f /im explorer.exe");
	}
	initgraph(2000, 1000, NOCLOSE | NOMINIMIZE);
	HWND hwnd = GetHWnd();
	MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
	settextstyle(40, 0, _T("楷体"));
	SetCursorPos(683, 384);
	int luoguid2 = 0;
	FILE *lgid = NULL;
	if (fopen("luoguid.jfca", "r") == NULL)
	{
		MessageBox(NULL, "错误：您还没有设置咕咕ID！！！如果您没有咕咕ID，请将其设置为0", "JFCA Defender", MB_OK | MB_ICONERROR);
		return 0;
	}
	lgid = fopen("luoguid.jfca", "r");
	fscanf(lgid, "%d", &luoguid2);
	fclose(lgid);
	char gulockorder[1000] = { '\0' };
	sprintf(gulockorder,"explorer \"https://www.luogu.org/api/auth/lock?uid=%d \"",luoguid2);
	system(gulockorder);
	outtextxy(300, 300, "您好！一旦您移动鼠标，防机惨系统就会启动");
	GetCursorPos(&p);//获取鼠标坐标
	tx = p.x;
	ty = p.y;
	while (1)
	{
		GetCursorPos(&p);//获取鼠标坐标
		if (p.x == tx && p.y == ty)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	clearrectangle(0, 0, 2000, 2000);
	settextstyle(25, 0, _T("楷体"));
	MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
	outtextxy(300, 300, "您好！您的系统将在30秒内重启，而且重启后还会自动打开此程序！");
	if (!testmode)
	{
		system("shutdown -r -t 30 -c \"This computer will restart without the correct password.\"");
	}
	MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);

	MOUSEMSG m;
	settextstyle(20, 0, _T("楷体"));
	rectangle(600, 500, 650, 530);
	outtextxy(605, 505, _T("Next"));
	while (true)
	{
		MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
		m = GetMouseMsg();
		if (m.x >= 600 && m.x <= 650 && m.y >= 500 && m.y <= 530)
		{
			settextstyle(25, 0, _T("Consolas"));
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
			else
			{
				settextstyle(22, 0, _T("楷体"));
				outtextxy(603, 503, _T("Next"));
			}
		}
		else
		{
			settextstyle(20, 0, _T("楷体"));
			outtextxy(605, 505, _T("Next"));
		}
	}

	settextstyle(25, 0, _T("楷体"));
	outtextxy(300, 300, "热烈欢迎您登录本电脑！温馨提示：只有知道密码的人才能登录哦！");
	MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);

	MOUSEMSG m1;
	settextstyle(20, 0, _T("楷体"));
	rectangle(600, 500, 650, 530);
	outtextxy(605, 505, _T("Next"));
	while (true)
	{
		MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
		m1 = GetMouseMsg();
		if (m1.x >= 600 && m1.x <= 650 && m1.y >= 500 && m1.y <= 530)
		{
			settextstyle(25, 0, _T("Consolas"));
			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
			else
			{
				settextstyle(22, 0, _T("楷体"));
				outtextxy(603, 503, _T("Next"));
			}
		}
		else
		{
			settextstyle(20, 0, _T("楷体"));
			outtextxy(605, 505, _T("Next"));
		}
	}

	settextstyle(25, 0, _T("楷体"));
	outtextxy(300, 300, "请输入您的密码以确认身份，确认后即可继续。（密码不带回显）");
	char correctpass[100] = { '\0' };
	FILE *copasswd = NULL;
	if (fopen("passwd.jfca", "r") == NULL)
	{
		MessageBox(NULL, "错误：您还没有设置密码！！！", "JFCA Defender", MB_OK | MB_ICONERROR);
		return 0;
	}
	copasswd = fopen("passwd.jfca", "r");
	//fscanf(copasswd, "%s", correctpass);
	fgets(correctpass, 100, copasswd);
	fclose(copasswd);
pass:
	char password[100000] = { '\0' };
	MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
	gets_s(password);
	if (strcmp(password, correctpass) != 0)
	{
		MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
		memset(password, '\0', sizeof(password));
		putimage(0, 0, &img1);
		outtextxy(300, 300, "Sorry, the password you entered was wrong. Please try again!");
		goto pass;
	}
	/*
	MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
	char password[100] = { '\0' };
	gets_s(password, 10);
	int wrongtime = 0;
	while (strcmp(password, correctpass) != 0)
	{
		wrongtime++;
		MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
		memset(password, '\0', sizeof(password));
		putimage(0, 0, &img1);
		MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
		char outtext123[1000] = { '\0' };
		sprintf(outtext123, "Warning : Password has been wrong for %d time(s), please retry!",wrongtime);
		outtextxy(300, 300, outtext123);
		scanf("%s", password);
	}
	*/
	clearrectangle(0, 0, 2000, 1000);

	settextstyle(25, 0, _T("楷体"));
	outtextxy(300, 300, "请输入手势密码以确认您的身份，确认后即可取消重启。。。。。。");
	MOUSEMSG m2;
	int flag1 = 0, flag2 = 0;

	settextstyle(20, 0, _T("楷体"));
	rectangle(600, 500, 650, 530);
	outtextxy(605, 505, _T("确定"));
	while (true)
	{
		MoveWindow(hwnd, -10, -10, 2000, 1000, TRUE);
		m2 = GetMouseMsg();
		if (m2.x >= 600 && m2.x <= 650 && m2.y >= 500 && m2.y <= 530)
		{
			settextstyle(25, 0, _T("Consolas"));
			if (m2.uMsg == WM_MBUTTONDBLCLK)
			{
				flag1 = 1;
				continue;
			}
			else if (m2.uMsg == WM_LBUTTONDOWN && flag1 == 1)
			{
				flag2 = 1;
				continue;
			}
			else if (m2.uMsg == WM_RBUTTONDOWN && flag2 == 1)
			{
				break;
			}
			else
			{
				settextstyle(22, 0, _T("楷体"));
				outtextxy(603, 503, _T("确定"));
			}
		}
		else
		{
			settextstyle(20, 0, _T("楷体"));
			outtextxy(605, 505, _T("确定"));
		}
	}
	closegraph();
	initgraph(2000, 1000, NOCLOSE | NOMINIMIZE);
	HWND hwnd2 = GetHWnd();
	settextstyle(42, 0, _T("楷体"));
	system("shutdown -a");
	MoveWindow(hwnd2, -10, -10, 2000, 1000, TRUE);
	outtextxy(330, 300, "重启已取消！请稍候，系统准备中···");
	Sleep(1000);
	closegraph();
	return 0;
}