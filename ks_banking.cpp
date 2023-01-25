#include<iostream>
#include<bits/stdc++.h>
#include<cstring>
using namespace std;

void date()
{
    time_t t = time(NULL);
struct tm tm = *localtime(&t);

cout<<"Time:"<< tm.tm_mday <<"-"<<tm.tm_mon + 1<<"-"<<tm.tm_year + 1900<<"  "<< tm.tm_hour<<":"<< tm.tm_min<<":"<<tm.tm_sec<<endl;
}

class stacks
{
public:
int a[100];
int top;
stacks()
{
    top=0;
}
void push(int x)
{
    a[top]=x;
    top++;
}
void display()
{
    for(int i=0;i<top;i++)
    {
        if(a[i]>0)
        {
            cout<<"+"<<a[i]<<" - Money received."<<endl;
        }
        else
        {
            cout<<a[i]<<" - Money transferred."<<endl;
        }
    }
    cout<<"                             Time:";
    date();
}

};
struct searching
{
    char uname[20];
    int uid;
    long umn;
    float bal;
    float debit;
    stacks his;

};

struct aSearch
{
    char aname[20];
    int aid;
};

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}




bool checkPassword(char name[],char password[])
{
    int l=strlen(name);
    char pass[20];
    for(int i=l-1;i>=0;i--)
    {
        pass[l-1-i]=name[i];
    }
    pass[l]='\0';
    if(strcmp(pass,password)==0)
        return true;
    return false;
}



void generatePassword(char name[])
{
    int l=strlen(name);
    char pass[20];
    for(int i=l-1;i>=0;i--)
    {
        pass[l-1-i]=name[i];
    }
    pass[l]='\0';
    cout<<pass;
}

class node
{
public:

    char cUsername[20];
    int cId;
    char cPassword[20];
    long cMn;
    float cbalance;
    float debit;
    stacks his;
    node* left;
    node* right;
};
node* root=NULL;

node* mini(node* root)
{
    if(root==NULL)
        return root;
    return mini(root->left);
}


node* deletion(node* &root,int key)
{
    if(root==NULL)
        return root;
    else if(key>root->cId)
        return deletion(root->right,key);
    else if(key<root->cId)
        return deletion(root->left,key);
    else
    {
        if(root->left==NULL&&root->right==NULL)
        {
            delete root;
            root=NULL;
            return root;
        }
        else if(root->right==NULL)
        {
            node*temp=root->left;
            delete root;
            return temp;

        }
        else if(root->left==NULL)
        {
            node*temp=root;
            root=root->right;
            delete temp;
            return root;

        }
        else
        {
            node* temp=mini(root->right);
            root->cId=temp->cId;
            return deletion(root->right,temp->cId);

        }
    }
}




node* searchFrom(node* root,int sid)
{
    if(root==NULL)
    {
        return root;
    }
    else if(sid>root->cId)
    {
        return searchFrom(root->right,sid);
    }
    else if(sid<root->cId)
    {
        return searchFrom(root->left,sid);
    }
    else
    {
        return root;
    }
}
node* insertIntobst(node* root,searching a)
{
    if(root==NULL)
    {
        node* newnode=new node();
        strcpy(newnode->cUsername,a.uname);
        newnode->cId=a.uid;
        newnode->cMn=a.umn;
        newnode->cbalance=a.bal;
        newnode->debit=a.debit;
        newnode->his=a.his;
        newnode->left=NULL;
        newnode->right=NULL;
        return newnode;
    }
    else if(a.uid>root->cId)
    {
        root->right=insertIntobst(root->right,a);
        return root;

    }
    else if(a.uid<root->cId)
    {
        root->left=insertIntobst(root->left,a);
        return root;
    }
    else
    {
        return root;
    }
}

void extract(node* &root)
  {
      ifstream infile;

      infile.open("Customer.dat");
      searching obj;

    while(infile.read((char*)&obj, sizeof(obj)))
    {
       root=insertIntobst(root,obj);

    }

    infile.close();

  }


void print(node* z)
{
    if(z!=NULL)
    {
        cout<<"Username: "<<z->cUsername<<endl<<endl;
        cout<<"ID: "<<z->cId<<endl<<endl;
        cout<<"Mobile no."<<z->cMn<<endl<<endl;
        cout<<"Balance :"<<z->cbalance<<endl<<endl;
        cout<<"Debited amount: "<<z->debit<<endl<<endl;
       // print(z->left);
       // print(z->right);
    }
    else
    {
        cout<<"Does not exist."<<endl;
    }
}

void reflect(node* &root)
{
    if(root==NULL)
        {
            return;
        }

    ofstream outfile;
    outfile.open("Customer.dat", ios::binary | ios::app);

    searching obj;

    strcpy(obj.uname,root->cUsername);
    obj.uid=root->cId;
    obj.umn=root->cMn;
    obj.bal=root->cbalance;
    obj.debit=root->debit;
    obj.his=root->his;
    outfile.write((char*)&obj, sizeof(obj));
    outfile.close();
    reflect(root->left);
    reflect(root->right);


}
class admin
{
public:
    char aUsername[20];
    int aId;
    char aPassword[20];

    void details()
    {
        int ID;
        cout<<"Enter the id of the customer: "<<endl;
        cin>>ID;
        node* z=searchFrom(root,ID);
        if(z==NULL)
        {
            cout<<"ID does not match"<<endl;
        }
        else
        {
        print(z);
        }
        asubmenu();
    }

    void deletefrom()
    {
        int ID;
        cout<<"Enter the id of customer:"<<endl;
        cin>>ID;
        node* z=searchFrom(root,ID);
        if(z==NULL)
        {
            cout<<"ID does not match"<<endl;
        }
        else
        {
            deletion(root,ID);
            cout<<endl<<endl<<"Customer account deleted Successfully."<<endl;
            remove("Customer.dat");
            reflect(root);

        }
        asubmenu();
    }



    void asubmenu()
    {
        cout<<"Please choose from the following services."<<endl;
        cout<<"1. View customer details."<<endl;
        cout<<"2. Delete customer account."<<endl;
        cout<<"3. Log out.    "<<endl;
        cout<<"4. Go Back."<<endl;
        int opt2;
        label:
            cout<<"Enter the option ";
            cin>>opt2;

        if(opt2==1)
        {
            details();
        }
        else if(opt2==2)
        {
           deletefrom();
        }

        else if(opt2==3)
        {
            cout<<"Are you sure!!"<<endl;
            delay(2000);
            cout<<endl<<endl<<"You are logged off"<<endl;
            cout<<"See you Soon!"<<endl;
            remove("Customer.dat");
            reflect(root);
            //root=NULL;
            //extract(root);
            //exit(0);
            amenu();
        }
        else if(opt2==4)
        {
            amenu();
        }

        else
        {
            cout<<"Option invalid!"<<endl;
            goto label;
        }

    }

 void amenu()
{

    cout<<"1. New admin."<<endl;
    cout<<"2. Already our Admin?"<<endl;
    cout<<"3. Exit this terminal!"<<endl;
    delay(1000);
    cout<<"Please choose from the above options. "<<endl;
     int opt1;
    label:
    cin>>opt1;
    if(opt1==1)
    {
        addAdmin();
    }
    else if(opt1==2)
    {
        loginIn();
    }
    else if(opt1==3)
    {
        cout<<"See you soon!"<<endl;
        delay(3000);
        exit(0);
    }
    else
    {
        cout<<"Option not valid!    "<<endl;
        cout<<"Choose another one"<<endl;
        goto label;
    }


}



    void addAdmin()
    {
        cout<<"Welcome!"<<endl;
        cout<<"Enter username"<<endl;
        cin>>aUsername;
        srand((unsigned)time(0));
        aId=100000+rand();
        delay(1000);
        cout<<"Your unique ID is: "<<aId<<endl;
        cout<<"Your password is:"<<endl;
        generatePassword(aUsername);
        cout<<endl<<endl<<"Admin added successfully."<<endl;


        ofstream outFile;
        outFile.open("admin.dat", ios::binary | ios::app);

        aSearch obj;

        strcpy(obj.aname,aUsername);
        obj.aid=aId;

        outFile.write((char*)&obj, sizeof(obj));
        outFile.close();
        asubmenu();

    }

    void loginIn()
    {
        bool flag=false;
        bool check=false;
        cout<<"Enter username"<<endl;
        cin>>aUsername;
        cout<<"Enter unique ID :"<<endl;
        cin>>aId;
        cout<<"Enter your unique password is"<<endl;
        cin>>aPassword;
        flag=checkPassword(aUsername,aPassword);
        ifstream inFile;

       inFile.open("admin.dat");
       aSearch obj;

        while(inFile.read((char*)&obj, sizeof(obj)))
        {
        if(obj.aid==aId)
        {
          check=true;
        }
        }

        inFile.close();
        if(flag==true && check==true )
        {
            asubmenu();
        }
        else
        {
            cout<<"Admin does not exist"<<endl;
            amenu();
        }

    }
};



class customer
{
public:
    char cUsername[20];
    int cId;
    char cPassword[20];
    long cMn;
    float cbalance;
    float debit;
    stacks his;

void balance(int id)
{
   node* x=NULL;
   x=searchFrom(root,id);
   cout<<"Balance of the provided account is"<<endl;
   cout<<x->cbalance<<"."<<endl<<endl<<endl<<endl;

   if(x->cbalance<=2000)
   {
       cout<<"Kindly deposit some amount to your account."<<endl;
   }
   delay(1000);
   menu(x->cUsername,id);

}

void transfer(int id)
{
    int tid,am;
    cout<<"Enter the ID of account you want to transfer money: "<<endl;
    cin>>tid;
    if(tid==id)
    {
        cout<<"*****Self-transfer*****"<<endl;
    }
    else
        cout<<"*****Third-Party transfer*****"<<endl;
    node* x=searchFrom(root,tid);
    node* y=searchFrom(root,id);
    if(x==NULL)
    {
        cout<<"Wrong ID"<<endl;
    }
    else
    {
        cout<<"Enter the amount you want to transfer: "<<endl;
        cin>>am;
        if(am>y->cbalance)
        {
            cout<<"INSUFFICIENT BALANCE!!"<<endl;
            delay(1000);
            menu(y->cUsername,id);
        }
        else
        {
        x->cbalance+=am;
        y->cbalance-=am;

        cout<<endl<<endl<<"Transaction Successfull."<<endl<<endl<<endl;
        y->his.push(-am);
        x->his.push(am);
        cout<<am<<" amount is successfully transferred to account with id: "<<tid<<"."<<endl<<endl;
        cout<<"Your current account balance is:"<<y->cbalance<<"."<<endl<<endl<<endl;
        }

    }
    delay(1000);
    menu(y->cUsername,id);
}

void history(int id)
{
    node* x=searchFrom(root,id);
    cout<<"All your last transaction as per time are:"<<endl<<endl<<endl;
    x->his.display();
    delay(1000);
    menu(x->cUsername,id);
}


void loan(int id)
{
    node* loan=searchFrom(root,id);
    if(loan->cbalance<=2000 || loan->debit>0)
    {
        cout<<"Sorry you are not eligible for the same."<<endl<<endl;
    }
    else
    {
        int opt;
        cout<<loan->debit;
        cout<<"Enter the amount you want from bank"<<endl;
        cin>>loan->debit;
        loan->cbalance+=loan->debit;
        cout<<"You will be charged 8.25% p.a. for this amount."<<endl;
        cout<<"Kindly pay the interest timely else penalty will charged. "<<endl<<endl;
        cout<<"Enter '1' if you want to proceed or '2' if you wanna go back."<<endl;
        cin>>opt;
        if(opt==1)
        {
            loan->cbalance-=loan->debit*0.0764;
            cout<<"Interest for 1st month is deducted."<<endl;
        }
        else if(opt==2)
        {
            delay(1000);
            menu(loan->cUsername,id);
        }
        cout<<"Loan approved."<<endl;
        cout<<"Your current account balance is:"<<loan->cbalance<<endl<<endl<<endl;
        delay(1000);

    }
     menu(loan->cUsername,id);


}


void addMoney(int id)
{
    node* x=searchFrom(root,id);
    int am;
    cout<<endl<<"Enter the amount you want to add."<<endl;
    cin>>am;
    x->cbalance+=am;
    cout<<endl<<endl<<"Money added successfully."<<endl;
    x->his.push(am);
    cout<<endl<<"Your current balance is: "<<x->cbalance<<endl;
    delay(1000);
    menu(x->cUsername,id);


}
void submenu()
{

    cout<<"1. Account Opening Services."<<endl;
    cout<<"2. Loan Service."<<endl;
    cout<<"3. Refill loan amount."<<endl;
    cout<<"4. Already our customer?"<<endl;
    cout<<"5. Exit this terminal!"<<endl;
    delay(1000);
    cout<<"Please choose from the above options. "<<endl;
     int opt1;
    label:
    cin>>opt1;
    if(opt1==1)
    {
        cSingup();
    }
    else if(opt1==4||opt1==3)
    {
        login();
    }
    else if(opt1==2)
    {
        cout<<"Login First!"<<endl;
        login();
    }
    else if(opt1==5)
    {
        cout<<"See you soon!"<<endl;
        delay(3000);
        remove("Customer.dat");
        reflect(root);
        exit(0);
    }
    else
    {
        cout<<"Option not valid!    "<<endl;
        cout<<"Choose another one"<<endl;
        goto label;
    }


}
void goBack(char name[],int id)
{
    cout<<"1. Loan Service."<<endl;
    cout<<"2. Refill loan amount."<<endl;
    cout<<"3. Exit this terminal!"<<endl;
    delay(1000);
    cout<<"Please choose from the above options. "<<endl;
     int opt1;
    label:
    cin>>opt1;
    if(opt1==2)
    {
        cout<<"Login first"<<endl;
        login();
    }
    else if(opt1==1)
    {
        loan(id);
    }
    else if(opt1==3)
    {
        cout<<"See you soon!"<<endl;
        delay(3000);
        remove("Customer.dat");
        reflect(root);
        exit(0);
    }
    else
    {
        cout<<"Option not valid!    "<<endl;
        cout<<"Choose another one"<<endl;
        goto label;
    }


}



   void menu(char name[],int id)
    {
        extract(root);
        cout<<"Please choose from the following services."<<endl;
        cout<<"1. View Account Balance."<<endl;
        cout<<"2. Transfer Money."<<endl;
        cout<<"3. View Transaction History."<<endl;
        cout<<"4. Apply for loan."<<endl;
        cout<<"5. Add money. "<<endl;
        cout<<"6. Log out.    "<<endl;
        cout<<"7. Go Back."<<endl;
        int opt2;
        label:
            cout<<"Enter the option ";
            cin>>opt2;

        if(opt2==1)
        {
            balance(id);
        }
        else if(opt2==2)
        {
           transfer(id);
        }
        else if(opt2==3)
        {
           history(id);
           remove("Customer.dat");
           reflect(root);
           exit(0);
        }
        else if(opt2==5)
        {
            addMoney(id);
        }
        else if(opt2==6)
        {
            cout<<"Are you sure!!"<<endl;
            delay(2000);
            cout<<endl<<endl<<"You are logged off"<<endl;
            cout<<"See you Soon!"<<endl;
           remove("Customer.dat");
           reflect(root);
           //root=NULL;
           //extract(root);
           submenu();
            //exit(0);
        }
        else if(opt2==4)
        {
            loan(id);
        }
        else if(opt2==7)
        {
            goBack(name,id);
        }
        else
        {
            cout<<"Option invalid!"<<endl;
            goto label;
        }
}



    void cSingup()
    {
        cout<<"Enter Username"<<endl;
        cin>>cUsername;
        srand((unsigned)time(0));
        cId = 60000+rand();
        delay(1000);
        cout <<"Your unique ID is:"<<endl;
        cout<<cId<<endl;
        delay(1000);
        cout<<"Enter your mobile number"<<endl;
        cin>>cMn;
        delay(1000);
        cout<<"Enter the amount you want to add"<<endl;
        cin>>cbalance;
        cout<<"You unique password for your account is"<<endl;
        generatePassword(cUsername);
        debit=0;

        searching obj;

        strcpy(obj.uname,cUsername);
        obj.uid=cId;
        obj.umn=cMn;
        obj.bal=cbalance;
        obj.debit=debit;
        root=insertIntobst(root,obj);

        cout<<endl<<"Thank You for signing In"<<endl<<endl;
        menu(cUsername,cId);


    }


    void login()
    {
        long Id;
        bool flag=false;
        cout<<"Enter Username"<<endl;
        cin>>cUsername;
        cout <<"Enter your unique ID :"<<endl;
        cin>>Id;
        cout<<"Enter your unique password "<<endl;
        cin>>cPassword;
        flag=checkPassword(cUsername,cPassword);
        node* x=searchFrom(root,Id);
        if(flag==true && x!=NULL)
        {
            cout<<"You are successfully logged IN"<<endl<<endl;
            delay(1000);
            if(x->debit>0)
            {
                int am;
                cout<<"Kindly refill your previous loan amount,you are not allowed to carry-out our feature."<<endl;
                cout<<"The amount to be deposited is:"<<x->debit<<endl;
                cout<<"Enter the amount you want to deposit "<<endl;
                cin>>am;
                if(am>x->cbalance)
                {
                    cout<<"Make sure you have sufficient balance."<<endl<<endl<<endl;
                    goBack(cUsername,Id);
                }
                else
                {
                    x->cbalance-=am;
                    x->debit-=am;
                    x->his.push(-am);
                    cout<<"REFILLED amount: "<<am<<endl;
                    cout<<"Your current account balance is: "<<x->cbalance<<endl;
                    cout<<"Thanking You"<<endl;
                }
            }
            menu(cUsername,Id);

        }
        else
        {
            cout<<"Your password is incorrect OR id does not match."<<endl;
            cout<<"Try Again!"<<endl;
            submenu();
        }

    }
};
int main()
{
    int ua;
    extract(root);
    cout<<" STATE BANK OF INDIA "<<endl<<endl;
    delay(2000);
    cout<<" WELCOME!! "<<endl<<endl;
    cout<<" Now, Have a look at our friendly services:"<<endl;
    delay(2000);
    customer user;
    admin a;
    cout<<" Enter 1 if Admin or any other for customer."<<endl;
    cin>>ua;

    if(ua==1)
    {
        a.amenu();
    }
    else
    {
        user.submenu();
    }
      reflect(root);
    return 0;

}
