#include <stddef.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iterator>
#include "tree.h"

using namespace std;
// Null Constructor
treeNode::treeNode(){
  value = "";
}

/*
* Main Constructor. Form a tree using the given formula
* @param the boolean formula 
*/
treeNode::treeNode(string formula){
   createNode(formula);
}


void treeNode::createNode(string formula){
  string formula2 = formula.substr(1, formula.size() - 1);
  vector<string> a;
  int open = 0;
  int closed = 0;
  string soFar = "";
  regex rx("[a-z][0-9]\\)*");
  for(char& c : formula2) {
      if (soFar == "and" | soFar == "xor" | soFar=="or" | soFar=="not"|regex_match(soFar, rx)){
        cout << "Value is " << soFar << '\n';
        a.push_back(soFar);
        soFar = "";
      }
      if(c == '('){
        open++;
        soFar += c;
      } else if(c == ')'){
        closed++;
        soFar += c;
      }else if(c == ' '){
      }else{
        soFar += c;
      }

      if((open != 0 && closed != 0) && open == closed){
        open = 0;
        closed = 0;
        a.push_back(soFar);
        soFar = "";
      }
  }  
  //cout << a.size() << '\n';
  if(a.at(0) == "and"){
    this->op_and = true;
  }else if(a.at(0) == "or"){
    this->op_or = true;
  }else if(a.at(0) == "xor"){
    this->op_xor = true;
  }else if(a.at(0) == "not"){
    this->op_not = true;
  }

  if(a.at(1).find('(') != std::string::npos){
    //cout << "LEFT IS:" << a.at(1) << '\n';
    left = new treeNode();
     left->createNode(a.at(1));
  }else{
    left = new treeNode();
    left->value = a.at(1);
    //cout << "Left VALUE IS:" << top.left->value << '\n';
  }
  if(a.at(0) != "not"){
    if(a.at(2).find('(') != std::string::npos){
      //cout << "RIGHT IS:" << a.at(2) << '\n';
      right = new treeNode();
      right->createNode(a.at(2));
    }else{
      right = new treeNode();
      right->value = a.at(2);
      //cout << "Right VALUE IS:" << top.right->value << '\n';
    }
  }
}


void treeNode::destroy_tree(node *leaf){
/*  if(leaf!= NULL){
      destroy_tree(leaf->left);
      destroy_tree(leaf->right);
      delete leaf;
  }*/
}


void treeNode::printTree(){
    if(this->op_and){
      cout << "and" << '\n';
    }else if(this->op_or){
      cout << "or" << '\n';
    }else if(this->op_not){
      cout << "not" << '\n';
    }else if(this->op_xor){
      cout << "xor" << '\n';
    }else if(this->value != ""){
      cout << this->value << '\n';
    }

   if(left != NULL){
      cout << "PRINT LEFT" << '\n';
      left->printTree();
    }

    if(right != NULL){
      cout << "PRINT RIGHT" << '\n';
      right->printTree();
    }


}



void treeNode::destroy_tree()
{
//  destroy_tree(root);
}

int getInputs(string formula){
    regex rx("[a-z][0-9]\\)*");
    istringstream iss(formula);
    vector<string> tokens;
    vector<string> inputs;
    copy(istream_iterator<string>(iss),
    istream_iterator<string>(),
    back_inserter(tokens));
    for(vector<string>::const_iterator i  = tokens.begin(); i != tokens.end(); ++i){
        string s = *i;
        if(regex_match(s, rx)){
            boost::erase_all(s, ")");
            boost::erase_all(s, "(");
            inputs.push_back(s);
        }
    }
    sort(inputs.begin(), inputs.end() );
    inputs.erase( unique(inputs.begin(), inputs.end() ), inputs.end());
    return inputs.size();   
}


bool next(string::iterator begin, string::iterator end)
{
    if (begin == end)      // changed all digits
    {                      // so we are back to zero
        return false;      // that was the last number
    }
    --end;
    if ((*end & 1) == 0)   // even number is treated as zero
    {
        ++*end;            // increase to one
        return true;       // still more numbers to come
    }
    else                   // odd number is treated as one
    {
        --*end;            // decrease to zero
        return next(begin, end);   // RECURSE!
    }
}

bool treeNode::checkUniformity(string formula, int inputs){
  string initial ="";
  int i;
  for(i = 0; i < inputs; i++){
    initial += "0";
  }

  vector<string> combinations;
  string test = "0000";
  do
  {
    combinations.push_back(test);
    cout << test << '\n';
  } while (next(test.begin(), test.end()));
    // now the vector contains all pssible combinations
  //permutate all possible values of values iterate through and calculate values
    
 this-> uniformp(combinations);
 return true;
}

/*
* Check if the formula if uniform for given possible values
* @param Enumuration of all possible values of the inputs of formula
* @return if the formula is uniform
*/
bool treeNode::uniformp(vector<string> combination){
  for(std::vector<string>::iterator it = combination.begin(); it != combination.end(); ++it) {
    cout << "Input" << *it << '\n';
    bool x = this->checkForOne(*it);
    cout << "Result: " << x << '\n';
  }
  //change this later
  return true;
}

/*
* Calculate the output for the given input value set
* @param input value set
* @return the output value for given inputs
*/
bool treeNode::checkForOne(string combination){
    bool result;
//  cout << "checkforone" << '\n';
        if(this->op_and){
//    cout << "ANDCHECK"<<'\n';
                result = left->checkForOne(combination) && right->checkForOne(combination);
        }else if(this->op_or){
//    cout << "ORCHECK"<<'\n';
                result = left->checkForOne(combination) || right->checkForOne(combination);
        }else if(this->op_not){
//    cout << "NOTCHECK"<<'\n';
                if(left != NULL){
                        result = !left->checkForOne(combination);
    }
    if(right != NULL){
      result = !right->checkForOne(combination);
    }
        }else if(this->op_xor){
//    cout << "XORCHECK"<<'\n';
                result= (!right->checkForOne(combination) != !left->checkForOne(combination));
        }else if(this->value != ""){
//    cout << "printing" << '\n';;
                string inp = (this->value).substr(1, (this->value).size());
//    cout << "here1: " << inp << '\n';
    int index = stoi(inp);
//    cout << "here2: " << index << '\n';
    char val = combination.at(index);
//    cout << "Combination value:" << val << '\n';
    if(val == '0'){
      result = false;
    }else{
      result = true;
    }
        }

  return result;
}

int main(){
  treeNode* a = new treeNode("(xor (or (not i1) (xor i3 i2)) (xor (not i0) (and i3 i0))))");
  //treeNode* a = new treeNode("(xor (or (not i1) i3) (xor (not i0) (and i3 i0)))");
  //printTree(a->root);
  int x = getInputs("(xor (or (not i1) (xor i3 i2)) (xor (not i0) (and i3 i0)))) ");
  a->checkUniformity("", x);  
  a->printTree();
}
