#include <iostream>
#include <fstream>  
#include <streambuf>
#include <string>

#include "InputBuffer.h"
#include "NFA.h"
#include "masktree.h"

const int TokenSpace 	= 1;
const int TokenNot 		= 2;
const int TokenXor 		= 3;
const int TokenAnd 		= 4;
const int TokenOr 		= 5;
const int TokenInput 	= 6;
const int TokenRand 	= 7;
const int TokenOpenPar 	= 8;
const int TokenClosePar = 9;

using namespace std;

int main () 
{
	std::ifstream myfile;
	myfile.open("input.txt");

	list <pair <int, string>> token_list;
	list <pair <int, string>>::iterator it_token_list;

	if (!myfile)
	{
		std::cout << "There is no input.txt file.\n";
	}
  	else
	{
		NFA nfa;

		// Final states
		nfa.setFinalState(2, TokenSpace);
		nfa.setFinalState(6, TokenNot);
		nfa.setFinalState(10, TokenXor);
		nfa.setFinalState(14, TokenAnd);
		nfa.setFinalState(17, TokenOr);
		nfa.setFinalState(20, TokenInput);
		nfa.setFinalState(23, TokenRand);
		nfa.setFinalState(25, TokenOpenPar);
		nfa.setFinalState(27, TokenClosePar);

		// Transitions from states 0, 1, 2
		nfa.addTransition(0, 0, 1);
		nfa.addTransition(0, 0, 3);
		nfa.addTransition(0, 0, 7);
		nfa.addTransition(0, 0, 11);
		nfa.addTransition(0, 0, 15);
		nfa.addTransition(0, 0, 18);
		nfa.addTransition(0, 0, 21);
		nfa.addTransition(0, 0, 24);
		nfa.addTransition(0, 0, 26);



		// Transitions for space
		nfa.addTransition(1, ' ', 2);
		nfa.addTransition(1, '\n', 2);
		nfa.addTransition(1, '\t', 2);

		nfa.addTransition(2, ' ', 2);
		nfa.addTransition(2, '\n', 2);
		nfa.addTransition(2, '\t', 2);

		// Transitions for 'not'
		nfa.addTransition(3, 'n', 4);
		nfa.addTransition(4, 'o', 5);
		nfa.addTransition(5, 't', 6);

		// Transitions for 'xor'
		nfa.addTransition(7, 'x', 8);
		nfa.addTransition(8, 'o', 9);
		nfa.addTransition(9, 'r', 10);

		// Transitions for 'and'
		nfa.addTransition(11, 'a', 12);
		nfa.addTransition(12, 'n', 13);
		nfa.addTransition(13, 'd', 14);

		// Transitions for 'or'
		nfa.addTransition(15, 'o', 16);
		nfa.addTransition(16, 'r', 17);

		// Transitions for 'input'
		nfa.addTransition(18, 'i', 19);
		for (char c = '0'; c <= '9'; c++)
			nfa.addTransition(19, c, 20);

		// Transitions for 'random'
		nfa.addTransition(21, 'r', 22);
		for (char c = '0'; c <= '9'; c++)
			nfa.addTransition(22, c, 23);

		// Transitions for '('
		nfa.addTransition(24, '(', 25);

		// Transitions for ')'
		nfa.addTransition(26, ')', 27);

		// Create input buffer
		InputBuffer input_buffer(myfile);

		while (true)
		{
			std::pair<int, std::string> pair = input_buffer.getToken(nfa);

			// No more tokens
			if (!pair.first)
				break;

			token_list.push_back(pair);
		}
	}

	
	unsigned int num_in = 2;

	unsigned int first_node_found = 0;
	MaskTree MaskTree(num_in);
	node_type *current_node;

	unsigned int node_index = 0;

	for(it_token_list = token_list.begin(); it_token_list != token_list.end(); it_token_list++)
	{
	//	std::cout << "Token " << it_token_list->first << ": '" << it_token_list->second << "'\n";


		if( (it_token_list->first >= TokenNot) && (it_token_list->first <= TokenOr) )
		{
			node_type *mask_node = new node_type{node_index, false, false, false, false, vector<bool>(2*num_in, false), false, NULL, NULL, NULL};
			node_index++;
			MaskTree.TreeNodes.insert(*mask_node);

			switch(it_token_list->first)
			{
				case TokenNot:
					mask_node->op_not = true;
					break;
				case TokenXor:
					mask_node->op_xor = true;
					break;
				case TokenAnd:
					mask_node->op_and = true;
					break;
				case TokenOr:
					mask_node->op_or = true;
					break;
				default:
					break;				
			}
		
			//*mask_node = {false, false, false, false, vector<bool>(2*num_in, false), false, NULL, NULL, NULL};
			
			cout << "New node is Operator " << mask_node->op_not << mask_node->op_xor << mask_node->op_and << mask_node->op_or << endl;




			// This is the root node
			if(first_node_found == 0)
			{
				MaskTree.Tree_root = mask_node;
				mask_node->parent = NULL;
				first_node_found = 1;

				current_node = mask_node;

				//cout << "Root found and it is " << it_token_list->first << endl;
			}
			else
			{
				if(current_node->left == NULL)
				{
					current_node->left = mask_node;
					cout << "Insert " << mask_node->node_index << " to left of " << current_node->node_index << endl;
				}
				else
				{
					current_node->right = mask_node;
					cout << "Insert " << mask_node->node_index << " to right of " << current_node->node_index << endl;
				}

				mask_node->parent = current_node;
				current_node = mask_node;
			} 
		}
		else if((it_token_list->first == TokenInput) | (it_token_list->first == TokenRand))
		{
			unsigned int InRand_number = stoi(it_token_list->second.substr(1,it_token_list->second.size()));

			if(it_token_list->first == TokenRand)
				InRand_number = InRand_number + num_in;

			cout << "InRand_number = " << InRand_number << endl;

			node_type *mask_node = new node_type{node_index, false, false, false, false, vector<bool>(2*num_in, false), false, NULL, NULL, NULL};
			node_index++;

			mask_node->choose[InRand_number] = true;

			if(current_node->left == NULL)
			{
				current_node->left = mask_node;
				mask_node->parent = current_node;

				cout << "Insert " << mask_node->node_index << " to left of " << current_node->node_index << endl;

				if(current_node->op_not == true)	//need to trace back
				{
					current_node->right == NULL;
					current_node = current_node->parent;

					while( (current_node->right != NULL) | (current_node->op_not == true) )
						current_node = current_node->parent;
				}	

				cout << "Trace back to node " << current_node->node_index << endl;		
			}
			else if(current_node->right == NULL)
			{
				current_node->right = mask_node;
				mask_node->parent = current_node;

				cout << "Insert " << mask_node->node_index << " to right of " << current_node->node_index << endl;
				
				//trace back
				current_node = current_node->parent;
				while( (current_node->right != NULL) )
					current_node = current_node->parent;
			}
		}
	}
		
	cout << "xor" << "\t" << "and" << "\t" << "not" << "\t" << "or" << "\t";// endl;
	cout << "i0" << "\t" << "i1" << "\t" << "r0" << "\t" << "r1" << endl;
	MaskTree.DFT(MaskTree.Tree_root);

	

	MaskTree.QMSCheck(MaskTree.Tree_root);

	return 0;
}

