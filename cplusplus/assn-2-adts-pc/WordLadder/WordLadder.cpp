
/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */
 
#include "genlib.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <iostream>
 
void findWord(Lexicon &dictionary, string start, string destination);
string findNext(string word, Lexicon &dictionary, Lexicon used);
 
 
int main(){
 
    Lexicon dictionary("EnglishWords.dat");
    string start;
    string destination;
 
    while (true)
    {
        while(true){
        cout << "Enter start word (RETURN to quit) : ";
        start = GetLine();
        if (start == "") return 0;
        else if(!dictionary.containsWord(start))
            cout << start<<" is not a vaild word! Please type again! "<<endl;
        else break;
        }
 
        while(true){
        cout << "Enter destination word (RETURN to quit) : ";
        destination = GetLine();
        if (destination == "") return 0;
        else if(!dictionary.containsWord(destination))
            cout << destination<<" is not a vaild word! Please type again! "<<endl;
        else break;
        }
 
        findWord(dictionary, start, destination);
    }
     
    return 0;
}
 
 
void findWord(Lexicon &dictionary, string start, string destination){
 
    Lexicon used;
    string nextWord;
 
    Queue<Vector<string>> queue;
    queue.clear();
 
    Vector<string> enqueueVector;
    enqueueVector.add(start);
     
    queue.enqueue(enqueueVector);
 
    while (true){
         
        if (queue.size() ==0){
            cout << "No ladder found."<< endl;
            break;
        }
 
        Vector<string> dequeueVector = queue.dequeue();
 
        while (true){
             
            nextWord = findNext(dequeueVector[dequeueVector.size()-1], dictionary, used);
             
            if (nextWord == destination){
 
                cout << "Found ladder: ";
 
                foreach (string records in dequeueVector){
                    cout << records << " -> ";
                }
 
                cout << destination << endl ;
 
                return;
 
            } 
             
            else if (nextWord != ""){
                Vector<string> addNew = dequeueVector;
                addNew.add(nextWord);
                queue.enqueue(addNew);
            }
             
            else if (nextWord =="")
                break;
 
            used.add(nextWord);
        }
    }
}
 
 
string findNext(string word, Lexicon &dictionary, Lexicon used){
    string nextWord;
 
    for (int i =0; i < word.length(); i++){
        nextWord = word;
        for (char ch = 'a'; ch <= 'z'; ch++){
            nextWord = nextWord.replace(i,1,1, ch);
     
            if (!used.containsWord(nextWord))
              if (dictionary.containsWord(nextWord))
                    return nextWord;
        }
    }
 
    return "";
}