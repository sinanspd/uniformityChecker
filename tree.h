#ifndef _TREE_H_
#define _TREE_H_
#include <string>

//Defunc
/*struct 
node{
    bool op_and = false;
    bool op_xor = false;
    bool op_or = false;
    bool op_not = false;
    std::string value = "";
    struct node *left = NULL;
    struct node *right = NULL;
};*/

class treeNode{

     public:
        //Fields 
        std::string formula;
        treeNode *left = NULL;
        treeNode *right = NULL;
        std::string value;
        bool op_and = false;
        bool op_xor = false;
        bool op_or = false;
        bool op_not = false;

        //methods
        treeNode();
        treeNode(std::string formula);
        ~treeNode();
        int main();
    
        
        void printTree();
        bool checkUniformity();
    
    private:
        void setCurrentNodeValue(std::string value);
        void setLeftAndRight(std::vector<std::string> values);
        bool getValue(std::string combination);
        void createNode(std::string n);
        int getInputs();
        bool uniformp(std::vector<std::string> v);
        bool checkForOne(std::string s);
        bool checkOccurances(std::vector<int> results);
        
};

#endif