/*
 * bst.cpp
 *
 *  Created on: Oct 28, 2021
 *      Author: manas
 */

#include "bst.hpp"
#include <iostream>
using namespace std;
bst::bst() { // empty constructor
root = NULL;
}
bst::bst(string f, string l, int n, string j) { // constructor that forms the root
root = new bstNode( f,l, n, j);
}
bool bst::insert(string f, string l, int n, string j){
	/*  this method takes as input parameters all
	the fields necessary to create a student object (and will be the fields passed into
	the bstNode constructor, where the student field exists). This method returns true
	if a new node is created and the data is inserted into the tree successfully, and
	false otherwise.
	Data is inserted alphabetically based:
	1) on the last name (the l input parameter) and, if there are 2 last names the
	same,
	2) then on the first name (f).
	Since we didn’t have any two students with the same name, we don’t have to worry
	about using the n to sort on if the last name and the first name are the same.
	Be aware: when you insert a new node into the binary search tree, this method should
	call the setHeights method to adjust the heights
	*/


	//need to add in setHeights
	bstNode *newNode = new bstNode(f,l,n,j);
	if(root == NULL){
		root=newNode;
		setHeight(root);
		return true;
	}
	else{
		bstNode *temp = root;
		while(temp!=NULL){
			if(temp->student->last<l){
				if(temp->right==NULL){
					temp->right = newNode;
					newNode->parent = temp;
					setHeight(newNode);
					return true;
				}
				else{
					temp = temp->right;
					continue;
				}
			}
			else if(l<temp->student->last){
				if(temp->left==NULL){
						temp->left = newNode;
						newNode->parent = temp;
						setHeight(newNode);
						return true;
					}
				else{
						temp = temp->left;
						continue;
				}
			}
			else if(l==temp->student->last){
				if(f<temp->student->first){
					if(temp->left==NULL){
							temp->left = newNode;
							newNode->parent = temp;
							setHeight(newNode);
							return true;
						}
					else{
							temp = temp->left;
							continue;
						}
				}
				else{
					if(temp->right==NULL){
							temp->right = newNode;
							newNode->parent = temp;
							setHeight(newNode);
							return true;
						}
					else{
							temp = temp->right;
							continue;
						}
				}
			}
			else{
				return false;
			}
		}
	}
	return false;

}
bstNode *bst::find(string l,string f){
	/*finds whether a student with the last name l and first
name f is in the tree is in the tree, and, if it is, returns the node holding that
student. Otherwise it returns NULL.
Note that if you find the last name l, you must then check for the first name f. If
it’s not the same, you must keep searching until you find both the last name and the
first name, and, if you don’t, return NULL*/
	bstNode *compare = root;

	while(compare!=NULL){
		if(compare->student->last<l){
			compare = compare->right;
		}
		else if(l<compare->student->last){
			compare = compare->left;
		}
		else if (compare->student->last==l){
			if(compare->student->first==f){
				compare->printNode();
				return compare;
			}
			else if(compare->student->first<f){
				compare = compare->right;
			}
			else{
				compare = compare->left;
			}
		}
		else{
			return NULL;
		}

	}

	return NULL;
}
void bst::printTreeIO(bstNode *n){
	/*recursive function that prints out the data in the tree
	in order*/
	if (n == NULL) {
	return;
	}
	else {
	printTreeIO(n->left);
	n->printNode();
	printTreeIO(n->right);
	}

}


void bst::printTreePre(bstNode *n){
	/*a recursive function that prints out the datain thetree in pre-order*/
	if (n == NULL) {
		return;
		}
	else {
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
		}


}


void bst::printTreePost(bstNode *n){
/*a recursive function that prints out the data in
the tree in post-order
*/
	if (n == NULL) {
		return;
		}
	else {
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
		}
}

//not finished
bstNode *bst::remove(string l, string f){
	/*this method removes a node from the tree, and
returns that node. There are 3 cases when you remove a node: either the node being
removed has no children (left or right), in which case this method calls the method
removeNoKids, the node you are removing has only one child, in which case the method
calls removeOneKid (with a Boolean flag set to true if there is a left child, and
false if there is a right child), or the node being removed has both a left and a
right child, in which you replace the node being removed with the appropriate
replacement child, and then remove the node used as a replacement by calling either
removeNoKids or removeOneKid, depending on which is appropriate.
NOTE: I used the rightmost of the left child as a replacement. To get my output, you
must do the same.
*/
	bstNode *t = find(l,f);
	if(t==NULL){
		return NULL;
	}
	bstNode *tmp =t;
	if (t->right!=NULL&&t->left==NULL){
		tmp= removeOneKid(t,false);
		setHeight(tmp);
	}
	else if (t->right==NULL&&t->left!=NULL){
			tmp = removeOneKid(t,true);
			setHeight(tmp);
		}
	else if (t->right==NULL&&t->left==NULL){
		tmp = removeNoKids(t);
		setHeight(tmp);
	}
	else if (t->right!=NULL&&t->left!=NULL){
		bstNode *leftright = t->left;
		while(leftright->right!=NULL){
			leftright=leftright->right;
		}
		cout << "Replacing with..."<<endl;
		bstNode *rightmost = remove(leftright->student->last,leftright->student->first);
		if(t!=root){
			if(t->parent->left->student->last==t->student->last){
				if(t->parent->left->student->first==t->student->first){
					t->parent->left = rightmost;
					rightmost->parent = t->parent;
				}
				}
			else if(t->parent->right->student->last == t->student->last){
				if(t->parent->right->student->first == t->student->first){
				t->parent->right = rightmost;
				rightmost->parent = t->parent;
				}
			}
		}
		else if(t==root){
					if(t->left!=NULL){
								bstNode *left = t->left;
								rightmost->left = left;
								left->parent = rightmost;
							}
							if(t->right!=NULL){
								bstNode *right = t->right;
								rightmost->right = right;
								right->parent = rightmost;
							}
							root=rightmost;
							t=NULL;
							setHeight(rightmost);
							return tmp;
				}
		if(t->left!=NULL){
			bstNode *left = t->left;
			rightmost->left = left;
			left->parent = rightmost;
		}
		if(t->right!=NULL){
			bstNode *right = t->right;
			rightmost->right = right;
			right->parent = rightmost;
		}
		t=NULL;
		setHeight(rightmost);
	}
	return tmp;
}


bstNode *bst::removeNoKids(bstNode *tmp){
/* for removing a node with no children
*/
	bstNode *t = tmp;
	if(tmp->student->first==root->student->first){
		if(tmp->student->last==root->student->last){
		tmp=NULL;
		}
	}
	else if(tmp->parent->left->student->first == tmp->student->first){
		if(tmp->parent->left->student->last==tmp->student->last){
				tmp->parent->left = NULL;
				tmp= NULL;
		}
	}
	else if(tmp->parent->right->student->first == tmp->student->first){
		if(tmp->parent->right->student->last==tmp->student->last){
						tmp->parent->right = NULL;
						tmp= NULL;
		}
	}

	return t;
}

bstNode *bst::removeOneKid(bstNode *tmp, bool leftFlag){
	/*for removing a node with one
child, with the leftFlag indicating whether the node’s child is either the left child
or the right child.
*/
	bstNode *t = tmp;
	if(tmp->student->last==root->student->last){
		if(tmp->student->first==root->student->first){
		if(leftFlag==false){
			root=tmp->right;
		}
		else{
			root=tmp->left;
		}
		tmp=NULL;
		return t;
		}
	}
	else if(tmp->parent->left->student->last==tmp->student->last){
		if(tmp->parent->left->student->first==tmp->student->first){
		bstNode *p=tmp->parent;
				if(leftFlag==false){
					p->left = tmp->right;
					tmp->right->parent = p;
					tmp=NULL;
					return t;
				}
				else{
					p->left = tmp->left;
					tmp->left->parent = p;
					tmp=NULL;
					return t;
				}
			}
	}
	else if(tmp->parent->right->student->last==tmp->student->last){
		if(tmp->parent->right->student->first==tmp->student->first){
		bstNode *p=tmp->parent;
					if(leftFlag==false){
						p->right = tmp->right;
						tmp->right->parent = p;
						tmp=NULL;
						return t;
					}
					else{
						p->right = tmp->left;
						tmp->left->parent = p;
						tmp=NULL;
						return t;
					}
				}
	}
	return NULL;
}

void bst::setHeight(bstNode *n){
	/*This method sets the heights of the nodes in a tree.
	Once a node is inserted, only the node’s ancestors can have their height changed.
	Thus you should set the height of the node being inserted (to 1) and then adjust the
	heights of the node’s parent, grandparent, etc. up until either the height of the
	node doesn’t change or you hit the root.*/

			if(n->left==NULL&&n->right==NULL){
				n->height =1;
			}
			else if(n->left!=NULL&&n->right==NULL){
				n->height = n->left->height +1;
			}
			else if(n->left==NULL&&n->right!=NULL){
				n->height = n->right->height +1;
			}
			else{
				if(n->left->height<=n->right->height){
					n->height = n->right->height+1;
				}
				else{
					n->height = n->left->height+1;
				}
			}
			if(n==root){
				return;
			}
			else{
			setHeight(n->parent);
			}
}
void bst::clearTree() { //clears out an old tree
	//This calls the recursive clearTree with the root node
	if (root == NULL) {
	cout << "Tree already empty" << endl;
	}
	else {
	cout << endl << "Clearing Tree:" << endl;
	clearTree(root);
	root = NULL;
	}
}
void bst::clearTree(bstNode *tmp) {
if (tmp == NULL) {
return;
}
else {
	clearTree(tmp->left);
	clearTree(tmp->right);
	tmp->printNode();
	delete(tmp);
}
}
/*Note: the following three functions’ sole job is to call printTreeIO(BstNode
*t),printTreePre(BstNode *t), and printTreePost(BstNode *t) while printint out which
Function is being called.
YOU MUST STILL WRITE THE RECURSIVE VERSION OF THESE FUNCTIONS!!!*/
void bst::printTreeIO() { // Just the start – you must write the recursive version
	if (root == NULL ) {
		cout << "Empty Tree" << endl;

}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}

void bst::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}
void bst::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}


