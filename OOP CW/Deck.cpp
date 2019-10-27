//
//  Deck.cpp
//  OOP CW
//
//  Created by Michael Dunwoody on 27/10/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//

#include "Deck.hpp"
#include "Card.hpp"

#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef enum {CLUBS, DIAMONDS, HEARTS, SPADES} SUITES;
typedef enum {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING} NUMBERS;

Deck::Deck(){}
Deck::Deck(int mode){}

vector<Card> Deck::setupDeck(){
    //for each SUITE, create an ace and then a card of each NUMBERS value
    vector<Card> deck;
    
    map<string, int> numberValues;
    numberValues["TWO"] = 2;
    numberValues["THREE"] = 3;
    numberValues["FOUR"] = 4;
    numberValues["FIVE"] = 5;
    numberValues["SIX"] = 6;
    numberValues["SEVEN"] = 7;
    numberValues["EIGHT"] = 8;
    numberValues["NINE"] = 9;
    numberValues["TEN"] = 10;
    numberValues["JACK"] = 10;
    numberValues["QUEEN"] = 10;
    numberValues["KING"] = 10;
    
    string suites[4] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    for (int i = 0; i < sizeof(suites); i++) {
        Card temp = Card("ACE", suites[i], 1, 11);
        deck.push_back(temp);//adds ace to deck
        map<string, int>::iterator it = numberValues.begin();
        while (it != numberValues.end()) {
            Card temp = Card(it->first, suites[i], it->second);
            deck.push_back(temp);
        }
    }
    return deck;
}

