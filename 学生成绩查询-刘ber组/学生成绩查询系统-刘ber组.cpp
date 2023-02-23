#include<iostream>
#include<cstring>
using namespace std;
struct STU{
	int id;
	char name[50];
	int score[3];
}student[100];
//3.输入输出
void Input(STU student[], int& n) {
	// 打开文件
	FILE* file = freopen("学生成绩.txt", "r", stdin);
	if (!file) {
		cout << "Failed to open file." <<endl;
		return;
	}
	
	// 从文件中读取学生人数
	cin >> n;
	
	// 读取每个学生的信息
	for (int i = 0; i < n; i++) {
		cin >> student[i].id;
		getchar();
		cin >> student[i].name;
		cin >> student[i].score[0] >> student[i].score[1] >> student[i].score[2];
	}
	
	// 关闭文件
	if(fclose(file))
	{
		cout<<"Failed to close file." <<endl;
	};
	
	// 重新定向标准输入流到终端
	freopen("CON", "r", stdin);
}
void OutputAll(STU student[],int &n)
{
	for(int i=0;i<n;i++)
	{
		cout<<student[i].id<<" "<<student[i].name<<" ";
		cout<<"语文："<<student[i].score[0]<<" ";
		cout<<"数学："<<student[i].score[1]<<" ";
		cout<<"英语："<<student[i].score[2]<<" ";
		cout<<endl;
	}
	cout<<endl;
}
void OutputOne(STU student)
{
	cout<<student.id<<" "<<student.name<<" ";
	cout<<"语文："<<student.score[0]<<" ";
	cout<<"数学："<<student.score[1]<<" ";
	cout<<"英语："<<student.score[2]<<" ";
	cout<<endl;
}

//5.查找学生数据
STU *SearchByID(STU student[],int &n,int id)
{
	for (int i = 0;i < n;i++)
	{
		if (student[i].id == id) return &student[i];
	}
	return NULL;
}
STU *SearchByName(STU student[],int &n,char name[])
{
	for (int i = 0;i < n;i++)
	{
		if (student[i].name[0]==name[0]) 
		{	
			int j=1;
			for(;j<strlen(name);j++)
			{
				if(student[i].name[j]!=name[j])break;
			}
			if(j==strlen(name))return &student[i];
		}
	}
	return NULL;
}
STU *SearchByScore(STU student[],int &n,int project,int score)
{
	for (int i = 0;i < n;i++)
	{
		if (student[i].score[project]== score) return &student[i];
	}
	return NULL;
}

//6.插入/删除数据（基于位置）
void InsertByPosition(STU student[],int &n,int position,struct STU NewStu)
{
	for (int i = 99;i >= position;i--)
		student[i + 1] = student[i];
	student[position]=NewStu;
	n++;
}
void RemoveByPosition(STU student[],int &n,int position)
{
	for (int i = position;i<=n;i++)
		student[i] = student[i+1];
	n--;
}
//7.删除特定数据（属性）
void RemoveByName(STU student[],int &n,char name[])
{
	for (int i = 0;i < n;i++)
	{
		if (strcmp(student[i].name,name)==0) 
		{
			for (int j = i;j<=n;j++)
				student[j] = student[j+1];
			n--;
			return;
		}
	}
}
void RemoveByID(STU student[],int &n,int id)
{
	for(int i=0;i<=n;i++)
	{
		if(student[i].id==id)
		{
			for (int j = i;j<=n;j++)
				student[j] = student[j+1];
			n--;
			return;
		}
	}
}
void RemoveByScore(STU student[],int &n,int score,int project)
{
	for (int i = 0;i < n;i++)
	{
		if (student[i].score[project]== score)
		{
			for (int j = i;j<=n;j++)
				student[j] = student[j+1];
			n--;
			return;
		}
	}
}

//8.有序插入
void InsertSeqByID(struct STU Student[],int &n,struct STU NewStu)  //默认 Students[]中已按学号升序排好，插入新学生信息Stu 
{
	int i=0,j; 
	while(i<n&&Student[i].id<NewStu.id) i++; //定位到需要插入的地方
	for(j=n;j>i;j--) Student[j]=Student[j-1];
	Student[j]=NewStu;
	n++;
}
void InsertBySeqSCORE(struct STU Student[],int &n,struct STU NewStu,int t)//默认 Students[]中已按score[t]降序排好，插入新学生信息Stu 
{
	int i=0,j; 
	while(i<n&&Student[i].score[t]>NewStu.score[t]) i++; //定位到需要插入的地方
	for(j=n;j>i;j--) Student[j]=Student[j-1];
	Student[j]=NewStu;
	n++;
}

//9.三种排序方式
//Sort1 单科排序
//Sort2 总分排序
//Sort3 学号排序
void Sort1(STU student[],int &n,int project)
{
	if(project==0)
	{
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(student[j].score[0]<student[j+1].score[0])
				{
					STU temp=student[j];
					student[j]=student[j+1];
					student[j+1]=temp;
				}
			}
		}
	}
	if(project==1)
	{
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(student[j].score[1]<student[j+1].score[1])
				{
					STU temp=student[j];
					student[j]=student[j+1];
					student[j+1]=temp;
				}
			}
		}
	}
	if(project==2)
	{
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(student[j].score[2]<student[j+1].score[2])
				{
					STU temp=student[j];
					student[j]=student[j+1];
					student[j+1]=temp;
				}
			}
		}
	}
}
void Sort2(STU student[],int &n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1-i;j++)
		{
			if(student[j].score[0]+student[j].score[1]+student[j].score[2]<student[j+1].score[0]+student[j+1].score[1]+student[j+1].score[2])
			{
				STU temp=student[j];
				student[j]=student[j+1];
				student[j+1]=temp;
			}
		}
	}
}
void Sort3(STU student[],int &n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1-i;j++)
		{
			if(student[j].id>student[j+1].id)
			{
				STU temp=student[j];
				student[j]=student[j+1];
				student[j+1]=temp;
			}
		}
	}
}

void System(int shuru,int n)
{
	printf("**********欢迎进入学生成绩系统**********\n");
	printf("    *****请选择你想使用的功能*****     \n");
	printf("0. 退出系统\n");
	printf("1. 查询学生成绩\n");
	printf("2. 插入学生成绩\n");
	printf("3. 删除学生成绩\n");
	printf("4. 学生成绩排序\n");
	printf("5. 有序插入学生成绩\n");
	Input(student,n);
	while(shuru!=0)
	{
		scanf("%d",&shuru);
		if(shuru==1)
		{
			int fangshi1;
			printf("请选择查询方式\n");
			printf("1. 学号查询\n");
			printf("2. 姓名查询\n");
			printf("3. 分数查询\n");
			scanf("%d",&fangshi1);
			if(fangshi1==1)
			{
				printf("请输入学号:\n");
				int id;
				scanf("%d",&id);
				STU* p=SearchByID(student,n,id);
				if(p==NULL)printf("查无此人");
				else OutputOne(*p);	
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(fangshi1==2)
			{
				char name1[100];
				printf("请输入姓名:\n");
				scanf("%s",&name1);
				STU* p=SearchByName(student,n,name1);
				if(p==NULL)printf("查无此人");
				else OutputOne(*p);	
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(fangshi1==3)
			{
				int score1,project1;
				printf("请选择查询科目：\n");
				printf("0:语文\n1:数学\n2:英语\n");
				scanf("%d",&project1);
				printf("请输入查询分数：");
				scanf("%d",&score1);
				STU* p=SearchByScore(student,n,project1,score1);
				if(p==NULL)printf("查无此人");
				else OutputOne(*p);	
				printf("    *****请选择你想使用的功能*****     \n");
			}
		}
		if(shuru==2)
		{
			struct STU New3;
			int position;
			printf("请选择插入或删除:\n");
			printf("0:插入\n1:删除\n");
			int panduan;
			scanf("%d",&panduan);
			if(panduan==0)
			{
				printf("请选择插入位置:\n");
				scanf("%d",&position);
				printf("请输入学号，姓名，分数:");
				scanf("%d",&New3.id);
				getchar();
				gets(New3.name);
				scanf("%d%d%d",&New3.score[0],&New3.score[1],&New3.score[2]);
				InsertByPosition(student,n,position,New3);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(panduan==1)
			{
				printf("请选择删除位置:\n");
				scanf("%d",&position);
				RemoveByPosition(student,n,position);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
		}
		if(shuru==3)
		{
			int panduan2;
			printf("请选择删除方式:\n");
			printf("0:学号\n1:姓名\n2:成绩\n");
			scanf("%d",&panduan2);
			if(panduan2==0)
			{
				int id;
				printf("请输入学号:\n");
				scanf("%d",&id);
				RemoveByID(student,n,id);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(panduan2==1)
			{
				char name2[100];
				printf("请输入姓名:\n");
				gets(name2);
				RemoveByName(student,n,name2);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(panduan2==2)
			{
				printf("请选择删除科目:\n");
				printf("0:语文\n1:数学\n2:英语\n");
				int score3,project2;
				scanf("%d",&project2);
				printf("请输入相应匹配分数:");
				scanf("%d",&score3);
				RemoveByScore(student,n,score3,project2);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
		}
		if(shuru==4)
		{
			int fangshi2;
			printf("请选择查询方式\n");
			printf("1. 单科降序排序\n");
			printf("2. 成绩总分排序\n");
			printf("3. 学号排序\n");
			scanf("%d",&fangshi2);
			int project;
			if(fangshi2==1)
			{
				printf("请输入排序科目：\n");
				printf("0:语文\n1:数学\n2:英语\n");
				scanf("%d",&project);
				Sort1(student,n,project);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");		
			}
			if(fangshi2==2)
			{
				Sort2(student,n);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(fangshi2==3)
			{
				Sort3(student,n);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
		}
		if(shuru==5)//默认先进行排序
		{
			struct STU New2;
			int fangshi3;
			printf("请输入插入方式：\n");
			printf("0:学号插入\n1:成绩插入\n");
			scanf("%d",&fangshi3);
			printf("请输入学号，姓名，成绩\n:");
			scanf("%d",&New2.id);
			getchar();
			gets(New2.name);
			scanf("%d%d%d",&New2.score[0],&New2.score[1],&New2.score[2]);
			if(fangshi3==0)
			{
				InsertSeqByID(student,n,New2);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
			if(fangshi3==1)
			{
				int kemu;
				printf("请输入科目：\n");
				printf("0:语文\n1:数学\n2:英语\n");
				scanf("%d",&kemu);
				InsertBySeqSCORE(student,n,New2,kemu);
				OutputAll(student,n);
				printf("    *****请选择你想使用的功能*****     \n");
			}
		}
	}
	return;
}
int main()
{
	int shuru=-1,n=0;
	System(shuru,n);
	return 0;
}

