/*
 * bstNode.cpp
 *
 *  Created on: Oct 28, 2021
 *      Author: manas
 */
#include "bstNode.hpp"
#include <iostream>
using namespace std;

bstNode::bstNode(){
	left = NULL;
	right= NULL;
	parent = NULL;
	student = NULL;
	height =0;
}

bstNode::bstNode(string f, string l, int n, string j){

	left = NULL;
	right= NULL;
	parent = NULL;
	student = new Student(f,l,n,j);
	height =1;
}
void bstNode::printNode(){
cout << "First name:"<<student->first<<endl;
cout << "Last name:"<<student->last << endl;
cout <<"Joke:"<<student->joke<<endl;
cout << "Height:"<<height<<endl;
}
bstNode::~bstNode(){
	delete student;
}




