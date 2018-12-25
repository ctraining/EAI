// EAI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define NULL 0
#define LEN sizeof(struct staff )

//定义一个结构题
struct staff
{
	char name[20];
	long int num;
	char sex[4];
	int age;
	char address[30];
	double tele_num;
	struct staff  *next;
};
struct position
{
	int position_id;

	char position_name[8];
	int age;
	char address[30];
	double tele_num;
	//char aihao[20];
	struct staff  *next;
};

int TOTAL_NUM = 0;							//员工总数
struct staff  *head = NULL;

void welcome();								//欢迎界面
void mainmenu();							//主界面
void record();								//记录数据
void insert(struct staff  *stu);			//插入数据
void display(struct staff  *stu);			//显示一个员工的信息
void displayAll();							//显示所有员工的信息
void query_by_num();						//按学号查询员工信息
void readData();							//读取文件里员工的信息
void writeData();							//向文件写入员工信息
void freeAll();								//清空链表内容
void del();									//删除员工信息
void change();								//更改员工信息
void devise(struct staff  *p);				//选择更改内容

int main(void)
{
	welcome();								//显示主菜单
	mainmenu();								//系统主菜单
	//system("pause");
	return 0;
}

//显示欢迎信息
void welcome()
{
	printf("+----------------------------------------------------------------------------+\n");
	printf("|                                                                            |\n");
	printf("|      欢迎使用应用技术学院计算机科学与技术12班企业信息管理系统              |\n");
	printf("|                                                                            |\n");
	printf("+----------------------------------------------------------------------------+\n");
}

//系统主菜单
void mainmenu()
{
	int choice = -1;		//选项
	readData();				//？为什么要读入数据
	printf("\n温馨提示：本企业管理系统会每10分钟自动保存一次数据，请放心使用^_^\n");
	do
	{
		printf("\n\n\n");
		printf("\t\t\t--------------------------------------------\n");
		printf("\t\t\t+    计算机科学与技术12班企业信息管理系统   |\n");
		printf("\t\t\t--------------------------------------------\n");
		printf("\t\t\t+        [1]----录入学生信息                |\n");
		printf("\t\t\t+        [2]----浏览学生信息                |\n");
		printf("\t\t\t+        [3]----查询学生信息                |\n");
		printf("\t\t\t+        [4]----删除学生信息                |\n");
		printf("\t\t\t+        [5]----修改学生信息                |\n");
		printf("\t\t\t+        [0]----退出系统                    |\n");
		printf("\t\t\t+*·*·*·*·*·*·*·*·*·*·*·*·*·*·*|\n");
		printf("\t\t\t--------------------------------------------\n");
		printf("请输入您的选择：");
		scanf("%d", &choice);
		switch (choice)			//选项功能
		{
		case 0:					//退出系统
			writeData();
			freeAll();			//？不晓得用来做什么
			exit(0);
		case 1:					//录入信息
			record();
			break;
		case 2:
			displayAll();		//浏览所有信息
			break;
		case 3:
			query_by_num();		//查询信息-->num
			break;
		case 4:					//删除信息
			del();
			break;
		case 5:					//修改信息
			change();
			break;
		default:
			printf("\n无效选项!");
			break;
		}
	} while (choice != 0);
}

//录入学生信息
void record()
{
	struct staff *p0;

	p0 = (struct staff *)malloc(LEN);
	printf("请输入学生的姓名:");
	scanf("%s", p0->name);
	printf("请输入学生的学号:");
	scanf("%ld", &p0->num);
	printf("请输入学生的性别:");
	scanf("%s", p0->sex);
	printf("请输入学生的年龄:");
	scanf("%d", &p0->age);
	printf("请输入学生的地址:");
	scanf("%s", p0->address);
	printf("请输入学生的电话:");
	scanf("%lf", &p0->tele_num);
	printf("请输入学生的爱好:");
//	scanf("%s", p0->aihao);

	insert(p0);
	printf("该学生的信息为:\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("姓名\t学号\t\t年龄\t性别\t地址\t\t电话\t\t爱好\n");
	display(p0);
}

void insert(struct staff *sta)
{
	struct staff *p0, *p1, *p2;

	p1 = head;
	p0 = sta;

	if (head == NULL)
	{
		head = p0;
		p0->next = NULL;
	}
	else
	{
		while ((p0->num > p1->num) && (p1->next != NULL))
		{
			p2 = p1;
			p1 = p1->next;
		}
		if (p0->num <= p1->num)
		{

			if (head == p1)
				head = p0;
			else
				p2->next = p0;
			p0->next = p1;
		}
		else
		{
			p1->next = p0;
			p0->next = NULL;
		}
	}
	TOTAL_NUM++;
}

void display(struct staff *p)
{
	printf("%s\t%ld\t%d\t%s\t%s\t\t%.0f\t%s\n", p->name, p->num, p->age, p->sex, p->address, p->tele_num, p->aihao);
}

//浏览员工信息
void displayAll()
{
	struct staff *p;

	printf("员工总数:%d\n", TOTAL_NUM);
	p = head;
	if (head != NULL)
	{
		printf("\n姓名\t学号\t\t年龄\t性别\t地址\t\t电话\n");
		printf("-------------------------------------------------------------------------------\n");
		do
		{
			display(p);
			p = p->next;
		} while (p != NULL);
	}
	printf("\n");
}

//按学号查询员工信息
void query_by_num()
{
	int num;
	struct staff *p1;

	printf("请输入员工的工号：");
	scanf("%ld", &num);
	if (head == NULL)
	{
		printf("无学生记录！\n");
		return;
	}
	p1 = head;
	while (num != p1->num && p1->next != NULL)
		p1 = p1->next;
	if (num == p1->num)
	{
		printf("姓名\t学号\t\t年龄\t性别\t地址\t\t电话\t\t爱好\n");
		printf("-------------------------------------------------------------------------------\n");
		display(p1);
	}
	else
		printf("没有该学生记录，请核对！");
}

//写入文件
void writeData()
{
	FILE*  fp;					//文件指针 
	struct staff *p;

	fp = fopen("1.txt", "w");	//打开文件
	if (!fp)
	{
		printf("文件打开错误！");
		return;
	}

	fprintf(fp, "%d\n", TOTAL_NUM);
	for (p = head; p != NULL; p = p->next)
	{
		fprintf(fp, "%s\t%ld\t%s\t%d\t%s\t%.0f\t%s\n", p->name, p->num, p->sex, p->age, p->address, p->tele_num, p->aihao);
	}
	fclose(fp);
}

void freeAll()					//不晓得这个函数用来做什么
{
	struct staff *p1, *p2;

	p1 = p2 = head;
	while (p1)
	{
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
}

//读取文件
void readData()
{
	FILE*  fp;//文件指针 
	struct staff *p1, *p2;
	fp = fopen("1.txt", "r");
	if (!fp)
	{
		printf("文件打开错误！");
		return;
	}

	fscanf(fp, "%d\n", &TOTAL_NUM);
	head = p1 = p2 = (struct staff *)malloc(LEN);
	fscanf(fp, "%s\t%ld\t%s\t%d\t%s\t%lf\t%s\n", p1->name, &p1->num, p1->sex, &p1->age, p1->address, &p1->tele_num, p1->aihao);
	while (!feof(fp))
	{
		p1 = (struct staff *)malloc(LEN);
		fscanf(fp, "%s\t%ld\t%s\t%d\t%s\t%lf\t%s\n", p1->name, &p1->num, p1->sex, &p1->age, p1->address, &p1->tele_num, p1->aihao);
		p2->next = p1;
		p2 = p1;
	}
	p2->next = NULL;
	fclose(fp);
}

//删除学生信息
void del()
{
	struct staff *p1, *p2;
	long int num;

	if (head == NULL)
	{
		printf("无学生记录！\n");
		return;
	}

	printf("请输入您要删除的学生的学号：");
	scanf("%ld", &num);
	p1 = head;

	while (num != p1->num && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (num == p1->num)
	{
		if (p1 == head)
			head = p1->next;
		else p2->next = p1->next;
		free(p1);
		TOTAL_NUM--;
	}
	else
		printf("没有该学生记录，请核对！\n");
}

//修改学生信息
void change()
{
	struct staff *p1, *p2;
	long int num;
	if (head == NULL)
	{
		printf("无学生记录！\n");
		return;
	}
	printf("请输入您要修改的学生的学号：");
	scanf("%ld", &num);
	p1 = head;
	while (num != p1->num && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (num == p1->num)
		devise(p1);
	else
		printf("没有该学生记录，请核对！\n");
}

void devise(struct staff *p)
{
	int choice;
	choice = -1;
	do
	{
		printf("请选择您要修改的学生的信息内容：\n");
		printf("+----------------------+\n");
		printf("| 姓名          请按 1 |\n");
		printf("| 学号          请按 2 |\n");
		printf("| 性别          请按 3 |\n");
		printf("| 年龄  请按 4 |\n");
		printf("| 地址          请按 5 |\n");
		printf("| 电话          请按 6 |\n");
		printf("| 爱好  请按 7 |\n");
		printf("| 取消          请按 0 |\n");
		printf("+----------------------+\n");

		printf("请输入您的选择：");
		scanf("%d", &choice);

		switch (choice)
		{
		case 0:
			return;
		case 1:
			printf("请输入新姓名：");
			scanf("%s", p->name);
			break;
		case 2:
			printf("请输入新学号：");
			scanf("%d", &p->num);
			break;
		case 3:
			printf("请输入新性别：");
			scanf("%s", p->sex);
			break;
		case 4:
			printf("请输入新年龄：");
			scanf("%s", &p->age);
			break;
		case 5:
			printf("请输入新地址：");
			scanf("%s", p->address);
			break;
		case 6:
			printf("请输入新电话：");
			scanf("%lf", &p->tele_num);
			break;
		case 7:
			printf("请输入新爱好：");
			scanf("%s", p->aihao);
			break;
		default:
			printf("\n无效选项!");
			break;
		}
	} while (choice != 0);
}