// quine mccluskey utility functions
#pragma once
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;

typedef unsigned int uint;
#define DELIM '-'
#define DEBUG false


class Binary
{
private:
    /* data */
    uint binsize;             // number of inputs
    string bins;              //binary array representing the minterms
    vector<uint> in_minterms; // vector of minterm involved in the binary expressions
    bool checked;             // defaulted to false

public:
    Binary(uint binsize, uint minterm); //constructor, returns a Binary object
    Binary(uint binsize);
    Binary();
    string tostring(string alphabet); // convert binaries to string input equivalent
    string &getbins();
    vector<uint> &getinmins();
    uint getnumones(); // return the number of ones in minterm
    uint getsize();
    void check(); // check the binary
    bool ischecked();
    ~Binary(); // destructor, free memory allocated for Binary object
};

/* petrick binary for tabular method */
class PBinary
{
private:
    /* data */
    uint binsize;
    unordered_map<string, unordered_map<string, Binary>> pbins;

public:
    PBinary();
    PBinary(uint binsize);
    PBinary(uint binsize, uint pos, Binary bin);
    void simplify();                                          // clear unnecessary expression using boolean identity
    void operator*=(const PBinary &rhs); // and 2 PBinaries
    void operator+=(const PBinary &rhs); // or 2 PBinary
    PBinary &operator=(const PBinary &rhs);                   // or 2 PBinary
    uint getbinsize();
    unordered_map<string, unordered_map<string, Binary>> getpbins();
    ~PBinary();
};

bool isdeletable(string x, string y); // return true is Y is deletable
string minterm2bin(uint minterm, uint size);
bool compatible(Binary bin1, Binary bin2); // return true if bins are matcheable

string OR(string bin1, string bin2); // ORing two binaries
Binary match(Binary bin1, Binary bin2);
string quine_mccluskey(string inputs, string midterms, string dontcare); // takes a number of inputs and midterms, returns reduced expression
string simplify(unordered_map<string, Binary> unchecked, vector<uint> dontcare, string alphabet);
void petrick(unordered_map<uint, vector<Binary>> &primeimp_table, unordered_map<string, Binary> &res);
// uint numones(string bin); // return number of ones in binary
uint getbinnums(unordered_map<uint, vector<Binary>> primeimp);      // get max number of binary present
int8_t coldom(vector<uint> a, vector<uint> b, vector<uint> domain); // return 1 if b should be deleted or -1 if a should, 0 if none
int8_t rowdom(vector<Binary> a, vector<Binary> b, unordered_map<string, Binary> domain); // return 1 if a should be deleted or -1 if b should, 0 if none
bool crossmatch(
    vector<vector<Binary>> &curr,
    vector<vector<Binary>> &prev,
    unordered_map<string, Binary> &unchecked);

template <typename T>
void parse(vector<T> &dest, string input, T (*fn)(string));

/* basic data structure for the method */