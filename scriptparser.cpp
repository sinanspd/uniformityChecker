#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iterator>
using namespace std;

bool isTokenp(string s, regex rx){
    return s.find("and") != string::npos || s.find("or") != string::npos || s.find("xor") != string::npos || 
            s.find("not") != string::npos || regex_match(s, rx);
}

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

vector<string> formVector(string s){
    istringstream iss(s);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
    istream_iterator<string>(),
    back_inserter(tokens));

    return tokens;
}

void writeFormula(string formula){
    cout << formula << '\n';
    ofstream logic1("formula1.txt");
    logic1 << formula;
    logic1.close();
}

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
    if(regex_search(out, match, rgx)){
       //       cout << match[1] << '\n';
    } 
    file.close();
    return out;

}

int main(int argc, char *argv[]){
    //Make it take in a file name
    regex rx("i[0-9]\\)*");
    string out = getPhrase(argv[1],"(define-fun");
    vector<string> tokens = formVector(out);
    string formula1 = getTokens(tokens, rx);
    writeFormula(formula1);
    return 0;
}
