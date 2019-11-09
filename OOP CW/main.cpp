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
#include "Hand.hpp"

using namespace std;

int balance = 0;
float bet = 0;

vector<Card> playingDeck;
Hand playerHandObj = Hand(true);//true as it is a player hand
Hand dealerHandObj = Hand(false);//false as it is a dealer hand

void init(){
    
    
    
    
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

void exitApplication(){
    cout <<"Bye!"<<endl;
    exit(0);
}

void dealCardToPlayer(){
    playerHandObj.dealCard(playingDeck.back());//Gives the player the card at the end of the deck
    playingDeck.pop_back();//Removes that card from the playingDeck
}

void dealCardToDealer(){
    dealerHandObj.dealCard(playingDeck.back());//Gives the dealer the card at the end of the deck
    playingDeck.pop_back();//Removes that card from the playingDeck
}


void createNewDeck(){
    cout << "Shuffling..."<<endl;
    playingDeck = Deck::setupDeck();
}

void dealerPlay(){
    dealerHandObj.calculateHandValue();
    if (dealerHandObj) {//Fix logic for how natural blackjacks are handled - move from Hand to main. Next up is programming the dealer 'AI'
        <#statements#>
    }
}

void standPlayer(){
    //So a player is standing. Dealer plays now.
    playerHandObj.calculateHandValue();
    int sumwithAceAsEleven = playerHandObj.getFirstValue();
    int sumwithAceAsOne = playerHandObj.getSecondValue();
    
    dealerPlay();
}

void setupGame(){//Method for setting up the beginning of a game
    dealCardToPlayer();
    dealCardToDealer();
    dealCardToPlayer();
    dealCardToDealer();
    playerHandObj.calculateHandValue();
    dealerHandObj.calculateHandValue();
    playerHandObj.displayHand(playerHandObj.isPlayer());
    dealerHandObj.displayHand(dealerHandObj.isPlayer());
}
void playerLoses(){
    balance -= bet;
    if (balance > 0) {
        cout << "You lose this round. You have lost £"<<bet<<"\nYour current balance is "<<balance<< endl;
        setupGame();//deal them cards again
    }
    else {//If the player loses all their money
        int i = 0;
        cout << "Thank you for playing! Unfortunately you have lost all your money.\nPlease press 1 if you wish to play again."<<endl;
        try {
            cin >> i;
        } catch (exception e) {
            exitApplication();
        }
        if (i == 1) {
            cout << "\n\n\n\n\n"<<endl;
            displayLogo();
        }
        exitApplication();
    }
}
void hitPlayer(){
    dealCardToPlayer();//Deal card to player and check if the player is bust
    playerHandObj.displayTopCard();
    playerHandObj.calculateHandValue();
    if (playerHandObj.checkBust()){
        cout << "Oh no! you've went bust"<<endl;
        playerLoses();
    }
}
int makeChoice(){
    int choice;
    cout << "Type '1' to hit or '2' to stand"<<endl;
    try {
        cin >> choice;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        makeChoice();
    }
    switch (choice){
        case 1:
        case 2:
            return choice; break;
        default: return 0;break;
    }
    return 0;
}

void runChoices(){
    int choice;
    do{
        choice = makeChoice();
        if (choice == 0) {
            choice = makeChoice();
        }
        switch (choice){
            case 1: hitPlayer();break;
            case 2: standPlayer();break;
            default: exitApplication();break;
        }
    }while (choice == 1);//Repeat this until the player stands
}

void initializeGame(){
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
    cout << "How much money do you have to play with?"<<endl;
    try {
        cin >> balance;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        initializeGame();
    }
    cout << "How much money do you wish to bet on this round?"<<endl;
    try {
        cin >> bet;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        initializeGame();
    }
    if (bet > balance) {
        cout << "You cannot bet more than your balance!"<<endl;
        initializeGame();
    }
    
    //Give a card to player then a card to dealer, then a second card to player then second to dealer. Hide the dealer's second card. Deal by popping off vector - dealing as if you're taking a card off the top/bottom of the deck. Hand class has been created for this
    createNewDeck();
    setupGame();
    runChoices();
    
}

void configureSettings(){
    
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
