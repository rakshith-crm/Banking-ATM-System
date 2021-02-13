#pragma once
#include "debit_card.h"
#include <iostream>
#include <string.h>
#include "transaction.h"
using namespace std;

class Account
{
protected:
    char type[10], owner[25];
public:
        static int generate_account();
};
class Current_account:public Account
{
    int account_number;
    float balance;
    Debit_card card;
public:
    Current_account()
    {
        account_number=-1;
        balance=-1;
    }
    Current_account(char *name)
    {
        strcpy(owner,name);
        strcpy(type,"current");
        account_number = Account::generate_account();
        cout<<"\nEnter initial deposit : ";
        cin>>balance;
        cout<<"\nDo you want a debit card : (1 or 0) : ";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            card.set_data(name,account_number,'c');
        }
        ofstream obj;
        obj.open("currentaccount.txt",ios::app);
        obj.write((char *)this,sizeof(Current_account));
        obj.close();
    }
    char * get_owner();
    int get_AccountNum();
    void display();
    int debit();
    int credit();
    int credit(float);
    int debit(float);
    void set_debitcard(Debit_card);
    static int get_account(int,Current_account &);
    void setup_account(char *);
};
int Current_account::debit(float in)
{
    if(in < balance-500.0)
    {
        balance -= in;
        ifstream obj("currentaccount.txt");
        Current_account ac;
        int count=0;
        obj.read((char *)&ac,sizeof(ac));
        while(!obj.eof())
        {
            if(ac.account_number==this->account_number)
            {
                break;
            }
            count++;
            obj.read((char *)&ac,sizeof(ac));
        }
        obj.close();
        fstream obj2;
        obj2.open("currentaccount.txt",ios::out | ios::in);
        obj2.seekp(count*sizeof(ac),ios::beg);
        obj2.write((char *)this,sizeof(ac));
        obj2.close();
        Withdrawl w(account_number,in,1);
        return 1;
    }
    else
    {
        cout<<"\n*** Insufficient Balance ***\n";
        return 0;
    }


}
int Current_account::credit(float in)
{
    balance += in;
    ifstream obj("currentaccount.txt");
    Current_account ac;
    int count=0;
    obj.read((char *)&ac,sizeof(ac));
    while(!obj.eof())
    {
        if(ac.account_number==this->account_number)
        {
            break;
        }
        count++;
        obj.read((char *)&ac,sizeof(ac));
    }
    obj.close();
    fstream obj2;
    obj2.open("currentaccount.txt",ios::out | ios::in);
    obj2.seekp(count*sizeof(ac),ios::beg);
    obj2.write((char *)this,sizeof(ac));
    obj2.close();
    Credited c(this->account_number,in,1);
    return 1;
}
char * Current_account::get_owner()
{
    return owner;
}
int Current_account::get_account(int ac,Current_account &c)
{
    ifstream obj("currentaccount.txt");
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        if(c.account_number==ac)
        {
            return 1;
        }
        else
        {
            obj.read((char *)&c,sizeof(c));
        }
    }
if(obj.eof())
{
    return 0;
}
}
void Current_account::set_debitcard(Debit_card card)
{
    fstream obj;
    obj.open("currentaccount.txt",ios::out | ios::in);
    int count=0;
    Current_account c;
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        if(c.account_number==this->account_number)
        {
            break;
        }
        count++;
        obj.read((char *)&c,sizeof(c));
    }
    obj.close();
    fstream obj2;
    obj2.open("currentaccount.txt",ios::out | ios::in);
    this->card=card;
    obj2.seekp(count*sizeof(c),ios::beg);
    obj2.write((char *)this,sizeof(Current_account));
    obj2.close();

}
int Current_account::get_AccountNum()
{
    return account_number;
}
void Current_account::setup_account(char *name)
{
    strcpy(owner,name);
    strcpy(type,"current");
    account_number = Account::generate_account();
    cout<<"\nEnter initial deposit : ";
    cin>>balance;
    cout<<"\nDo you want a debit card : (1 or 0) : ";
    int opt;
    cin>>opt;
    if(opt==1)
    {
        card.set_data(name,account_number,'c');
    }
    ofstream obj;
    obj.open("currentaccount.txt",ios::app);
    obj.write((char *)this,sizeof(Current_account));
    obj.close();

}
void Current_account::display()
{
    cout<<"\nAccount Owner   : "<<owner;
    cout<<"\nAccount type    : "<<type;
    cout<<"\nAccount Number  : "<<account_number;
    cout<<"\nAccount Balance : "<<balance;
    if(card.get_AccountNum()!=0)
    {
        cout<<"\n\nYour Debit Card Details :\n";
        Debit_card::get_card(card.get_cardNum(),card);
        card.display();
    }
}
int Current_account::credit()
{
    float in;
    cout<<"\nEnter Amount to be Credit : ";
    cin>>in;
    balance += in;
    ifstream obj("currentaccount.txt");
    Current_account ac;
    int count=0;
    obj.read((char *)&ac,sizeof(ac));
    while(!obj.eof())
    {
        if(ac.account_number==this->account_number)
        {
            break;
        }
        count++;
        obj.read((char *)&ac,sizeof(ac));
    }
    obj.close();
    fstream obj2;
    obj2.open("currentaccount.txt",ios::out | ios::in);
    obj2.seekp(count*sizeof(ac),ios::beg);
    obj2.write((char *)this,sizeof(ac));
    obj2.close();
    Credited c(this->account_number,in);
    return 1;

}

int Current_account::debit()
{
    float in;
    cout<<"\nEnter Amount to be Debited : ";
    cin>>in;
    if(in < balance-500.0)
    {
        cout<<"\nCollect your Cash\n";
        balance -= in;
        ifstream obj("currentaccount.txt");
        Current_account ac;
        int count=0;
        obj.read((char *)&ac,sizeof(ac));
        while(!obj.eof())
        {
            if(ac.account_number==this->account_number)
            {
                break;
            }
            count++;
            obj.read((char *)&ac,sizeof(ac));
        }
        obj.close();
        fstream obj2;
        obj2.open("currentaccount.txt",ios::out | ios::in);
        obj2.seekp(count*sizeof(ac),ios::beg);
        obj2.write((char *)this,sizeof(ac));
        obj2.close();
        Withdrawl w(account_number,in);
        return 1;
    }
    else
    {
        cout<<"\n*** Insufficient Balance ***\n";
        return 0;
    }

}

class Savings_account:public Account
{
    int account_number;
    float balance;
    Debit_card card;
public:
    Savings_account()
    {
        account_number=-1;
        balance=-1;
    }
    Savings_account(char *name)
    {
        strcpy(owner,name);
        strcpy(type,"savings");
        account_number = Account::generate_account();
        cout<<"\nEnter initial deposit : ";
        cin>>balance;
        cout<<"\nDo you want a debit card : (1 or 0) : ";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            card.set_data(name,account_number,'s');
        }
        ofstream obj;
        obj.open("savingaccount.txt",ios::app);
        obj.write((char *)this,sizeof(Savings_account));
        obj.close();
    }
    static int get_account(int,Savings_account &);
    void set_debitcard(Debit_card);
    int get_AccountNum();
    char * get_owner();
    void setup_account(char *);
    void display();
    int debit();
    int credit();
    int debit(float);
    int credit(float);
};
int Savings_account::credit(float in)
{
    balance += in;
    ifstream obj("savingaccount.txt");
    Savings_account ac;
    int count=0;
    obj.read((char *)&ac,sizeof(ac));
    while(!obj.eof())
    {
        if(ac.account_number==this->account_number)
        {
            break;
        }
        count++;
        obj.read((char *)&ac,sizeof(ac));
    }
    obj.close();
    fstream obj2;
    obj2.open("savingaccount.txt",ios::out | ios::in);
    obj2.seekp(count*sizeof(ac),ios::beg);
    obj2.write((char *)this,sizeof(ac));
    obj2.close();
    Credited c(account_number,in,1);
    return 1;
}
int Savings_account::debit(float in)
{
    if(in < balance-500.0)
    {
        balance -= in;
        ifstream obj("savingaccount.txt");
        Savings_account ac;
        int count=0;
        obj.read((char *)&ac,sizeof(ac));
        while(!obj.eof())
        {
            if(ac.account_number==this->account_number)
            {
                break;
            }
            count++;
            obj.read((char *)&ac,sizeof(ac));
        }
        obj.close();
        fstream obj2;
        obj2.open("savingaccount.txt",ios::out | ios::in);
        obj2.seekp(count*sizeof(ac),ios::beg);
        obj2.write((char *)this,sizeof(ac));
        obj2.close();
        Withdrawl w(account_number,in,1);
        return 1;
    }
    else
    {
        cout<<"\n*** Insufficient Balance ***\n";
        return 0;
    }

}
char * Savings_account::get_owner()
{
    return owner;
}
int Savings_account::get_account(int ac,Savings_account &c)
{
    ifstream obj("savingaccount.txt");
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        if(c.account_number==ac)
        {
            return 1;
        }
        else
        {
            obj.read((char *)&c,sizeof(c));
        }
    }
    if(obj.eof())
    {
        return 0;
    }
}
void Savings_account::set_debitcard(Debit_card card)
{
    fstream obj;
    obj.open("savingaccount.txt",ios::out | ios::in);
    int count=0;
    Savings_account c;
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        if(c.account_number==this->account_number)
        {
            break;
        }
        count++;
        obj.read((char *)&c,sizeof(c));
    }
    obj.close();
    fstream obj2;
    obj2.open("savingaccount.txt",ios::out | ios::in);
    this->card=card;
    obj2.seekp(count*sizeof(c),ios::beg);
    obj2.write((char *)this,sizeof(Savings_account));
    obj2.close();
}
int Savings_account::get_AccountNum()
{
    return account_number;
}
void Savings_account::setup_account(char *name)
{
    strcpy(owner,name);
    strcpy(type,"savings");
    account_number = Account::generate_account();
    cout<<"\nEnter initial deposit : ";
    cin>>balance;
    cout<<"\nDo you want a debit card : (1 or 0) : ";
    int opt;
    cin>>opt;
    if(opt==1)
    {
        card.set_data(name,account_number,'s');
    }
    ofstream obj;
    obj.open("savingaccount.txt",ios::app);
    obj.write((char *)this,sizeof(Savings_account));
    obj.close();
}
void Savings_account::display()
{
    cout<<"\nAccount Owner   : "<<owner;
    cout<<"\nAccount type    : "<<type;
    cout<<"\nAccount Number  : "<<account_number;
    cout<<"\nAccount Balance : "<<balance;
    if(card.get_AccountNum()!=0)
    {
        cout<<"\n\nYour Debit Card Details :\n";
        Debit_card::get_card(card.get_cardNum(),card);
        card.display();
    }
}
int Savings_account::credit()
{
    float in;
    cout<<"\nEnter Amount to be Credit : ";
    cin>>in;
    balance += in;
    ifstream obj("savingaccount.txt");
    Savings_account ac;
    int count=0;
    obj.read((char *)&ac,sizeof(ac));
    while(!obj.eof())
    {
        if(ac.account_number==this->account_number)
        {
            break;
        }
        count++;
        obj.read((char *)&ac,sizeof(ac));
    }
    obj.close();
    fstream obj2;
    obj2.open("savingaccount.txt",ios::out | ios::in);
    obj2.seekp(count*sizeof(ac),ios::beg);
    obj2.write((char *)this,sizeof(ac));
    obj2.close();
    Credited c(account_number,in);
    return 1;
}

int Savings_account::debit()
{
    float in;
    cout<<"\nEnter Amount to be Debited : ";
    cin>>in;
    if(in < balance-500.0)
    {
        cout<<"\nCollect your Cash\n";
        balance -= in;
        ifstream obj("savingaccount.txt");
        Savings_account ac;
        int count=0;
        obj.read((char *)&ac,sizeof(ac));
        while(!obj.eof())
        {
            if(ac.account_number==this->account_number)
            {
                break;
            }
            count++;
            obj.read((char *)&ac,sizeof(ac));
        }
        obj.close();
        fstream obj2;
        obj2.open("savingaccount.txt",ios::out | ios::in);
        obj2.seekp(count*sizeof(ac),ios::beg);
        obj2.write((char *)this,sizeof(ac));
        obj2.close();
        Withdrawl w(account_number,in);
        return 1;
    }
    else
    {
        cout<<"\n*** Insufficient Balance ***\n";
        return 0;
    }
}

int Account::generate_account()
{
    ifstream obj1("currentaccount.txt"),obj2("savingaccount.txt");
    int count1=0,count2=0;
    Current_account ca;
    Savings_account sa;
    if(obj1.is_open())
    {
        obj1.read((char *)&ca,sizeof(ca));
        while(!obj1.eof())
        {
            count1++;
            obj1.read((char *)&ca,sizeof(ca));
        }
        obj1.close();
    }
    if(obj2.is_open())
    {
        obj2.read((char *)&sa,sizeof(sa));
        while(!obj2.eof())
        {
            count2++;
            obj2.read((char *)&sa,sizeof(sa));
        }
    }
        return 1+count1+count2;
}
