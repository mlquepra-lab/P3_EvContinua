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
    return words.size();
}

int Dictionary::getOccurrences(const char c) const
{
    int n = 0;
    string w;
    for(const_iterator it = words.begin();it != words.end();it++) {
        w = *it;
        for (size_t i = 0; i < w.length(); ++i)
            if (w[i] == c)
            ++n;    
    }

    return n;
}
    
void Dictionary::anade(const Dictionary &dic){
    Dictionary::const_iterator it = dic.begin();

    for(; it != dic.end(); it++){
        if(!exists(*it)){
            words.insert(*it);
        }
    }    
}


bool Dictionary::insert(const string &val){
    pair<set<string>::iterator, bool> b = words.insert(val);
    return b.second;
}

Dictionary& Dictionary::operator=(const Dictionary &dic){
    clear();
    anade(dic);
    return *this;
}

istream& operator>>(istream &is, Dictionary &dic){
    string palabra;
    while (is >> palabra)
        dic.words.insert(palabra);
    return is;
}

ostream& operator<<(ostream &os, const Dictionary &dic){
    Dictionary::const_iterator it = dic.begin();

    for(; it != dic.end(); it++){
        os << *it;
        os << "\n";
    }

    return os;
}


// bool exists(const string& val)const{return words.count(val) > 0;} 
// Definición inline en .h

//bool erase(const string &val){return words.erase(val) > 0;}
// Definición inline en .h

//bool empty()const{return words.empty();}
// Definición inline en .h

vector<string> Dictionary::wordsOfLength(int length) const
{
    vector<string> palabras;
    for(const_iterator it=words.begin();it != words.end();it++) {
        if((*it).length() == length)
            palabras.push_back(*it);
    }

    return palabras;
}