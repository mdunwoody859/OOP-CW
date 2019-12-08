//
//  Hand.cpp
//  OOP CW
//
//  Created by Michael Dunwoody on 05/11/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "Card.hpp"
#include "Hand.hpp"

using namespace std;

Hand::Hand(){};
Hand::Hand(bool _player)
    :player(_player){};

bool Hand::isPlayer(){
    return player;
}

int Hand::getFirstValue(){
    return value[0];
}

int Hand::getSecondValue(){
    return value[1];
}

void Hand::displayTopCard(bool player){
    if (player){
        cout << "You were dealt the " << cards.back().getValueString() << " of " << cards.back().getSuit() << endl;
    }
    else {
        cout << "The dealer was dealt the " << cards.back().getValueString() << " of " << cards.back().getSuit() << endl;
    }
}

void Hand::dealCard(Card cardBeingDealt){
    cards.push_back(cardBeingDealt);
}
void Hand::calculateHandValue(){
    int total1 = 0;
    int total2 = 0;
    for (size_t i = 0; i < cards.size(); i++) {
        total1 += cards[i].getValue();
        if (cards[i].getValueString() == "ACE") {
            total2 += cards[i].getSecondValue();
        }
        else total2 += cards[i].getValue();
    }
    *value = total1;
    *(value + 1) = total2;
}

void Hand::clearCards(){
    cards.clear();
    cards.clear();
}

bool Hand::checkBust(){
    bool isBust = false;
    if (*value > 21 && *(value + 1) > 21) {
        isBust = true;
    }
    return isBust;
}

bool Hand::checkForNaturals(){
    calculateHandValue();
    if (getFirstValue() == 21 || getSecondValue() == 21) {
        return true;
    }
    else return false;
}

void Hand::displayHand(bool isPlayer, bool hideTopCard){
    
    calculateHandValue();//Calculates the hand's value for the player or dealer hand
    
    if (isPlayer) {//If the hand belongs to the player...
        cout << endl << "Your hand:"<<endl;
        for (size_t i = 0; i < cards.size(); i++) {
            cout << cards[i].getValueString() << " of " <<cards[i].getSuit()<<endl;
        }
        if (*value == *(value + 1)) {
            cout << "Total hand value:\t" << *value << endl;
        }
        else{
            cout << "Total hand value:\t" << *value << " or " << *(value+1) << endl;
        }
    }
    else{//If the hand belongs to the dealer
        if (cards.size() == 2) {
            if (hideTopCard) {
                //The dealer's second card is always face down at first
                cout << endl << "Dealer hand:\n"<<cards[0].getValueString() << " of "<<cards[0].getSuit()<<endl<<"The dealer's second card is face-down"<<endl;//dealerHand[1] is hidden
            }
            else {
                cout << endl << "Dealer hand:"<<endl;
                for (size_t i = 0; i < cards.size(); i++) {
                    cout << cards[i].getValueString() << " of " <<cards[i].getSuit()<<endl;
                }
                if (*value == *(value + 1)) {
                    cout << "Total hand value:\t" << *value << endl;
                }
                else{
                    cout << "Total hand value:\t" << *value << " or " << *(value+1) << endl;
                }
            }
            
            // Check for naturals - 10 card + ace.
            // If shown dealer card is a ten card or ace, they check their other card to see if they have a natural.
            // If so, collect all bets of players that do not have naturals.
            // If player has it and dealer does not, player receives 1.5x bet
            // If both have it, player gets their bet back but no winnings.
            // If neither have it, begin play
            if ((cards[0].getValue() >= 10 || cards[0].getSecondValue() >= 10) && hideTopCard) {//if first card is ace or 10
                cout << "The dealer is checking for blackjack..." <<endl;
                if (!(*value == 21 || *(value+1) == 21)) {
                    cout << "The dealer does not have blackjack."<<endl;
                }
                else {
                    cout << "The dealer has blackjack!"<<endl;//After here, main class continues
                }
            }
        }
        else {
            //In here goes any logic for displaying the dealer hand if they have 'hit'
            cout << endl << "Dealer hand:"<<endl;
            for (size_t i = 0; i < cards.size(); i++) {
                cout << cards[i].getValueString() << " of " <<cards[i].getSuit()<<endl;
            }
            if (*value == *(value + 1)) {
                cout << "Total hand value:\t" << *value << endl;
            }
            else{
                cout << "Total hand value:\t" << *value << " or " << *(value+1) << endl;
            }
        }
    }
}

void Hand::clear(){
    cards.~vector();
}

