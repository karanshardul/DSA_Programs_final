//============================================================================
// Name        : Assignment5_HashingDict.cpp
// Author      : Sameer Patil
// Version     :
// Copyright   : Don't You Dare
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <string>
using namespace std;
#define SIZE 26

class Node{
	string value;
	Node *next;
public:
	Node(string val){
		value=val;
		next=NULL;
	}
	friend class HashTable;
};

class HashTable{
	Node *arr[SIZE];
public:
	HashTable(){
		for(int i=0;i<SIZE;i++){
			arr[i]=NULL;
		}
	}
	int hashfunc(char w){
		int ch=w;
		return ch%26;
	}

	void insert(string word){
		int hashcode=hashfunc(word[0]);
		if(arr[hashcode]==NULL){
			arr[hashcode]=new Node(word);
		}
		else{
			Node *temp=arr[hashcode];
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=new Node(word);
		}
	}
	
	void display(){
		for(int i=0;i<26;i++){
			cout<<i;
			if(arr[i]!=NULL){
			Node *temp=arr[i];
				while(temp!=NULL){
					cout<<"     "<<temp->value<<"-->";
					temp=temp->next;
				}
			}
			cout<<endl;
		}
	}
};


int main() {
	HashTable ht;
	string word;
	int ch;
	while(1){
		cout<<endl<<"----------------Menu-----------------"<<endl;
		cout<<"1.Insert\n2.Display\n3.Exit"<<endl;
		cout<<"\nEnter Your Choice: ";
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter the String: ";
				cin>>word;
				ht.insert(word);
				break;
			case 2:
				cout<<"All Entries...\n";
				ht.display();
				break;
			case 3:
				cout<<"\nExited...!!!";
				exit(0);
			default:
				cout<<"Incorrect choice entered!!!";

		}
	}
	return 0;
}



/*

OUTPUT:


----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 1
Enter the String: Sameer
----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 1
Enter the String: Alok
----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 1
Enter the String: Pranav
----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 1
Enter the String: Harshal
----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 1
Enter the String: Diksha
----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 2
All Entries...
0
1
2     Pranav-->
3
4
5     Sameer-->
6
7
8
9
10
11
12
13     Alok-->
14
15
16     Diksha-->
17
18
19
20     Harshal-->
21
22
23
24
25

----------------Menu-----------------
1.Insert
2.Display
3.Exit

Enter Your Choice: 3
Exited...!!!


*/