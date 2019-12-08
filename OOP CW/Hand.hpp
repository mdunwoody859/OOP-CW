//
//  Hand.hpp
//  OOP CW
//
//  Created by Michael Dunwoody on 05/11/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include "Card.hpp"

class Hand{
    
public:
    Hand();
    Hand(bool _player);
    bool isPlayer();
    void clear();
    void dealCard(Card cardBeingDealt);
    void displayHand(bool player, bool hide);
    void calculateHandValue();
    bool checkBust();
    bool checkForNaturals();
    void displayTopCard(bool player);//Grabs the card from top of stack - the last one which was dealt
    void clearCards();
    int getFirstValue();
    int getSecondValue();
private:
    std::vector<Card> cards;
    bool player;
    int value[2];
};
