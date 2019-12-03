#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 19 // number of students

int sumascii(char str[]);


int sumascii(char str[])
{
	int sum=0;
	for(int i=0;i<strlen(str);i++)
	{
		sum=sum+str[i];
	}
	return sum;
}

typedef struct Student
{
    char AM[256]; 
    char Firstname[256];
    char Lastname[256];
    float grade;
    struct Student *next;
    
} STUDENTH; 

int find(STUDENTH *list,char AM[]);


typedef struct Array_List//each index of the array can be stored with linked list
{
	STUDENTH *head;
	STUDENTH *tail;
	
} ARRAYLIST;

int size=0;
int max=19; 

int hashcode(char key[])
{
	char AM[10];
	int s=sumascii(key);
	return(s % max);
}

STUDENTH* find_student(STUDENTH *list, int find_index);
void delete_student(STUDENTH AM[]);
void init_array();
STUDENTH * createNode(char AM[], char first[], char last[],float grade);


STUDENTH * createStud(char AM[], char first[], char last[],float grade)
{
	STUDENTH *new_student;
	new_student= (STUDENTH*)malloc(sizeof(STUDENTH));
	strcpy(new_student->AM, AM);
	strcpy(new_student->Firstname, first);
	strcpy(new_student->Lastname, last);
	new_student->grade = grade;
	new_student->next=NULL;
	return new_student;
}



void insert(ARRAYLIST *array, char AM[], char first[], char last[],float grade)
{
	int index=hashcode(AM);
	STUDENTH *new_student=createStud(AM, first,  last, grade);
	STUDENTH *list=(STUDENTH*) array[index].head;
	if(list==NULL)//we make linked list at given index of the table
	{
		printf("Inserting student with AM:%s\n",new_student->AM);
		array[index].head=new_student;
		array[index].tail=new_student;
		size++;
	}
	else//already made linked list at given index
	{
		int find_index=find(list,new_student->AM);
		if(find_index == -1)//AM not found,put student at the of the list
		{
			array[index].tail->next=new_student;
			array[index].tail=new_student;
			size++;
		}
		else//AM already in list,update the attributes
		{
			STUDENTH *updated=find_student(list,find_index);
			strcpy(updated->Firstname,new_student->Firstname);
			strcpy(updated->Lastname,new_student->Lastname);
			updated->grade=new_student->grade;		
		}
	}
}

int find(STUDENTH *list,char AM[])//search AM in list
{
	int k = 0;
	STUDENTH *temp = list;
	while(temp != NULL)
	{
		if(temp->AM ==AM)
		{
			return k;
		}
		temp = temp->next;
		k++;
	}
	return -1;
}

STUDENTH* find_student(STUDENTH *list,int find_index)//returns list's item at given fin_index
{
	int i=0;
	STUDENTH *temp = list;
	while(i != find_index)
	{
		temp = temp->next;
		i++;
	}
	return temp;
}

void remove_student(ARRAYLIST *array,char AM[])
{
	int index=hashcode(AM);
	STUDENTH *list=(STUDENTH*)array[index].head;
	if(list==NULL)
	{
		printf("THIS AM DOESN'T EXISTS\n");
	}
	else
	{
		int find_index = find(list,AM);
		if(find_index == -1)
		{
			printf("THIS AM DOESN'T EXISTS\n");
		}
		else
		{
			STUDENTH *temp=list;
			if(temp->AM ==AM)
			{
				array[index].head=temp->next;
				printf("This AM has been removed\n");
				return;
			}
			while(temp->next->AM != AM)
			{
				temp=temp->next;
			}
			if(array[index].tail==temp->next)
			{
				temp->next=NULL;
				array[index].tail=temp;
			}
			else
			{
				temp->next = temp->next->next;
			}
			printf("This AM has been removed\n");

		}
	}
}

void present(ARRAYLIST *new_array)
{
	int i=0;
	for(i=0;i<max;i++)
	{
		STUDENTH *temp = new_array[i].head;
		if(temp==NULL)
		{
			printf("Array[%d] has no elements\n",i);
		}
		else
		{
			printf("Array[%d] has elements: ",i);
			while(temp!=NULL)
			{
				printf("AM=%s\tFIRST:%s\tLAST:%s\tGRADE=%f\n",temp->AM,temp->Firstname,temp->Lastname,temp->grade);
			}
			printf("\n");
		}
	}
}

void init_array(ARRAYLIST *new_array)
{
	int i=0;
	for(i=0;i<max;i++)
	{
		new_array[i].head=NULL;
		new_array[i].tail=NULL;
	}
}

int size_of_array()
{
	return size;
}

typedef struct student
{
    char AM[256]; 
    char Firstname[256];
    char Lastname[256];
    float grade;
	struct student *left;
	struct student *right;
    
} STUDENT; 

void update(STUDENT *root, char AM[])
{
    if(root == NULL) {
		printf("NOT FOUND!!\n");
        return;
    }
	else
    {
        if(strcmp(AM , root->AM) < 0)
            update(root->left, AM);
        else if(strcmp(AM , root->AM) > 0)
            update(root->right, AM);
        else
		{
			printf("Give new firstname, lastname, grade: ");
        	scanf("%s%s%f", root->Firstname, root->Lastname, &root->grade);
        	printf("SUCCESS");        	
		}
    }
}

void search(STUDENT *root, char AM[])
{
    if(root == NULL) {
		printf("NOT FOUND!!\n");
        return;
    }
	else
    {
        if(strcmp(AM , root->AM) < 0)
            search(root->left, AM);
        else if(strcmp(AM , root->AM) > 0)
            search(root->right, AM);
        else
		{
			printf("SUCCESS\t"); 
			printf("Student's firstname, lastname, grade: ");
        	printf("\t%s\t%s\t%f\n", root->Firstname, root->Lastname, root->grade);      	
		}
    }
}



STUDENT *CreateBST(STUDENT *root, STUDENT *new_student)
{
    if(root == NULL)
        return new_student;
	else
    {
        if(strcmp(new_student->AM , root->AM) < 0)
            root->left = CreateBST(root->left, new_student);
        else if(strcmp(new_student->AM , root->AM) > 0)
            root->right = CreateBST(root->right, new_student);
		return root;
    }
}

void Inorder(STUDENT *root)
{
    if( root != NULL)
    {
        Inorder(root->left);
        printf("%s\t%s\t%s\t%f\n",root->AM,root->Firstname,root->Lastname,root->grade);
        Inorder(root->right);
    }
}

void sort_students_top()
{
   
    int i=0;
    
    FILE *fp;

    STUDENT Student[N];

    fp = fopen("grades.txt","r"); //opens the file in read mode 

    
    if (fp == NULL) //check if file is empty
    {
        printf("Could not open file\n");
    }
    
    while(EOF!=fscanf(fp, "%s %s %s %f\n", Student[i].AM, Student[i].Firstname, Student[i].Lastname,&Student[i].grade)) //scannig the students and their attributes
    {
        i++; // next student
    }

    
   	fclose(fp);
    
	int a,b,max;
	
	STUDENT temp;
	
		 for(a=0; a<N; a++)  
		 {
       		 for(b=a+1; b<N; b++)
			{
	            if(Student[a].grade < Student[b].grade ) //with a bubblesort style we sort them alphabetically base on their grades
				{
	                temp = Student[a];
	                Student[a] = Student[b];
	                Student[b] = temp;
 					
	            }
	        }
   		}
   		
   		// printf("%s %s %s %s\n", Student[0].AM, Student[0].Firstname, Student[0].Lastname, Student[0].grade); --> top grades
   		
   		 //due to the above sorting the student[0].grade will be the highest so below we print those who have the same grade as the top
			  
		/* for(a=0; a<N; a++) toys ektypwnei swsta apo ton megalutero sto mikrotero
	    {
	   	
		   printf("%s %s %s %s\n", Student[a].AM, Student[a].Firstname, Student[a].Lastname, Student[a].grade);
	    
	   	}	*/
		for(int i=0;i<N;i++)	   		
	   	{	
			if(Student[i].grade == Student[0].grade) 
	   		{
		   		printf("%s %s %s %f\n", Student[i].AM, Student[i].Firstname, Student[i].Lastname, Student[i].grade);
	  	 	}
 		}
}

void sort_students_low()
{
   
    int i=0;
    
    FILE *fp;

    STUDENT Student[N];

    fp = fopen("grades.txt","r"); //opens the file in read mode 

    
    if (fp == NULL) //check if file is empty
    {
        printf("Could not open file\n");
    }
    
    while(EOF!=fscanf(fp, "%s %s %s %f\n", Student[i].AM, Student[i].Firstname, Student[i].Lastname,& Student[i].grade)) //scannig the students and their attributes
    {
        i++; // next student
    }

    
   	fclose(fp);
    
	int a,b,max;
	
	STUDENT temp;
	
		 for(a=0; a<N; a++)  
		 {
       		 for(b=a+1; b<N; b++)
			{
	            if(Student[a].grade < Student[b].grade ) //with a bubblesort style we sort them alphabetically base on their grades
				{
	                temp = Student[a];
	                Student[a] = Student[b];
	                Student[b] = temp;
 					
	            }
	        }
   		}
   		
   		// printf("%s %s %s %s\n", Student[0].AM, Student[0].Firstname, Student[0].Lastname, Student[0].grade); --> top grades
   		
   		int x=0; //due to the above sorting the student[0].grade will be the highest so below we print those who have the same grade as the top
			  
		/* for(a=0; a<N; a++) toys ektypwnei swsta apo ton megalutero sto mikrotero
	    {
	   	
		   printf("%s %s %s %s\n", Student[a].AM, Student[a].Firstname, Student[a].Lastname, Student[a].grade);
	    
	   	}	*/
			   		
   		for(int i=0;i<N;i++)	   		
	   	{	
			if(Student[i].grade == Student[N-1].grade) 
	   		{
		   		printf("%s %s %s %f\n", Student[i].AM, Student[i].Firstname, Student[i].Lastname, Student[i].grade);
	  	 	}
 		}
 		
}

int main()
{
	int choice,choice1,i,n;
	FILE *fp = fopen("grades.txt", "r");
	printf("\n1.Load file to Binary Search Tree\n");
	printf("2.Load file to Hash Table\n");
	printf("3.Terminate Programm");
	printf("\nChoose how to load the file:");
	scanf("%d",&choice);
	do
	{
		if(choice==1)
		{
			
				STUDENT *root = NULL;
				do
			    {
		        printf("\n\nBinary Search Tree Operations\n");
		        printf("\n1. Creation of BST");
		        printf("\n2. Traverse in Inorder");
		        printf("\n3. Update");
		        printf("\n4. Search");
		        printf("\n5. Print students with best grade");
		        printf("\n6. Print students with worst grade");
		        printf("\n7. Exit\n");
		        printf("\nEnter Choice : ");
		        scanf("%d",&choice1);
		        switch(choice1)
		        {
			        case 1:
						if (fp == NULL)
						{
						    printf("Error opening file grades.txt!\n");
						    exit(1);
						}
						
						char name[256], AM[256], last[256];
						float grade;
						while(fscanf(fp, "%s%s%s%f", AM, name, last, &grade)!=EOF) //scannig the students and their attributes
						{
							STUDENT *new_student = (STUDENT*)malloc(sizeof(STUDENT));
							strcpy(new_student->AM, AM);
							strcpy(new_student->Firstname, name);
							strcpy(new_student->Lastname, last);
							new_student->left = NULL;
							new_student->right = NULL;
							new_student->grade = grade;	
							root = CreateBST(root, new_student);
						}
				        printf("\nBST isready to Use!!\n");
						fclose(fp);
			
				        break;
			        case 2:
			            printf("\nBST Traversal in Inorder\n");
			            Inorder(root);
			            break;
			        case 3:
			        	printf("\nGive AM: ");
			        	//char AM[256];
			        	scanf("%s", AM);
			        	update(root, AM);
						break;
			        case 4:
			        	printf("\nGive AM: ");
			        	//char AM[256];
			        	scanf("%s", AM);
			        	search(root, AM);
						break;
					case 5:
			        	printf("\nStudents with best grade: \n");
			        	sort_students_top();
						break;
					case 6:
			        	printf("\nStudents with worst grade: \n");
			        	sort_students_low();
						break;
				    case 7:
			            printf("\n\nTerminating\n\n");
			            return 0;	// exit main
			            break;
			        default:
			            printf("\n\nInvalid Option !!! Try Again !!\n\n");
			            break;
			        }
			        
			    } while(1);
		}
		if(choice==2)
		{		
				FILE *fp = fopen("grades.txt", "r");
				do
				{
					printf("HASH TABLE MODE!!!\n");
					printf("Menu: \n1.Make HASH TABLE\n2.Remove student from HASH TABLE\n3.Update Student's attributes\n4.Size of HASH TABLE\n5.Present HASH TABLE\n6.Terminating\n\nEnter choice: ");
					scanf("%d", &choice);
					ARRAYLIST *array;//array type ARRAYLIST

					switch(choice)
					{
						case 1:
							char AM[256];
							char LAST[256];
							char FIRST[256];
							float GRADE;
							array=(ARRAYLIST*)malloc(max * sizeof(ARRAYLIST*));
							init_array(array);
							if (fp == NULL)
							{
						   		printf("\nError opening file grades.txt!\n");
						    	exit(1);
							}
							int i;
							while(fscanf(fp, "%s%s%s%f", AM, FIRST, LAST, &GRADE)!=EOF)
							{	
								insert(array,AM,FIRST,LAST,GRADE);
							}
							printf("HASH TABLE ready to use!!!\n");
							fclose(fp);
							break;
						case 2:
							printf("Give the AM you want to delete: ");
							scanf("%s", AM);
							remove_student(array,AM);
							break;
						case 3:
							printf("Give the AM you want to update: ");
							scanf("%s", AM);
							printf("Give Student's new attributes(First,Last,Grade):\t");
							scanf("%s%s%f",  FIRST, LAST, &GRADE);				
							insert(array,AM,FIRST,LAST,GRADE);
							break;
						case 4:
							n=size_of_array();
							printf("Size of HASH TABLE is:%d\n",n);
							break;
						case 5:
							present(array);
							break;
						case 6:
							printf("\n\nTerminating\n\n");
				        	return 0;	// exit main
				        	break;
						default:
							printf("Wrong input\n");			
					}
				}while(1);
		}
		if(choice==3)
		{
				printf("\n\nTerminating\n\n");
				return 0;	// exit main
				break;
		}
	}while(choice!=1&&choice!=2&&choice!=3);
}
