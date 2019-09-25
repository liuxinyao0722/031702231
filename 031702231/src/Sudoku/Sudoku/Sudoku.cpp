// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"pch.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
using namespace std;
int finish, m, n, i, j;
int sudu[9][9];
FILE* fpin;
FILE* fpout;
void memset() { //初始化数独数组
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++) {
			sudu[i][j] = 0;
		}
}
void output()//输出
{
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			fprintf(fpout, "%d", sudu[i][j]);//打印到输出文件
			if (j < m - 1)//非行末都要加空格 
			{
				fprintf(fpout, " ");
			}
		}
		fprintf(fpout, "\n");//每行结束换行 
	}
}
bool gong(int x, int row, int column, int w)//判断宫 
{
	int a, b;
	a = x / m; b = x % m;
	a = a / row * row;//行
	b = b / column * column;//列
	for (int i = a; i < a + row; i++)
	{
		for (int j = b; j < b + column; j++)
		{
			if (sudu[i][j] == w)
			{
				return 0;
			}
		}
	}
	return 1;
}

bool hanglie(int x, int w)//验证行与列,宫格为4 6 8 9的时候需要判断宫 
{
	int row = x / m;
	int column = x % m;
	for (int i = 0; i < m; i++)//行 
	{
		if (sudu[row][i] == w)
		{
			return 0;
		}
	}
	for (int i = 0; i < m; i++)//列 
	{
		if (sudu[i][column] == w)
		{
			return 0;
		}
	}
	if (m == 4)//4*4
	{
		if (gong(x, 2, 2, w)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (m == 6)//6*6
	{
		if (gong(x, 2, 3, w)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (m == 8)//8*8
	{
		if (gong(x, 4, 2, w)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (m == 9)//9*9
	{
		if (gong(x, 3, 3, w)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 1;
}

void DFS(int x)//回溯遍历 
{
	int row, column;//定义行和列 
	if (finish)//若已完成 直接返回 
	{
		return;
	}
	if (x == m * m)//已经找完 输出返回 
	{
		output();
		finish = 1;
		return;
	}
	row = x / m;//行
	column = x % m;//列
	if (!sudu[row][column])//位置为空则填入数字 
	{
		for (int i = 1; i <= m; i++)
		{
			if (hanglie(x, i))
			{
				sudu[row][column] = i;
				DFS(x + 1);
				sudu[row][column] = 0;//回溯 
			}
		}
	}
	else//有数字则跳过 
	{
		DFS(x + 1);
	}
}

int main(int argc, char *argv[])
{
	m = atoi(argv[2]);//宫格数 
	n = atoi(argv[4]);//盘数 
	char *inname = argv[6];//输入文件名 
	char *outname = argv[8];//输出文件名 
	fpin = fopen(inname, "r");//打开输入文件
	if (fpin == NULL) {
		return -1;
	}
	fpout = fopen(outname, "w");//打开输出文件
	if (fpout == NULL) {
		return -1;
	}
	fclose(fpout);//关闭输出文件 
	while (n--)//当盘数非0循环 
	{
		finish = 0;
		memset();//初始化 置零  
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				fscanf(fpin, "%d", &sudu[i][j]);
			}//文件读入  
		}
		fpout = fopen(outname, "a");//打开输出文件
		DFS(0); //填入数字 
		if (n > 0)//盘数非0时，打印到输出文件 
		{
			fprintf(fpout, "\n");
		}
		fclose(fpout);//关闭输出文件
	}
	fclose(fpin);//关闭输入文件
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
