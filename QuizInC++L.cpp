#include<string.h>
#include<ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

using namespace std;
//Global Variables//

int selected[10],alloted[10];	//Questions selected randomly are stored and selected option marks//
char opted[10],category[10][50];	//Saving results//

class Candidiate{			//Class defined a any candidiate info//
	char name[50];
	char rollno[12];
	char clg[50];
	public:
		//To accept Data from the candidiate//
		void getData()
		{					
			system("cls");
			cout<<"\t\t\t\t\tWELCOME\n";
			cout<<"\nEnter your Name					:				";
			gets(name);
			cout<<"\nEnter your roll number				:				";
			gets(rollno);
			cout<<"\nEnter your College name				:				";
			gets(clg);
		}
		//To display basic details of candidiate//
		void displayName()
		{
			system("cls");
			cout<<"\nName		:				"<<name;
			cout<<"\nRoll Number	:				"<<rollno;
			cout<<"\nCollege		:				"<<clg;
			cout<<endl;
		}
		//To diaplay result of the candidiate//
		void result(int score)
		{
			displayName();
			cout<<"\nCongratulations !!! ";
			cout<<"\nYou have completed the quiz.";
			cout<<"You have got "<<score<<" correct out of 10 questions.";
		}
		
		
};	//End of the class//

class Question	//Question class defined for the data of one question//
{	private:
	char cat[50];
	char ques[400];
	char choice[4][100];
	char ans;
	public:
		
		Question(){		//Constructor//
			
		}
		~Question(){	//Destructor//
			
		}
		
		//Function to write data into a file//
		void write(){
		cout<<"Enter no. of Records";
		int n;
		cin>>n;
		fstream fp;
		Question qq;
		fp.open("QuestionBank.txt", ios::out | ios::in |ios::trunc  );
		for(int i=1;i<=n;i++)
			{
				fflush(stdin);
				cout<<"\nEnter Category		:	";
				gets(qq.cat);
				cout<<"\nEnter Ques			:	";
				gets(qq.ques);
				cout<<"Enter Choices		:	";
				cout<<"Enter choice A	:	";
				gets(qq.choice[0]);
				cout<<"Enter choice B	:	";
				gets(qq.choice[1]);
				cout<<"Enter choice C	:	";
				gets(qq.choice[2]);
				cout<<"Enter choice D	:	";
				gets(qq.choice[3]);
				cout<<"Enter correct choice	:	";
				cin>>qq.ans;
				cout<<"confirm";
				int chh;
				cin>>chh;
				if(chh==1)
				fp.write((char*)&qq,sizeof(Question));
				else
				i--;
			}
			fp.close();
	}
	
	//Function to read all the questions fromthe file//
	
	void read(Question q[])
	{
		
		fstream fp1;		
		fp1.open("QuestionBank.txt", ios::in | ios::out );
		int i=0;
		while(i<30)
			{
				fp1.read((char*)&q[i],sizeof(q[i]));
				i++;
			}
			fp1.close();
	}


	//Function returns the marks of the particular question and takes input from the user for each question//
	int display(Question q,int qno, Candidiate c){
		system("cls");
		c.displayName();
		//
		int flag=0;
		char a;
		cout<<"\nCategory	:	"<<q.cat;
		cout<<"\nQ"<<qno<<" ) "<<q.ques;
		cout<<"\n\nPLEASE SELECT ONLY ONE OPTION FROM BELOW";
		cout<<"\n\nA.	"<<q.choice[0];
		cout<<"\n\nB.	"<<q.choice[1];
		cout<<"\n\nC.	"<<q.choice[2];
		cout<<"\n\nD.	"<<q.choice[3];
		cout<<"\n\n\n\nEnter your Choice	:	";
		fflush(stdin);
		cin>>a;
		a=toupper(a);
		opted[qno-1]=a;
		strcpy(category[qno-1],q.cat);
		
		if(a==q.ans || q.ans==(a-32) )
			{
				flag=1;
			}
		else
			{
				flag=0;
			}
		
		return flag;
	}


//to display the question answer and selected option per question//
void displayQ(int qno){
		
		int flag=0;
		char a;
		cout<<"\n\nHere are your Answers :";
		cout<<"\nCategory			:	"<<cat;
		cout<<"\nQ"<<qno+1<<" ) "<<ques;
		cout<<"\n\nA.	"<<choice[0];
		cout<<"\n\nB.	"<<choice[1];
		cout<<"\n\nC.	"<<choice[2];
		cout<<"\n\nD.	"<<choice[3];
		cout<<"\nYou entered		:	"<<opted[qno];
		cout<<"\nCorrect Anwer		:	"<<ans;
		cout<<"\nMarks Alloted		:	"<<selected[qno];
		fflush(stdout);
		getch();
				
	}	
	
	protected:
		
}q[30];


//To initiale all the arrays and select randomquestion no.//
void init(){
	int i=0,j,s,f;
	//Intialize Select array to -1//
	for(i=0;i<30;i++)
		{
			selected[i]=0;
			alloted[i]=-1;
		}
	
	
	for(i=0;i<10;i++)
		{
		srand(time(NULL));
		j=rand()%30;
		while(1){
				f=1;
				j=rand()%30;
		
				for(s=0;s<i;s++)
				{	
					if(alloted[s]==j)
					{
					f=0;		
					}
				}	
			
				if(f==1)
				{
				alloted[i]=j;
				break;
				}
		}
		
		}		
}


//to run the quiz for the candidiate//
void quiz(Candidiate c){
	int i;
	Question qu;
	qu.read(q);
	init();
	for(i=0;i<10;i++)
		{	
		selected[i] = qu.display(q[alloted[i]],i+1,c);
		}

	}

//To calculate and disply result of the quiz//
void completed(Candidiate c, int score){
			int i;
			for(i=0;i<10;i++)
			{	
			system("cls");
			c.result(score);
			q[alloted[i]].displayQ(i);
			}
			
			system("cls");
			int j=0,s=0;
			for(i=0;i<10;i++)
			{
				for(j=i+1;j<10;j++)
				{
					if(strcmpi(category[i],category[j])==0)
					{
						selected[i]+=selected[j];
						strcpy(category[j],"-1");
					}
				}
			}
			
			cout<<"Category Wise Marking";
			for(i=0;i<10;i++){
				if(strcmpi(category[i],"-1")!=0)
				{
					cout<<"\n"<<s+1<<" > Category : "<<category[i];
					cout<<"\n\t\tMarks : "<<selected[i];
					s++;
				}
			}
			
			cout<<"\n\nYour total Score is "<<score<<" out of 10";
						
		}

//to calculate and return the score//
int cal(){
	int score=0;
	for(int i=0;i<10;i++)
	{
		score+=selected[i];
	}
	return score;
}

//Main Function//
int main(){
	system("cls");
	int i,score;
	Candidiate c;
	c.getData();
	quiz(c);		
	score=cal();
	completed(c,score);
	return 0;
}
