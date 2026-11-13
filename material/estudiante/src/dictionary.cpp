#include "../include/dictionary.h"
#include <iterator>
#include <set>
#include <vector>
using namespace std;

Dictionary::Dictionary(){
}

Dictionary::Dictionary(const Dictionary& other){
    words = other.words;
}

Dictionary::~Dictionary()
{
    words.clear();
}

void Dictionary::clear(){
    words.clear();
}

unsigned int Dictionary::size() const{
}

vector<string> Dictionary::wordsOfLength(int length){
    vector<string> resultado;

    for (set<string>::iterator it = words.begin(); it != words.end(); it++) {
        if(it->length() == length){
            resultado.push_back(*it);
        }
    }

    return resultado;
}

int Dictionary::getOccurrences(const char c){}
    
void Dictionary::anade(const Dictionary &dic){}


bool Dictionary::insert(const string &val){
}

Dictionary& Dictionary::operator=(const Dictionary &dic){}

istream& Dictionary::operator>>(istream &is, Dictionary &dic){}

ostream& Dictionary::operator<<(ostream &os, const Dictionary &dic){}

}