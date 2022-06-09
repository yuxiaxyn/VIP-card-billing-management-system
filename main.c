#include <stdio.h>                  //编译预处理指令，引入头文件
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 10                      //自定义符号常量
#define MENU_MAIN_COUNT 7 		    //主菜单的选项个数
typedef struct member               //定义结构体类型member，采用链式存储结构 
{              
	char name[MAX];	                 //姓名 
	char id[MAX];                    //卡号 
	char sex[2];		             //性别 
	int age;		             	//年龄 
	float money;	            	 //余额 
	char tel[12]; 	                //电话 
	struct member *next;             //定义一个指针指向下一个会员信息 
	float cost;		            	//消费金额 
}mem;                                //定义结构体变量mem
                                        /*声明函数*/
void menu();                          /*声明函数，声明菜单函数*/		
void save(mem *p);                     //声明保存函数
 
mem *head=NULL;	                         //头指针为NULL 
mem* get_last(mem *p)                   //取得链表最后一个元素的节点指针并返回该指针
{	                                     
		if(p->next == NULL)
		{
			return p;
		}
		else
		{
			get_last(p->next);
		}
	}
 
 
 
void creat_member(mem *pNew)                                      //输入信息操作，会员登记函数
{		                                                          //创建一个新的会员 
	char s;
    printf("卡号:");					scanf("%s",pNew->id);     //运用指针输入卡号
    printf("请输入姓名: ");				scanf("%s",pNew->name);   //运用指针输入姓名
    a:
    printf("请输入性别(f--女m--男): ");	getchar();                //输入男女
	s = getchar();
	if(s=='f'||s=='m')                                            //判断是 男 是 女
	{
		if (s == 'f' || s == 'F') strcpy(pNew->sex,"女");        
		if (s == 'M' || s == 'm') strcpy(pNew->sex,"男");       
	}
	else                                                           //如果输入错误
	{
		printf("输入错误，请重新输入...\n");
		goto a;                                                    //跳转至a，重新输入
	}
    printf("请输入年龄: ");				scanf("%d",&(pNew->age));   //运用指针输入年龄
    printf("请输入缴费金额: ");			scanf("%f",&(pNew->money));  //运用指针输入余额
    printf("请输入电话: ");				scanf("%s",pNew->tel);       //运用指针输入电话
	pNew->cost=0;                                                    //运用指针初始化消费额为0
    printf("\n创建完毕!\n"); 
}
 
 
void newMember()                                                    //会员登记函数
{	                                               	                //添加会员信息 
	char con='N';
	mem *pLast= NULL;
	mem *pNew=(mem *)malloc(sizeof(mem));                           //按 mem 动态分配内存
	pNew->next=NULL;
	creat_member(pNew);                                             //调用会员登记函数
	if(head == NULL)
	{
		head = pNew;
	}
	else
	{
		pLast = get_last(head);
		pLast->next = pNew;
	}
	printf("继续输入会员信息？(Y 继续， N 返回菜单)");              //判断是否继续登记
	getchar();
	con = getchar();
	if (con == 'n' || con == 'N')
	{
		save(pNew);
		menu();
	}
	else{
		save(pNew);
		newMember();
	}
}                                                                 
 
 
                                                                     //显示信息操作
 
void table_head()                                             
 {	                                                             	//定义表头 
	printf("+----------+------+------+------+--------+--------+-----------+\n");
	printf("|   卡号   | 姓名 | 性别 | 年龄 |  余额  |累计消费|   电话    |\n");
	printf("+----------+------+------+------+--------+--------+-----------+\n");	
}
void table_buttom()
{                                                               	//定义底线 
	printf("+----------+------+------+------+--------+--------+-----------+\n");
}  
void table_row(mem *p)
{	                                                                // 定义中间部分
	printf("|%10s|%6s|%6s|%6d|%8.2f|%8.2f|%11s|\n",
			p->id,p->name,p->sex,p->age,p->money,p->cost,p->tel);
}
 
 
 
 
void display(mem *p)
{	                                        //显示所有信息 
	p = head;
	table_head();                            //调用表头
	while(p != NULL) 
	{
		table_row(p);                       //调用中间部分
		p = p->next;
	}
	table_buttom();                          //调用底线
}
 
 
void display_one(mem *p)
{	                                        //只显示一条信息 
	table_head();
	table_row(p);
	table_buttom();
}
 
 
void table_sum()
{                                //定义总计
	printf("+----------+------+------+------+--------+--------+-----------+\n");
	printf("|          |      |      |      |  总计  |  总计  |           |\n");
	printf("+----------+------+------+------+--------+--------+-----------+\n");	
}
void table_r(float money,float cost)
{                              //定义总计2
	printf("|          |      |      |      |%8.2f|%8.2f|           |\n",money,cost);
}
 
 
 
 
void display_statistics(mem *p,float money,float cost)
{                                                                  //显示统计信息函数
    p = head;
	table_head();                                                 //调用表头
	while(p != NULL)
	{
		table_row(p);                                             //定义中间部分
		p = p->next;
	}
	p=head;
	table_sum();                                                  //定义总计
	table_r(money,cost);                                          //定义总计2
	table_buttom();                                               //定义表尾
}                                                                 //文件相关操作
 
 
 
void save(mem *p)
{	                                            	                 //保存函数
	FILE *fp;                                                        //定义一个指向文件的指针变量
    fp=fopen("member.dat", "a");                                     //将fopen函数的返回值赋给指针变量fp
	while(p != NULL)
	{
		fprintf(fp, "%s %s %s %d %f %s %d\n",p->id, p->name, p->sex, p->age, p->money, p->tel,p->cost);
		p = p->next;
	}
	fclose(fp);                                                       //关闭指针
	getchar();                                                    
}
 
 
 
void modify_file(mem *p)
{	                                                                //保存修改会员信息函数
	FILE *fp;
	p= head;
	if((fp=fopen("member.dat", "w"))==NULL)
	{                                                               //检查打开文件的操作是否有错
		printf("文件不存在");
		getchar();
		menu();                                                     //调用菜单函数
	}
	while(p != NULL)
	{                                          
		fprintf(fp, "%s %s %s %d %f %s %f\n",p->id, p->name, p->sex, p->age, p->money, p->tel,p->cost);
		p = p->next;
	}
	fclose(fp);
	getchar();
}
 
 
 
void load(mem *p)
{	                                                          //从文件加载信息 
	FILE *fp; 
	mem *pLast = NULL;
	head=NULL;
	if((fp=fopen("member.dat","r"))==NULL)
	{                                                         //检查打开文件的操作是否有错
		printf("没有会员信息，请录入！");
		getch();
		menu();                                               //调用菜单函数
	}
	while(!feof(fp))
	{                                                         //文件指针是否到达末尾
		mem *pNew = (mem *)malloc(sizeof(mem));               //按 mem 动态分配内存
		pNew->next = NULL;
		fscanf(fp, "%s %s %s %d %f %s %f\n",
					pNew->id, pNew->name, pNew->sex, &(pNew->age), &(pNew->money), pNew->tel,&(pNew->cost));
		if(head == NULL)
		{
			head = pNew;
		}  
		else
		{
			pLast = get_last(head);
			pLast->next = pNew;
		}		
	}
	p = head;
	fclose(fp);
}
                                                          //通过卡号搜索信息函数 
 
 
mem* search_id(mem *p)
{ 	                                                      //通过卡号搜索信息 
	char id[MAX];
	int i=0;
	p = head;
	scanf("%s",id);
	while(p&&(strcmp(id,"n")!=0))
	{                                                       //判断id是否不为n
		if(strcmp(p->id,id)==0)
		{                                                   //找到
			i=1;
			break;
		}
		else
			p=p->next;
	}
	if(strcmp(id,"n")==0)	                                //输入n时返回菜单 
		menu();
	if(p==NULL)
	{			                                           //重新搜索卡号 
		printf("您查找的卡号不存在，请重新输入：\n");
		p=search_id(p);                                    //调用寻找函数
	}
	else
		return p;                                          //返回p
}
                                                           /*修改会员信息操作*/ 
 
 
 
void modify_m()
{	                                                       //修改会员的信息 
 
	char s,fun='y';
	char pro[] =                                  
	"|\n"
	"| 1 姓名\n"
	"| 2 性别\n"
	"| 3 年龄\n"
	"| 4 电话\n"
	"| 5 返回\n"
	"|\n";
	mem *p;
	load(p);
	display(p);                                    //调用显示函数
	printf("请输入需要修改信息的会员卡号（n返回菜单）："); 
	p=search_id(p);                                //调用按号寻找函数
	while(fun=='y'||fun=='Y')
	{                                              //当继续寻找时
		system("cls");                            //清屏
		display_one(p);                            //调用显示一条函数
		printf("请选择修改的项目：\n");            
		printf(pro);                               //输出pro
		getchar();
		scanf("%c",&fun);
		switch(fun)
		{                                           //用switch语句选择修改内容
			    case '1':	printf("请输入姓名: ");				scanf("%s",p->name);break;
			    case '2':	a:
						    printf("请输入性别(f--女m--男): ");	getchar();
							s = getchar();
							if(s=='f'||s=='m')
							{
								if (s == 'f' || s == 'F') strcpy(p->sex,"女"); 
								if (s == 'M' || s == 'm') strcpy(p->sex,"男"); 
							}
							else
							{
								printf(">输入错误，请重新输入...\n");
								goto a;
							}
							break;
			    case '3':	printf("请输入年龄: ");				scanf("%d",&(p->age));break;
			    case '4': 	printf("请输入电话: ");				scanf("%s",p->tel);	break;
				default :	break;
		}
		printf("是否继续修改Y/N?");                     //判断是否继续寻找
		getchar();  
		fun=getchar();
	}
	modify_file(p);                                    //调用保存修改会员信息函数                                      
	system("cls");                                     //清屏
	display_one(p);                                    //调用显示一条函数
	printf("\n修改成功,按任意键继续!");
	getchar();
	menu();                                            //调用菜单函数
}
                                                       //会员续费函数
 
 
void add()
{			                                           //会员续费 
	float money;
	mem *p;
	load(p);
	display(p);                                        //调用浏览函数
	printf("\n");
	printf("请输入需要续费的会员卡号（n返回菜单）："); 
	p=search_id(p);                                      //调用按号寻找函数
	system("cls");                                       //清屏
	display_one(p);                                      //调用显示一条函数
	printf("请输入续费金额：");
	scanf("%f",&money);
	p->money+=money;                                      //续费
	modify_file(p);                                        //调用保存修改会员信息函数 
	system("cls");                                         //清屏
	display_one(p);                                        //调用显示一条函数
	printf("续费成功，任意键继续!");
	getchar();
	menu();                                                  //调用菜单函数
}
                                                           //会员结算函数
 
 
 
void consume()
{	                                                     	//会员结算 
	mem *p;
float cost;
	load(p);
	display(p);                                                /* 调用浏览函数*/
	printf("\n");
	printf("请输入需要结算的会员卡号（n返回菜单）："); 
	p=search_id(p);                                          //调用按号寻找函数    
	system("cls");                                           //清屏
	display_one(p);                                          //调用显示一条函数
	printf("请输入花费金额：");
	scanf("%f",&cost);
	if(p->cost>=1000)
	{                                                         //判断是否升级为vip
		printf("恭喜您已经升级为VIP，本次消费9折优惠。\n"); 
		printf("本次实际消费%.2f元！",cost*0.9);              //升级为vip，消费打9折
		cost*=0.9;
		if((p->money-cost)<0)
		{                                                     //判断余额是否充足
			printf("对不起，余额不足，请及时充值！");
			getchar();
			menu();            
		}
		p->cost+=cost;                                         
		p->money-=cost;                                       //消费
		getchar();
	}
	else
	{
		if((p->money-cost)<0)
		{                                 //同上
			printf("对不起，余额不足，请及时充值！");
			getchar();
			menu();
		}
		p->cost+=cost;
		p->money-=cost;  
	}
	modify_file(p);                                       //调用保存修改会员信息函数 
	system("cls");                                         //清屏
	display_one(p);                                       //调用显示一条函数
	printf("结算成功，任意键继续!");
	getch();
	menu();                                               //调用菜单函数
}
                                                          /*会员退出函数*/ 
 
 
 
void delete_m()
{	                                                      //删除会员信息 
	mem *p,*q=head,*thelast;
	float money;
	load(p);
	display(p);                                           /* 调用浏览函数*/
	printf("\n");
	printf("请输入需要删除的会员卡号（n返回菜单）："); 
	p=search_id(p);                                        //调用按号寻找函数
	thelast=head;
	if(p==head)
	{                                                     //判断指针
		head=p->next;
		money=p->money;
		free(p) ;
	}
	else
	{
		while(thelast)
		{
			if(thelast->next==p)
				break;
			else
				thelast=thelast->next;
		}
		thelast->next=p->next;
		money=p->money;
		free(p);
	}
	modify_file(q);                                           //调用保存函数
	printf("退回余额%.2f元！\n",money);
	printf("删除成功，按任意键继续！");                         //显示退回的余额
	getch(); 
	menu();                                                    //调用菜单函数
}                                                                /*统计函数*/ 
 
 
mem *sort_m()
{                                                             //按缴费总额排序
	mem *q,*tail,*p=(mem*)malloc(sizeof(mem));    
	p->next=head;    
	head=p;    
	tail=NULL;                                                  //定义 tail
	while(tail!=head->next)   
	{
		p=head;    
		q=p->next;      
		while(q->next!=tail)  
		{                                                        //判断 q是否为空
			if(p->next->money>q->next->money)  
			{
				p->next=q->next;                                 //比较大小，排序
				q->next=q->next->next;    
				p->next->next=q;    
			}    
			p=p->next;    
			q=p->next;    
		}    
		tail=q;    
	}    
	head=head->next;    
	free(p);
	return head;                                                  //返回值
} 
 
 
mem* sort_c() 
{                                                                //按消费金额排序 
	mem *q,*tail,*p=(mem*)malloc(sizeof(mem));    
	p->next=head;    
	head=p;    
	tail=NULL;                                                     //定义 tail                             
	while(tail!=head->next)   
	{
		p=head;    
		q=p->next;    
		while(q->next!=tail)    
		{
			if(p->next->cost>q->next->cost)  
			{                                                    //比较大小，排序
				p->next=q->next;    
				q->next=q->next->next;    
				p->next->next=q;    
			}    
			p=p->next;    
			q=p->next;    
		}    
		tail=q;    
	}    
	head=head->next;    
	free(p); 
	return head;                                        //返回值
}
 
 
float summ(mem *p)
{	                                   //计算缴费总额 
	float summ=0;
	p=head;
	while(p)
	{                                         //循环，实现求总额
		summ+=p->money;
		p=p->next;
	}
	return summ;                                      //返回总额
}
 
 
 
float sumc(mem *p)
{	                              //计算消费总额 
	float sumc=0;
	p=head;
	while(p)
	{                                          //循环，实现求总额
		sumc+=p->cost;                              
		p=p->next;
	}
	return sumc;                                       //返回总额
}
 
 
void statistics()
{		                          //统计会员信息函数
	int f=0;
	mem *p;
	load(p);
	
	system("cls");
	printf("\t\t=======================================\n"
	"\t\t|\n"
	"\t\t|1 按缴费总额排序\n"
	"\t\t|2 按消费总额排序\n"
	"\t\t|3 返回菜单\n"
	"\t\t|\n"
	"\t\t=======================================\n"
		) ;
	printf("请选择功能：");
	scanf("%d",&f);
	switch(f) 
	{                                          //用switch语句选择功能
		case 1:	p=sort_m(p);                              //调用按缴费总额排序
				display_statistics(p,summ(p),sumc(p));    //调用函数
				getch(); 
				menu();
				break;
		case 2: p=sort_c(p);                             //调用按消费总额排序
				display_statistics(p,summ(p),sumc(p));   //调用函数
				getch(); 
				menu();break;
		default : menu();break;
	}
}
                                               /*退出系统操作*/ 
 
 
 
void clear(mem *p)
{		                                     //释放链表空间 
	if(p==NULL)
	{
		return;
	}	
	if(p->next ==NULL)
	{
		free(p);
	}
	else
	{
		clear(p->next);
		free(p);
		p = NULL;
	}
} 
 
 
 
void quit()
{                                               //退出函数
	clear(head); 
	exit(0); 
}
                                                /*菜单信息*/ 
 
 
void menu_tile(char *title)
{                                              //菜单表头  
	printf("\t\t=======================================\n");
	printf("\t\t| %s\n", title);
	printf("\t\t---------------------------------------\n");
}
 
 
void (* menu_main_func[])()=                                    /*函数指针数组 menu_main_func[] 存储的是主菜单项中7个功能函数的地址，
	                                                            分别对应1-7菜单项。例如用户选择1时，调用数组的第0个元素，即调用 
                                                                newMember()函数，以此类推。*/
{                 
	newMember,
	modify_m,
	add,
	consume,
	delete_m,
	statistics,
	quit, 
};	
char menu_main[] =                                              //菜单主函数
"\t\t\n"
"\t\t| 1 新会员登记\n"
"\t\t| 2 会员信息修改\n"
"\t\t| 3 会员续费\n"
"\t\t| 4 会员消费结算\n"
"\t\t| 5 会员退卡\n"
"\t\t| 6 统计功能\n"
"\t\t| 7 退出系统\n"
"\t\t|\n";
void menu()
{                                                               //菜单函数
	int selected = 0;                                           //初始化变量
	system("cls");                                              //清屏
	
    printf("                 会员卡计费系统");
	printf(menu_main);                                          //输出菜单主函数
	printf("\t\t=======================================\n");
	
	while(!(selected >= 1 && selected <= MENU_MAIN_COUNT))
	{                                                          //判断初始值
		printf("请选择：");
		scanf("%d",&selected);
		if(selected >= 1 && selected <= MENU_MAIN_COUNT)
		{    //判断输入值是否有效
			break;
		}
		printf("\n>输入错误！（注：请选择 1 - %d)\n", MENU_MAIN_COUNT);
	}
	menu_main_func[selected-1]();                             //调用相应的函数指针数组中的函数，执行操作
	                                             
}                                              
  int main()                                                  /*主函数*/
{
	menu();                                                   //调用菜单函数
	return 0;                                                //返回值
}
 
