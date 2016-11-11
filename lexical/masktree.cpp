#include "masktree.h"

MaskTree::MaskTree(unsigned int num_in)
{
	this->num_in = num_in;
}


void MaskTree::DFT(node_type *root)
{
	if(root->left)
		DFT(root->left);

	cout << root->op_xor << "\t" << root->op_and << "\t" << root->op_not << "\t" << root->op_or << "\t";// endl;

	for(unsigned int i=0; i<2*num_in; i++)
		cout << root->choose[i] << "\t";

	cout << endl;

	if(root->right)
		DFT(root->right);
}

void MaskTree::QMSCheck(node_type *root)
{
	
}
/*
void MaskTree::QMSCheck(node_type *root)
{
	
}
*/
