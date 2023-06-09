//============================================================================
// Name        : Assignment1_BST.cpp
// Author      : Sameer Patil
// Version     :
// Copyright   : Don't You Dare
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;
class Node
{
	string key, mean;
	Node *rchild;
	Node *lchild;

public:
	friend class Dictionary;
	Node()
	{
		rchild = NULL;
		lchild = NULL;
	}
	Node(string key, string mean)
	{
		this->key = key;
		this->mean = mean;
		rchild = NULL;
		lchild = NULL;
	}
};
class Dictionary
{
	Node *root;

public:
	Dictionary()
	{
		root = NULL;
	}
	void create();
	void deleteNode(string);
	void ascending(Node *r);
	void descending(Node *r);
	void inorder()
	{
		if (root == NULL)
		{
			cout << "\nDictionary is empty\n";
			return;
		}
		ascending(root);
	}
	void postorder()
	{
		if (root == NULL)
		{
			cout << "\nDictionary is empty\n";
			return;
		}
		descending(root);
	}
	bool insert(string key, string mean);
	int search(string key);
	void update(Node *r);
	void updatation()
	{
		update(root);
	}
};
void Dictionary::create()
{
	int n;
	string key1, mean1;
	cout << "Enter How Many Word to be Inserted: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter Key: ";
		cin >> key1;
		cout << "Enter Meaning: ";
		cin.ignore();
		getline(cin, mean1);
		insert(key1, mean1);
		cout << "KEY INSERTED SUCCESSFULLY\n";
	}
}
bool Dictionary::insert(string key, string mean)
{
	Node *r = new Node(key, mean);
	if (root == NULL)
	{
		root = r;
		return true;
	}
	Node *curr = root;
	Node *par = root;
	while (curr != NULL)
	{
		if (key > curr->key)
		{
			par = curr;
			curr = curr->rchild;
		}
		else if (key < curr->key)
		{
			par = curr;
			curr = curr->lchild;
		}
		else
		{
			cout << "\nKey is already exists in dictionary";
			return false;
		}
	}

	if (key > par->key)
	{
		par->rchild = r;
		return true;
	}
	else
	{
		par->lchild = r;
		return true;
	}
}

void Dictionary::ascending(Node *root)
{
	if (root)
	{
		ascending(root->lchild);
		cout << " " << root->key << " : " << root->mean << endl;
		ascending(root->rchild);
	}
}

void Dictionary::descending(Node *root)
{
	if (root)
	{
		descending(root->lchild);
		descending(root->rchild);
		cout << " " << root->key << " : " << root->mean << endl;
	}
}
int Dictionary::search(string key)
{
	Node *curr = root;
	int count = 0;
	if (curr == NULL)
	{
		return -1;
	}
	if (root->key == key)
	{
		return 1;
	}
	while (curr != NULL)
	{
		count++;
		if (curr->key < key)
		{
			curr = curr->rchild;
			count++;
		}
		else if (curr->key > key)
		{
			curr = curr->lchild;
			count++;
		}
		else if (curr->key == key)
		{
			return count;
		}
	}
	return -1;
}
void Dictionary::update(Node *root)
{
	Node *curr;
	string Ukey;
	cout << "Enter key to update:";
	cin >> Ukey;
	curr = root;
	while (curr)
	{
		if (curr->key == Ukey)
		{
			cout << "Enter New Meaning: ";
			cin >> curr->mean;
			cout << "MEANNING UPDATED SUCCESSFULLY\n";
			return;
		}
		else
		{
			if (curr->key < Ukey)
			{
				curr = curr->lchild;
			}
			else
			{
				curr = curr->rchild;
			}
		}
		cout << "Key not found!\n";
	}
}

void Dictionary::deleteNode(string key)
{
    Node* par = NULL;
    Node* curr = root;

    // Find the node with the given key
    while (curr != NULL && curr->key != key)
    {
        par = curr;
        if (key < curr->key)
            curr = curr->lchild;
        else
            curr = curr->rchild;
    }

    // Node with the given key not found
    if (curr == NULL)
    {
        cout << "Key not found in the dictionary";
        return;
    }

    // Case 1: Deleting a leaf node
    if (curr->lchild == NULL && curr->rchild == NULL)
    {
        if (par == NULL)  // Deleting the root node
            root = NULL;
        else if (par->lchild == curr)
            par->lchild = NULL;
        else
            par->rchild = NULL;
        delete curr;
    }
    // Case 2: Deleting a node with a single child
    else if (curr->lchild == NULL || curr->rchild == NULL)
    {
        Node* child = (curr->lchild != NULL) ? curr->lchild : curr->rchild;
        if (par == NULL)  // Deleting the root node
            root = child;
        else if (par->lchild == curr)
            par->lchild = child;
        else
            par->rchild = child;
        delete curr;
    }
    // Case 3: Deleting a node with two children
    else
    {
        Node* successorParent = curr;
        Node* successor = curr->rchild;
        // Find the leftmost node in the right subtree (successor)
        while (successor->lchild != NULL)
        {
            successorParent = successor;
            successor = successor->lchild;
        }

        // Replace the key and value of the node to be deleted with the successor's key and value
        curr->key = successor->key;
        curr->mean = successor->mean;

        // Delete the successor node (Case 1 or Case 2 will be triggered)
        if (successorParent->lchild == successor)
            successorParent->lchild = NULL;
        else
            successorParent->rchild = NULL;
        delete successor;
    }
}

// void Dictionary::deleteNode(string key)
// {
// 	Node *par = NULL;
// 	Node *curr = NULL;
// 	Node *temp = NULL;
// 	int flag = 0, res = 0;
// 	if (root == NULL)
// 	{
// 		cout << "Dictionary is empty";
// 		return;
// 	}
// 	curr = root;
// 	while (1)
// 	{
// 		res = key.compare(curr->key);
// 		if (res == 0)
// 		{
// 			break;
// 		}
// 		flag = res;
// 		par = curr;
// 		curr = (res > 0) ? curr->lchild : curr->rchild;
// 		if (curr == NULL)
// 		{
// 			return;
// 		}
// 	}
// 	// deleting leaf node
// 	if (curr->rchild == NULL)
// 	{
// 		if (curr == root && curr->lchild == NULL)
// 		{
// 			delete (curr);
// 			root = NULL;
// 			return;
// 		}
// 		else if (curr == root)
// 		{
// 			root = curr->lchild;
// 			delete (curr);
// 			return;
// 		}
// 		flag > 0 ? (par->lchild = curr->lchild) : (par->rchild = curr->lchild);
// 	}
// 	else
// 	{
// 		// delete node with single child
// 		temp = curr->rchild;
// 		if (!temp->lchild)
// 		{
// 			temp->lchild = curr->lchild;
// 			if (curr == root)
// 			{
// 				root = temp;
// 				delete (curr);
// 				return;
// 			}
// 			flag > 0 ? (par->lchild = temp) : (par->rchild = temp);
// 		}
// 		else
// 		{
// 			// deleting with two child
// 			Node *successor = NULL;
// 			while (1)
// 			{
// 				successor = temp->lchild;
// 				if (!successor->lchild)
// 				{
// 					break;
// 				}
// 				temp = successor;
// 			}
// 			temp->lchild = successor->rchild;
// 			successor->lchild = curr->lchild;
// 			successor->rchild = curr->rchild;
// 			if (curr == root)
// 			{
// 				root = successor;
// 				delete (curr);
// 				return;
// 			}
// 			(flag > 0) ? (par->lchild = successor) : (par->rchild = successor);
// 		}
// 	}
// 	delete (curr);
// 	return;
// }

int main()
{
	string key;
	Dictionary d1;
	int comparisons;
	int ch;
	do
	{
		cout << "********* MENU *********" << endl;
		cout << "\n1.Insert in Dictionary";
		cout << "\n2.Ascending Order";
		cout << "\n3.Descending Order";
		cout << "\n4.Search";
		cout << "\n5.Update Dictionary";
		cout << "\n6.Delete Dictionary";
		cout << "\n7.Exit";
		cout << "\nEnter Your Choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "INSERTION\n";
			d1.create();
			cout << endl;
			break;
		case 2:
			cout << "\nAscending Order:\n";
			d1.inorder();
			cout << " ";
			break;
		case 3:
			cout << "\nDescending Order:\n";
			d1.postorder();
			cout << " ";
			break;
		case 4:
			cout << "\nSearching operation:";
			cout << "\nEnter key for search:";
			cin >> key;
			comparisons = d1.search(key);
			if (comparisons == -1)
			{
				cout << "Key not found\n";
			}
			else
			{
				cout << "\n"
					 << key << " found in " << comparisons << " comparison" << endl;
			}
			d1.search(key);
			break;
		case 5:
			cout << "Update Dictionary:\n";
			d1.updatation();
			break;
		case 6:
			cout << "Deleting Node\n";
			cout << "\nEnter Key to Delete:";
			cin >> key;
			d1.deleteNode(key);
			break;
		case 7:
			cout << "EXIT";
			exit(0);
			break;
		}
	} while (ch != 7);
	return 0;
}


/*

OUTPUT:

********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 1

INSERTION

Enter How Many Word to be Inserted: 5
Enter Key: First

Enter Meaning: firstKey
KEY INSERTED SUCCESSFULLY

Enter Key: Second
Enter Meaning: secKey
KEY INSERTED SUCCESSFULLY

Enter Key: Third
Enter Meaning: thirdKey
KEY INSERTED SUCCESSFULLY

Enter Key: Forth
Enter Meaning: forthKey
KEY INSERTED SUCCESSFULLY

Enter Key: Fifth
Enter Meaning: fifthKey
KEY INSERTED SUCCESSFULLY

********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 2

Ascending Order:
 Fifth : fifthKey
 First : firstKey
 Forth : forthKey
 Second : secKey
 Third : thirdKey

 ********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 3

Descending Order:
 Fifth : fifthKey
 Forth : forthKey
 Third : thirdKey
 Second : secKey
 First : firstKey

 ********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 4

Searching operation:
Enter key for search:Third
Third found in 5 comparison

********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 5

Update Dictionary:
Enter key to update:First
Enter New Meaning: updatedKey
MEANNING UPDATED SUCCESSFULLY

********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 6

Deleting Node

Enter Key to Delete:First

********* MENU *********

1.Insert in Dictionary
2.Ascending Order
3.Descending Order
4.Search
5.Update Dictionary
6.Delete Dictionary
7.Exit

Enter Your Choice: 7

EXIT

*/	