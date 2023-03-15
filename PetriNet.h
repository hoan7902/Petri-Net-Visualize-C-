#ifndef PETRINET_H_ 
#define PETRINET_H_ 
#include<iostream>
#include "graphics.h"
#include<vector> 
#include<map> 
using namespace std;
class PetriNet
{ 
private:
    class Place;
    class Transition {
        string label;
        vector<Place*> list_in;     
        vector<Place*> list_out;  
        friend class PetriNet;
        Transition(string label) {
            this->label = label;
        }
    };
    class Place {
        string label;
        int numOfTokens;
        vector<Transition*> list_in;
        vector<Transition*> list_out;
        friend class PetriNet;
    public:
        Place(string label) {
            numOfTokens = 0;
            this->label = label;
        }
    };
private:
    vector<Place*> listPlace;
    vector<Transition*> listTransition;
public:
    void pushPlace(string label) {  // push Place into Petri Net 
        Place* p = new Place(label);
        listPlace.push_back(p);
    }
    void pushTransition(string label) { //push transition into Petri Net 
        Transition* t = new Transition(label);
        listTransition.push_back(t);
    }
    Place* findPlace(string label) {
        for (size_t i = 0; i < listPlace.size(); i++) {
            if (listPlace[i]->label == label) return listPlace[i];
        }
        return NULL;
    }
    Transition* findTransision(string label) {
        for (size_t i = 0; i < listTransition.size(); i++) {
            if (listTransition[i]->label == label) return listTransition[i];
        }
        return NULL;
    }
    void arcPT(string place, string transition) {
        Place* p = findPlace(place);
        Transition* t = findTransision(transition);
        p->list_out.push_back(t);
        t->list_in.push_back(p);
    }
    void arcTP(string transition, string place) {
        Place* p = findPlace(place);
        Transition* t = findTransision(transition);
        t->list_out.push_back(p);
        p->list_in.push_back(t);
    }
    map<string, int> getMarking() {
        map<string, int> res;
        for (size_t i = 0; i < listPlace.size(); i++) {
            res.insert(pair<string, int>(listPlace[i]->label, listPlace[i]->numOfTokens));
        }
        return res;
    }
    void setMarking(map<string,int> marking) { 
        for (auto const& pair : marking) {
            Place* p = findPlace(pair.first);
            p->numOfTokens = pair.second;
        }
    }
    void setMarking() {
        cout << "Enter the marking of Petri Net: [" ;
        for (size_t i = 0; i < listPlace.size(); i++) {
            cout<<"... " ;
            cout<<listPlace[i]->label ;
            if (i != listPlace.size() - 1) cout<<"," ;
            else cout<<"]\n" ;
        }
        for (size_t i = 0; i < listPlace.size(); i++) {
            cin >> listPlace[i]->numOfTokens;
        }
    }
    bool enabled(string transition) {
        Transition* t = findTransision(transition);
        if (t == NULL) return false;
        for (size_t i = 0; i < t->list_in.size(); i++) {
            if (t->list_in[i]->numOfTokens == 0) return false;
        }
        return true;
    }
    bool firing(string transition) {
        if (!enabled(transition)) return false ;
        Transition* t = findTransision(transition);
        for (size_t i = 0; i < t->list_in.size(); i++) {
            t->list_in[i]->numOfTokens--;
        }
        for (size_t i = 0; i < t->list_out.size(); i++) {
            t->list_out[i]->numOfTokens++;
        }
        return true;
    }
    void printMarking() {
        textcolor(15);
        cout << " [";
        for (size_t i = 0; i < listPlace.size(); i++) {
            textcolor(3);
            cout << listPlace[i]->numOfTokens;
            textcolor(15);
            cout << " " << listPlace[i]->label;
            if (i != listPlace.size() - 1) cout << ", ";
        }
        textcolor(15); cout << "]\n";
    }
    void cleanUp() {
        while (!listPlace.empty()) {
            delete listPlace.back();
            listPlace.pop_back();
        }
        while (!listTransition.empty()) {
            delete listTransition.back();
            listTransition.pop_back();
        }
    }
};
#endif // !PETRINET_H_ 

