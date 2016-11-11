#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iterator>
using namespace std;

/*
* Check if the current string is a token 
* @param the current string
* @param regex to match the input variables
* @return true if a token
*/
bool isTokenp(string s, regex rx){
    return s.find("and") != string::npos || s.find("or") != string::npos || s.find("xor") != string::npos || 
            s.find("not") != string::npos || regex_match(s, rx);
}

/*
* For the formula from the given set of tokens by filtering out irrelevant ones
* @param initial set of tokens
* @param regex to match the input variables
* @return the extracted boolean formula
*/
string getTokens(vector<string> tokens , regex pattern){
    string formula1 = "";
    for(vector<string>::const_iterator i  = tokens.begin(); i != tokens.end(); ++i){
        string s = *i;
        if(isTokenp(s, pattern)){
            formula1 += s + " ";
        }
    }

    return formula1;
}

/*
* Form a token vector from the given phrase
* @param the phrase
* @return the vector of tokens in this phrase
*/
vector<string> formVector(string s){
    istringstream iss(s);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
    istream_iterator<string>(),
    back_inserter(tokens));

    return tokens;
}

/*
* Write the generated formula to an output file
* @param the generated formula
*/
void writeFormula(string formula){
    cout << formula << '\n';
    ofstream logic1("formula1.txt");
    logic1 << formula;
    logic1.close();
}

/*
* Extract the relevant phrase from the given file
* @param the path to the script file
* @param the regex representing input variable patterns
* @return the phrase containing the formula
*/
string getPhrase(string path, string pattern){
    ifstream file(path);
    string str;
    string out = "";
    bool counto = false;
    size_t open = 0;
    size_t close = 0;
    regex rgx("\\((.*?)\\)");
    smatch match;
    while (getline(file, str))
    {
        if(str.find(pattern) == 0){
            counto = true;
        }
        if(counto){
            open += count(str.begin(), str.end(), '(');
            close += count(str.begin(), str.end(), ')');
            out += str;
        }
        if(open == close){
            counto = false;
        }
    }
    file.close();
    return out;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "Please provide the path to the script" << '\n';
        return 0;
    }
    regex rx("[a-z][0-9][0-9]*\\)*");
    string out = getPhrase(argv[1],"(define-fun");
    vector<string> tokens = formVector(out);
    string formula1 = getTokens(tokens, rx);
    writeFormula(formula1);
    return 0;
}
