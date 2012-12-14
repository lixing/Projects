/*
 * File: ListCompletions.cpp
 * ----------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the starter project for the cell phone mind reading problem on
 * Assignment #3
 * [TODO: extend the documentation]
 */
  
#include "genlib.h"
#include "simpio.h"
#include "lexicon.h"
#include <iostream>
 
void ListCompletions(string digits, Lexicon & lex);
void listCompletions(string digits, Lexicon lex);

 
int main() {
    Lexicon lex("EnglishWords.dat");
    string digits = "";
    string reply;
 
    //ask the user to input the digits.
    while(true){
    cout << "input numbers without 0 and 1: ";
    digits = GetLine();
    listCompletions(digits,lex);
 
    cout << "Do you want to play again?(press n to exit).";
    reply = GetLine();
    if(reply == "n" || reply == "no") break;
    }
 
    return 0;
}
 
//To tranfer the digit to its corresponding letters.
string digitToLetters(char c) {
        switch (c) {
        case '0': return "0";
        case '1': return "1";
        case '2': return "abc";
        case '3': return "def";
        case '4': return "ghi";
        case '5': return "jkl";
        case '6': return "mno";
        case '7': return "pqrs";
        case '8': return "tuv";
        case '9': return "wxyz";
        default: cout <<"Bad digit" <<endl;
                 return "";
}
}
 
 
void listCompletions(string prefix, string digits, Lexicon lex) {
     
    //the input digits have been analyzed
    if (digits == "") {
        if(lex.containsWord(prefix))
           cout << prefix <<endl;
 
 
        //To generate the extended words by adding letters from a to z.
        if(lex.containsPrefix(prefix)){
            for(char i= 'a'; i< 'z'; i++){
               if(i == 'a')
               prefix += i;
 
               //change the last letter.
               else prefix[prefix.length() - 1] = i;
 
               listCompletions(prefix, "", lex);
            }
        }
    }
     
     //analyze the input digit
     else {
            char ch = digits[0];
            string letters = digitToLetters(ch);
 
            //to analyze every possiblity of the letters for each digit.Read the digit's all coresponding letters.
            for (int i = 0; i < letters.length(); i++) {
                                   
            //if the letters are legal prefix, go to next letter
             if (lex.containsPrefix(prefix + letters[i])) {
                 listCompletions(prefix + letters[i],digits.substr(1,digits.length() - 1), lex);
                                      
             }
        }
  
     }
 }
  
//Wrapper. To call listCompletions(string prefix, string digits, Lexicon lex).
void listCompletions(string digits, Lexicon lex) {
      listCompletions("", digits, lex);
}