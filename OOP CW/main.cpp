//
//  main.cpp
//  OOP CW
//
//  Created by Michael Dunwoody on 27/10/2019.
//  Copyright © 2019 Michael Dunwoody. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>

#include "Deck.hpp"
#include "Card.hpp"

using namespace std;

int balance = 0;
vector<Card> playingDeck;

void init(){
    // start by asking to press 1 if they want to play or press 2 to access settings
    // Play -> ask them how much money they have to play with
    // Take that value (Use as pointer/reference passes)
    // Create a deck of cards
    // Deck of cards - 13 values * 4 suits (Settings can multiply this again by no. of decks)
    // Get bet value of player for how much they wager on this round
    // Shuffle deck
    // One card given to player(s), then one to dealer (shown)
    // Second card given to player(s) then second to dealer (hidden)
    // Upon each deal, remove that card from the deck
    
    // Check for naturals - 10 card + ace.
    // If shown dealer card is a ten card or ace, they check their other card to see if they have a natural.
    // If so, collect all bets of players that do not have naturals.
    // If player has it and dealer does not, player receives 1.5x bet
    // If both have it, player gets their bet back but no winnings.
    // If neither have it, begin play
    
    // Player sees the suit and value of both their card and the total value of their hand
    // Can see the value of the dealer's shown cards
    // If a card is an ace, total hand may be calculated as 2 potential values
    // Can decide to 'Hit' or 'Stand'
    // Dealer must hit if their
}

int displayLogo(){
    int choice;
    
    cout << "   ______     _______."<<endl;
    cout << "  /     /\\   |   .   |\\"<<endl;
    cout << " /  '  /  \\  | .   . |.\\"<<endl;
    cout << "/_____/. . \\ |_______|.'|"<<endl;
    cout << "\\ . . \\    /  \\ ' .   \\'|"<<endl;
    cout << " \\ . . \\  /    \\____'__\\|"<<endl;
    cout << "  \\_____\\/"<<endl<<endl;;
    cout << "Welcome to blackjack!\n";
    
    cout << "Press 1 to play or press 2 to access game settings. Press any other key to exit" << endl;
    try{
        cin >> choice;
    }catch(exception ex){
        return 0;
    }
    return choice;
}

void initializeGame(){
    cout << "How much money do you have to play with?"<<endl;
    try {
        cin >> balance;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        initializeGame();
    }
    playingDeck = Deck::setupDeck();
    for (int i = 0; i < sizeof(playingDeck); i++) {
        cout << playingDeck[i].getValue() << " "<<playingDeck[i].getSuit();
    }
}

void configureSettings(){
    
}

void exitApplication(){
    cout <<"Bye!"<<endl;
    exit(0);
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int mode = displayLogo();
    switch (mode){
        case 1:
            initializeGame();break;
        case 2:
            configureSettings();break;
        default:
            exitApplication();break;
    }
    return 0;
}
