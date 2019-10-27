//
//  Card.hpp
//  OOP CW
//
//  Created by Michael Dunwoody on 27/10/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <string>

class Card{
public:
    Card();
    Card(int _value);
    Card(std::string _suit);
    Card(int value, std::string _suit);
    Card(std::string cardNumber, std::string _suit, int value);
    Card(std::string cardNumber, std::string _suit, int value, int secondValueForAces);
    int getValue();
    std::string getSuit();
    std::string getValueString();
private:
    const int value;
    const std::string suit;
    const std::string cardNumber;
    const int secondValue;
};
