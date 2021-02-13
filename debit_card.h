#pragma once
#include <iostream>
#include <string.h>
#include "account.h"
#include <fstream>
using namespace std;

class Debit_card
{
    long long int card_no;
    int pin;
    int acc_no;
    char card_holder[25];
    char acc_type;
public:
    static long long int generate_cardnumber();
    Debit_card(char *,int,char);
    Debit_card();
    int access();
    void change_pin();
    char get_type();
    static int get_card(long long int,Debit_card &);
    static int get_card(char *,Debit_card &);
    void display();
    long long int get_cardNum();
    int get_AccountNum();
    void set_data(char *name,int,char);
};
long long int Debit_card::get_cardNum()
{
    return this->card_no;
}
char Debit_card::get_type()
{
    return this->acc_type;
}
int Debit_card::get_card(char *name,Debit_card &d)
{
    ifstream obj("debitcards.txt");
    if(!obj.is_open())
    {
        return 0;
    }
    obj.read((char *)&d,sizeof(d));
    while(!obj.eof())
    {
        if(!strcmp(d.card_holder,name))
        {
            return 1;
        }
        else
        {
            obj.read((char *)&d,sizeof(d));
        }
    }
if(!strcmp(d.card_holder,name))
{
    return 1;
}
else
{
    return 0;
}

}
int Debit_card::get_card(long long int card,Debit_card &d)
{
    ifstream obj("debitcards.txt");
    if(!obj.is_open())
    {
        return 0;
    }
    obj.read((char *)&d,sizeof(d));
    while(!obj.eof())
    {
        if(d.card_no==card)
        {
            return 1;
        }
        else
        {
            obj.read((char *)&d,sizeof(d));
        }
    }
if(d.card_no==card)
{
    return 1;
}
else
{
    return 0;
}
}
long long int Debit_card::generate_cardnumber()
{
    Debit_card d;
    long long int count=1000;
    ifstream obj("debitcards.txt");
    if(!obj.is_open())
    {
        return count;
    }
    obj.read((char *)&d,sizeof(d));
    while(!obj.eof())
    {
        count++;
        obj.read((char *)&d,sizeof(d));
    }
    return count;
}
Debit_card::Debit_card()
{
    card_no=0;
    card_holder[0]='\0';
    pin=-1;
    acc_type=0;
    acc_no=0;
}
int Debit_card::get_AccountNum()
{
    return acc_no;
}
void Debit_card::set_data(char *name,int ac,char type)
{
    this->acc_type=type;
    card_no = Debit_card::generate_cardnumber();
    cout<<"\nYour Card Number : "<<card_no;
    strcpy(card_holder,name);
    cout<<"\nEnter Your Pin : ";
    cin>>pin;
    this->acc_no=ac;
    ofstream obj;
    obj.open("debitcards.txt",ios::app);
    obj.write((char *)this,sizeof(Debit_card));
    obj.close();
}
Debit_card::Debit_card(char *name,int no,char type)
{
    this->acc_type=type;
    card_no = Debit_card::generate_cardnumber();
    cout<<"\nYour Card Number : "<<card_no;
    strcpy(card_holder,name);
    cout<<"\nEnter Your Pin : ";
    cin>>pin;
    while(!(pin>=1000 && pin<=9999))
    {
        cout<<"\nEnter a Valid Pin Number for your account : ";
        cin>>pin;
    }
    this->acc_no=no;
    ofstream obj;
    obj.open("debitcards.txt",ios::app);
    obj.write((char *)this,sizeof(Debit_card));
    obj.close();
}

void Debit_card::display()
{
    cout<<"Card No      : "<<card_no<<endl;
    cout<<"Account type : "<<acc_type<<endl;
    cout<<"Holder       : "<<card_holder<<endl;
//    cout<<"Pin          : "<<pin<<endl<<endl;

}

int Debit_card::access()
{
    int pin,count=4;
    cout<<"\nEnter your Pin : ";
    cin>>pin;
    while(1)
    {
        if(pin==this->pin)
        {
            return 1;
        }
        count--;
        if(count==0)
        {
            break;
        }
        cout<<"\nInvalid Pin...Re-Enter pin : ";
        cin>>pin;

    }
    cout<<"\nToo many Invalid Attempts...Contact your nearest branch !\n";
return 0;
}
void Debit_card::change_pin()
{
    if(access())
    {
        cout<<"\nEnter your new Pin : ";
        cin>>pin;
        fstream obj;
        obj.open("debitcards.txt",ios::out | ios::in);
        int count=this->card_no-1000;
        obj.seekp(count*sizeof(Debit_card),ios::beg);
        obj.write((char *)this,sizeof(Debit_card));
    }
}
