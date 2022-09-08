#include<stdio.h>
#include<stdlib.h>


int stack[127];
int top = -1;

int isempty()
{
	if (top == -1) return 1;
	else return 0;
}

int push(int data)
{
	if (top >= 127)
		return 0;
	else
	{
		stack[++top] = data;
		return 1;
	}
}

int pop()
{
	if (isempty())
		return -1;
	else
		return stack[top--];
}

int main()
{
	int treeval[7] = { 0 };

	printf("input 7 values of tree (only int & not repeating) \n");
	for (int i = 0; i < 7; i++)
		scanf("%d", &treeval[i]);

	int treeval2[127] = { 0 }; //2的7次方-1

	//建立一維link list(存原始資料)
	struct tree
	{
		int index;
		int val;
		struct tree* next;
	};
	typedef struct tree btree;
	btree* ptr;  //存取指標
	btree* head;  //串列開頭指標
	btree* newnode;  //新元素指標

	head = (btree*)malloc(sizeof(btree));  //建立串列首
	head->next = NULL;
	ptr = head;

	//存陣列到二元樹中
	for (int i = 0; i < 7; i++)
	{
		newnode = (btree*)malloc(sizeof(btree));
		newnode->index = i;            //存索引
		newnode->val = treeval[i];     //存值

		ptr->next = newnode;
		newnode->next = NULL;
		ptr = ptr->next;
	}

	//建立一維link list(二元搜尋樹)
	struct tree2
	{
		int index2;
		int val2;
		struct tree2* next2;
	};
	typedef struct tree2 btree2;
	btree2* ptr2;  //存取指標
	btree2* head2;  //串列開頭指標
	btree2* newnode2;  //新元素指標

	head2 = (btree2*)malloc(sizeof(btree2));  //建立串列首
	head2->next2 = NULL;
	ptr2 = head2;

	//建二元搜尋樹
	for (int j = 0; j < 127; j++)
	{
		newnode2 = (btree2*)malloc(sizeof(btree2));
		newnode2->index2 = j;            //存索引
		newnode2->val2 = treeval2[j];     //存值

		ptr2->next2 = newnode2;
		newnode2->next2 = NULL;

		ptr2 = ptr2->next2;
	}

	ptr = head->next;
	ptr2 = head2->next2;

	for (int i = 0; i < 7; i++)
	{
		ptr2 = head2->next2; //搜尋二元樹從頭開始比

		for (int level = 1; ptr2->val2 != 0; )
		{
			if (level >= 64)
				break;

			else if (ptr->val > ptr2->val2) //大於向右
			{
				level = (level * 2) + 1;
				for (int k = 0; ptr2->index2 != level - 1; k++) //指到新節點位置 直到搜尋樹此位置=0
					ptr2 = ptr2->next2;
			}

			else
			{
				level = level * 2;
				for (int k = 0; ptr2->index2 != level - 1; k++) //指到新節點位置 直到搜尋樹此位置=0
					ptr2 = ptr2->next2;
			}
		}

		ptr2->val2 = ptr->val; //存入搜尋樹
		ptr = ptr->next; //下一個值進去比較
	}


	int choose = 0;
	//選單
	while (choose != 5)
	{
		printf("\n\nchoose functions :\n1.output binary search tree\n2.search your input element \n3.inorder binary search tree(small to big) \n4.inorder binary search tree(big to small)\n5.leave\n\nYour choose : ");
		scanf("%d", &choose);
		if (choose == 1)
		{
			printf("your input : ");
			for (int i = 0; i < 7; i++)
				printf("[%2d] ", treeval[i]);
			printf("\nbinary search tree:\n");

			ptr2 = head2->next2;
			for (int j = 0; j < 127; j++)
			{
			        if(ptr2->val2==0)
			          {
			          ptr2 = ptr2->next2;
			          continue;
			          }
				else
				{
				printf("[%3d] [%3d]\n", (ptr2->index2) + 1, ptr2->val2);
				ptr2 = ptr2->next2;
				}
			}
		}

		else if (choose == 2)
		{   //搜尋
			int searchval;
			printf("輸入要尋找的數字:");
			scanf("%d", &searchval);

			int exit = 0;
			for (int i = 0; i < 7; i++)
			{
				if (treeval[i] == searchval)
				{
					printf("%d在此二元搜尋樹中存在\n\n", searchval);
					exit = 1;
					break;
				}
			}

			if (exit == 0)
				printf("%d在此二元搜尋樹中不存在\n\n", searchval);
		}
		else if (choose == 3)
		{
			printf("your input : ");
			for (int i = 0; i < 7; i++)
				printf("[%2d] ", treeval[i]);
			printf("\n");

			//中序拜訪(小到大)
			ptr2 = head2->next2;
			for (int j = 0; j < 127; j++)
			{
			     if(ptr2->val2==0)
			         {
			          ptr2 = ptr2->next2;
			          continue;
			         }
			    else
				{
				printf("[%3d] [%3d]\n", (ptr2->index2) + 1, ptr2->val2);
				ptr2 = ptr2->next2;
				}
			}
		}
		else if (choose == 4)
		{
			printf("your input : ");
			for (int i = 0; i < 7; i++)
				printf("[%2d] ", treeval[i]);
			printf("\n");

			//中序拜訪(大到小)
			ptr2 = head2->next2;
			for (int j = 0; j < 127; j++)
			{
			       push(ptr2->val2);
				ptr2 = ptr2->next2;
			}

			for (int j = 0; j < 127; j++)
			     {
			     int valinorder = pop();
			     
			     if(valinorder==0)
			          continue;
			        
			     else
				   printf("[%3d][%3d]\n", 127 - j, valinorder);
			      }
		}
		
		else
			break;
	}

	
	return 0;
}
