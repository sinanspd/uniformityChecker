#ifndef _MASKTREE_H_
#define _MASKTREE_H_

#include <assert.h>
#include <vector>
#include <set>

#include <iostream>		// std::cout, std::right, std::endl
#include <iomanip>		// std::setw
#include <fstream>
#include <sstream> 
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;


struct node_type{	
					unsigned int node_index;
					bool op_and;
					bool op_xor;
					bool op_or;
					bool op_not;
					vector <bool> choose;	//the leaf node is in/rand
					bool value;
					struct node_type *parent;
					struct node_type *left;
					struct node_type *right;
				};

inline bool operator==(const node_type& lhs, const node_type& rhs)
{
	return (lhs.node_index == rhs.node_index);
}
inline bool operator<(const node_type& lhs, const node_type& rhs)
{
  	return (lhs.node_index < rhs.node_index);
}


class MaskTree
{
public:
	unsigned int num_in;	
	struct node_type *Tree_root;

	set <node_type> TreeNodes;
	
	MaskTree(unsigned int num_in);
	void DFT(node_type *root);
	void QMSCheck(node_type *root);



private:


};


#endif
