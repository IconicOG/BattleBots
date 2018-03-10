// BattleBots.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
//Structure to hold current battle bots
struct bot {
	std::string name;
	int health;
	int attack;
	int defense;
	int random;
	int swift;
};
struct match {
	//type of match
	std::string type;
	//Robot #1 stats
	bot one;

	//Robot#2 stats
	bot two;

};
//A void function that has a short introduction to the game
void introduction()
{
	//Welcomes the player
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("     WELCOME TO BATTLE BOTS!!!!!\n     --------- HYPE ------------\n          ARE YOU READY???\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	std::string temp;
	//gets input
	std::cin.ignore();
	std::getline(std::cin, temp);
	//Ignores the input and let's the user know the game will begin
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("DOESN'T MATTER!! LET'S START!!!\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Temp for the actual function
void playAgain();
//Capitalize each letter in a word or leave it as it is
std::string upperAllLetters(std::string word) {
	//Temp variable to hold word
	std::string fixUp = "";
	//Upper case the input if it vaguely fits the size of the desired inputs
	if (word.length() == 6 || word.length() == 7 || word.length() == 9) {
		//Run through each character and make a word
		for (int i = 0; i < word.length(); i++) {
			if (islower(word[i])) {
				fixUp += toupper(word[i]);
			}
			else {
				//Assume the character is alreayd capitalized
				fixUp += word[i];
			}
		}
	}
	return fixUp;
}
//This function will return a string that will give information on the # of players and game type
std::string chooseGameMode()
{
	//Will prompt the users to fill out if there are 1 or 2 player 
	printf("----------------------------------------------------------------------\n");
	printf("Enter the number of players: 1 player or 2 players? (Just the number!)\n");
	printf("Note that 1 player will lead to a tournament style while 2 players will be fighting against each other!\n");
	std::string players;
	std::getline(std::cin, players);
	//Checks for invalid responses and will continually prompt users to enter either or
	while ((players != "1" && players != "2")) {
		//Continue to prompt user to enter the follwoing
		printf("Invalid input.\nEnter: 1 or 2!\n");
		std::getline(std::cin, players);
	}
	//Holds the type of game choice they will play
	std::string gameType;
	//Will figure out if the user wants to play automatically or manually
	printf("----------------------------------------------\n");
	printf("Enter the type of game: manual or automatic?\n Note that manual means you can choose to attack or defend while automatic is done by the computer\n");
	//Get their choice
	std::getline(std::cin, gameType);
	gameType = upperAllLetters(gameType);
	//Ensures that one of the two inputs were submitted
	while (!(gameType == "AUTOMATIC" || gameType == "MANUAL")) {
		//Continue to prompt them to choose of of the options
		printf("Enter either manual or automatic for game type!\n");
		//Get their choice
		std::getline(std::cin, gameType);
		//UpperCase all letters so automatic == AUTOMATIC
		gameType = upperAllLetters(gameType);
	}
	//return the combination of the # of players and game type
	return (players + gameType);
}
//Will produce a  true or false if the robot dodged
bool dodgeAttack(int n) {
	//Will dodge if the chanceOfDodge is greater than the 
	int chanceOfDodge;
		chanceOfDodge=	rand() % n;
	int dodgeRate = rand() % 10000 + 1;
	//Will only dodge if the chanceofDodge is greater than the dodgeRate
	return chanceOfDodge > dodgeRate;
}
//Decipher the input for the move of the player
void decidedMove(int *v1) {
	//The string that will hold the input of what they want to do
	std::string move;
	//Prompt user to choose a move
	printf("----------------------------------------------------\n");
	printf("Enter attack or defense\n");
	do {
		//Take in what the user wants to do
		std::getline(std::cin, move);
		move = upperAllLetters(move);
		if (move == "ATTACK") {
			//Set the act value so it guarantees attack
			*v1 = 0;
		}
		else if (move == "DEFENSE") {
			//ensures they have to attack
			*v1 = 10000;
		}
		else {
			//Prompt them to correctly enter stuff
			printf("Invalid input!! Please enter attack or defense\n");
		}
	} while (move != "ATTACK" && move != "DEFENSE");
}
//startBattles will initiate the battle phase
bool startBattles(struct match *val) {
	//Start the introduction
	printf("-------------------------------------------------------------------------------\n");
	printf("WE HAVE TWO ROBOTS WITH AMAZING BUILDS! LET'S SEE WHAT THEY CAN DO NOW!\n");
	//Start the autobattle
	printf("First we have %s with an attack power of %d, defense of %d, and health of %d!\n", (val->one).name.c_str(), (val->one).attack, (val->one).defense, (val->one).health);
	printf("Then we have %s with an attack power of %d, defense of %d, and health of %d!\n", (val->two).name.c_str(), (val->two).attack, (val->two).defense, (val->two).health);
	while (true) {
		if ((val->one).health <= 0 && (val->two).health <= 0) {
			//Will continue to have the robots enter more and more rounds until someone won
			printf("-----------------------------------------------------\n");
			printf("Since there is a tie... WE WILL GO INTO ANOTHER ROUND!\n");
			return startBattles(val);
		}
		else if ((val->two).health <= 0) {
			//Tells the user that player 1 won
			printf("--------------------------------------------------\n");
			printf("WINNER!!!! %s WON THIS ROUND!!\n", (val->one).name.c_str());
			printf("--------------------------------------------------\n");
			return true;
		}
		else if ((val->one).health <= 0) {
			//Says that Player 2 won
			printf("--------------------------------------------------\n");
			printf("WINNER!!!! %s WON THIS ROUND!!\n", (val->two).name.c_str());
			printf("--------------------------------------------------\n");
			return false;

		}
		//Initialize player 1 and player 2 move
		int v1, v2;
		//Checks the gamemode
		if (val->type == "1AUTOMATIC" || val->type == "2AUTOMATIC") {
			//randomly generate a number between 1 to 100
			v1 = rand() % 100 + 1;
			v2 = rand() % 100 + 1;
		}
		else if (val->type == "1MANUAL") {
			decidedMove(&v1);
			//Randomly decide if the second player should attack
			v2 = rand() % 100 + 1;
		}
		else {
			if (rand() % (val->one).swift + 1 > rand() % (val->two).swift + 1) {
				//Prompt the user to make a move (player 1 goes first)
				decidedMove(&v1);
				decidedMove(&v2);
			}
			else {
				//Prompt the user to make a move (player 2 goes first)
				decidedMove(&v2);
				decidedMove(&v1);
			}
		}

		//Checks the attack and defend pattern based off the result
		if (v1 <= (val->one).random && v2 <= (val->two).random) {
			//Both players attacked, let the player know
			printf("WOW! BOTH ROBOTS ATTACKED EACH OTHER\n");
			//Check if any of them dodged
			int dodge1 = dodgeAttack((val->one).swift), dodge2 = dodgeAttack((val->two).swift);
			if (dodge1 && dodge2) {
				//When they both dodged, no damage is taken
				printf("HOW IS THIS POSSIBLE! THEY BOTH DODGED THE ATTACKS?!??\n");
			}
			else if (dodge1) {
				//Only player 2 gets hurt since player 1 dodged
				printf("Somehow %s ended up dodging that attack!\n", (val->one).name.c_str());
				(val->two).health -= (val->one).attack;

			}
			else if (dodge2) {
				//Player 2 dodged and managed to hit player 1
				printf("Woah! %s managed to hit %s and dodge the attack!!!\n", (val->two).name.c_str(), (val->one).name.c_str());
				(val->one).health -= (val->two).attack;
			}
			else {
				//Reduce health since no one dodged
				(val->one).health -= (val->two).attack;
				(val->two).health -= (val->one).attack;
			}
		}
		else if (v1 <= (val->one).random&& v2 > (val->two).random) {
			int dodge1 = dodgeAttack((val->two).swift);
			if (dodge1) {
				//Player 2 managed to dodge player 1's attack
				printf("%s went for the attack! Good thing %s dodged!!!\n", (val->one).name.c_str(), (val->two).name.c_str());
			}
			else {
				//Informs the user that the first player attacked while the second defended
				printf("%s went for the attack! Good thing %s blocked!\n", (val->one).name.c_str(), (val->two).name.c_str());
				//Checks if the attack is greater than the defense
				if ((val->one).attack> (val->two).defense) {
					//If so, subtract the health damage
					(val->two).health -= ((val->one).attack - (val->two).defense);
					printf("Even while defending, that's gotta hurt!\n");
				}
				else {
					//Otherwise inform user that no damage was taken
					printf("%s's defenses are too strong! %s didn't look hurt at all!\n", (val->two).name.c_str(), (val->two).name.c_str());
				}
			}
		}
		//If player 1 defends and player 2 attacks
		else if (v1 > (val->one).random&& v2 <= (val->two).random) {
			int dodge1 = dodgeAttack((val->one).swift);
			if (dodge1) {
				//Similair to the above
				printf("%s went for the attack! Good thing %s dodged!!!\n", (val->two).name.c_str(), (val->one).name.c_str());
			}
			else {
				//Informs the user that the 2nd player attacked while the first defended
				printf("%s went for the attack! Good thing %s blocked!\n", (val->two).name.c_str(), (val->one).name.c_str());
				//Checks if the attack is greater than the defense
				if ((val->two).attack > (val->one).defense) {
					//If so, subtract the health damage
					(val->one).health -= ((val->two).attack - (val->one).defense);
					printf("Even while defending, that's gotta hurt!\n");
				}
				else {
					//Otherwise inform user that no damage was taken
					printf("%s's defenses are too strong! %s didn't look hurt at all!\n", (val->one).name.c_str(), (val->one).name.c_str());
				}
			}

		}
		else {
			//The case where no one attacks
			printf("THEY BOTH DEFENDED! LOOKS LIKE THEY'RE PLAYING A BIT SAFE!!!!\n");
		}
		//Updates health and condition of robots
		printf("%s is at %d and %s is at %d\n", (val->one).name.c_str(), (val->one).health, (val->two).name.c_str(), (val->two).health);

		if (val->type == "1AUTOMATIC" || val->type == "2AUTOMATIC") {
			//When the game type is automatic, this will allow players to break down steps of what is happening
			printf("Press Enter to Continue\n");
			//Allows players to slowly see the progress
			std::string tempVariable;
			std::getline(std::cin, tempVariable);
		}
	}

}

//A subprogram that will continue to prompt users to enter valid integers
int correctInteger(std::string statType, int boundValue) {
	int x;
	printf("%s: ", statType.c_str());
	do {
		std::cin >> x;
		if (std::cin.fail() || x > boundValue || x < 0) {
			//Clear the error state of the buffering
			std::cin.clear();
			//Ignores the rest of the line of the input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//Prompt them to input a valid integer
			printf("Enter a valid integer within the bounds!!!\n %s: ", statType.c_str());
			x = -1;
		}
	} while (x > boundValue || x < 0);
	//Ignores the rest of the line of the input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return x;
}
//Assign new robot information
void implementRobot(struct bot *val, std::string type) {
	//Prompt the player to input the correct stats for robot and explain how points should be allocated
	printf("Split the 2500 points between the Health, Attack, Defense and Swift by entering stats:\n");
	printf("To clarify, health is how much additonal health (to the base of 5000) the robot has, attack is the damage the robot will give, defense will reduce damage taken from enemy's attack, and swift gives a chance to dodge!\n");
	//variable to hold the stats temporary
	int health, attack, swift, defense;
	while (true) {
		//Gets input for stats & prompt users to initially add stats
		health = correctInteger("Health", 2500);
		attack = correctInteger("Attack", 2500);
		defense = correctInteger("Defense", 2500);
		swift = correctInteger("Swift", 2500);
		//Tell them what they made
		printf("Health: %d, Attack: %d, Defense: %d, and Swiftness: %d\n", health, attack, defense, swift);
		//Checks if the stats are properly allocated
		if (health + attack + defense + swift == 2500) {
			break;
		}
		else {
			//Will warn them of the issue
			if (health + attack + defense + swift > 2500) {
				//Warns them they have uused more than they are allowed
				printf("ERROR!! You had %d more points than desired. Try again!\n", health + attack + defense + swift - 2500);
			}
			else {
				//Warms them they have not used all their points
				printf("ERROR!! You need to use %d more points. Try again!\n", 2500 - health - attack - defense - swift);
			}
			//Will prompt them to try again
			printf("Split the 2500 points between the Health, Attack and Defense by entering stats:\n");
		}
	}
	//Gives the player the que to give the robot a name
	printf("Now we have the robot...: ");
	//Saves the name
	std::string name;
	std::getline(std::cin, name);
	printf("\n");
	//For automatic game types, have a % of how often they want the robot to attack
	int box = 0;
	if (type == "1AUTOMATIC" || type == "2AUTOMATIC") {
		//Choose how often the person attacks
		std::cout << "Put in a number from 1 to 100. The higher the number the more likely you'll attack!" << "\n";
		box = correctInteger("Attack rate of: ", 100);
	}
	val->attack = attack;
	val->defense = defense;
	val->health = health;
	val->name = name;
	val->swift = swift;

}
//Sets up the robots based on players preference
void setUpPlayerMode() {
	std::string type = chooseGameMode();
	struct bot bot1, bot2;
	//Make first robot
	implementRobot(&bot1, type);
	//Checks if a second player data needs to be made
	if (type == "2AUTOMATIC" || type == "2MANUAL") {
		implementRobot(&bot2, type);
	}
	//start the automatic battle between the robots
	if (type == "1AUTOMATIC" || type == "1MANUAL") {
		//Creation of the enemies
		bot playerEnemy[5];
		//Build the 4 enemies they have to face in the tournament
		playerEnemy[0] = { "King Round", 4520, 750, 750, 50, 250 };
		playerEnemy[1] = { "B.I.G. Boy", 6750, 1500, 250, 75, 100 };
		playerEnemy[2] = { "The Defender", 9000, 500, 1000, 45, 200 };
		//Note that his stats are slightly greater than 25000
		playerEnemy[3] = { "Ulti-bot", 6009, 650, 550, 70, 2000 };
		playerEnemy[4] = { "Shadow the Champion", 10500, 1250, 750, 80, 4500 };
		for (int i = 0; i <= 4; i++) {
			struct bot botRound = playerEnemy[i];
			struct match robot = { type,bot1,botRound };
			//Pass in the robots and let them battle
			if (!startBattles(&robot)) {
				printf("YOU LOST!!!\n");
				i = 5;
				//have a restart thing?
			}
			else if (i == 4) {
				//Introducing the boss stage
				printf("============================================================================================================\n");
				printf("NEXT IS SHADOW! HE IS the STRONGEST ROBOT EVER!!!!!!!!!! DOES ANYONE HAVE A CHANCE AGAINST OUR CHAMPION???\n");
				printf("============================================================================================================\n");
			}
			else {
				//Let them continue to fight the rounds
				std::string name;
				printf("Are you ready to face another tough enemy? What do you say to the challenge?!?!\n");
				std::getline(std::cin, name);
			}

		}
	}
	else {
		//Introduce the event
		printf("%s VS %s\n", bot1.name.c_str(), bot2.name.c_str());
		struct match robot = { type,bot1,bot2 };
		//Holds the number of wins player 1 has
		int winner1 = 0;
		//start the battle between robots! Let them have 3 rounds
		for (int i = 0; i < 3; i++) {
			printf("===========================================\n");
			printf("    OFFICIALLY ENTERING ROUND %d !!!!!\n", i);
			printf("===========================================\n");
			if (startBattles(&robot)) {
				winner1++;
			}

			//Allows players to slowly see the progress
			std::cout << "[Press Enter to Continue]" << "\n";
			std::string tempVariable;
			std::getline(std::cin, tempVariable);
		}
		if (winner1 > 1) {
			printf("=======================================================================================================================================\n");
			printf("CONGRATZ %s ON DESTROYING THE COMPETITION!!!!!\n", bot1.name.c_str());
			printf("=======================================================================================================================================\n");
		}
		else {
			printf("=======================================================================================================================================\n");
			printf("CONGRATZ %s ON DESTROYING THE COMPETITION!!!!!\n", bot2.name.c_str());
			printf("=======================================================================================================================================\n");
		}
	}
	playAgain();

}

//Start the entire game
void startGame()
{
	//Introduces how the points system work for the robots
	printf("-------------------------------------------------------------------------------\n");
	printf("Let's begin by building the stats for the robot! You have 2500 points to build your robot.\n");
	//Start up game modes
	setUpPlayerMode();
}
//Asks them if they want to play again
void playAgain() {
	//Tells them to enter anything if they want to procceed
	printf("--------------------------------------------------------------------------\n\n");
	printf("To continue playing, enter anything! Otherwise close the game now!\n\n");
	printf("--------------------------------------------------------------------------\n\n");
	std::string tempVariable;
	std::getline(std::cin, tempVariable);
	//Give them the options for game mode and start-instructions
	startGame();
}
int main()
{
	//Gives the players an introduction to the game
	introduction();
	//Give them the options for game mode and start-instructions
	startGame();
	return 0;
}


