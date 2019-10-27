//
//  Deck.hpp
//  OOP CW
//
//  Created by Michael Dunwoody on 27/10/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include "Card.hpp"

class Deck{
public:
    Deck();
    Deck(int mode);
    static std::vector<Card> setupDeck();
};
