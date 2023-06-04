#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#include<stdio.h>
#include<conio.h>

using namespace std;
class product
{
private:
int pId,pPrice,pQuantity;
string pName,pBrand;

protected:
void showheader();

public:
void purchase();
void getproduct();
void showproduct();
void addproduct();
void viewproduct();
void searchproduct();
void deleteproduct();
void updateproduct();

};
void product ::purchase()
{
int pid,quantity;
cout<<"\nEnter Product Id Of The Product You want to Purchase :";
cin>>pid;
cout<<"Enter Quantity ";
cin>>quantity;
int price,total;
fstream f;
f.open("product.txt",ios::in);
if(!f)
{
cout<<"file not found";
}
else
{
f.read((char*)this,sizeof(*this));
while(!f.eof())
{
if(this->pId==pid)
{
price=this->pPrice;
total=price*quantity;
cout<<"Your Total Amount is"<<total;
}
f.close();
}
}
}


void product :: showheader()
{
cout<<"\n"<<setw(20)<<"PRODUCT ID"<<setw(20)<<"PRODUCT NAME "<<setw(20)<<"PRODUCT BRAND "<<setw(20)<<"PRODUCT PRICE "<<setw(20)<<"PRODUCT QUANTITY";
}

void product :: getproduct()
{
fstream file;
int pcode;
int f=0;
cout<<"\nEnter Product Id : ";
cin>>pcode;
file.open("product.txt",ios::in);

while(!file.eof())
{
if(this->pId==pcode)
{
f=1;
cout<<"\nRecord already Exists ";
break;
}
file.read((char*)this,sizeof(*this));
}
file.close();
fflush(stdin);
if(f==0)
{
pId=pcode;
cout<<"\nEnter Product Name :";
getline(cin,pName);
cout<<"Enter Product Brand :";
getline(cin,pBrand);
fflush(stdin);
cout<<"Enter Product Price :";
cin>>pPrice;
cout<<"Enter Product Quantity :";
cin>>pQuantity;
}
if(f==1)
{
getproduct();
}
}
//create function to add new student

void product :: showproduct()
{
cout<<"\n"<<setw(20)<<pId<<setw(20)<<pName<<setw(20)<<pBrand<<setw(20)<<pPrice<<setw(20)<<pQuantity;

}

void product:: addproduct()
{

fstream file;
file.open("product.txt",ios::out|ios::app);
if(!file)
{
cout<<"file can not open";
}
else
{
file.write((char*)this,sizeof(*this));
file.close();
}
cout<<"\n"<<"Product Added Successfully ";
}

void product:: viewproduct()
{
fstream file;
file.open("product.txt",ios::in);
if(!file)
{
cout<<"File not found";
}
else
{
showheader();
file.read((char*)this,sizeof(*this));
while(!file.eof())
{
showproduct();
file.read((char*)this,sizeof(*this));
}
}
file.close();
}

void product:: searchproduct()
{
fstream file;
int pno;
file.open("product.txt",ios::in|ios::binary);
cout<<"Enter Product id you want to search ?";
cin>>pno;
if(!file)
{
cout<<"file not found";
}
else
{
file.read((char*)this,sizeof(*this));
while(!file.eof())
{
if(this->pId==pno)
{
showheader();
showproduct();
break;
}
file.read((char*)this,sizeof(*this));
}
if(file.eof())
{
cout<<"\nRecord not found";
}
file.close();
}
}

void product :: updateproduct()
{
int id,r=0;
fstream f;
f.open("product.txt",ios::in|ios::out);
cout<<"\n Enter record number you wan to update(productId) :";
cin>>id;
if(!f)
{
cout<<"File not found";
}
else
{
f.read((char*)this,sizeof(*this));
while(!f.eof())
{
r++;
if(this->pId==id)
{
showheader();
showproduct();
cout<<"\t\t\n Re-Enter product details  :";
cout<<"\t\t\nEnter Product id :";
cin>>pId;
fflush(stdin);
cout<<"\t\tEnter Product Name :";
getline(cin,pName);
cout<<"\t\tEnter Product Brand :";
getline(cin,pBrand);
cout<<"\t\tEnter Product Price :";
cin>>pPrice;
cout<<"\t\tEnter Product Quantity :";
cin>>pQuantity;
f.seekp((r-1)*sizeof(product),ios::beg);
f.write((char*)this,sizeof(*this));
cout<<"\t\tRecord Updated";

break;
}
f.read((char*)this,sizeof(*this));
}
if(f.eof())
{
cout<<"\t\tRecord not found";
}
f.close();
}
}

void product :: deleteproduct()
{
fstream fin;
fstream fout;
int id;
char x;
fin.open("product.txt",ios::in);
fout.open("tempfile.txt",ios::out);
cout<<"Enter book id to delete particular record :?";
cin>>id;
if(!fin)
{
cout<<"File not Found";
}
else
{
fin.read((char*)this,sizeof(*this));
while(!fin.eof())
{
if(this->pId==id)
{
cout<<"\n\t\t Record you want to delete is :";
showheader();
showproduct();
cout<<"\n\t\tWant to delete this record(y/n)";
fflush(stdin);
cin>>x;
if(x=='n')
fout.write((char*)this,sizeof(*this));
else
cout<<"\n\t\tRecord deleted";
}
else
{
fout.write((char*)this,sizeof(*this));
}
fin.read((char*)this,sizeof(*this));
}
fin.close();
fout.close();
remove("product.txt");
getch();
rename("tempfile.txt","product.txt");
}
}

 main()
{

product ob;
int choice;
char ch[30];

while(choice!=6)
{
cout<<"\n\t\t-------------------------------"<<endl;
cout<<"\t\tProduct Management System"<<endl;
cout<<"\t\t-------------------------------"<<endl;
cout<<"\t\tAre You An Admin or Customer?";
cin>>ch;
if(strcmpi(ch,"Admin")==0)
{
cout<<"\t\t1.Add new Product"<<endl;
cout<<"\t\t2.View all Products"<<endl;
cout<<"\t\t3.Search Product"<<endl;
cout<<"\t\t4.Modify Product"<<endl;
cout<<"\t\t5.Delete Product"<<endl;
cout<<"\t\t6.Exit"<<endl;
cout<<"\t\tEnter your choice :";
cin>>choice;
switch(choice)
{
case 1:

        ob.getproduct();
        ob.addproduct();
        break;

case 2:
       ob.viewproduct();
       break;
case 3:
        ob.searchproduct();
         break;
case 4:
        ob.updateproduct();
        break;
case 5:
        ob.deleteproduct();
        break;
case 6:
        exit(1);

       default:
       cout<<"\t\tEnter Valid Choice...."<<endl;

       }

}
else if(strcmpi(ch,"Customer")==0)
{
int chh;
while(chh!=3)
{
cout<<"\n\t\t1.View all products"<<endl;
cout<<"\t\t2.Purchase Product"<<endl;
cout<<"\t\t3.Exit"<<endl;
cout<<"Enter your choice :";
cin>>chh;
switch(chh)
{
case 1:
       ob.viewproduct();
       break;
case 2:
       ob.purchase();
       break;
case 3:
        exit(1);
        default:
        cout<<"Invalid choice number ";
}
}
}
 cout<<"\n\t\tDo you want to continue[y /N] ? :";
       cin>>choice;
}
}
