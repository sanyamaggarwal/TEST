#include<bits/stdc++.h>
using namespace std;

#define MAX 100

typedef long long int lli;
static int nodeNum=0;
static int ownId=0;
lli genesisNodeVal;

struct date
{
    int day;
    int month;
    lli year;
};

struct data
{
    lli ownerId;
    float value;
    string ownerName;
    lli hashOfSet;
};
struct node
{
    time_t now=time(0);
    date d1;
    data d2;
    lli nodeNumber;
    string nodeId;
    node * referenceNodeId;
    node * childReferenceNodeId[MAX];
    node * genesisReferenceNodeId;
    string HashValue;
    lli kp=0; //...Indicates current number of children....//
};

//........FUNCTIONS IMPLEMENTED.....//

struct node *d;
void inorder(struct node *p);
void VerifyOwnership(lli newOwnerId,string hashValue,struct node *p,lli oldId);
void EditValueOfAnode(struct node *p,lli newVal,lli oldVal);
void TransferOwnership(lli newOwnerId,string hashValue,struct node *p,lli oldId);
string Encrypt(lli key,string str,lli n);
string Decrypt(lli key,string str,lli n);
node * insertion(struct node *root);
//......Finding appropriate parent for the node for insertion.......//
void inorder(struct node *p)
{

    if(p==NULL || p->childReferenceNodeId[p->kp]==NULL)
        return;
    else
    {
        //inorder(p->childReferenceNodeId[p->kp]);
        lli num,sum=0;
        lli n=p->kp;
        for(lli i=0;i<n;i++)
        {
            sum+=p->childReferenceNodeId[i]->d2.value;
        }
        sum+=p->d2.value;
        if(sum<genesisNodeVal)
        {
            d=p;
            return;
        }
        inorder(p->childReferenceNodeId[(p->kp)++]);
        return;
    }
    return;
}
//.........Verification OF Ownership........//

void VerifyOwnership(lli newOwnerId,string hashValue,struct node *p,lli oldId)
{
    lli len=hashValue.length();

    string str;
    string id=p->d2.ownerName;
    lli n=id.length();
    str=Decrypt(oldId,hashValue,n);
    string sd;
    lli i=0;

    for(i=n;i<len;i++)
    {
        sd[i]=str[i];
    }
    if(to_string(oldId)==sd)
    {
        cout<<"Ownership is valid\n";
    }
    else
    {
        cout<<"Ownership is invalid\n";
    }
}

//........Assumption ::: value can only be updated if sum of sibilings are less than parent..........//

void EditValueOfAnode(struct node *p,lli newVal,lli oldVal)
{
    struct node *q;
    q=p->referenceNodeId;
    lli val=q->d2.value;
    lli numOfchild=q->kp;
    lli sum=0;
    for(lli i=0;i<numOfchild;i++)
    {
        sum+=q->childReferenceNodeId[i]->d2.value;
    }
    sum=sum-oldVal;
    sum=sum-newVal;
    if(sum<val)
    {
        //......VALUE UPDATED......//
        p->d2.value=newVal;
        cout<<"Value updated successfully........\n";
    }
    else
        cout<<"Value cannot be updated.......\n";
}

//......Transfer OF Ownership.......//

void TransferOwnership(lli newOwnerId,string hashValue,struct node *p,lli oldId)
{
    lli len=hashValue.length();

    string str;
    string id=p->d2.ownerName;

    lli n=id.length();
    str=Decrypt(oldId,hashValue,n);

    string sd;
    lli i=0;

    for(i=n;i<len;i++)
    {
        sd[i]=str[i];
    }
    if(to_string(oldId)==sd)
    {
        p->d2.ownerId=newOwnerId;
        cout<<"Owner id changed\n";
        string s=Encrypt(p->d2.ownerId,str,p->d2.ownerName.length());
        p->HashValue=s;
    }
    else
    {
        cout<<"Ownership is invalid\n";
    }
}
//...Encryption and Decryption is done using Caesar Cipher Technique........////
string Encrypt(lli key,string str,lli n)
{
    lli len=str.length();
    for(lli i=0;i<len;i++)
    {
        lli x=str[i]+key;
        //x=x%26;
        str[i]=x;
    }
    return str;
}
string Decrypt(lli key,string str,lli n)
{
    lli len=str.length();
    for(lli i=1;i<n;i++)
    {
        lli x=str[i]-key;
        str[i]=x;
    }
    return str;
}
//......INSERTION OF A NEW NODE AND GENESIS NODE.......//
 node * insertion(struct node *root)
{
    string name;
    lli val;

    struct node *p;
    p=new node;

    cout<<"Enter Owner Name:";
    cin>>p->d2.ownerName;

    cout<<"Enter Node Value:";
    cin>>p->d2.value;

    p->nodeNumber=nodeNum++;
    p->d2.ownerId=ownId++;
    p->referenceNodeId=NULL;
    p->genesisReferenceNodeId=NULL;
    p->d2.hashOfSet=p->d2.ownerId;

    string id=to_string(p->d2.ownerId);
    string str=strcat(p->d2.ownerName,id);

    //.......Encryption and Decryption of data here....../
    string s=Encrypt(p->d2.ownerId,str,p->d2.ownerName.length());
    cout<<"Encrypted data is :"<<s<<"\n";
    string s1=Decrypt(p->d2.ownerId,str,p->d2.ownerName.length());
    cout<<"Decrypted data is :"<<s1<<"\n";

    p->HashValue=s;

    if(root==NULL)
    {
        // .....RETURNS THE POINTER TO THE GENESIS NODE........//
        genesisNodeVal=p->d2.value;
        return p;
    }
    else
    {
        //.......INSERTION OF A NODE........//
        inorder(root);
        d->childReferenceNodeId[(p->kp)++]=p;
        p->referenceNodeId=d;
        p->genesisReferenceNodeId=root;
    }
    return root;
}


int main()
{
    lli choice;
    struct node *root=NULL;

    struct node e;
    char* dt = ctime(&(e.now));
    cout << "The local date and time is: " << dt << endl;

    cout<<"1:INSERT\n"<<"2:ENCRYPT DATA IN NODE\n"<<"3:DECRYPT DATA IN NODE\n";
    cout<<"Enter choice:";
    cin>>choice;

    struct node obj;
    //............FUNCTIONS FOR THE GIVEN QUESTIONS HAVE BEEN CREATED ........//
    switch(choice)
    {
        case 1:
            root=insertion(root);
            break;
        case 2:
           /* lli n;
            cout<<"Enter key:";
            cin>>n;
            string s=Encrypt(lli key,string str,lli n)
            break;
        case 3:

            //Encrypt(p->h)*/
    }
}
