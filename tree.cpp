#include <stddef.h>
#include <fstream>
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
   this->formula = formula;
   cout << "Creating Tree" <<'\n';
   createNode(formula);
}

/*
* Create the current node according to the given formula
* @param formula to create the node
*/
void treeNode::createNode(string formula){
  string formula2 = formula.substr(1, formula.size() - 1);
  vector<string> a;
  int open = 0;
  int closed = 0;
  string soFar = "";
  regex rx("[a-z][0-9][0-9]*\\)*");
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

  this->setCurrentNodeValue(a.at(0));
  this->setLeftAndRight(a);
}

/*
* Form the left and right nodes according to given values
* @param vector representing values for this left and rights
*/
void treeNode::setLeftAndRight(vector<string> a){
   if(a.at(1).find('(') != std::string::npos){
    left = new treeNode();
    left->createNode(a.at(1));
  }else{
    left = new treeNode();
    left->value = a.at(1);
  }
  if(a.at(0) != "not"){
    if(a.at(2).find('(') != std::string::npos){
      right = new treeNode();
      right->createNode(a.at(2));
    }else{
      right = new treeNode();
      right->value = a.at(2);
    }
  }
}

/*
* Set the value of the current Node
* @param the value to be set
*/
void treeNode::setCurrentNodeValue(string value){
  if(value == "and"){
    this->op_and = true;
  }else if(value == "or"){
    this->op_or = true;
  }else if(value == "xor"){
    this->op_xor = true;
  }else if(value == "not"){
    this->op_not = true;
  }
}


/*
* Traverse the Tree and print its nodes 
* Uses a depth first traversal  
* meaning all the nodes to the left will be printed before nodes to the right
*/
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

/*
* Get the number of all distint inputs in the given formula
* @return int representing number of distinct inputs 
* return result of 4 implies i0, i1, i2, i3 are present in the formula
*/
int treeNode::getInputs(){
    string formula = this->formula;
    regex rx("[a-z][0-9][0-9]*\\)*");
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

/*
* Create the next permutation given a base test string
* @param iterator pointing to the start
* @param iterator pointing to the end
* @return the value of the next param
*/
bool next(string::iterator begin, string::iterator end)
{
    if (begin == end)      
    {                      
        return false;      
    }
    --end;
    if ((*end & 1) == 0)   
    {
        ++*end;            
        return true;       
    }
    else                  
    {
        --*end;            
        return next(begin, end);   
    }
}

/*
* Check if the given formula is uniform in terms of output
*/
bool treeNode::checkUniformity(){
  int inputs = this->getInputs();
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
  } while (next(test.begin(), test.end()));
    
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
    cout << "For Input: " << *it << '\n';
    bool x = this->checkForOne(*it);
    cout << "Result is: " << x << '\n';
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
    if(this->op_and){
      result = left->checkForOne(combination) && right->checkForOne(combination);
    }else if(this->op_or){
      result = left->checkForOne(combination) || right->checkForOne(combination);
    }else if(this->op_not){
      if(left != NULL){
        result = !left->checkForOne(combination);
      }
      if(right != NULL){
        result = !right->checkForOne(combination);
      }
    }else if(this->op_xor){
      result= (!right->checkForOne(combination) != !left->checkForOne(combination));
    }else if(this->value != ""){
      result = this->getValue(combination);
    }
  return result;
}


/*
* Get the value of the current input from the combination
* @param Input value combination
* @return true if 1, false if 0
*/
bool treeNode::getValue(string combination){
  string inp = (this->value).substr(1, (this->value).size());
  int index = stoi(inp);
  char val = combination.at(index);
  if(val == '0'){
    return false;
  }else{
    return true;
  }
}

/*
* Read the input from the given file
* @param path to the file
* @return extracted formula
*/
string getFormula(string path){
  ifstream file(path);
  string formula;
  getline(file, formula);
  return formula;
}
 
int main(int argc, char *argv[]){
  string formula;
  if(argc < 2){
    formula = getFormula("formula1.txt");
  }else{
    formula = getFormula(argv[1]);
  }
  treeNode* a = new treeNode(formula);
  a->checkUniformity();  
}
