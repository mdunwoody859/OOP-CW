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
Card::Card(int _value)
    :value(_value),secondValue(0){}
Card::Card(string _suit)
    :suit(_suit),value(0),secondValue(0){}
Card::Card(int _value, string _suit)
    :value(_value),suit(_suit),secondValue(0){}
Card::Card(string _cardNumber, string _suit, int _value)
    :cardNumber(_cardNumber),suit(_suit),value(_value),secondValue(0){}
Card::Card(string _cardNumber, string _suit, int _value, int _secondValue)
    :cardNumber(_cardNumber),suit(_suit),value(_value),secondValue(_secondValue){}

int Card::getValue(){
    return value;
}
string Card::getSuit(){
    return suit;
}
string Card::getValueString(){
    return cardNumber;
}
