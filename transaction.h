#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

class Transactions
{
protected:
    int transaction_id;
    int account_num;
    char trans_time[25], type [20];
public:
    static int generate_transac_id();
    static void display_all();
    static void display_transaction_of(int);
};
class Withdrawl:public Transactions
{
    float amount;
public:
    Withdrawl(int acc_num,float amount,int i=0);
    Withdrawl()=default;
    void display();
    static void display_all();
};

void Withdrawl::display_all()
{
    ifstream obj("transactionW.txt");
    if(obj.is_open())
    {
        Withdrawl w;
        obj.read((char *)&w,sizeof(w));
        while(!obj.eof())
        {
            w.display();
            obj.read((char *)&w,sizeof(w));
        }
    }
    else
    {
        cout<<"\n--No Withdrawal Details--\n";
    }
}

void Withdrawl::display()
{
    cout<<"\nTransaction-id      : "<<this->transaction_id;
    cout<<"\nTransaction Type    : "<<this->type;
    cout<<"\nTime of Transaction : "<<this->trans_time;
    cout<<"\nAccount Number      : "<<this->account_num;
    cout<<"\nTransaction Amount  : "<<this->amount<<endl<<endl;
}
Withdrawl::Withdrawl(int acc_num,float amount,int i)
{
    transaction_id=Transactions::generate_transac_id();
    if(i==0)
    {
        cout<<"\nYour Transaction-id : "<<transaction_id<<endl;
    }
    this->amount=amount;
    account_num=acc_num;
    time_t now = time(0);
    char *dt = ctime(&now);
    strcpy(trans_time,dt);
    strcpy(type,"withdraw/debit");
    ofstream obj;
    obj.open("transactionW.txt",ios::app);
    obj.write((char *)this,sizeof(Withdrawl));
}
class Credited: public Transactions
{
    float amount;
public:
    Credited(int acc_num,float amount,int i=0);
    Credited()=default;
    void display();
    static void display_all();
};
void Credited::display_all()
{
    ifstream obj("transactionC.txt");
    if(obj.is_open())
    {
        Credited w;
        obj.read((char *)&w,sizeof(w));
        while(!obj.eof())
        {
            w.display();
            obj.read((char *)&w,sizeof(w));
        }
    }
    else
    {
        cout<<"\n--No Credit Details--\n";
    }

}
void Credited::display()
{
    cout<<"\nTransaction-id      : "<<this->transaction_id;
    cout<<"\nTransaction Type    : "<<this->type;
    cout<<"\nTime of Transaction : "<<this->trans_time;
    cout<<"\nAccount Number      : "<<this->account_num;
    cout<<"\nTransaction Amount  : "<<this->amount<<endl;
}
Credited::Credited(int acc_num,float amount,int i)
{
    transaction_id=Transactions::generate_transac_id();
    if(i==0)
    {
        cout<<"\nYour Transaction-id : "<<transaction_id<<endl;
    }
    this->amount=amount;
    account_num=acc_num;
    time_t now=time(0);
    char *temp=ctime(&now);
    strcpy(trans_time,temp);
    strcpy(type,"credit");
    ofstream obj;
    obj.open("transactionC.txt",ios::app);
    obj.write((char *)this,sizeof(Credited));

}

class Transfer:public Transactions
{
    int to_account;
    float amount;
public:
    Transfer(int acc1,int to_acc,float amt);
    Transfer()=default;
    void display();
    static void display_all();
};
void Transfer::display_all()
{
    ifstream obj("transactionT.txt");
    if(obj.is_open())
    {
        Transfer w;
        obj.read((char *)&w,sizeof(w));
        while(!obj.eof())
        {
            w.display();
            obj.read((char *)&w,sizeof(w));
        }
    }
    else
    {
        cout<<"\n--No Transfer Details--\n";
    }

}
void Transfer::display()
{
    cout<<"\nTransaction-id      : "<<this->transaction_id;
    cout<<"\nTransaction Type    : "<<this->type;
    cout<<"\nTime of Transaction : "<<this->trans_time;
    cout<<"\nFrom Account        : "<<this->account_num;
    cout<<"\nTo Account          : "<<this->to_account;
    cout<<"\nTransaction Amount  : "<<this->amount<<endl;

}
Transfer::Transfer(int acc1,int to_acc,float amount)
{
    transaction_id=Transactions::generate_transac_id();
    cout<<"\nYour Transaction-id : "<<transaction_id<<endl;
    this->amount=amount;
    account_num=acc1;
    to_account=to_acc;
    time_t now=time(0);
    char *temp=ctime(&now);
    strcpy(trans_time,temp);
    strcpy(type,"transfer");
    ofstream obj;
    obj.open("transactionT.txt",ios::app);
    obj.write((char *)this,sizeof(Transfer));

}



//////////////////////////////////
int Transactions::generate_transac_id()
{
    ifstream obj1("transactionW.txt"),obj2("transactionC.txt"),obj3("transactionT.txt");
    int count1=0,count2=0,count3=0;
    if(obj1.is_open())
    {
        Withdrawl w;
        obj1.read((char *)&w,sizeof(w));
        while(!obj1.eof())
        {
            count1++;
            obj1.read((char *)&w,sizeof(w));
        }
    }
    if(obj2.is_open())
    {
        Credited w;
        obj2.read((char *)&w,sizeof(w));
        while(!obj2.eof())
        {
            count2++;
            obj2.read((char *)&w,sizeof(w));
        }
    }
    if(obj3.is_open())
    {
        Transfer w;
        obj3.read((char *)&w,sizeof(w));
        while(!obj3.eof())
        {
            count3++;
            obj3.read((char *)&w,sizeof(w));
        }
    }
    return 1000+count1+count2+count3;
}

void Transactions::display_all()
{
    cout<<"\nWithdrawal Details   : \n--------------------\n";
    Withdrawl::display_all();
    cout<<"\n\nCrediting Details : \n--------------------\n";
    Credited::display_all();
    cout<<"\n\nTransfer Details  : \n--------------------\n";
    Transfer::display_all();
    cout<<"\n\n";
}

void Transactions::display_transaction_of(int acc)
{
    cout<<"\nWithdrawal Details   : \n--------------------\n";
    ifstream obj1("transactionW.txt");
    int flag=0;
    if(obj1.is_open())
    {
        Withdrawl w;
        obj1.read((char *)&w,sizeof(w));
        while(!obj1.eof())
        {
            if(w.account_num==acc)
            {
                w.display();
                flag=1;
            }
            obj1.read((char *)&w,sizeof(w));
        }
    }
    if(flag==0)
    {
        cout<<"\n--No Withdrawal Details--\n";
    }
    cout<<"\n\nCrediting Details : \n--------------------\n";
    ifstream obj2("transactionC.txt");
    flag=0;
    if(obj2.is_open())
    {
        Credited w;
        obj2.read((char *)&w,sizeof(w));
        while(!obj2.eof())
        {
            if(w.account_num==acc)
            {
                w.display();
                flag=1;
            }
            obj2.read((char *)&w,sizeof(w));
        }
    }
    if(flag==0)
    {
        cout<<"\n--No Credit Details--\n";
    }

    cout<<"\n\n";
}
