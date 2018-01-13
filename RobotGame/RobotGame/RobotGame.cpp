// RobotGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
std::string battleName[2];
int battlePlayers[4][2];
//A void function that has a short introduction to the game
void introduction()
{
	//Welcomes the player
	std::cout << "WELCOME TO BATTLE BOTS!!!!!" << "\n" << "--------- HYPE -------------" << "\n" << "ARE YOU READY???" << "\n";
	std::string temp;
	//gets input
	std::cin >> temp;
	//Ignores the input and let's the user know the game will begin
	std::cout << "DOESN'T MATTER!! LET'S START!!!" << "\n";
}

//This function will return a string that will give information on the # of players and game type
std::string chooseGameMode()
{
	//Will prompt the users to fill out if there are 1 or 2 player 
	std::cout << "Enter the number of players: 1-player or 2-players?" << "\n";
	std::cout << "Note that 1-player will lead to a tournament style while 2-players will be fighting your friend!" << "\n";
	std::string players;
	std::cin >> players;
	//Checks for invalid responses and will continually prompt users to enter either or
	while (true) {
		//Checks if the input is not any of the 2 desired
		if (players != "1-player" && players != "2-players") {
			//Continue to prompt user to enter the follwoing
			std::cout << "Invalid input." << "\n" << "Enter: 1-player or 2-players?" << "\n";
			std::cin >> players;
		}
		else {
			//if so exit out of the while loop
			break;
		}
	}
	//Holds the type of game choice they will play
	std::string gameType;
	//Will figure out if the user wants to play automatically or manually
	std::cout << "Enter the type of game: manual or automatic?" << "\n" << "Note that manual means you can choose to attack or defend while automatic is done by the computer" << "\n";
	//Get their choice
	std::cin >> gameType;
	//Ensures that one of the two inputs were submitted
	while (true) {
		//Checks if the input was one of the two
		if (gameType == "manual" || gameType == "automatic") {
			break;
		}
		else {
			//Continue to prompt them to choose of of the options
			std::cout << "Enter either manual or automatic for game type!" << "\n";
			//Get their choice
			std::cin >> gameType;

		}
	}
	return (players + gameType);
}

//Creating the class for the robots
class robotBuild {
	std::string name;
	int health, attack, defense,randomAttack;
public:
	void buildbot(std::string, int, int, int, int);
	std::string namebot() { return name; }
	int healthbot() { return health; }
	int attackbot() { return attack; }
	int defensebot() { return defense; }
	int randombot() { return randomAttack; }
};

//Save info for the robot
void robotBuild::buildbot(std::string names, int x, int y, int z, int ran) {
	name = names;
	health = x;
	attack = y;
	defense = z;
	randomAttack = ran;
}
//Assign information about the robot to the array that holds contestants
void assignbot(int x, robotBuild bot) {
	//Assign specific details to their bot parts
	battleName[x] = bot.namebot();
	battlePlayers[0][x] = bot.healthbot();
	battlePlayers[1][x] = bot.attackbot();
	battlePlayers[2][x] = bot.defensebot();
	battlePlayers[3][x] = bot.randombot();
}
bool startBattle(robotBuild p1, robotBuild p2, std::string gameType) {
	//take it from healthbot/attack/etc and save it
	assignbot(0, p1);
	assignbot(1, p2);
	bool result;
	//start the autobattle
	while (true) {
		if (battlePlayers[0][0] <= 0 && battlePlayers[0][1] <= 0){
			//Maybe round 2?????????!!!!!!!!11``````````````````````````````````````````````
			std::cout << "--------------------------------------------------" << "\n";
			std::cout << "It's a tie!!!!!!!!!!!! Both sides have lost!!!" << "\n";
			std::cout << "--------------------------------------------------" << "\n";
			result = false;
			break;
		}
		else if (battlePlayers[0][1] <= 0) {
			std::cout << "--------------------------------------------------" << "\n";
			std::cout << "WINNER!!!! " << battleName[0] << " will procceed!!" << "\n";
			std::cout << "--------------------------------------------------" << "\n";
			result = true;
			break;
		}
		else if (battlePlayers[0][0] <= 0) {
			std::cout << "--------------------------------------------------" << "\n";
			std::cout << battleName[1] << " IS THE WINNNNNNNNNNNNNNNER! :O" << "\n";
			std::cout << "--------------------------------------------------" << "\n";
			result = false;
			break;

		}
		//Initialize player 1 and player 2 move
		int v1, v2;
		//Checks the gamemode
		if (gameType == "1-playerautomatic" || gameType == "2-playersautomatic") {
			//randomly generate a number between 1 to 100
			v1 = rand() % 100 + 1;
			v2 = rand() % 100 + 1;
		}
		else if (gameType == "1-playermanual") {
			//Given that the player wants to choose their own attack, prompt them to decide
			std::string move;
			std::cout << battleName[0]<< "'s turn! Enter ATTACK or DEFENSE" << "\n";
			//Take in what the user wants to do
			std::cin >> move;
			while (true) {
				if (move == "ATTACK") {
					//Set the act value so it guarantees attack
					v1 = 0;
					break;
				}
				else if (move == "DEFENSE") {
					//ensures they have to attack
					v1 = 10000;
					break;
				}
				else {
					//Prompt them to correctly enter stuff
					std::cout << battleName[0] << "'s turn! Enter ATTACK or DEFENSE" << "\n";
					std::cin >> move;
				}
			}
			//Randomly decide if the second player should attack
			v2 = rand() % 100 + 1;
		}
		else {
			//Given that the player wants to choose their own attack, prompt them to decide
			std::string move;
			std::cout << battleName[0] << "'s turn! Enter ATTACK or DEFENSE" << "\n";
			//Take in what the user wants to do
			std::cin >> move;
			while (true) {
				if (move == "ATTACK") {
					v1 = 0;
					break;
				}
				else if (move == "DEFENSE") {
					v1 = 10000;
					break;
				}
				else {
					std::cout << battleName[0] << "'s turn! Enter ATTACK or DEFENSE" << "\n";
					std::cin >> move;
				}
			}
			//Given that the player wants to choose their own attack, prompt them to decide
			std::cout << battleName[1] << "'s turn! Enter ATTACK or DEFENSE" << "\n";
			//Take in what the user wants to do
			std::cin >> move;
			while (true) {
				if (move == "ATTACK") {
					v2 = 0;
					break;
				}
				else if (move == "DEFENSE") {
					v2 = 10000;
					break;
				}
				else {
					std::cout << battleName[1]<< "'s turn! Enter ATTACK or DEFENSE" << "\n";
					std::cin >> move;
				}
			}
		}

		//Checks the attack and defend pattern based off the result
		if (v1 <= battlePlayers[3][0] && v2 <= battlePlayers[3][1]) {
			//Both players attacked, let the player know
			std::cout << "WOW! BOTH ROBOTS ATTACKED EACH OTHER!!" << "\n";
			//Reduce health
			battlePlayers[0][0] -= battlePlayers[1][1];
			battlePlayers[0][1] -= battlePlayers[1][0];
		}
		else if (v1 <= battlePlayers[3][0] && v2 > battlePlayers[3][1]) {
			//Informs the user that the first player attacked while the second defended
			std::cout << battleName[0] << " went for the attack! Good thing " << battleName[1] << " blocked! ";
			if (battlePlayers[1][0] > battlePlayers[2][1]) {
				battlePlayers[0][1] -= (battlePlayers[1][0] - battlePlayers[2][1]);
				std::cout << "Even while defending, that's gotta hurt!" << "\n";
			}
			else {
				std::cout << battleName[1] << "'s defenses are too strong! " << battleName[1] << " didn't look hurt at all!" << "\n";
			}
		}
		else if (v1 > battlePlayers[3][0] && v2 <= battlePlayers[3][1]) {
			std::cout << battleName[1] << " went for the attack! Good thing " << battleName[0] << " blocked! ";
			if (battlePlayers[1][1] > battlePlayers[2][0]) {
				battlePlayers[0][0] -= (battlePlayers[1][1] - battlePlayers[2][0]);
				std::cout << "Even while defending, that's gotta hurt!" << "\n";
			}
			else {
				std::cout << battleName[1] << "'s defenses are too strong! " << battleName[1] << " didn't look hurt at all!" << "\n";
			}
		}
		else {
			std::cout << "THEY BOTH DEFENDED! LOOKS LIKE THEY'RE PLAYING A BIT SAFE!!!!" << "\n";
		}
		std::cout << battleName[0] << " is at " << battlePlayers[0][0] << " and " << battleName[1] << " is at " << battlePlayers[0][1] << "\n";
	}
	return result;
}

/*
 CODE CRASHES IF THE INTEGERS ARE TOO LARGE

*/
void SetUpPlayerMode(std::string typeOfBattle) {
	//Prompt player to start building the robot
	std::cout << "Split the 2500 points between the Health, Attack and Defense by entering stats:" << "\n";
	std::cout << "Enter 3 separate numbers each corresponding with the list above." << "\n";
	//variables to hold the health, attack, and defense
	int x, y, z;
	//Gets input
	std::cin >> x >> y >> z;
	//Ensures that the points are all fully used without extra stats
	while (true) {
		//Checks if the stats are properly allocated
		if (x + y + z == 2500) {
			break;
		}
		else {
			//Will warn them of the issue
			if (x + y + z > 2500) {
				//Warns them they have uused more than they are allowed
				std::cout << "ERROR!! You had " << x + y + z - 2500 << " more points than desired. Try again! ";
			}			
			else {
				//Warms them they have not used all their points
				std::cout << "ERROR!! You still have "<< 2500 - x - y - z <<" more points! Try again! ";
			}
			//Will prompt them to try again
			std::cout <<"\n" << "Split the 2500 points between the Health, Attack and Defense by entering stats:" << "\n";
			std::cout << "Enter 3 separate numbers each corresponding with the list above." << "\n";
			std::cin >> x >> y >> z;
		}
	}
	//Build the
	robotBuild player1,player2;
	std::cout << "Player 1's robot... AKA:";
	std::string name;
	std::cin >> name;
	std::cout << "\n";
	int box=0;
	if (typeOfBattle == "1-playerautomatic" || typeOfBattle == "2-playersautomatic") {
		//Choose how often the person attacks
		std::cout << "Put in a number from 1 to 100. The higher the number the more likely you'll attack!" << "\n";
		std::cin >> box;
		while (box < 0 || box > 100) {
			std::cout << "Put in a number from 1 to 100. The higher the number the more likely you'll attack!" << "\n";
			std::cin >> box;
		}
	}
	//Create an object for the player 1
	player1.buildbot(name,x, y, z,box);
	//Checks if a second player data needs to be made
	if (typeOfBattle == "2-playersautomatic" || typeOfBattle == "2-playersmanual") {
		//Prompt player to start building the robot
		std::cout << "Split the 2500 points between the Health, Attack and Defense by entering stats:" << "\n";
		std::cout << "Enter 3 separate numbers each corresponding with the list above." << "\n";
		//Gets input
		std::cin >> x >> y >> z;
		//Ensures that the points are all fully used without extra stats
		while (true) {
			//Checks if the stats are properly allocated
			if (x + y + z == 2500) {
				break;
			}
			else {
				//Will warn them of the issue
				if (x + y + z > 2500) {
					//Warns them they have uused more than they are allowed
					std::cout << "ERROR!! You had " << x + y + z - 2500 << " more points than desired. Try again! ";
				}
				else {
					//Warms them they have not used all their points
					std::cout << "ERROR!! You still have " << 2500 - x - y - z << " more points! Try again! ";
				}
				//Will prompt them to try again
				std::cout << "\n" << "Split the 2500 points between the Health, Attack and Defense by entering stats:" << "\n";
				std::cout << "Enter 3 separate numbers each corresponding with the list above." << "\n";
				std::cin >> x >> y >> z;
			}
		}
		std::cout << "Player 2's robot... AKA:";
		std::cin >> name;
		box = 0;
		if (typeOfBattle == "2-playersautomatic") {
			//Choose how often the person attacks
			std::cout << "Put in a number from 1 to 100. The higher the number the more likely you'll attack!" << "\n";
			std::cin >> box;
			while (box < 0 || box > 100) {
				std::cout << "Put in a number from 1 to 100. The higher the number the more likely you'll attack!" << "\n";
				std::cin >> box;
			}
		}
		player2.buildbot(name, x, y, z, box);
	}
	//Creation of the enemies
	robotBuild playerEnemy[4];
	//Build the 4 enemies they have to face in the tournament
	playerEnemy[0].buildbot("King Round", 1000, 750, 750, 50);
	playerEnemy[1].buildbot("B.I.G. Boy", 750, 1500, 250, 75);
	playerEnemy[2].buildbot("The Defender", 1000, 500, 1000, 45);
	//Note that his stats are slightly greater than 25000
	playerEnemy[3].buildbot("Ulti-bot", 2000, 650, 550, 70);
	//start the automatic battle between the robots
	if (typeOfBattle == "1-playerautomatic" || typeOfBattle == "1-playermanual") {
		for (int i = 0; i < 4; i++) {
			//Pass in the robots and let them battle
			if (!startBattle(player1, playerEnemy[i], typeOfBattle)) {
				std::cout << "YOU LOST!!!";
				i = 5;
				//have a restart thing?
			}
			else {
				std::cout << "Are you ready to face another tough enemy? What do you say to the challenge?!?!" << "\n";
				std::cin >> name;
			}

		}
	}
	else {
		//Introduce the event
		std::cout << player1.namebot() << " VS " << player2.namebot() << "\n";
		//start the battle between robots!
		startBattle(player1, player2, typeOfBattle);
	}

}
//Have a subprogram for automatic robot fight vs manual

//Start the entire game
void startGame(std::string gameMode)
{
	//Introduces how the points system work for the robots
	std::cout << "Let's begin by building the stats for the robot! You have 2500 points to build your robot." << "\n";
	std::cout << "Points will be split between: Health, Attack, and Defense (This will represent your robots!)" << "\n";
	//Start up game modes
	SetUpPlayerMode(gameMode);
}
int main()
{
	//Gives the players an introduction to the game
	introduction();
	//Give them the options for game mode and start-instructions
	startGame(chooseGameMode());
    return 0;
}




