#pragma once
#include <iostream>
#include "account.h"
#include "debit_card.h"
#include <fstream>
#include <string.h>
using namespace std;

class Customer
{
    long long int id;
    char name[25], dob[11], address[50],password[20];
    Savings_account s;
    Current_account c;
public:
    Customer(int i=0);
    void owns();
    friend void update(char *);
    void display();
    char *get_name();
    static long long int generate_customer_id();
    friend int get_customer(Customer &,long long int,char *);
    friend int get_customer(Customer &,char *);
    void set_CurrentAccount(Current_account);
    void set_SavingAccount(Savings_account);
    Savings_account get_SavingsAccount();
    Current_account get_CurrentAccount();
};
char * Customer::get_name()
{
    return name;
}
Savings_account Customer::get_SavingsAccount()
{
    return this->s;
}
Current_account Customer::get_CurrentAccount()
{
    return this->c;
}
void Customer::set_CurrentAccount(Current_account acc)
{
    fstream obj;
    obj.open("customers.txt",ios::out | ios::in);
    int count=0;
    Customer cust(1);
    obj.read((char *)&cust,sizeof(cust));
    while(!obj.eof())
    {
        if(cust.id==this->id)
        {
            break;
        }
        count++;
        obj.read((char *)&cust,sizeof(cust));
    }
    obj.close();
    fstream obj2;
    obj2.open("customers.txt",ios::out | ios::in);
    this->c=acc;
    obj2.seekp(count*sizeof(cust),ios::beg);
    obj2.write((char *)this,sizeof(Customer));
    obj2.close();
}
void Customer::set_SavingAccount(Savings_account acc)
{
    fstream obj;
    obj.open("customers.txt",ios::out | ios::in);
    int count=0;
    Customer cust(1);
    obj.read((char *)&cust,sizeof(cust));
    while(!obj.eof())
    {
        if(cust.id==this->id)
        {
            break;
        }
        count++;
        obj.read((char *)&cust,sizeof(cust));
    }
    obj.close();
    fstream obj2;
    obj2.open("customers.txt",ios::out | ios::in);
    this->s=acc;
    obj2.seekp(count*sizeof(cust),ios::beg);
    obj2.write((char *)this,sizeof(Customer));
    obj2.close();

}
long long int Customer::generate_customer_id()
{
    ifstream obj("customers.txt");
    if(!obj.is_open())
    {
        return 1;
    }
    long long int count=0;
    Customer c(1);
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        obj.read((char *)&c,sizeof(c));
        count++;
    }
    obj.close();
    return count+1;
}
Customer::Customer(int i)
{
    if(i==0)
    {
        cout<<"\nEnter your Name    : ";
        cin>>name;
        cout<<"\nEnter you DOB      : ";
        cin>>dob;
        cout<<"\nEnter your Address : ";
        cin>>address;
        cout<<"\ngeneration customer-id...\n";
        id=Customer::generate_customer_id();
        cout<<"\nYour Customer ID : "<<id<<"  (IMPORTANT LOGIN-CREDENTIAL*)\n";
        cout<<"\nEnter Password For your Account : ";
        cin>>password;
        cout<<"\n\nAccount Creation Portal :\n\n";
        int opt;
        cout<<"\nCreate Your Savings Account (1 or 0) : ";
        cin>>opt;
        if(opt==1)
        {
            this->s.setup_account(this->name);
        }
        cout<<"\nCreate your Current Account (1 or 0) : ";
        cin>>opt;
        if(opt==1)
        {
            this->c.setup_account(this->name);
        }
    }
}
int get_customer(Customer &c,long long int id,char *ch)
{
    ifstream obj("customers.txt");
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        if(c.id==id && !strcmp(c.password,ch))
        {
            return 1;
        }
        else
        {
            obj.read((char *)&c,sizeof(c));
        }
    }
return 0;
}
int get_customer(Customer &c,char *owner)
{
    ifstream obj("customers.txt");
    obj.read((char *)&c,sizeof(c));
    while(!obj.eof())
    {
        if(!strcmp(owner,c.name))
        {
            return 1;
        }
        else
        {
            obj.read((char *)&c,sizeof(c));
        }
    }
    return 0;

}
void Customer::display()
{
    cout<<"\n-----------------------\n";
    cout<<"Name     : "<<name<<endl;
    cout<<"DOB      : "<<dob<<endl;
    cout<<"Address  : "<<address<<endl;
    if(this->s.get_AccountNum()!=-1)
    {
        cout<<"\nYour Savings Account Details : \n";
        Savings_account::get_account(s.get_AccountNum(),s);
        s.display();
    }
    if(this->c.get_AccountNum()!=-1)
    {
        cout<<"\nYour Current Account Details : \n";
        Current_account::get_account(c.get_AccountNum(),c);
        c.display();
    }
}

