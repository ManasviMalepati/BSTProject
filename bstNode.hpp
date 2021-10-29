/*
 * bstNode.hpp
 *
 *  Created on: Oct 28, 2021
 *      Author: manas
 */

#ifndef BSTNODE_HPP_
#define BSTNODE_HPP_
#include "Student.hpp"
	class bstNode {
		/*For this I had the following fields:
	• left: the left child (a bstNode pointer)
	• right: right child (a bstNode pointer)
	• parent: the parent (a bstNode pointer)
	• height: the height (an int)
	• student: the data of type pointer to student
		 *
		 */
		friend class bst;
		bstNode *left;
		bstNode *right;
		bstNode *parent;
		int height;
		Student *student;
	public:
		bstNode();
		bstNode(string f, string l, int n, string j);
		~bstNode();
		void printNode();


	};





#endif /* BSTNODE_HPP_ */
