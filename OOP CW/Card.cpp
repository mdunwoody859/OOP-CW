//
//  Card.cpp
//  OOP CW
//
//  Created by Michael Dunwoody on 27/10/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//

#include "Card.hpp"
#include <iostream>
using namespace std;

Card::Card():value(0),secondValue(0){}
Card::Card(int value)
    :value(value),secondValue(0){}
Card::Card(string suit)
    :suit(suit),value(0),secondValue(0){}
Card::Card(int value, string suit)
    :value(value),suit(suit),secondValue(0){}
Card::Card(string cardNumber, string suit, int value)
    :cardNumber(cardNumber),suit(suit),value(value),secondValue(0){}
Card::Card(string cardNumber, string suit, int value, int secondValue)
    :cardNumber(cardNumber),suit(suit),value(value),secondValue(secondValue){}

int Card::getValue(){
    return value;
}

int Card::getSecondValue(){
    return secondValue;
}
string Card::getSuit(){
    return suit;
}
string Card::getValueString(){
    return cardNumber;
}
