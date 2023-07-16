//PROJECT SUPERMARKET

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>

class STOCK
{ char item[20];
  long icode;
  float price;
  long qty;
  public:
   void display();
   void OOS(int);
   void SM_display();
   void FindITEM();
   void enter();
   long geticode()
   { return icode;}
   float getprice()
   { return price;}
   char *getitem()
   { return item;}
}S;
//enter stock

void STOCK::enter()
{
   cout<<"\nITEM: ";gets(item);
   cout<<"PRICE: ";cin>>price;
   cout<<"BARCODE: ";cin>>icode;
   cout<<"QTY: ";cin>>qty;
}

//display stock

void STOCK::display()
{
  cout<<"ITEM: "<<item<<"\nPRICE: "<<price<<"\nBARCODE: "<<icode
      <<"\nQTY: "<<qty<<endl<<endl;
}

//create file

void SMFile()
{ char ch;
  do
  {
    ofstream fout("SupMar.dat",ios::binary|ios::app);
    S.enter();
    fout.write((char*)&S,sizeof(STOCK));
    fout.close();
    cout<<"Do you want to add more items:";
    ch=getch();
  }while(int(ch)!=13);
}

//insert new stock

void SMinst()
{ STOCK Snew;
  ofstream fout("SupMar.dat",ios::binary|ios::app);
  Snew.enter();
  fout.write((char*)&Snew,sizeof(STOCK));
  fout.close();
}

//modify stock

void SMmody()
{ STOCK Sold; long bcode;int found=0;
  fstream f("SupMar.dat",ios::binary|ios::in|ios::out);
  cout<<"\n\n\n\tBARCODE of the item to be modified: ";cin>>bcode;
  while(f.read((char*)&Sold,sizeof(STOCK))&& !found)
  { if(bcode==Sold.geticode())
    { Sold.enter();
      f.seekp(-1*int(sizeof(STOCK)),ios::cur);
      f.write((char*)&Sold,sizeof(STOCK));
      found=1;
    }
  }
  f.close();
}

//delete stock

void SMDelt()
{ STOCK Sdel;
  fstream fin,fout;
  fin.open("SupMar.dat",ios::binary|ios::in);
  fout.open("Tmp.dat",ios::binary|ios::out);
  int BCd;
  cout<<"Input BARCODE of the ITEM to be deleted: ";
  cin>>BCd;
  while(fin.read((char*)&Sdel,sizeof(STOCK)))
  { if(BCd!=Sdel.geticode())
     fout.write((char*)&Sdel,sizeof(STOCK));
  }
  fin.close();
  fout.close();
  remove("SupMar.dat");
  rename("Tmp.dat","SupMar.dat");
}

//display full stock

void STOCK::SM_display()
{ ifstream fin("SupMar.dat",ios::binary);
  cout<<"\n\n\n\t\t\t\tSTOCK DETAILS\n\n";
  while(fin.read((char*)&S,sizeof(STOCK)))
  { display();
    cout<<endl<<endl;
  }
  fin.close();
}

//find item

void STOCK::FindITEM()
{
  cout<<"\n\n\tInput BARCODE of the ITEM:";
  int bcode,found=0;
  cin>>bcode;
  ifstream fin("SupMar.dat",ios::binary);
  while(fin.read((char*)&S,sizeof(STOCK)))
  { if(bcode==icode)
       display();
       found=1;
  }
  if(found==0)
    cout<<"\n\n\n\t\tITEM NOT FOUND!!";

  fin.close();
}

//stock decrement fn

void STOCK::OOS(int no)
{ qty-=no;
  if(qty<=10)
   cout<<item<<" running out of stock!!\n\n\n ";
  else
   cout<<"\n\t\tQTY: "<<qty<<endl;
   fstream f("SupMar.dat",ios::binary|ios::in|ios::out);
   STOCK r;
   while(f.read((char*)&r,sizeof(STOCK)))
   {
     if(r.geticode()==icode)
     {  f.seekg(-1*int(sizeof(STOCK)),ios::cur);
	f.write((char*)this,sizeof(STOCK));
	break;
     }

   }
   f.close();

}

//billing fn

void E_BILLING()
{ int bc,no,a=0;float amt=0,tot=0;  char ch=' ';
    ifstream fin("SupMar.dat",ios::binary);
 do
 {  cout<<"\n\nBCo:\b\b\b\b";
    cin>>bc;
    cout<<"\nNo:\b\b\b\b";cin>>no;int Found=0;  char item;
    while(fin.read((char*)&S,sizeof(STOCK)))
    {
      if(bc==S.geticode()&&!Found)
      { //cout<<"icode= "<<S.geticode()<<endl;
	amt=no*S.getprice();
	tot+=amt;
	Found=1;
	S.OOS(no);
       //++Found;
       //fin.seekg(-1*int(sizeof(STOCK)),ios::cur);
	cout<<"  "<<++a<<"\t"<<S.getitem();
	cout<<"\t"<<no<<"\t"<<S.getprice()<<"\t"<<no*S.getprice()<<endl;
	break;
      }
      getch();
    }
    fin.seekg(0,ios::beg);
    cout<<"\n Next item?";ch=getch();
  }while(int(ch)!=13);
   cout<<"\nTOTAL= "<<tot;
}

//CASHIER: Employee details

class Employee
{ int Eno;
  char name[25];
  float Sal; int yrs;
  public:
      void input();
      void show();
      int GetEno()
      { return Eno;}
      int Getyrs()
      { return yrs;}
      void chanSal(float s=2000)
      { Sal+=s;}
}E;

 //enter emp

void Employee::input()
{ cout<<"Input Eno: ";cin>>Eno;
  cout<<"Input Ename: ";gets(name);
  cout<<"Input salary: ";cin>>Sal;
  cout<<"Input experience: ";cin>>yrs;
}

//show emp

void Employee::show()
{ cout<<"\n\n\t\tEno: "<<Eno<<"\n\t\tName: "<<name<<"\n\t\tSalary: "
      <<Sal<<"\n\t\tExperience: "<<yrs;
}

//file emp create

void wEmpFile()
{
  char ch;
  do
  { ofstream fout("SupEmp.dat",ios::binary|ios::app);
    E.input();
    fout.write((char*)&E,sizeof(Employee));
    fout.close();
    cout<<" Add more?";ch=getch();
  }
  while(int(ch)!=13);

}
// read file

void rEmpFile()
{
  textcolor(GREEN);cout<<endl<<endl<<endl;
  cputs("                    EMPLOYEE DETAILS");
    ifstream fin("SupEmp.dat",ios::binary);
  while(fin.read((char*)&E,sizeof(Employee)))
  {
   if(E.Getyrs()>=5)
      E.chanSal(2000);
   E.show();
  }
  fin.close();
}

//Emp search

void SearchEno()
{ int eno;
  cout<<"Input ENO: ";cin>>eno;
  ifstream fin("SupEmp.dat",ios::binary);
  while(fin.read((char*)&E,sizeof(Employee)))
  { if(eno==E.GetEno())
      { if(E.Getyrs()>=5)
	  E.chanSal(2000);
	E.show();
      }
  }
  fin.close();
}

//main fn

void main()
{
  clrscr();
  textcolor(YELLOW);
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n  ";
  cout<<"\n\n\n\t    ********************************************************\n"
      <<"\t    *                                                      *\n"
      <<"\t    *                                                      *\n"
      <<"\t    *                                                      *\n"
      <<"\t    *                                                      *\n";
     cputs("                          WELCOME TO EZGo SUPERMARKET                     ");
     cout <<"\t          *                                                      *\n"
      <<"\t    *                                                      *\n"
      <<"\t    *                                                      *\n"
      <<"\t    *                                                      *\n"
      <<"\t    ********************************************************";
  getch();clrscr();gotoxy(39,11);textcolor(GREEN);
  cputs("USER");
  cout<<"\n\n\n\t\t\t\t1.OWNER\n\n\t\t\t\t2.CASHIER\n\n\t\t\t\t3.STAFF\n\n\t\t\t\t4.EXIT\n\n\n";
  cout<<"\t\tEnter choice:";
  int ch;
  cin>>ch;clrscr();
  switch(ch)
  {
    case 1: gotoxy(28,22); char PM[15];int i=0;char pch=' ';
	    cout<<"Enter password:";
	    while(1)
	    { pch=getch();
	      if(pch==13)
		  break;
	      cout<<"*";
	      PM[i]=pch;i++;
	    }
	     PM[i]='\0';
	     char ch1;
	     if(strcmp(PM,"superezgo")==0)
	     {do
	      { clrscr();
		gotoxy(33,11); textcolor(RED);int mch;
		cputs("MENU");
		cout<<"\n\n\n\t\t\t\t1.Create STOCK file\n\n\t\t\t\t2.Insert STOCK\n\n\t\t\t\t3.Modify STOCK\n\n\t\t\t\t4.Delete STOCK\n\n\n"
		    <<"\t\t\t\t5.View STOCK\n\n\t\t\t\t6.Find an ITEM\n\n\n\t\t\t\t7.Create EMPLOYEE file\n\n\t\t\t\t8.EMPLOYEE details"
		    <<"\n\n\t\t\t\t9.Search Employee\n\n\t\t\t\t10.EXIT\n\n\t\t Enter choice:";
		cin>>mch;
		clrscr();
		  switch(mch)
		  {
		    case 1:SMFile();break;
		    case 2:SMinst();break;
		    case 3:SMmody();break;
		    case 4:SMDelt();break;
		    case 5:S.SM_display();break;
		    case 6:S.FindITEM();break;
		    case 7:wEmpFile();break;
		    case 8:rEmpFile();break;
		    case 9:SearchEno();break;
		    case 10:clrscr();
			    gotoxy(35,22);
			    cout<<"THANK YOU!";
			    getch();
			    exit(0);
		  }cout<<"\n\t\t\t<<Back to MENU?";
		   cin>>ch1;
		 } while(ch1=='y');
	      }
	     else
	       { gotoxy(30,25);
		 textcolor(RED);
		 cputs("ACCESS DENIED!!");
	       }
	    break;
    case 2:gotoxy(28,22); char PC[15];i=0; pch=' ';
	    cout<<"Enter password:";
	    while(1)
	    { pch=getch();
	      if(pch==13)
		 break;
	      cout<<"*";
	      PC[i]=pch;i++;
	    }
	    PC[i]='\0';

	    if(strcmp(PC,"nameezgo")==0)
	    {do
	     {clrscr();
	      gotoxy(33,11); textcolor(RED);int cch;
	      cputs("MENU");
	      cout<<"\n\n\n\t\t\t\t1.Billing\n\n\t\t\t\t2.STOCK details\n\n\t\t\t\t3.EMPLOYEE details"
		  <<"\n\n\t\t\t\t4.Exit\n\n\t\tEnter choice:";cin>>cch;
		  switch(cch)
		  { case 1:clrscr();
			   E_BILLING();break;
		    case 2:clrscr();
			    S.SM_display();break;
		    case 3:clrscr();
			    rEmpFile();break;
		    case 4: clrscr();
			    gotoxy(35,22);
			    cout<<"THANK YOU!";
			    getch();
			    exit(0);
		  }
		 char ch;cin>>ch;
	       } while(ch==' ');
	      }
	     else
	       { gotoxy(30,25);
		 textcolor(RED);
		 cputs("ACCESS DENIED!!");
	       }

	   break;

    case 3:gotoxy(28,22); char PS[15];i=0; pch=' ';
	    cout<<"Enter password:";
	    while(1)
	    { pch=getch();
	       if(pch==13)
		  break;
		 cout<<"*";
	      PS[i]=pch;i++;
	    }
	    PS[i]='\0';

	    if(strcmp(PS,"ezgosupmar")==0)
	    {do
	     {clrscr();
	      gotoxy(33,11); textcolor(RED);int sch;
	      cputs("MENU");
	      cout<<"\n\n\n\t\t\t\t1.Billing\n\n\t\t\t\t2.View STOCK"
		  <<"\n\n\t\t\t\t3.Exit\n\n\t\tEnter choice:";cin>>sch;
		  switch(sch)
		  { case 1:clrscr();
			   E_BILLING();
			   break;
		    case 2:clrscr();
			    S.SM_display();
			    break;
		    case 3: clrscr();
			    gotoxy(35,22);
			    cout<<"THANK YOU!";
			    getch();
			    exit(0);

		  }
		char ch;cin>>ch;
	      } while(ch==' ');
	      }
	     else
	       { gotoxy(30,25);
		 textcolor(RED);
		 cputs("ACCESS DENIED!!");
	       }
	    break;
    case 4:clrscr();
	  gotoxy(35,22);
	   cout<<"THANK YOU!\n\n";
	   getch();
	   exit(0);

  }
   getch();
}
