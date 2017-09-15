/*************************************************************************
    > File Name: CphoneFile.c
    > Author: Karl
    > Mail: karkei@qq.com 
    > Created Time: 2017年09月11日 星期一 16时14分11秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define LEN sizeof(struct message_manguy)
#define numscando 2

typedef struct message_manguy
{
	char number[11];
	char name[20];
}manguy;

extern int numsguy;
extern manguy *pointer;
extern int lens;

int menu_select();
int openfile(manguy mans[]);
int findman(manguy mans[]);
int writetotext(manguy mans[]);
void welcome();
void display(manguy mans[],int n1,int n2);
void showtable();
void addman(manguy mans[]);
void amendman(manguy mans[]);
void deleteman(manguy mans[],int i);

int menu_select()
{
	char c;
	printf("\n\n");
	printf(" | 1.新建联系人\t4.打开文件 |\n");
	printf(" | 2.查看联系人\t5.保存文件 |\n");
	printf(" | 3.修改信息　\t6.显示记录 |\n");
	printf(" | 0.退出系统   |\n");
	printf("\n\n");
	printf("请选择(0-6): ");
	c=getchar();
	getchar();
	return(c-'0');
}

int findman(manguy mans[])
{
	char str[2];
	int i,num;
	if(numsguy==0)
	{
		printf("没有可以查找的联系人");
		return -1;
	}
	else
	{
		printf("选择查找方式:\n1.姓名\t2.号码\n");
		gets(str);
		if(str[0]=='1')
		{
			printf("请输入姓名: ");
			gets(str);
			for(i=0;i<=numsguy;i++)
				if(strcmp(str, mans[i].name)==0)
				{
					display(mans,i,i);
					break;
				}
				else continue;
		}
		else if(str[0]=='2')
		{
			printf("请输入号码: ");
			gets(str);
			for(i=0;i<numsguy;i++)
			{
				if(strcmp(str, mans[i].number)==0)
				{
					display(mans,i,i);
					break;
				}
				else continue;
			}
		}
		if(i>numsguy)
		{
			printf("没有所查找的信息\n");
			return -1;
		}
		return i;
	}
}

int openfile(manguy mans[])
{
	int i=0,j;
	FILE *fp;
	char filename[20],str[2];
	if(numsguy!=0)
	{
		printf("是否保存已有记录?(y/N): ");
		gets(str);
		if(str[0]=='y'||str[0]=='Y')
			writetotext(mans);
	}
	printf("请输入文件名: ");
	gets(filename);
	numsguy=0;
	if((fp=fopen(filename,"rb+"))==NULL)
	{
		printf("无法打开该文件\n");
		return -1;
	}
	//fscanf(fp, "%d", &numsguy);
	//getc(fp);
	while(i<numsguy)
	{
		fscanf(fp,"%s",mans[i].name);
		fscanf(fp,"%s",mans[i].number);
		i++;
	}
	fclose(fp);
	printf("文件读取成功\n");
	printf("是否显示记录?(y/N)");
	gets(str);
	if(str[0]=='y'||str[0]=='Y')
		display(mans,0,numsguy-1);
	return 0;
}

int writetotext(manguy mans[])
{
	int i=0;
	FILE *fp;
	char filename[20];
	printf("输入文件名称: ");
	gets(filename);
	fp=fopen(filename,"w");
	fprintf(fp,"%d\n",numsguy);
	while(i<numsguy)
	{
		fprintf(fp,"%s\t%s",mans[i].name,mans[i].number);
		i++;
	}
	fclose(fp);
	printf("已成功存储\n");
	display(mans,0,numsguy-1);
	numsguy=0;
	return 0;
}

void welcome()
{
	printf("\t*************************************************************\n"); 
	printf("\t\t\t\t\t**通讯录**\t\t\t\t\t");
	printf("\t*************************************************************\n"); 
}

void showtable()
{
	printf("---------------------------------------------------------------------------------------\n");
	printf("姓名\t号码\n");
	printf("---------------------------------------------------------------------------------------\n");
}

void display(manguy mans[],int n1,int n2)
{
	int i;
	showtable();
	for(i=n1;i<=n2;i++)
		printf("%s\t%s\n",mans[i].name,mans[i].number);
}

void amendman(manguy mans[])
{
	char str[5];
	int i=-1,j;

	if(numsguy==0)
		printf("没有可供修改的记录");
	while(i<0)
	{
		i=findman(mans);
		if(i>=0)
		{
			printf("要删除此联系人吗?(y/N)");
			gets(str);
			if(str[0]=='y'||str[0]=='Y')
			{
				deleteman(mans,i);
			}
			else
			{
				printf("确定修改此联系人的信息?(y/N)");
				gets(str);
				if(str[0]=='y'||str[0]=='Y')
				{
					printf("下面请重新输入联系人信息: \n");
					printf("请输入姓名:");
					gets(mans[i].name);
					printf("请输入号码: ");
					gets(mans[i].number);
				}
			}
			display(mans,0,numsguy-1);
		}
		printf("是否进行其他修改?(y/N)\n");
		gets(str);
		if(str[0]=='y'||str[0]=='Y')
			i=-1;
		else i=1;
	}
}

void deleteman(manguy mans[],int i)
{
	int j;

	while(i>=0)
	{
		for(j=i;j<numsguy;j++)
			mans[j]=mans[j+1];
		numsguy--;
		printf("删除成功\n");
		break;
	}
}

void addman(manguy mans[])
{
	int i=0,j,num;
	char str[5];
	if(numsguy!=0)
	{
		printf("已有记录存在是否覆盖?(y/N)\n");
		gets(str);
		if(str[0]=='y'||str[0]=='Y')
			i=0;
		else i=numsguy;
	}

	printf("请输入增加联系人信息条目数:");
	scanf("%d",&num);
	if(i==0)
		numsguy=num;
	else numsguy+=num;
	if(numsguy>lens)
	{
		lens+=50;
		pointer=(manguy *)realloc(pointer, lens*LEN);
	}
	printf("请输入联系人信息:\n");
	for(;i<numsguy;i++)
	{
		getchar();
		printf("请输入任意字符继续信息输入\n");
		getchar();
		printf("请输入姓名: ");
		gets(pointer[i].name);
		printf("请输入号码: ");
		gets(pointer[i].number);
	}
	display(mans,0,numsguy-1);
	getchar();
}

int numsguy;
int lens;
manguy *pointer;
void main()
{
	int i=1;
	char str[2];
	lens=100;
	pointer=(manguy *)malloc(lens*LEN);
	numsguy=0;
	welcome();
	while(i>0)
	{
		i=menu_select();
		switch(i)
		{
			case 1:addman(pointer);break;
			case 2:findman(pointer);break;
			case 3:amendman(pointer);break;
			case 4:openfile(pointer);break;
			case 5:writetotext(pointer);break;
			case 6:display(pointer,0,numsguy-1);break;
			case 0:
				if(numsguy!=0)
					printf("是否保存当前记录?(y/N)");
				gets(str);
				if(str[0]=='y'||str[0]=='Y')
					writetotext(pointer);
				i=-1;break;
			default:printf("请输入数字0-6:\n");i=1;
		}
	}
	printf("\t\t谢谢使用\n\n");
}
