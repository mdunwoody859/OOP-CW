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
#include <random>
#include "Card.hpp"

class Deck{
public:
    Deck();
    Deck(int mode);
    static std::vector<Card> setupDeck();
    static std::default_random_engine getRandomEngine();
private:
    static std::default_random_engine engine;
};
