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
    Card(int value);
    Card(std::string suit);
    Card(int value, std::string suit);
    Card(std::string cardNumber, std::string suit, int value);
    Card(std::string cardNumber, std::string suit, int value, int secondValueForAces);
    int getValue();
    std::string getSuit();
    std::string getValueString();
private:
    int value;
    std::string suit;
    std::string cardNumber;
    int secondValue;
};
