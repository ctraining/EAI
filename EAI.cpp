// EAI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define NULL 0
#define LEN sizeof(struct employee )

//定义一个结构题
struct employee
{	
	int employee_id;
	int department_id;
	char employee_name[20];
	int age;
	char sex[4];
	//char employee_birthday[20];
	//char employee_phone[12];
	//char employee_email[15];
	//char employee_address[20];
	//char address[30];
	//char ZhuanYe[20];
	struct employee  *next;
};

int TOTAL_NUM = 0;							//员工总数
struct employee  *head = NULL;

void welcome();								//欢迎界面
void mainmenu();							//主界面
void record();								//记录数据
void insert(struct employee  *p_employee);			//插入数据
void display(struct employee  *p_employee);			//显示一个员工的信息
void displayAll();							//显示所有员工的信息
void query_by_num();						//按工号查询员工信息
void readData();							//读取文件里员工的信息
void writeData();							//向文件写入员工信息
void freeAll();								//清空链表内容
void del();									//删除员工信息
void change();								//更改员工信息
void devise(struct employee  *p);				//选择更改内容

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
		printf("\t\t\t+        [1]----录入员工信息                |\n");
		printf("\t\t\t+        [2]----浏览员工信息                |\n");
		printf("\t\t\t+        [3]----查询员工信息                |\n");
		printf("\t\t\t+        [4]----删除员工信息                |\n");
		printf("\t\t\t+        [5]----修改员工信息                |\n");
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

//录入员工信息
void record()
{
	struct employee *p0;

	p0 = (struct employee *)malloc(LEN);
	printf("请输入员工的姓名:");
	scanf("%s", p0->employee_name);
	printf("请输入员工的工号:");
	scanf("%ld", &p0->employee_id);
	printf("请输入员工的性别:");
	scanf("%s", p0->sex);
	printf("请输入员工的年龄:");
	scanf("%d", &p0->age);
	//printf("请输入员工的地址:");
	//scanf("%s", p0->address);
	//printf("请输入员工的电话:");
	//scanf("%lf", &p0->tele_num);
	//printf("请输入员工的专业:");
	//scanf("%s", p0->ZhuanYe);

	insert(p0);
	printf("该员工的信息为:\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("姓名\t工号\t性别\t年龄\n");
	display(p0);
}

//插入数据
void insert(struct employee *p_employee)
{
	struct employee *p0, *p1, *p2;

	p1 = head;
	p0 = p_employee;

	if (head == NULL)
	{
		head = p0;
		p0->next = NULL;
	}
	else
	{
		while ((p0->employee_id > p1->employee_id) && (p1->next != NULL))
		{
			p2 = p1;
			p1 = p1->next;
		}
		if (p0->employee_id <= p1->employee_id)
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

void display(struct employee *p)
{
	printf("%s\t%d\t%d\t%s\n", p->employee_name, p->employee_id, p->age, p->sex);
}

//浏览员工信息
void displayAll()
{
	struct employee *p;

	printf("员工总数:%d\n", TOTAL_NUM);
	p = head;
	if (head != NULL)
	{
		printf("\n姓名\t工号\t\t年龄\t性别\n");
		printf("-------------------------------------------------------------------------------\n");
		do
		{
			display(p);
			p = p->next;
		} while (p != NULL);
	}
	printf("\n");
}

//按工号查询员工信息
void query_by_num()
{
	int num;
	struct employee *p1;

	printf("请输入员工的工号：");
	scanf("%ld", &num);
	if (head == NULL)
	{
		printf("无员工记录！\n");
		return;
	}
	p1 = head;
	while (num != p1->employee_id && p1->next != NULL)
		p1 = p1->next;
	if (num == p1->employee_id)
	{
		printf("姓名\t工号\t\t年龄\t性别\n");
		printf("-------------------------------------------------------------------------------\n");
		display(p1);
	}
	else
		printf("没有该员工记录，请核对！");
}

//写入文件
void writeData()
{
	FILE*  fp;					//文件指针 
	struct employee *p;

	fp = fopen("1.txt", "w");	//打开文件
	if (!fp)
	{
		printf("文件打开错误！");
		return;
	}

	fprintf(fp, "%d\n", TOTAL_NUM);
	for (p = head; p != NULL; p = p->next)
	{
		fprintf(fp, "%s\t%d\t%s\t%d\n", p->employee_name, p->employee_id, p->sex, p->age);
	}
	fclose(fp);
}

void freeAll()					//不晓得这个函数用来做什么
{
	struct employee *p1, *p2;

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
	struct employee *p1, *p2;
	fp = fopen("1.txt", "r");
	if (!fp)
	{
		printf("文件打开错误！");
		return;
	}

	fscanf(fp, "%d\n", &TOTAL_NUM);
	head = p1 = p2 = (struct employee *)malloc(LEN);
	fscanf(fp, "%s\t%ld\t%s\t%d\t%s\t%lf\t%s\n", p1->employee_name, &p1->employee_id, p1->sex, &p1->age);
	while (!feof(fp))
	{
		p1 = (struct employee *)malloc(LEN);
		fscanf(fp, "%s\t%ld\t%s\t%d\t%s\t%lf\t%s\n", p1->employee_name, &p1->employee_id, p1->sex, &p1->age);
		p2->next = p1;
		p2 = p1;
	}
	p2->next = NULL;
	fclose(fp);
}

//删除员工信息
void del()
{
	struct employee *p1, *p2;
	long int num;

	if (head == NULL)
	{
		printf("无员工记录！\n");
		return;
	}

	printf("请输入您要删除的员工的工号：");
	scanf("%ld", &num);
	p1 = head;

	while (num != p1->employee_id && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (num == p1->employee_id)
	{
		if (p1 == head)
			head = p1->next;
		else p2->next = p1->next;
		free(p1);
		TOTAL_NUM--;
	}
	else
		printf("没有该员工记录，请核对！\n");
}

//修改员工信息
void change()
{
	struct employee *p1, *p2;
	long int num;
	if (head == NULL)
	{
		printf("无员工记录！\n");
		return;
	}
	printf("请输入您要修改的员工的工号：");
	scanf("%ld", &num);
	p1 = head;
	while (num != p1->employee_id && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (num == p1->employee_id)
		devise(p1);
	else
		printf("没有该员工记录，请核对！\n");
}

void devise(struct employee *p)
{
	int choice;
	choice = -1;
	do
	{
		printf("请选择您要修改的员工的信息内容：\n");
		printf("+----------------------+\n");
		printf("| 姓名          请按 1 |\n");
		printf("| 工号          请按 2 |\n");
		printf("| 性别          请按 3 |\n");
		printf("| 年龄          请按 4 |\n");
	/*	printf("| 地址          请按 5 |\n");
		printf("| 电话          请按 6 |\n");*/
		//printf("| 爱好  请按 7 |\n");
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
			scanf("%s", p->employee_id);
			break;
		case 2:
			printf("请输入新工号：");
			scanf("%d", &p->employee_name);
			break;
		case 3:
			printf("请输入新性别：");
			scanf("%s", p->sex);
			break;
		case 4:
			printf("请输入新年龄：");
			scanf("%s", &p->age);
			break;
		/*case 5:
			printf("请输入新地址：");
			scanf("%s", p->address);
			break;
		case 6:
			printf("请输入新电话：");
			scanf("%lf", &p->tele_num);
			break;*/
		/*case 7:
			printf("请输入新爱好：");
			scanf("%s", p->aihao);
			break;*/
		default:
			printf("\n无效选项!");
			break;
		}
	} while (choice != 0);
}