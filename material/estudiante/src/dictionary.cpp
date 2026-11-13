#include "../include/dictionary.h"
#include <iterator>
#include <set>
#include <string>
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
    set<string>::iterator it = words.begin();
    
    for (; it != words.end(); it++) {
        if(it->length() == length){
            resultado.push_back(*it);
        }
    }

    return resultado;
}

int Dictionary::getOccurrences(const char c){}
    
void Dictionary::anade(const Dictionary &dic){
    Dictionary::const_iterator it = dic.begin();

    for(; it != dic.end(); it++){
        if(!exists(*it)){
            words.insert(*it);
        }
    }    
}


bool Dictionary::insert(const string &val){
}

Dictionary& Dictionary::operator=(const Dictionary &dic){
    clear();
    anade(dic);
    return *this;
}

istream& operator>>(istream &is, Dictionary &dic){}

ostream& operator<<(ostream &os, const Dictionary &dic){
    Dictionary::const_iterator it = dic.begin();

    for(; it != dic.end(); it++){
        os << *it;
    }

    return os;
}

