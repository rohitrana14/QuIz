#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<iterator>
#include <ctime>
using namespace std;

#define queno 4

struct ques
{
	int qID;
	char question[50];
	char opt1[50];
	char opt2[50];
	char opt3[50];
	char opt4[50];
	int correctOption;
	int allotedMarks;
};

class finalQues
{
	public:
	int qID;
	char question[50];
	char opt1[50];
	char opt2[50];
	char opt3[50];
	char opt4[50];
	int correctOption;
	int allotedMarks;
	int chosenOption;
	void copy(struct ques q)
	{
		qID=q.qID;
		strcpy(question,q.question);
		strcpy(opt1,q.opt1);
		strcpy(opt2,q.opt2);
		strcpy(opt3,q.opt3);
		strcpy(opt4,q.opt4);
		correctOption=q.correctOption;
		allotedMarks=q.allotedMarks;
		chosenOption=0;	
	}
};

void printQuestions()
{
	getchar();
	system("cls");
	ques toprint;
	fstream fp("question.txt",ios::in |ios::binary);
	cout<<"\n\t\t\tQuestion List\n\n";;
	while(fp.read((char *)&toprint,sizeof(struct ques)))
	{
		cout<<"\n\n";
		cout<<"\nQuestion Id : "<<toprint.qID;
		cout<<"\nQuestion Text : "<<toprint.question;
		cout<<"\n1st Option : "<<toprint.opt1;
		cout<<"\n2nd Option : "<<toprint.opt2;
		cout<<"\n3rd Option : "<<toprint.opt3;
		cout<<"\n4th Option : "<<toprint.opt4;
		cout<<"\nCorrect Option : "<<toprint.correctOption;
		cout<<"\nAllotted Marks : "<<toprint.allotedMarks;
		
	}
	getchar();
	return;
}

void deleteQuestion()
{
	int id;
	bool deleted=false;
	getchar();
	system("cls");
	cout<<"\nDelete Questions\n\n";
	cout<<"\nQuestion Id (4 digits)      : ";
	cin>>id;
	cout<<"\n\n";
	ques todelete;
	fstream fp("question.txt",ios::in |ios::binary);
	fstream temp("temp.txt",ios::out|ios::binary);
	while(fp.read((char *)&todelete,sizeof(struct ques)))
	{
		if (todelete.qID!=id)
			temp.write((char *)&todelete,sizeof(struct ques));
		else
		{
			deleted=true;
			cout<<"\n\nQuestion Text : "<<todelete.question;
			cout<<"\n1st Option : "<<todelete.opt1;
			cout<<"\n2nd Option : "<<todelete.opt2;
			cout<<"\n3rd Option : "<<todelete.opt3;
			cout<<"\n4th Option : "<<todelete.opt4;
			cout<<"\nCorrect Option : "<<todelete.correctOption;
			cout<<"\nAllotted Marks : "<<todelete.allotedMarks;
			cout<<"\nConfirm Deletion (Y/N) : ";
			char choice='n';
			cin>>choice;
			if(choice!='y'&&choice!='Y')
				temp.write((char *)&todelete,sizeof(struct ques));
		}
			
	}
	fp.close();
	temp.close();
	remove("question.txt");
	rename("temp.txt","question.txt");
	if(!deleted)
	{
		cout<<"\n\nNo Question with this question ID exist!!!";
		Sleep(2000);
	}
	return;	
}

void modifyQuestion()
{
	int id,choice;
	bool modified=false;
	getchar();
	system("cls");
	cout<<"\nModify Questions\n\n";
	cout<<"\nQuestion Id (4 digits)      : ";
	cin>>id;
	cout<<"\nField to modify";
	cout<<"\n\t1) Question Text";
	cout<<"\n\t2) 1st Option";
	cout<<"\n\t3) 2nd Option";
	cout<<"\n\t4) 3rd Option";
	cout<<"\n\t5) 4th Option";
	cout<<"\n\t6) Correct Option";
	cout<<"\n\t7) Allotted Marks";
	cout<<"\n\nEnter your choice (1/2/3/4/5/6) : ";
	cin>>choice;
	cout<<"\n\n";
	ques tomodify;
	fstream fp("question.txt",ios::in |ios::out | ios::binary);
	fp.seekg(0,ios::beg);
	while(!fp.eof())
	{
		streampos pos=fp.tellg();
		fp.read((char *)&tomodify,sizeof(struct ques));
		if (tomodify.qID==id)
		{
			modified=true;
			switch(choice)
			{
				case 1:
					cout<<"Question Text : "<<tomodify.question;
					cout<<"\nEnter new value : ";
					gets(tomodify.question);
					break;
				case 2:
					cout<<"1st Option : "<<tomodify.opt1;
					cout<<"\nEnter new value : ";
					gets(tomodify.opt1);
					break;
				case 3:
					cout<<"2nd Option : "<<tomodify.opt2;
					cout<<"\nEnter new value : ";
					gets(tomodify.opt2);
					break;
				case 4:
					cout<<"3rd Option : "<<tomodify.opt3;
					cout<<"\nEnter new value : ";
					gets(tomodify.opt3);
					break;
				case 5:
					cout<<"4th Option : "<<tomodify.opt4;
					cout<<"\nEnter new value : ";
					gets(tomodify.opt4);
					break;
				case 6:
					cout<<"Correct Option : "<<tomodify.correctOption;
					cout<<"\nEnter new value (1/2/3/4) : ";
					cin>>tomodify.correctOption;
					break;
				case 7:
					cout<<"Allotted Marks : "<<tomodify.allotedMarks;
					cout<<"\nEnter new value (out of 5) : ";
					cin>>tomodify.allotedMarks;
					break;
				default : cout<<"\n\nWrong Input!!!";
					Sleep(2000);
			}
			fp.seekp(pos);
			fp.write((char *)&tomodify,sizeof(struct ques));
			break;
		}
		else
		{
			fp.seekp(pos);
			fp.write((char *)&tomodify,sizeof(struct ques));
		}
	}
	fp.close();
	if(!modified)
	{
		cout<<"\n\nNo Question with this question ID exist!!!";
		Sleep(2000);
	}
	return;	
}

void addQuestion()
{
	getchar();
	
	ques toAdd;
	char confirm='N';
	while(confirm!='Y')
	{
		system("cls");
		cout<<"\nAdd New Questions\n\n";
		cout<<"\nQuestion Id (4 digits)      : ";
		cin >>toAdd.qID;
		getchar();
		cout<<"\nQuestion Text (max 50 char) : ";
		gets(toAdd.question);
		cout<<"\n1st Option (max 50 char)    : ";
		gets(toAdd.opt1);
		cout<<"\n2nd Option (max 50 char)    : ";
		gets(toAdd.opt2);
		cout<<"\n3rd Option (max 50 char)    : ";
		gets(toAdd.opt3);
		cout<<"\n4th Option (max 50 char)    : ";
		gets(toAdd.opt4);
		cout<<"\nCorrect Option (1/2/3/4)    : ";
		cin>>toAdd.correctOption;
		cout<<"\nallotted Marks (out of 5)   : ";
		cin>>toAdd.allotedMarks;
		cout<<"\n\nConfirm (Y/X) : ";
		cin>>confirm;
		
	}
	fstream fp;
	fp.open("question.txt",ios::app|ios::binary);
	fp.write((char *)&toAdd,sizeof(struct ques));
	fp.close();
	return;
	
	
	
}

void questionManage() 
{
	while(1)
	{
		system("cls");
		int choice;
		cout<<"Manage Questions\n\n";
		cout<<"\t1) Add New Questions\n";
		cout<<"\t2) Modify Existing Questions\n";
		cout<<"\t3) Delete Questions\n";
		cout<<"\t4) Print Question List\n";
		cout<<"\t5) Exit from this menu\n\n";
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1: addQuestion();
					break;
			case 2: modifyQuestion();
					break;
			case 3: deleteQuestion();
					break;
			case 4: printQuestions();
					break;
			case 5: return;
			default : cout<<"\n\nWrong Input!!!";
					Sleep(2000);
		}
	}
}

void administratorScreen()
{
	system("cls");
	char userName[30];
	char password[20];
	getchar();
	cout<<"Administrator Login\n\n";
	cout<<"User Name  : ";
	cin.getline(userName,30);
	cout<<"\nPassword  : ";
	cin.getline(password,20);
	if(!strcmp(userName,"Rohit Rana")&&!strcmp(password,"hello123"))
	{
		questionManage();
	}
	else
	{
		cout<<"\n\nWrong details!!!";
		Sleep(2000);
	}
	
}

void printResult(finalQues testQ[],char pName[80])
{
	getchar();
	system("cls");
	cout<<"\nFetching Result. Please wait.";
	Sleep(2000);
	float scoreMarks=0,totalMarks=0;
	for(int i=0;i<queno;i++)
	{
		if(testQ[i].chosenOption==testQ[i].correctOption)
		{
			scoreMarks+=testQ[i].allotedMarks;	
		}
		totalMarks+=testQ[i].allotedMarks;	
	}
	float percent=(scoreMarks/totalMarks)*10;
	system("cls");
	cout<<"\n";
	cout<<"Congratulations "<<pName<<" .You have completed the quiz.\n\n";
	cout<<"You have scored "<<percent<<" out of 10.\n\n";
	cout<<"Here are your answers";
	for(int i=0;i<queno;i++)
	{
		cout<<"\n\n";
		cout<<"Question Number :"<<i+1;
		cout<<"\nQuestion Text : ";
		puts(testQ[i].question);
		cout<<"\n\nAvalable Answers : ";
		cout<<"\n1) "<<testQ[i].opt1;
		cout<<"\n2) "<<testQ[i].opt2;
		cout<<"\n3) "<<testQ[i].opt3;
		cout<<"\n4) "<<testQ[i].opt4;
		cout<<"\n\nMarks allotted : "<<testQ[i].allotedMarks;
		cout<<"\nChosen Option : "<<testQ[i].chosenOption;
		cout<<"\nCorrect Option : "<<testQ[i].correctOption;
	}
	cout<<"\n\nYour final score "<<scoreMarks<<" out of "<<totalMarks;
	cout<<"\n\nPress any key to go to main menu ";
	getchar();
	return;
}

void runQuiz(char pName[80])
{
	getchar();
	system("cls");
	map<int,struct ques>questionSet;
	set<int>selectedQuestions;
	int i=0;
	ques question;
	fstream fp("question.txt",ios::in |ios::binary);
	while(fp.read((char *)&question,sizeof(struct ques)))	
		questionSet.insert({i++,question});
	fp.close();
	if(i<2*queno)
	{
		cout<<"\n\nThere are not enough questions!!! ";
		Sleep(2000);
		return ;
	}
	int totalQ=i;
	finalQues testQ[queno];
	cout<<"\nFetching Questions. Please wait.";
	for(int j=0;j<queno;)
	{
		srand(time(NULL));
		int no=rand()%totalQ;
		if(selectedQuestions.find(no)==selectedQuestions.end())
		{
			selectedQuestions.insert(no);
			ques temp=questionSet.at(no);
			testQ[j++].copy(temp);
		}
	}
	system("cls");
	cout<<"\n\n";
	for(int j=0;j<queno;j++)
	{
		cout<<"Question Number :"<<j+1;
		cout<<"\nQuestion Text : ";
		puts(testQ[j].question);
		cout<<"\n\nAvalable Answers : ";
		cout<<"\n1) "<<testQ[j].opt1;
		cout<<"\n2) "<<testQ[j].opt2;
		cout<<"\n3) "<<testQ[j].opt3;
		cout<<"\n4) "<<testQ[j].opt4;
		cout<<"\n\nMarks allotted : "<<testQ[j].allotedMarks;
		char lock='n';
		cout<<"\n";
		while(lock!='Y'&&lock!='y')
		{
			cout<<"\nEnter the correct answer : ";
			cin>>testQ[j].chosenOption;
			cout<<"\nLock it (Y/N) : ";
			cin>>lock;
			
		}
		cout<<"\n\n\n";
	}
	printResult(testQ,pName);
	return;

}

void startQuiz()
{
	char pName[80];
	char choice;
	getchar();
	system("cls");
	cout<<"\nWelcome to Simple Quiz Game..\n";
	cout<<"\nPlayer Name : ";
	gets(pName);
	cout<<"\nReady (Y/N) : ";
	cin>>choice;
	if(choice=='y'||choice=='Y')
	{
		runQuiz(pName);
	}
	return;
}

void openScreen()
{
	while(1)
	{
		system("cls");
		int option;
		cout<<"Welcome to Simple Quiz Game..\n\n";
		cout<<"Your Options\n\n";
		cout<<"\t1) Administer Quiz\n";
		cout<<"\t2) Attend the Quiz\n";
		cout<<"\t3) Exit\n\n";
		cout<<"Choose option : ";
		cin>>option;
		if(option==1)
		{
			administratorScreen();	
		}
		else if(option==2)
		{
			startQuiz();
		}
		else if(option==3)
		{
			break;
		}
		else
		{
			cout<<"\nWrong input!!!";
			Sleep(2000);
		}
	}
}
int main()
{
	openScreen();
	return 0;
}
