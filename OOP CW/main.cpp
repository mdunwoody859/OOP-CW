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
vector<Card> playerHand;
vector<Card> dealerHand;

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

void dealCardToPlayer(){
    playingDeck.back();
    playerHand.push_back(playingDeck.back());//Gives the player the card at the end of the deck
    playingDeck.pop_back();//Removes that card from the playingDeck
}

void dealCardToDealer(){
    playingDeck.back();
    dealerHand.push_back(playingDeck.back());//Gives the dealer the card at the end of the deck
    playingDeck.pop_back();//Removes that card from the playingDeck
}

void initializeGame(){
    cout << "How much money do you have to play with?"<<endl;
    try {
        cin >> balance;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        initializeGame();
    }
    cout << "Shuffling..."<<endl;
    playingDeck = Deck::setupDeck();
    dealCardToPlayer();
    dealCardToDealer();
    dealCardToPlayer();
    dealCardToDealer();
    cout << endl << "Your hand:\n"<<playerHand[0].getValueString() << " of "<<playerHand[0].getSuit()<<endl<<playerHand[1].getValueString()<<" of "<< playerHand[1].getSuit();
    
    cout << endl << "Dealer hand:\n"<<dealerHand[0].getValueString() << " of "<<dealerHand[0].getSuit()<<endl<<dealerHand[1].getValueString()<<" of "<< dealerHand[1].getSuit()<<endl;//HIDE SECOND CARD!!
    //Give a card to player then a card to dealer, then a second card to player then second to dealer. Hide the dealer's second card. Deal by popping off vector - dealing as if you're taking a card off the top/bottom of the deck. Maybe create Hand class?
    
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
