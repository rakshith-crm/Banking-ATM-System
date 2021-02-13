#include "account.h"
#include "customer.h"
#include "transaction.h"
#include "debit_card.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;


int main()
{
    int resp;
    while(1)
    {
        cout<<"\t\t----------------------ATM & BANK PORTAL----------------------\n";
        cout<<"\n(1)Enter as Customer\n(2)Enter Bank\n(3)ATM\n(4)Exit\n\nEnter your option : ";
        cin>>resp;
        if(resp==1)
        {
            int opt;
            cout<<"(1)Customer Login\n(2)New Customer(Sign-up)\n\nEnter your option : ";
            cin>>opt;
            if(opt==1)
            {
                char password[20];
                long long int id;
                Customer c(1);
                cout<<"\nEnter your ID  : ";
                cin>>id;
                cout<<"\nEnter Password : ";
                cin.ignore();
                cin.getline(password,20);
                int op=get_customer(c,id,password);
                if(op==1)
                {
                    cout<<"\nLogged-in Successfully\n";
                    cout<<"\n(1)Display Details\n(2)My Transactions\n(3)Transfer Money";
                    if(c.get_CurrentAccount().get_AccountNum()==-1)
                    {
                        cout<<"\n(4)Create Current Account";
                    }
                    if(c.get_SavingsAccount().get_AccountNum()==-1)
                    {
                        cout<<"\n(5)Create Savings Account";
                    }
                    cout<<"\n\nEnter your option : ";
                    int option;
                    cin>>option;
                    if(option==1)
                    {
                        cout<<"\nYour Account Details :\n\n";
                        c.display();
                    }
                    else if(option==2)
                    {
                        int opt;
                        cout<<"\n(1)Savings Account\n(2)Current Account\n\nEnter your option : ";
                        cin>>opt;
                        cout<<"\nYour Transaction Details : \n\n";
                        if(opt==1)
                        {
                            cout<<"Savings Account\n----------------\n";
                            Transactions::display_transaction_of(c.get_SavingsAccount().get_AccountNum());
                        }
                        else if(opt==2)
                        {
                            cout<<"\nCurrent Account\n----------------\n";
                            Transactions::display_transaction_of(c.get_CurrentAccount().get_AccountNum());
                        }
                        else
                        {
                            cout<<"\nInvalid Option\n";
                        }
                    }
                    else if(option==3)
                    {
                        if(c.get_SavingsAccount().get_AccountNum()!=-1)
                        {
                            cout<<"\n(1)Transfer from Savings Account\n";
                        }
                        if(c.get_CurrentAccount().get_AccountNum()!=-1)
                        {
                            cout<<"(2)Transfer from Current Account\n";
                        }
                        cout<<"\nEnter your option : ";
                        int oppp;
                        cin>>oppp;
                        if(oppp==1)
                        {
                            Savings_account my_account;
                            Savings_account::get_account(c.get_SavingsAccount().get_AccountNum(),my_account);
                            cout<<"\nEnter Account Number of the Recipient : ";
                            int to_account;
                            float amount;
                            cin>>to_account;
                            Current_account acc1;
                            Savings_account acc2;
                            int n1,n2;
                            n1=Current_account::get_account(to_account,acc1);
                            n2=Savings_account::get_account(to_account,acc2);
                            if(n1==1)
                            {
                                cout<<"\nEnter Amount to Transfer : ";
                                cin>>amount;
                                if(my_account.debit(amount))
                                {
                                    acc1.credit(amount);
                                    cout<<"\nTransfer Successful\n";
                                    Transfer t(my_account.get_AccountNum(),acc1.get_AccountNum(),amount);
                                }
                            }
                            if(n2==1)
                            {
                                cout<<"\nEnter Amount to Transfer : ";
                                cin>>amount;
                                if(my_account.debit(amount))
                                {
                                    acc2.credit(amount);
                                    cout<<"\nTransfer Successful\n";
                                    Transfer t(my_account.get_AccountNum(),acc2.get_AccountNum(),amount);
                                }
                            }
                            if(n1==0 && n2==0)
                            {
                                cout<<"\nRecipient Account Does not exist\nTransfer Failed!!\n";
                            }
                        }
                        else if(oppp==2)
                        {
                            Current_account my_account;
                            Current_account::get_account(c.get_CurrentAccount().get_AccountNum(),my_account);
                            cout<<"\nEnter Account Number of the Recipient : ";
                            int to_account;
                            float amount;
                            cin>>to_account;
                            Current_account acc1;
                            Savings_account acc2;
                            int n1,n2;
                            n1=Current_account::get_account(to_account,acc1);
                            n2=Savings_account::get_account(to_account,acc2);
                            if(n1==1)
                            {
                                cout<<"\nEnter Amount to Transfer : ";
                                cin>>amount;
                                if(my_account.debit(amount))
                                {
                                    acc1.credit(amount);
                                    cout<<"\nTransfer Successful\n";
                                    Transfer t(my_account.get_AccountNum(),acc1.get_AccountNum(),amount);
                                }
                            }
                            if(n2==1)
                            {
                                cout<<"\nEnter Amount to Transfer : ";
                                cin>>amount;
                                if(my_account.debit(amount))
                                {
                                    acc2.credit(amount);
                                    cout<<"\nTransfer Successful\n";
                                    Transfer t(my_account.get_AccountNum(),acc2.get_AccountNum(),amount);
                                }
                            }
                            if(n1==0 && n2==0)
                            {
                                cout<<"\nRecipient Account Does not exist\nTransfer Failed!!\n";
                            }
                        }
                    }
                    else if(option==4)
                    {
                        Current_account acc(c.get_name());
                        c.set_CurrentAccount(acc);
                    }
                    else if(option==5)
                    {
                        Savings_account acc(c.get_name());
                        c.set_SavingAccount(acc);
                    }
                }
                else
                {
                    cout<<"\nLogin Unsuccessful\n";
                }
            }
            else if(opt==2)
            {
                cout<<"\nEnter Your Details :\n";
                Customer c;
                ofstream obj;
                obj.open("customers.txt",ios::app);
                obj.write((char *)&c,sizeof(c));
                obj.close();
            }
        }
        else if(resp==2)
        {
            cout<<"(*) Display ";
            cout<<"\n\t(1)All Transactions\n\t(2)Credit Transactions\n\t(3)Debit Transactions\n\t(4)Transfer Transactions\n";
            cout<<"\nEnter your Option : ";
            int opt;
            cin>>opt;
            if(opt==1)
            {
                Transactions::display_all();
            }
            else if(opt==2)
            {
                cout<<"\n\nCrediting Details : \n--------------------\n";
                Credited::display_all();
            }
            else if(opt==3)
            {
                cout<<"\nWithdrawal Details   : \n--------------------\n";
                Withdrawl::display_all();
            }
            else if(opt==4)
            {
                cout<<"\n\nTransfer Details  : \n--------------------\n";
                Transfer::display_all();
            }
            else
            {
                cout<<"Invalid Option!\n\n ";
            }
        }
        else if(resp==3)
        {
            long long int card;
            cout<<"\nEnter Your Card Number : ";
            cin>>card;
            Debit_card my_card;
            if(Debit_card::get_card(card,my_card)==0)
            {
                cout<<"\nInvalid Debit Card Number! Contact your nearest branch\n";
            }
            else
            {
                if(my_card.access())
                {
                    cout<<"(1)Change Pin\n(2)Credit\n(3)Withdraw\n";
                    cout<<"\nEnter your option : ";
                    int opt;
                    cin>>opt;
                    if(opt==1)
                    {
                        my_card.change_pin();
                        char type=my_card.get_type();
                        if(type=='c')
                        {
                            cout<<"\nUpdated Account Info :\n";
                            Current_account acc;
                            Current_account::get_account(my_card.get_AccountNum(),acc);
                            acc.set_debitcard(my_card);
                            Customer cust(1);
                            cust=get_customer(cust,acc.get_owner());
                            cust.set_CurrentAccount(acc);
                        }
                        else if(type=='s')
                        {
                            cout<<"\nUpdated Account Info :\n";
                            Savings_account acc;
                            Savings_account::get_account(my_card.get_AccountNum(),acc);
                            acc.set_debitcard(my_card);
                            Customer cust(1);
                            cust=get_customer(cust,acc.get_owner());
                            cust.set_SavingAccount(acc);
                        }

                    }
                    else if(opt==2)
                    {
                        cout<<"\nCredit Option : \n";
                        char type=my_card.get_type();
                        if(type=='c')
                        {
                            Current_account acc;
                            Current_account::get_account(my_card.get_AccountNum(),acc);
                            acc.credit();

                        }
                        else if(type=='s')
                        {
                            Savings_account acc;
                            Savings_account::get_account(my_card.get_AccountNum(),acc);
                            acc.credit();
                        }
                    }
                    else if(opt==3)
                    {
                        char type=my_card.get_type();
                        if(type=='c')
                        {
                            Current_account acc;
                            Current_account::get_account(my_card.get_AccountNum(),acc);
                            acc.debit();
                        }
                        else if(type=='s')
                        {
                            Savings_account acc;
                            Savings_account::get_account(my_card.get_AccountNum(),acc);
                            acc.debit();

                        }
                    }
                    else
                    {
                        cout<<"\nInvalid Option...Exiting ATM\n";
                    }
                }
            }

        }
        else if(resp==4)
        {
            break;
        }
        else
        {
            cout<<"\nInvalid Option...\n";
        }
        cout<<"\nEnter any key to continue...";
        getch();
        system("cls");
    }
    return 0;
}
