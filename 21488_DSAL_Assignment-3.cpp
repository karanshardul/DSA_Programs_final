//============================================================================
// Name        : Assignment3_ThreadedBST.cpp
// Author      : Sameer Patil
// Version     :
// Copyright   : Don't You Dare
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;

class Node
{
	int data;
	Node *lchild;
	Node *rchild;
	bool lbit,rbit;

public:
	Node()
	{
		data=0;
		lchild = NULL;
		rchild = NULL;
		lbit = false;
		rbit = false;
	}
	Node(int x)
	{
		data = x;
		lchild = NULL;
		rchild = NULL;
		lbit = false;
		rbit = false;
	}
	friend class TBT;
};

class TBT{
	Node *header;
	Node *root;
public:
	TBT(){
		header=root=NULL;
	}
	
	void create(){
		int n,ele;
		cout << "Enter How many elements to be inserted: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter element: ";
			cin >> ele;
			insert(ele);
			cout << "ELEMENT INSERTED SUCCESSFULLY\n";
		}
	}
	void insert(int ele){
		Node *ptr;
		Node *temp;
		if(root==NULL){
			header=new Node(-99);
			header->lbit=0;
			header->rbit=0;
			header->rchild=header;
			root=new Node(ele);
			root->lbit=0;
			root->rbit=0;
			root->lchild=header;
			root->rchild=header;
			header->lchild=root;
		}
		else{
			ptr=root;
			temp=new Node(ele);
			while(1){
				if(ptr->data > ele){
					if(ptr->lbit!=0){
						ptr=ptr->lchild;
					}
					else{
						temp->lbit=0;
						temp->rbit=0;
						temp->lchild=ptr->lchild;
						temp->rchild=ptr;
						ptr->lbit=1;
						ptr->lchild=temp;
						return;
					}
				}
				else{
					if(ptr->rbit!=0){
						ptr=ptr->rchild;
					}
					else{
						temp->lbit=0;
						temp->rbit=0;
						temp->lchild=ptr;
						temp->rchild=ptr->rchild;
						ptr->rbit=1;
						ptr->rchild=temp;
						return;
					}
				}
			}
		}
	}
	void inorder(){
		if(root==NULL){
			cout<<"Tree is not present...!!";
			return;
		}
		Node *t=root;
		while(t->lbit!=0){
			t=t->lchild;
		}
		while(t!=header){
			cout<<t->data << " ";
			if(t->rbit!=0){
				t=t->rchild;
				while(t->lbit!=0){
					t=t->lchild;
				}
			}
			else{
				t=t->rchild;
			}
		}
	}

	void preorder1(){
		if(root==NULL){
			cout<<"Tree is not present...!!";
			return;
		}
		Node *t=root;
		while(t!=header){
			cout<<t->data<<" ";
			if(t->lbit==1){
				t=t->lchild;
			}
			else{
				if(t->rbit==1){
					t=t->rchild;
				}
				else{
					t=t->rchild->rchild;
				}
			}
		}
	}
	void preorder2(){
		int flag=0;
		Node *t=root;
		while(t!=header){
			if(flag==0)
				cout<<t->data<<" ";
			if(flag==0 && t->lbit==1){
				t=t->lchild;
			}
			else{
				if(t->rbit==1){
					flag=0;
				}
				else{
					flag=1;
				}
				t=t->rchild;
			}
		}
	}

	int search(int x, Node* &curr, Node* &parent){
		int count=0;
		while(curr!=NULL){
			count++;
			if(curr->data==x){
				return count;
			}
			else{
				parent=curr;
				if(parent->data > x)
					curr=curr->lchild;
				else
					curr=curr->rchild;
			}
		}
		return 0;
	}

	void delete_TBT(int x){
		Node *t=root;
		Node *p=NULL;
		search(x,t,p);
		Node *temp=t;
		if(t->lbit==1 && t->rbit==1){
			Node *c_s=t->rchild;
			do{
				p=c_s;
				c_s=c_s->lchild;
			}while(c_s->lbit!=0);
			t->data=c_s->data;
			t=c_s;
		}
		if(t->lbit==0 && t->rbit==0){
			if(p->lbit==1){
				p->lchild=t->lchild;
				p->lbit=0;
			}
			else{
				p->rchild=t->rchild;
				p->rbit=0;
			}
			delete(t);
		}
		if(t->lbit==1 && t->rbit==0){
			temp=t->lchild;
			if(p->lchild==t){
				p->lchild=temp;
			}
			else{
				p->rchild=temp;
			}
			while(temp->rbit==1){
				temp=temp->rchild;
			}
			temp->rchild=t->rchild;
			delete(t);
		}
		if(t->lbit==0 && t->rbit==1){
			temp=t->rchild;
			if(p->lchild==t){
				p->lchild=temp;
			}
			else{
				p->rchild=temp;
			}
			while(temp->lbit==1){
				temp=temp->lchild;
			}
			temp->lchild=t->lchild;
			delete(t);
		}
	}
};

int main() {
	TBT obj;
	int ch;
	do
	{
		cout << "\n1.Insert Element";
					cout << "\n2.In-order";
					cout << "\n3 Pre-order Traversal-1";
					cout << "\n4.Pre-order Traversal-2";
					cout << "\n5.Delete";
					cout << "\n6.Exit\n";
					cout << "\nEnter your Choice: ";
					cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "INSERTION\n";
			obj.create();
			cout << endl;
			break;
		case 2:
			cout << "\nInorder Traversal:\n";
			obj.inorder();
			cout << endl;
			break;
		case 3:
			cout << "\nPreorder logic 1:\n";
			obj.preorder1();
			cout << endl;
			break;
		case 4:
			cout << "\nPreorder logic 2:\n";
			obj.preorder2();
			cout << endl;
			break;
		case 5:
			int ele;
			cout << "\nDelete:\n";
			cout << "Enter the element that you want to delete: ";
			cin >> ele;
			obj.delete_TBT(ele);
			cout << endl;
			break;
		case 6:
			cout << "Exited...!!";
			exit(0);
			break;
		default:
			cout << "Wrong choice entered...!!";
			cout << endl;
			break;
		}
	} while (ch != 6);
	return 0;
}


/*

OUTPUT:


1.Insert Element
2.In-order
3 Pre-order Traversal-1
4.Pre-order Traversal-2
5.Delete
6.Exit

Enter your Choice: 1
INSERTION
Enter How many elements to be inserted: 5
Enter element: 34
ELEMENT INSERTED SUCCESSFULLY
Enter element: 55
ELEMENT INSERTED SUCCESSFULLY
Enter element: 12
ELEMENT INSERTED SUCCESSFULLY
Enter element: 67
ELEMENT INSERTED SUCCESSFULLY
Enter element: 90
ELEMENT INSERTED SUCCESSFULLY


1.Insert Element
2.In-order
3 Pre-order Traversal-1
4.Pre-order Traversal-2
5.Delete
6.Exit

Enter your Choice: 2
Inorder Traversal:
12 34 55 67 90 

1.Insert Element
2.In-order
3 Pre-order Traversal-1
4.Pre-order Traversal-2
5.Delete
6.Exit

Enter your Choice: 3
Preorder logic 1:
34 12 55 67 90 

1.Insert Element
2.In-order
3 Pre-order Traversal-1
4.Pre-order Traversal-2
5.Delete
6.Exit

Enter your Choice: 4
Preorder logic 2:
34 12 55 67 90 

1.Insert Element
2.In-order
3 Pre-order Traversal-1
4.Pre-order Traversal-2
5.Delete
6.Exit

Enter your Choice: 5
Delete:
Enter the element that you want to delete: 90
1.Insert Element
2.In-order
3 Pre-order Traversal-1
4.Pre-order Traversal-2
5.Delete
6.Exit

Enter your Choice: 6
Exited...!!


*/