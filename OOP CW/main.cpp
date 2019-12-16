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
#include <fstream>

#include "Deck.hpp"
#include "Card.hpp"
#include "Hand.hpp"

using namespace std;

float balance = 0;
bool handInPlay = true;//control boolean used to make play stop if a hit makes a player bust
float bet = 0;

vector<Card> playingDeck;
Hand playerHandObj = Hand(true);//true as it is a player hand
Hand dealerHandObj = Hand(false);//false as it is a dealer hand
void mainMenu();

void setBalance(){
    cout << "How much money do you have to play with?"<<endl;
    try {
        cin >> balance;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        setBalance();
    }
}
void setRoundBet(){//
    cout << "How much money do you wish to bet on this round?"<<endl;
    try {
        cin >> bet;
        if (bet > balance) {
            cout << "You cannot bet more than your balance!"<< " ( $"<<balance<<")"<<endl;
            setRoundBet();
        }
		else {
			balance -= bet;
		}
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        setRoundBet();
    }
    // Player sees the suit and value of both their card and the total value of their hand
    // Can see the value of the dealer's shown cards
    // If a card is an ace, total hand may be calculated as 2 potential values
    // Can decide to 'Hit' or 'Stand'
    // Dealer must hit if their total is under 17
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

void setupGame(){//Method for setting up the beginning of a game
    dealCardToPlayer();
    dealCardToDealer();
    dealCardToPlayer();
    dealCardToDealer();
    playerHandObj.calculateHandValue();
    dealerHandObj.calculateHandValue();
    playerHandObj.displayHand(playerHandObj.isPlayer(), false);
    dealerHandObj.displayHand(dealerHandObj.isPlayer(), true);
}

void clearHands(){
    //Cleanup method to destroy the cards in each player's hand. These cards will not be added back to the deck and are instead 'discarded'. The players will be dealt cards again if they wish to play again, but it will be from an ever-diminishing deck as it would be with a real-life deck of cards.
    playerHandObj.clearCards();
    dealerHandObj.clearCards();
    handInPlay = false;
}

void displayBalance(){
    cout << "Your current balance is $"<< balance << endl;
}

void playerLoses(){
    handInPlay = false;
    clearHands();
    if (balance > 0) {
        cout << "You lose this round. You have lost $"<<bet<<endl;
        displayBalance();
        //deal them cards again - runGame runs. Maybe run a clearHand method now?
        //prompt for another round?
    }
    else {//If the player loses all their money
        int i = 0;
        cout << "Thank you for playing! Unfortunately you have lost all your money.\nPlease press 1 if you wish to return to the main menu."<<endl;
        try {
            cin >> i;
        } catch (exception e) {
            exitApplication();
        }
        if (i == 1) {
            cout << "\n\n\n\n\n"<<endl;
            mainMenu();//Make them set a new balance before runGame takes over and prompts bets
        }
        else {
            exitApplication();
        }
    }
}
void runDraw(){
    handInPlay = false;
    clearHands();
    balance += bet;
    cout << "This round ended in a draw"<<endl;
    displayBalance();
    bet = 0;
}
void playerWins(){
    handInPlay = false;
    clearHands();
    float winnings = 2* bet;
    balance += winnings;
    bet = 0;
    cout << "Congatulations! You have won this round!" <<endl;
    displayBalance();
}
void hitPlayer(){
    dealCardToPlayer();//Deal card to player and check if the player is bust
    playerHandObj.displayTopCard(true);
    playerHandObj.calculateHandValue();
    playerHandObj.displayHand(1, 0);
    if (playerHandObj.checkBust()){
        cout << "Oh no! you've gone bust"<<endl;
        handInPlay = false;
    }
    if (playerHandObj.getFirstValue() == 21 || playerHandObj.getSecondValue() == 21) {
        handInPlay = false;
    }
}

void hitDealer(){
    cout << "The dealer hits"<<endl;
    dealCardToDealer();//Deal card to player and check if the player is bust
    dealerHandObj.displayTopCard(false);
    dealerHandObj.calculateHandValue();
    if (dealerHandObj.checkBust()){
        cout << "Congratulations! The dealer has gone bust"<<endl;
        handInPlay = false;
    }
}

void revealSecondCard(){
    cout << "The dealer flips over his second card" <<endl;
    dealerHandObj.displayHand(false,false);
}

bool dealerPlay(){
    int hand1 = dealerHandObj.getFirstValue();
    int hand2 = dealerHandObj.getSecondValue();
    if (hand1 < 17 || hand2 < 17) {
        //Next up is programming the dealer 'AI'
        //if both are less than 17, dealer must hit
        hitDealer();
        if (hand1 > 21 && hand2 > 21) {
            return false;
        }
        return true;
    }
    return false;
}

void determineWinner(int p1, int p2, int d1, int d2){
    if (p1 > 21 && p2 > 21) {
        playerLoses();
    }
    if (d1 > 21 && d2 > 21) {
        playerWins();
    }
    else {
        if (p1 == p2 && d1 == d2) {//no aces
            if (p1 > d1) {
                playerWins();
            }
            else if (d1 > p1) {
                playerLoses();
            }
            else {
                runDraw();
            }
        }
        if (p1 != p2 && d1 == d2) {//if player has an ace and dealer does not
            if (p2 > 21){//player's 11 score is bust
                if (p1 > d1) {
                    playerWins();
                }
                else if (d1 > p1){
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
            else {//p2 not bust, therefore we know it's a better hand than p1 where ace=1
                if (p2 > d1){
                    playerWins();//player is not bust so if they win either hand they win since d1==d2
                }
                else if (p2 < d1) {
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
        }
        if (p1 == p2 && d1 != d2) {//if dealer has an ace and player does not
            if (d2 > 21) {//if dealer is bust with 11 hand
                if (p1 > d1) {
                    playerWins();
                }
                else if (d1 > p1) {
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
            else {//d2 is not bust, therefore will be a better hand than d1
                if (p1 > d2) {
                    playerWins();
                }
                else if (d2 > p1){
                    playerWins();
                }
                else {
                    runDraw();
                }
            }
        }
        if (p1 != p2 && d1 != d2) {//both player and dealer have aces
            if (p2 >21 && d2 > 21) {//Both players 11 value hand would be bust
                if (p1 > d1) {
                    playerWins();
                }
                else if (p1 < d1) {
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
            else if (p2 > 21){//p2 is bust, d2 not
                if (p1 > d2){//d2 not bust so will be a better hand than d1
                    playerWins();
                }
                else if (p1 < d2){
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
            else if (d2 > 21){//d2 bust, p2 not
                if (p2 > d1) {
                    playerWins();
                }
                else if (p2 < d1){
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
            else {//Neither player bust, therefore p2 > p1 && d2 > d1
                if (p2 > d2) {
                    playerWins();
                }
                else if (p2 < d2){
                    playerLoses();
                }
                else {
                    runDraw();
                }
            }
        }
    }
}

void standPlayer(){
    //So a player is standing. Dealer plays now.
    playerHandObj.calculateHandValue();
    int playerFirstValue = playerHandObj.getFirstValue();
    int playerSecondValue = playerHandObj.getSecondValue();
    if (playerFirstValue > 21 && playerSecondValue > 21) {
        playerLoses();
    }
    else {
        //First, the dealer flips his covered card
        revealSecondCard();
        bool dealerIsPlaying = true;
        while (dealerIsPlaying) {
            dealerIsPlaying = dealerPlay();//return true on hitDealer
        }//only breaks when the dealer is standing
        dealerHandObj.calculateHandValue();
        int dealerFirstValue = dealerHandObj.getFirstValue();
        int dealerSecondValue = dealerHandObj.getSecondValue();
        //following if statements determine winner
        determineWinner(playerFirstValue,playerSecondValue,dealerFirstValue,dealerSecondValue);
            //first value has ace as 1, second as 11
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
    handInPlay = true;
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
    }while (choice == 1 && handInPlay);//Repeat this until the player stands
    if (choice == 1 && !handInPlay) {
        standPlayer();//if the player has hit and the hand is no longer in play, they did not stand but have reached 21
    }
}

bool runNaturals(){
    bool playerNatural = playerHandObj.checkForNaturals();
    bool dealerNatural = dealerHandObj.checkForNaturals();
    if (dealerNatural) {
        if (playerNatural) {
            cout << "But so do you!"<<endl;
            runDraw();
        }
        else {
            playerLoses();
        }
    }
    else if (playerNatural) {
        cout << "You have blackjack!"<<endl;
        playerWins();
    }
	if (playerNatural || dealerNatural){
		return true;
	}
	return false;
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
    setRoundBet();
    //Give a card to player then a card to dealer, then a second card to player then second to dealer. Hide the dealer's second card. Deal by popping off vector - dealing as if you're taking a card off the top/bottom of the deck. Hand class has been created for this
    setupGame();
    bool naturals = runNaturals();
    //if both have naturals, cout "but so do you!"
    if (!naturals)
		runChoices();
}

void configureSettings(){
    int noOfDecks;
    cout << "\n\nHow many decks do you want to play with?\nEnter a value between 1 and 10" << endl;
    try {
        cin >> noOfDecks;
    } catch (exception) {
        cout << "Please enter a numeric value between 1 and 10" << endl;
        configureSettings();
    }
    if (!(noOfDecks >= 1 && noOfDecks <= 10)) {
        cout << "Please enter a numeric value between 1 and 10" << endl;
        configureSettings();
    }
    string filepath = "settings.txt";
    fstream myFile;
    myFile.open(filepath);
    if (myFile.is_open()) {
        myFile << noOfDecks;
    }
    else {
        cout << "an error has occurred. Please check that settings.txt is in the project folder" << endl;
    }
    myFile.close();
    mainMenu();
}

void runGame(){
    initializeGame();
    int choice;
    cout << "Type '1' to play another round!"<<endl;
    try {
        cin >> choice;
    }catch(exception ex){
        cout << "Whoa! That's not a number!"<<endl;
        exitApplication();
    }
    switch (choice) {
        case 1:
            runGame();//If they're playing again, run this so initializeGame runs then the prompts
            break;
            
        default: exitApplication();
            break;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    mainMenu();
}

void mainMenu(){
    int mode = displayLogo();
    switch (mode){
        case 1:
            createNewDeck();
            setBalance();
            runGame();break;
        case 2:
            configureSettings();break;
        default:
            exitApplication();break;
    }
}
//Clear hands after rounds.
//Prompt for playing another round, then runGame() upon end of last round
