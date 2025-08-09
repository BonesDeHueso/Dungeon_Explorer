#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

class DungeonGame {
private:
    // Random number generator
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

    // Variables
    std::string fight, inspecting, advised, used, doorAnswer, door, doorTwo;
    std::string doorChosen, whichWay, buying, armor, weapon, monster;

    double points = 0;
    int health = 30;
	int maxHealth = 30;
    int speed = 20;
    int damage = 1;
    int monsterSpeed, monsterHealth, monsterDamage, monsterAC;
    int AC = 5;
    int precision = 0;
    int useHowMany, buyHowMany, cost;

    // Potion timers
    int smallSpeedTimer = -1;
    int smallStrengthTimer = -1;
    int smallPrecisionTimer = -1;
    int speedTimer = -1;
    int strengthTimer = -1;
    int precisionTimer = -1;
	int largeSpeedTimer = -1;
	int largeStrengthTimer = -1;
    int largePrecisionTimer = -1;

    // Inventory
	int gp = 0;
    int smallHealthPotion = 0;
    int smallSpeedPotion = 0;
    int smallStrengthPotion = 0;
    int smallPrecisionPotion = 0;
    int healthPotion = 0;
    int speedPotion = 0;
    int strengthPotion = 0;
    int precisionPotion = 0;
	int largeHealthPotion = 0;
	int largeSpeedPotion = 0;
	int largeStrengthPotion = 0;
    int largePrecisionPotion = 0;

    // Bools
    bool needToAsk = false;
    bool weaponAsk = false;
    bool armorChosen = false;
    bool weaponChosen = false;
    bool inRoom = false;
    bool shopped = false;

public:
    DungeonGame() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

    int random(int max) {
        std::uniform_int_distribution<int> dist(0, max - 1);
        return dist(rng);
    }

    void delay(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    std::string getInput() {
        std::string input;
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        return input;
    }

    int getIntInput() {
        int value;
        std::cin >> value;
        std::cin.ignore();
        return value;
    }

    void actions() {
        std::cout << "y = attack\n";
        std::cout << "n = run away\n";
        std::cout << "stats = check your stats\n";
        std::cout << "inventory = check your inventory\n";
        std::cout << "use = use an item\n";
        std::cout << "inspect = get details on what you inspect\n";
        std::cout << "advice = get general advice on what you should do\n";
    }

    void advice() {
        std::cout << "What would you like advice about? To exit type 'quit'.\n";
        std::cout << "You can get advice about:\n";
        std::cout << "Doors\nFighting\nPotions\nBosses\n";

        while (true) {
            advised = getInput();
            if (advised == "quit") {
                std::cout << "You have exited the 'advise' menu.\n";
                break;
            }
            else if (advised == "doors") {
                std::cout << "The doors will have different treasure, chances at having treasure, and level of monsters.\n";
                std::cout << "Wood has a 10% chance at getting a bit of treasure and the weakest monsters\n";
                std::cout << "Stone has a 20% chance for getting ok treasure and slightly stronger monsters.\n";
                std::cout << "Metal has a 30% chance for getting pretty good treasure and has stronger monsters.\n";
                std::cout << "Gold has an 80% chance for getting great treasure, the strongest monsters, and sometimes will have bosses.\n";
            }
            else if (advised == "fighting") {
                std::cout << "If you have more speed you'll attack first.\n";
                std::cout << "If you hit the monster before it can attack it won't.\n";
                std::cout << "Having a higher AC will make you less likely to get hit.\n";
                std::cout << "The stronger the monster the better the loot.\n";
            }
            else if (advised == "potions") {
                std::cout << "The small speed/strength potion can be used in combination with the speed/strength potion.\n";
            }
            else if (advised == "bosses") {
                std::cout << "The three bosses are Dreadlord Varak, Dale, and Brash the Stonehided.\nThey each have a special ability and can only be found inside a boss door.\nThe bosses are way harder than an ordinary opponent, so get plenty of potions before hand\n ";
                std::cout << "You can't run away from boss fights.";
            }
        }
    }

    void stats() {
        std::cout << "Points = " << points << "\n";
        std::cout << "Health = " << health << "\n";
		std::cout << "Max Health = " << maxHealth << "\n";
        std::cout << "Speed = " << speed << "\n";
        std::cout << "Damage = " << damage << "\n";
    }

    void inventory() {
        std::cout << "Small health potion = x" << smallHealthPotion << "\n";
        std::cout << "Small speed potion = x" << smallSpeedPotion << "\n";
        std::cout << "Small strength potion = x" << smallStrengthPotion << "\n";
        std::cout << "Small precision potion =x" << smallPrecisionPotion << "\n";
        std::cout << "Health potion = x" << healthPotion << "\n";
        std::cout << "Speed potion = x" << speedPotion << "\n";
        std::cout << "Strength potion = x" << strengthPotion << "\n";
        std::cout << "Precision potion x" << precisionPotion << "\n";
		std::cout << "Large health potion = x" << largeHealthPotion << "\n";
		std::cout << "Large speed potion = x" << largeSpeedPotion << "\n";
        std::cout << "Large strength potion = x" << largeStrengthPotion << "\n";
        std::cout << "Large precision potion = x" << largePrecisionPotion << "\n";
    }

    void inspect() {
        std::cout << "What would you like to inspect? To exit type 'quit'.\n";
        while (true) {
            inspecting = getInput();
            if (inspecting == "quit") {
                std::cout << "You've exited the 'inspect' menu\n";
                break;
            }
            else if (inspecting == "t-shirt" || inspecting == "t shirt") {
                std::cout << "The T-shirt will give you a x3 point bonus at the end of the game.\n";
            }
            else if (inspecting == "chain mail" || inspecting == "chainmail") {
                std::cout << "The chainmail will give you -5 speed, +5 AC, and a x2 points bonus at the end of the game\n";
            }
            else if (inspecting == "metal plate") {
                std::cout << "The metal plate will give you -10 speed and +10 AC\n";
            }
            else if (inspecting == "fists") {
                std::cout << "Your fists will give you a x3 points bonus at the end of the game\n";
            }
            else if (inspecting == "dagger") {
                std::cout << "The dagger gives you +2 damage, -1 speed, and a x2 point bonus at the end of the game\n";
            }
            else if (inspecting == "sword") {
                std::cout << "The sword gives you +5 damage and -2 speed\n";
            }
            else if (inspecting == "small health potion") {
                std::cout << "The small health potion gives you +3 health. Your max health is 30\n";
            }
            else if (inspecting == "small speed potion") {
                std::cout << "The small speed potion gives +1 speed for 3 turns. Stacking time is possible.\n";
            }
            else if (inspecting == "small strength potion") {
                std::cout << "The small strength potion gives +1 damage for 3 turns. Stacking time is possible.\n";
            }
            else if (inspecting == "small precision potion") {
                std::cout << "The small precision potion gives +1 to your hit chance for 3 turns.\n";
            }
            else if (inspecting == "health potion") {
                std::cout << "The health potion gives +5 health. Your max health is 30\n";
            }
            else if (inspecting == "speed potion") {
                std::cout << "The speed potion gives +3 speed for 3 turns. Stacking time is possible.\n";
            }
            else if (inspecting == "strength potion") {
                std::cout << "The strength potion gives +3 damage for 3 turns. Stacking time is possible\n";
            }
            else if (inspecting == "precision potion") {
                std::cout << "The precision potion gives +3 to your hit chance for 3 turns.";
            }
            else if (inspecting == "large health potion") {
                std::cout << "The large health potion gives +10 health. Your max health is 30\n";
            }
            else if (inspecting == "large speed potion") {
                std::cout << "The large speed potion gives +5 speed for 3 turns. Stacking time is possible.\n";
            }
            else if (inspecting == "large strength potion") {
                std::cout << "The large strength potion gives +5 damage for 3 turns. Stacking time is possible.\n";
            }
            else if (inspecting == "large precision potion") {
                std::cout << "The large precision potion gives +5 to your hit chance for 3 turns.\n";
            }
            else if (inspecting == "goblin") {
				std::cout << "The goblin stats:\nHP = 2\nSpeed = 3\n AC = 5\nDamage = 1\n";
            }
            else if (inspecting == "skeleton") {
                std::cout << "The skeleton stats:\nHP = 5\nSpeed = 5\nAC = 3\nDamage = 2\n";
            }
			else if (inspecting == "kobold") {
				std::cout << "The kobold stats:\nHP = 8\nSpeed = 7\nAC = 6\nDamage = 3\n";
            }
            else if (inspecting == "hobgoblin") {
				std::cout << "The hobgoblin stats:\nHP = 10\nSpeed = 10\nAC = 5\nDamage = 4\n";
            }
            else if (inspecting == "orc") {
                std::cout << "The orc stats:\nHP = 12\nSpeed = 8\nAC = 6\nDamage = 5";
            }
            else if(inspecting == "bugbear") {
                std::cout << "The bugbear stats:\nHP = 14\nSpeed = 10\n AC = 6\nDamage = 6";
            }
            else if (inspecting == "ogre") {
                std::cout << "The ogre stats:\nHp = 15\nSpeed = 12\nAC = 7\nDamage = 5\n";
            }
            else if (inspecting == "troll") {
                std::cout << "The troll stats:\nHP = 18\nSpeed = 9\nAC = 8\nDamage = 7\n";
            }
            else if (inspecting == "gnoll") {
                std::cout << "The gnoll stats:\nHP = 13\nSpeed = 11\nAC = 6\nDamage = 6\n";
            }
            else if (inspecting == "minotaur") {
                std::cout << "The minotaur stats:\nHP = 20\nSpeed = 15\nAC = 10\nDamage = 6\n";
            }
            else if (inspecting == "banshee") {
                std::cout << " The banshee stats:\nHP = 16\nSpeed = 18\nAC = 5\nDamage = 8\n";
            }
            else if (inspecting == "wight") {
                std::cout << "The wight stats:\nHP = 17\nSpeed = 14\nAC = 9\nDamage = 7\n";
            }
            else if (inspecting == "mimic") {
                std::cout << "The mimic stats:\nHP = 25\nSpeed = 5\nAC = 9\nDamage = 3\n";
            }
            else if (inspecting == "dreadlord varak") {
                std::cout << "The boss Dreadlord Varak is a skeleton king. It's stats are:\nAbility = can summon undead\nHP = 50\nSpeed = 10\nAC = 10\nDamage = 6\n";
            }
            else if (inspecting == "dale") {
                std::cout << "The boss Dale is a vampire warlord. It's stats are:\nAbility = lifesteal\nHP = 35\nSpeed 15\nAC = 15\nDamage = 10\n";
            }
            else if (inspecting == "brash the stonehided") {
                std::cout << "The boss Brash the StoneHided is a stone dragon. It's stats are:\nAbility = has insanely high HP and AC\nHP = 100\nSpeedd = 15\nAC = 18\nDamage = 10\n";
            }
            else {
                std::cout << "Invalid item. Try again or type 'quit'.\n";
            }
        }
    }

    void use() {
        std::cout << "What would you like to use? To exit type 'quit'.\n";
        while (true) {
            used = getInput();
            if (used == "small health potion") {
                std::cout << "How many would you like to use? You have " << smallHealthPotion << " small health potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > smallHealthPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= smallHealthPotion && useHowMany > 0) {
                    smallHealthPotion -= useHowMany;
                    health = useHowMany * 3 + health;
                    if (health > maxHealth) health = maxHealth;
                    std::cout << "You now have " << health << " health!\n";
                }
                else {
                    std::cout << "Invalid answer. Please try using something else!\n";
                }
            }
            else if (used == "small speed potion") {
                std::cout << "How many would you like to use? You have " << smallSpeedPotion << " small speed potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > smallSpeedPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= smallSpeedPotion && useHowMany > 0) {
                    smallSpeedPotion -= useHowMany;
                    if (smallSpeedTimer > 0) {
                        smallSpeedTimer += useHowMany * 3;
                    }
                    else {
                        smallSpeedTimer = useHowMany * 3;
                        speed += 1;
                    }
                    std::cout << "You now have " << speed << " speed!\n";
                }
            }
            else if (used == "small strength potion") {
                std::cout << "How many would you like to use? You have " << smallStrengthPotion << " small strength potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > smallStrengthPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= smallStrengthPotion && useHowMany > 0) {
                    smallStrengthPotion -= useHowMany;
                    if (smallStrengthTimer > 0) {
                        smallStrengthTimer += useHowMany * 3;
                    }
                    else {
                        smallStrengthTimer = useHowMany * 3;
                        damage += 1;
                    }
                    std::cout << "You now deal " << damage << " damage!\n";
                }
            }
            else if (used == "small precision potion") {
                std::cout << "How many would you like to use? You have " << smallPrecisionPotion << " small precision potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > smallPrecisionPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= smallPrecisionPotion && useHowMany > 0) {
                    smallPrecisionPotion -= useHowMany;
                    if (smallPrecisionTimer > 0) {
                        smallPrecisionTimer += useHowMany * 3;
                    }
                    else {
                        smallPrecisionTimer = useHowMany * 3;
                        precision += 1;
                    }
                    std::cout << "You now have +" << precision << " to your hit chance!\n";
                }
            }
            else if (used == "health potion") {
                std::cout << "How many would you like to use? You have " << healthPotion << " health potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > healthPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= healthPotion && useHowMany > 0) {
                    healthPotion -= useHowMany;
                    health = useHowMany * 5 + health;
                    if (health > maxHealth) health = maxHealth;
                    std::cout << "You now have " << health << " health!\n";
                }
            }
            else if (used == "speed potion") {
                std::cout << "How many would you like to use? You have " << speedPotion << " speed potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > speedPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= speedPotion && useHowMany > 0) {
                    speedPotion -= useHowMany;
                    if (speedTimer > 0) {
                        speedTimer += useHowMany * 3;
                    }
                    else {
                        speedTimer = useHowMany * 3;
                        speed += 3;
                    }
                    std::cout << "You now have " << speed << " speed!\n";
                }
            }
            else if (used == "strength potion") {
                std::cout << "How many would you like to use? You have " << strengthPotion << " strength potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > strengthPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= strengthPotion && useHowMany > 0) {
                    strengthPotion -= useHowMany;
                    if (strengthTimer > 0) {
                        strengthTimer += useHowMany * 3;
                    }
                    else {
                        strengthTimer = useHowMany * 3;
                        damage += 3;
                    }
                    std::cout << "You now deal " << damage << " damage!\n";
                }
            }
            else if (used == "precision potion") {
                std::cout << "How many would you like to use? You have " << precisionPotion << " precision potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > precisionPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= precisionPotion && useHowMany > 0) {
                    precisionPotion -= useHowMany;
                    if (precisionTimer > 0) {
                        precisionTimer += useHowMany * 3;
                    }
                    else {
                        precisionTimer = useHowMany * 3;
                        precision += 3;
                    }
                    std::cout << "You now have +" << precision << " to your hit chance!\n";
                }
                }
			else if (used == "large health potion") {
                std::cout << "How many would you like to use? You have " << largeHealthPotion << " large health potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > largeHealthPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= largeHealthPotion && useHowMany > 0) {
                    largeHealthPotion -= useHowMany;
                    health = useHowMany * 10 + health;
                    if (health > maxHealth) health = maxHealth;
                    std::cout << "You now have " << health << " health!\n";
                }
			}
            else if (used == "large speed potion") {
                std::cout << "How many would you like to use? You have " << largeSpeedPotion << " large speed potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > largeSpeedPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= largeSpeedPotion && useHowMany > 0) {
                    largeSpeedPotion -= useHowMany;
                    if (largeSpeedTimer > 0) {
                        largeSpeedTimer += useHowMany * 3;
                    }
                    else {
                        largeSpeedTimer = useHowMany * 3;
                        speed += 5;
                    }
                    std::cout << "You now have " << speed << " speed!\n";
				}
                }
            else if (used == "large strength potion") {
                std::cout << "How many would you like to use? You have " << largeStrengthPotion << " large strength potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > largeStrengthPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= largeStrengthPotion && useHowMany > 0) {
                    largeStrengthPotion -= useHowMany;
                    if (largeStrengthTimer > 0) {
                        largeStrengthTimer += useHowMany * 3;
                    }
                    else {
                        largeStrengthTimer = useHowMany * 3;
                        damage += 5;
                    }
                    std::cout << "You now deal " << damage << " damage!\n";
                }
            }
            else if (used == "large precision potion") {
                std::cout << "How many would you like to use? You have " << largePrecisionPotion << " large precision potions!\n";
                useHowMany = getIntInput();
                if (useHowMany > largePrecisionPotion) {
                    std::cout << "You don't have enough. Try using something else.\n";
                }
                else if (useHowMany <= largePrecisionPotion && useHowMany > 0) {
                    largePrecisionPotion -= useHowMany;
                    if (largePrecisionTimer > 0) {
                        largePrecisionTimer += useHowMany * 3;
                    }
                    else {
                        largePrecisionTimer = useHowMany * 3;
                        precision += 5;
                    }
                    std::cout << "You now have +" << precision << " to your hit chance!\n";
                }
                }
            else if (used == "quit") {
                std::cout << "You have exited the 'use' menu.\n";
                break;
            }
            else {
                std::cout << "Invalid answer. Try using something else or type 'quit'.\n";
            }
        }
    }

    void doorPick() {
        int doorChoose = random(16);
        if (doorChoose >= 0 && doorChoose <= 4) {
            door = "wood";
        }
        else if (doorChoose >= 5 && doorChoose <= 7) {
            door = "stone";
        }
        else if (doorChoose >= 8 && doorChoose <= 10) {
            door = "metal";
        }
        else if (doorChoose == 11 || doorChoose == 12) {
            door = "gold";
        }
        else if (doorChoose == 13 || doorChoose == 14) {
            door = "shop";
        }
        else if (doorChoose == 15) {
            door = "boss";
		}
    }

    void doorPickTwo() {
        int doorChooseTwo = random(16);
        if (doorChooseTwo >= 0 && doorChooseTwo <= 4) {
            doorTwo = "wood";
        }
        else if (doorChooseTwo >= 5 && doorChooseTwo <= 7) {
            doorTwo = "stone";
        }
        else if (doorChooseTwo >= 8 && doorChooseTwo <= 10) {
            doorTwo = "metal";
        }
        else if (doorChooseTwo == 11 || doorChooseTwo == 12) {
            doorTwo = "gold";
        }
        else if (doorChooseTwo == 13 || doorChooseTwo == 14) {
            doorTwo = "shop";
        }
        else if (doorChooseTwo == 15) {
            doorTwo = "boss";
		}
    }

    void treasure() {
        if (door == "wood") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest had barely anything in it!\n";
                std::cout << "It contained 1 small health potion and 5 gp!\n";
                smallHealthPotion++;
                gp += 5;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 2 small health potions and 10 gp!\n";
                smallHealthPotion += 2;
                gp += 10;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 small health potions, 1 small speed potion, and 15 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                gp += 15;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 2 small health potions, 1 small speed potion, 1 small strength potion, and 20 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                smallStrengthPotion++;
                gp += 20;
            }
        }
        else if (door == "stone") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest didn't have much in it!\n";
                std::cout << "It contained 2 small health potions and 10 gp!\n";
                smallHealthPotion += 2;
                gp += 10;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 2 small health potions, 1 small speed potion, and 15 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                gp += 15;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 small health potions, 1 small speed potion, 1 small strength potion, and 20 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                smallStrengthPotion++;
                gp += 20;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 2 health potions, 1 small speed potion, 1 small strength potion, and 20 gp!\n";
                healthPotion += 2;
                smallSpeedPotion++;
                smallStrengthPotion++;
                gp += 20;
            }
        }
        else if (door == "metal") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest contained 2 health potions, 1 strength potion, and 5 gp!\n";
                healthPotion += 2;
                strengthPotion++;
                gp += 5;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 3 health potions, 2 speed potions, and 15 gp!\n";
                healthPotion += 3;
                speedPotion += 2;
                gp += 15;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 health potions, 1 speed potion, 1 strength potion, and 25 gp!\n";
                healthPotion += 2;
                speedPotion++;
                strengthPotion++;
                gp += 25;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 2 health potions, 2 speed potions, 2 strength potions, and 35 gp!\n";
                healthPotion += 2;
                speedPotion += 2;
                strengthPotion += 2;
                gp += 35;
            }
        }
        else if (door == "gold") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest contained 3 health potions and 15 gp!\n";
                healthPotion += 3;
                gp += 15;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 2 health potions, 1 speed potion, 1 strength potion, and 25 gp!\n";
                healthPotion += 2;
                speedPotion++;
                strengthPotion++;
                gp += 25;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 health potions, 2 speed potions, 2 strength potions, and 35 gp!\n";
                healthPotion += 2;
                speedPotion += 2;
                strengthPotion += 2;
                gp += 35;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 3 health potions, 2 speed potions, 2 strength potions, and 45 gp!\n";
                healthPotion += 3;
                speedPotion += 2;
                strengthPotion += 2;
                gp += 45;
            }
        }
        inRoom = false;
    }

    void treasureTwo() {
        if (doorTwo == "wood") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest had barely anything in it!\n";
                std::cout << "It contained 1 small health potion and 5 gp!\n";
                smallHealthPotion++;
                gp += 5;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 2 small health potions and 10 gp!\n";
                smallHealthPotion += 2;
                gp += 10;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 small health potions, 1 small speed potion, and 15 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                gp += 15;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 2 small health potions, 1 small speed potion, 1 small strength potion, and 20 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                smallStrengthPotion++;
                gp += 20;
            }
        }
        else if (doorTwo == "stone") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest didn't have much in it!\n";
                std::cout << "It contained 2 small health potions and 10 gp!\n";
                smallHealthPotion += 2;
                gp += 10;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 2 small health potions, 1 small speed potion, and 15 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                gp += 15;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 small health potions, 1 small speed potion, 1 small strength potion, and 20 gp!\n";
                smallHealthPotion += 2;
                smallSpeedPotion++;
                smallStrengthPotion++;
                gp += 20;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 2 health potions, 1 small speed potion, 1 small strength potion, and 20 gp!\n";
                healthPotion += 2;
                smallSpeedPotion++;
                smallStrengthPotion++;
                gp += 20;
            }
        }
        else if (doorTwo == "metal") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest contained 2 health potions, 1 strength potion, and 5 gp!\n";
                healthPotion += 2;
                strengthPotion++;
                gp += 5;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 3 health potions, 2 speed potions, and 15 gp!\n";
                healthPotion += 3;
                speedPotion += 2;
                gp += 15;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 health potions, 1 speed potion, 1 strength potion, and 25 gp!\n";
                healthPotion += 2;
                speedPotion++;
                strengthPotion++;
                gp += 25;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 2 health potions, 2 speed potions, 2 strength potions, and 35 gp!\n";
                healthPotion += 2;
                speedPotion += 2;
                strengthPotion += 2;
                gp += 35;
            }
        }
        else if (doorTwo == "gold") {
            int chestLoot = random(4);
            if (chestLoot == 0) {
                std::cout << "The chest contained 3 health potions and 15 gp!\n";
                healthPotion += 3;
                gp += 15;
            }
            else if (chestLoot == 1) {
                std::cout << "The chest had 2 health potions, 1 speed potion, 1 strength potion, and 25 gp!\n";
                healthPotion += 2;
                speedPotion++;
                strengthPotion++;
                gp += 25;
            }
            else if (chestLoot == 2) {
                std::cout << "The chest contained 2 health potions, 2 speed potions, 2 strength potions, and 35 gp!\n";
                healthPotion += 2;
                speedPotion += 2;
                strengthPotion += 2;
                gp += 35;
            }
            else if (chestLoot == 3) {
                std::cout << "Nice! The chest had 3 health potions, 2 speed potions, 2 strength potions, and 45 gp!\n";
                healthPotion += 3;
                speedPotion += 2;
                strengthPotion += 2;
                gp += 45;
            }
        }
        inRoom = false;
    }

    void shop() { 
        std::cout << "You walk into a little shop. You have " << gp << " gp. After buying something type 'leave'.\n";
        std::cout << "PRICES:\n";
        std::cout << "Small healing potions: 20 per\n";
        std::cout << "Small speed potions: 30 per\n";
        std::cout << "Small strength potion: 30 per\n";
        std::cout << "Small precision potion: 30 per\n";
        std::cout << "Healing potion: 40 per\n";
        std::cout << "Speed potion: 60 per\n";
        std::cout << "Strength potion: 60 per\n";
        std::cout << "Precision potion: 60 per\n";
		std::cout << "Large healing potion: 80 per\n";
		std::cout << "Large speed potion: 120 per\n";
		std::cout << "Large strength potion: 120 per\n";
        std::cout << "Large precision potion: 120 per\n";
        while (!shopped) {
            buying = getInput();
            if (buying == "leave") {
                std::cout << "You have exited the shop.\n";
                inRoom = false;
                break;
            }
            else if (buying == "small healing potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 20;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    smallHealthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " small health potions!\n";
                    std::cout << "You now have " << smallHealthPotion << " small health potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "small speed potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 30;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    smallSpeedPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " small speed potions!\n";
                    std::cout << "You now have " << smallSpeedPotion << " small speed potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "small strength potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 30;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    smallStrengthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " small strength potions!\n";
                    std::cout << "You now have " << smallStrengthPotion << " small strength potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "small precision potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 30;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    smallStrengthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " small precision potions!\n";
                    std::cout << "You now have " << smallPrecisionPotion << " small precision potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "healing potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 40;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    healthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " health potions!\n";
                    std::cout << "You now have " << healthPotion << " health potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "speed potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 60;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    speedPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " speed potions!\n";
                    std::cout << "You now have " << speedPotion << " speed potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "strength potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 60;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    strengthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " strength potions!\n";
                    std::cout << "You now have " << strengthPotion << " strength potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "strength potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 60;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    precisionPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " precision potions!\n";
                    std::cout << "You now have " << precisionPotion << " precision potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "large healing potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 80;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    largeHealthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " large health potions!\n";
                    std::cout << "You now have " << largeHealthPotion << " large health potions and " << gp << " gp!\n";
                }
			}
            else if (buying == "large speed potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 120;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    largeSpeedPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " large speed potions!\n";
                    std::cout << "You now have " << largeSpeedPotion << " large speed potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "large strength potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 120;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    largeStrengthPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " large strength potions!\n";
                    std::cout << "You now have " << largeStrengthPotion << " large strength potions and " << gp << " gp!\n";
                }
            }
            else if (buying == "large precision potion") {
                std::cout << "How many would you like to buy?\n";
                buyHowMany = getIntInput();
                cost = buyHowMany * 120;
                if (gp < cost) {
                    std::cout << "You don't have enough money. Try buying something else.\n";
                }
                else {
                    gp -= cost;
                    largePrecisionPotion += buyHowMany;
                    std::cout << "You bought " << buyHowMany << " large precision potions!\n";
                    std::cout << "You now have " << largePrecisionPotion << " large precision potions and " << gp << " gp!\n";
                }
            }
            else {
                std::cout << "Invalid item. Try again or type 'leave'.\n";
				}
        }
    }

    void inside() {
        int insideRoom = random(50);
        if (door == "wood") {
            std::cout << "You walk through a wooden doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 4) {
                std::cout << "a treasure chest!\n";
                treasure();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVOne();
                combat();
            }
        }
        else if (door == "stone") {
            std::cout << "You walk through a stone doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 9) {
                std::cout << "a treasure chest!\n";
                treasure();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVTwo();
                combat();
            }
        }
        else if (door == "metal") {
            std::cout << "You walk through a metal doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 14) {
                std::cout << "a treasure chest!\n";
                treasure();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVThree();
				combat();
            }
        }
        else if (door == "gold") {
            std::cout << "You walk through a gold doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 39) {
                std::cout << "a treasure chest!\n";
                treasure();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVFour();
				combat();
            }
        }
        else if (door == "shop") {
            shop();
        }
        else if (door == "boss") {
			generateBoss();
			bossCombat();
        }
    }

    void insideTwo() {
        int insideRoom = random(50);
        if (doorTwo == "wood") {
            std::cout << "You walk through a wooden doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 4) {
                std::cout << "a treasure chest!\n";
                treasureTwo();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVOne();
				combat();
            }
        }
        else if (doorTwo == "stone") {
            std::cout << "You walk through a stone doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 9) {
                std::cout << "a treasure chest!\n";
                treasureTwo();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVTwo();
				combat();
            }
        }
        else if (doorTwo == "metal") {
            std::cout << "You walk through a metal doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 14) {
                std::cout << "a treasure chest!\n";
                treasureTwo();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVThree();
				combat();
            }
        }
        else if (doorTwo == "gold") {
            std::cout << "You walk through a gold doorway and see ";
            if (insideRoom >= 0 && insideRoom <= 39) {
                std::cout << "a treasure chest!\n";
                treasureTwo();
            }
            else {
                std::cout << "a monster!\n";
                generateMonsterLVFour();
				combat();
            }
        }
        else if (doorTwo == "shop") {
            shop();
        }
        else if (doorTwo == "boss") {
			generateBoss();
			bossCombat();
        }
    }

    void monsterLootTables() {
        if (monster == "goblin") {
            points += 1;
            gp += 5;
			std::cout << "The goblin was carrying 3 gp!\n";
            int potionPick = random(25);
            if (potionPick == 0) {
                std::cout << "The goblin was carrying a small health potion!\n";
                std::cout << "You gain 1 small health potion!\n";
                smallHealthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "The goblin was carrying a small speed potion!\n";
                std::cout << "You gain 1 small speed potion!\n";
                smallSpeedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "The goblin was carrying a small strength potion!\n";
                std::cout << "You gain 1 small strength potion!\n";
                smallStrengthPotion++;
            }
        }
        else if (monster == "skeleton") {
            points += 2;
			gp += 5;
			std::cout << "The skeleton was carrying 5 gp!\n";
            int potionPick = random(20);
            if (potionPick == 0) {
                std::cout << "The skeleton was carrying a small health potion!\n";
                std::cout << "You gain 1 small health potion!\n";
                smallHealthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "The skeleton was carrying a small speed potion!\n";
                std::cout << "You gain 1 small speed potion!\n";
                smallSpeedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "The skeleton was carrying a small strength potion!\n";
                std::cout << "You gain 1 small strength potion!\n";
                smallStrengthPotion++;
            }
        }
        else if (monster == "kobold") {
            points += 3;
			gp += 8;
			std::cout << "The kobold was carrying 8 gp!\n";
            int potionPick = random(15);
            if (potionPick == 0) {
                std::cout << "The kobold was carrying a small health potion!\n";
                std::cout << "You gain 1 small health potion!\n";
                smallHealthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "The kobold was carrying a small speed potion!\n";
                std::cout << "You gain 1 small speed potion!\n";
                smallSpeedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "The kobold was carrying a small strength potion!\n";
                std::cout << "You gain 1 small strength potion!\n";
                smallStrengthPotion++;
            }
        }
        else if (monster == "hobgoblin") {
            points += 5;
			gp += 10;
			std::cout << "The hobgoblin was carrying 10 gp!\n";
            int potionPick = random(20);
            if (potionPick == 0 || potionPick == 1) {
                std::cout << "The hobgoblin was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick == 2 || potionPick == 3) {
                std::cout << "The hobgoblin was carrying a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick == 4 || potionPick == 5) {
                std::cout << "The hobgoblin was carrying a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
            else if (potionPick == 6) {
                std::cout << "The hobgoblin was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
        }
        else if (monster == "orc") {
            points += 6;
			gp += 12;
			std::cout << "The orc was carrying 12 gp!\n";
            int potionPick = random(20);
            if (potionPick == 0 || potionPick == 1) {
                std::cout << "The orc was carrying a small health potion!\n";
                std::cout << "You gain 1 small health potion!\n";
                smallHealthPotion++;
            }
            else if (potionPick == 2 || potionPick == 3) {
                std::cout << "The orc was carrying a small speed potion!\n";
                std::cout << "You gain 1 small speed potion!\n";
                smallSpeedPotion++;
            }
            else if (potionPick == 4 || potionPick == 5) {
                std::cout << "The orc was carrying a small strength potion!\n";
                std::cout << "You gain 1 small strength potion!\n";
                smallStrengthPotion++;
            }
            else if (potionPick == 6) {
                std::cout << "The orc was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
        }
        else if (monster == "bugbear") {
            points += 7;
			gp += 14;
			std::cout << "The bugbear was carrying 14 gp!\n";
            int potionPick = random(20);
            if (potionPick == 0 || potionPick == 1) {
                std::cout << "The bugbear was carrying a small health potion!\n";
                std::cout << "You gain 1 small health potion!\n";
                smallHealthPotion++;
            }
            else if (potionPick == 2 || potionPick == 3) {
                std::cout << "The bugbear was carrying a small speed potion!\n";
                std::cout << "You gain 1 small speed potion!\n";
                smallSpeedPotion++;
            }
            else if (potionPick == 4 || potionPick == 5) {
                std::cout << "The bugbear was carrying a small strength potion!\n";
                std::cout << "You gain 1 small strength potion!\n";
                smallStrengthPotion++;
            }
            else if (potionPick == 6) {
                std::cout << "The bugbear was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
			}
        }
        else if (monster == "ogre") {
            points += 8;
			gp += 12;
			std::cout << "The ogre was carrying 12 gp!\n";
            int potionPick = random(10);
            if (potionPick == 0) {
                std::cout << "The ogre was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "The ogre was carrying a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "The ogre was carrying a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
        }
        else if (monster == "troll") {
            points += 9;
            gp += 14;
            std::cout << "The troll was carrying 14 gp!\n";
            int potionPick = random(10);
            if (potionPick == 0) {
                std::cout << "The troll was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "The troll was carrying a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "The troll was carrying a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
        }
        else if (monster == "gnoll") {
            points += 10;
            gp += 16;
            std::cout << "The gnoll was carrying 16 gp!\n";
            int potionPick = random(10);
            if (potionPick == 0) {
                std::cout << "The gnoll was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "The gnoll was carrying a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "The gnoll was carrying a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
         }
        else if (monster == "banshee") {
            points += 11;
            gp += 18;
            std::cout << "You scoured the room and found 10 gp and ";
            int potionPick = random(10);
            if (potionPick == 0) {
                std::cout << "a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick == 1) {
                std::cout << "a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick == 2) {
                std::cout << "a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
            else {
                std::cout << "nothing!";
            }
         }
        else if (monster == "minotaur") {
            points += 12;
			gp += 20;
			std::cout << "The minotaur was carrying 20 gp!\n";
            int potionPick = random(20);
            if (potionPick == 0 || potionPick == 1) {
                std::cout << "The minotaur was carrying a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick == 2 || potionPick == 3) {
                std::cout << "The minotaur was carrying a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick == 4 || potionPick == 5) {
                std::cout << "The minotaur was carrying a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
            else if (potionPick == 6) {
                std::cout << "The minotaur was carrying a large health potion!\n";
                std::cout << "You gain 1 large health potion!\n";
                largeHealthPotion++;
            }
        }
        else if (monster == "mimic") {
            points += 15;
			gp += 25;
            std::cout << "The mimic turned into a chest!\n";
			std::cout << "You open it and find some potions and 25 gp!\n";
            int potionPick = random(14);
            if (potionPick <= 4) {
                std::cout << "You found a health potion!\n";
                std::cout << "You gain 1 health potion!\n";
                healthPotion++;
            }
            else if (potionPick >= 5 && potionPick <= 8) {
                std::cout << "You found a speed potion!\n";
                std::cout << "You gain 1 speed potion!\n";
                speedPotion++;
            }
            else if (potionPick >= 9 && potionPick <= 12) {
                std::cout << "You found a strength potion!\n";
                std::cout << "You gain 1 strength potion!\n";
                strengthPotion++;
            }
            else if (potionPick >= 13 && potionPick <= 16) {
                std::cout << "You found two health potions!\n";
                std::cout << "You gain 2 health potions!\n";
                healthPotion += 2;
            }
            else if (potionPick >= 17 && potionPick <= 20) {
                std::cout << "You found a speed potion and a strength potion!\n";
                std::cout << "You gain 1 speed potion and 1 strength potion!\n";
                speedPotion++;
                strengthPotion++;
            }
            else if (potionPick == 21 || potionPick == 22) {
                std::cout << "You found a health potion, speed potion, AND a strength potion!\n";
                std::cout << "You gain 1 health potion, 1 speed potion, and 1 strength potion!\n";
                healthPotion++;
                speedPotion++;
                strengthPotion++;
           }
            else if (potionPick == 23) {
                std::cout << "You found a large health potion, large speed potion, AND a large strength potion!";
                std::cout << "You gain 1 large health potion, 1 large speed potion, 1 large strength potion!";
                largeHealthPotion++;
                largeSpeedPotion++;
                largeStrengthPotion++;
            }
        }
        else if (monster == "vampire") {
            points += 30;
			int potionPick = random(6);
			std::cout << "You found the chest that Dale was protecting!\n";
            if (potionPick == 0) {
				std::cout << "You found 2 large health potion, 1 large speed potion, 1 large strength potion, and 50 gp!\n";
				largeHealthPotion += 2;
				largeSpeedPotion++;
				largeStrengthPotion++;
				gp += 50;
            }
            else if (potionPick == 1 || potionPick == 2) {
				std::cout << "You found 2 large health potions, 2 large speed potions, 2 large strength potions, and 75 gp!\n";
				largeHealthPotion += 2;
				largeSpeedPotion += 2;
				largeStrengthPotion += 2;
                gp += 75;
            }
            else if (potionPick == 3 || potionPick == 4) {
				std::cout << "You found 3 large health potions, 3 large speed potions, 3 large strength potions, and 100 gp!\n";
				largeHealthPotion += 3;
				largeSpeedPotion += 3;
                largeStrengthPotion += 3;
                gp += 100;
            }
            else if (potionPick == 5) {
				std::cout << "As you open the chest, a mystical mist engulfs you and you feel stronger!\n";
				std::cout << "You gain +5 health permanently!\n";
			    std::cout << "The rest of the chest contained 3 large health potions, 2 large speed potion, 2 large strength potion, and 100 gp!\n";
			    largeHealthPotion += 3;
			    largeSpeedPotion += 2;
			    largeStrengthPotion += 2;
			    gp += 100;
				maxHealth += 5;
            }
        }
        else if (monster == "skeletonKing") {
			points += 50;
			int potionPick = random(6);
			std::cout << "You find the chest Dreadlord Varak was protecting!\n";
            if (potionPick == 0) {
				std::cout << "You found 2 large health potions, 2 large speed potion, 1 large strength potion, and 50 gp!\n";
				largeHealthPotion += 2;
				largeSpeedPotion += 2;
				largeStrengthPotion++;
                gp += 50;
            }
            else if (potionPick == 1 || potionPick == 2) {
				std::cout << "You found 2 large health potions, 2 large speed potions, 2 large strength potions, and 75 gp!\n";
				largeHealthPotion += 2;
				largeSpeedPotion += 2;
                largeStrengthPotion += 2;
                gp += 75;
            }
            else if (potionPick == 3 || potionPick == 4) {
				std::cout << "You found 3 large health potions, 3 large speed potions, 3 large strength potions, and 100 gp!\n";
				largeHealthPotion += 3;
                largeSpeedPotion += 3;
                largeStrengthPotion += 3;
                gp += 100;
            }
            else if (potionPick == 5) {
				std::cout << "As you open the chest, a mystical mist engulfs you and you feel stronger!\n";
				std::cout << "You gain +1 speed permanently!\n";
				std::cout << "The rest of the chest contained 2 large health potions, 3 large speed potion, 2 large strength potion, and 100 gp!\n";
				largeHealthPotion += 2;
				largeSpeedPotion += 3;
				largeStrengthPotion += 2;
				gp += 100;
				speed += 1;
            }
		}
        else if (monster == "dragon") {
			points += 100;
            int potionPick = random(6);
            std::cout << "You find the chest Brash the Stonehided was protecting!";
            if (potionPick == 0) {
                std::cout << "You found 2 large health potoins, 2 large speed potions, 2 large strength potions, and 75 gp!";
                largeHealthPotion += 2;
                largeSpeedPotion += 2;
                largeStrengthPotion += 2;
                gp += 75;
            }
            else if (potionPick == 1 || potionPick == 2) {
                std::cout << "You found 3 large health potions, 2 large speed potions, 2 large strength potions, and 100 gp!";
                largeHealthPotion += 3;
                largeSpeedPotion += 2;
                largeStrengthPotion += 2;
                gp += 100;
            }
            else if (potionPick == 3 || potionPick == 4) {
                std::cout << "You found 3 large health potions, 3 large speed potions, 3 large strength potions, and 125 gp!";
                largeHealthPotion += 3;
                largeSpeedPotion += 3;
                largeStrengthPotion += 3;
                gp += 100;
            }
            else if (potionPick == 5) {
                std::cout << "As you open the chest, a mystical mist engulfs you and you feel stronger!";
                std::cout << "You deal +1 damage permanently!";
                std::cout << "The rest of the chest contained 2 large health potions, 2 large speed potions, 3 large strength potions, and 100 gp!";
                largeHealthPotion += 2;
                largeSpeedPotion += 2;
                largeStrengthPotion += 3;
                gp += 100;
                damage += 1;
            }
        }
    }

    void updateTimers() {
        if (smallSpeedTimer == 0) {
            speed--;
            smallSpeedTimer--;
        }
        else if (smallSpeedTimer > 0) {
            smallSpeedTimer--;
        }

        if (smallStrengthTimer == 0) {
            damage--;
            smallStrengthTimer--;
        }
        else if (smallStrengthTimer > 0) {
            smallStrengthTimer--;
        }

        if (smallPrecisionTimer == 0) {
            precision--;
            smallPrecisionTimer--;
        }
        else if (smallPrecisionTimer > 0) {
            smallPrecisionTimer--;
        }

        if (speedTimer == 0) {
            speed -= 3;
            speedTimer--;
        }
        else if (speedTimer > 0) {
            speedTimer--;
        }

        if (strengthTimer == 0) {
            damage -= 3;
            strengthTimer--;
        }
        else if (strengthTimer > 0) {
            strengthTimer--;
        }

        if (precisionTimer == 0) {
            precision -= 3;
            precisionTimer--;
        }
        else if (precisionTimer > 0) {
            precisionTimer--;
        }

        if (largeSpeedTimer == 0) {
            speed -= 5;
            largeSpeedTimer--;
        }
        else if (largeSpeedTimer > 0) {
            largeSpeedTimer--;
		}

        if (largeStrengthTimer == 0) {
            damage -= 5;
            largeStrengthTimer--;
        }
        else if (largeStrengthTimer > 0) {
            largeStrengthTimer--;
		}

        if (largePrecisionTimer == 0) {
            precision -= 5;
            largePrecisionTimer--;
        }
        else if (largePrecisionTimer > 0) {
            largePrecisionTimer--;
        }
    }

    void generateMonsterLVOne() {

        int monsterChoose = random(3);
        if (monsterChoose == 0) {
            monsterHealth = 2; monsterSpeed = 3; monsterAC = 5; monsterDamage = 1;
            monster = "goblin";
        }
        else if (monsterChoose == 1) {
            monsterHealth = 5; monsterSpeed = 5; monsterAC = 3; monsterDamage = 2;
            monster = "skeleton";
        }
        else {
            monsterHealth = 8; monsterSpeed = 7; monsterAC = 7; monsterDamage = 3;
            monster = "kobold";
        }
    }

    void generateMonsterLVTwo() {
        int monsterChoose = random(8);
        if (monsterChoose == 0) {
            monsterHealth = 5; monsterSpeed = 5; monsterAC = 3; monsterDamage = 2;
            monster = "skeleton";
        }
        else if (monsterChoose == 1) {
            monsterHealth = 8; monsterSpeed = 7; monsterAC = 7; monsterDamage = 3;
            monster = "kobold";
        }
        else if (monsterChoose == 2 || monsterChoose == 3) {
            monsterHealth = 10; monsterSpeed = 10; monsterAC = 5; monsterDamage = 4;
            monster = "hobgoblin";
        }
        else if (monsterChoose == 4 || monsterChoose == 5) {
            monsterHealth = 12; monsterSpeed = 8; monsterAC = 6; monsterDamage = 5;
            monster = "orc";
        }
        else {
            monsterHealth = 14; monsterSpeed = 10; monsterAC = 6; monsterDamage = 6;
            monster = "bugbear";
        }
	}

    void generateMonsterLVThree() {
        int monsterChoose = random(8);
        if (monsterChoose == 0) {
            monsterHealth = 10; monsterSpeed = 10; monsterAC = 6; monsterDamage = 5;
            monster = "orc";
        }
        else if (monsterChoose == 1) {
            monsterHealth = 14; monsterSpeed = 10; monsterAC = 6; monsterDamage = 6;
            monster = "bugbear";
        }
        else if (monsterChoose == 2 || monsterChoose == 3) {
            monsterHealth = 15; monsterSpeed = 12; monsterAC = 7; monsterDamage = 5;
            monster = "ogre";
        }
        else if (monsterChoose == 4 || monsterChoose == 5) {
            monsterHealth = 18; monsterSpeed = 9; monsterAC = 8; monsterDamage = 7;
            monster = "troll";
        }
        else {
            monsterHealth = 13; monsterSpeed = 11; monsterAC = 6; monsterDamage = 6;
            monster = "gnoll";
		}
    }

    void generateMonsterLVFour() {
        int monsterChoose = random(14);
        if (monsterChoose == 0 || monsterChoose == 1) {
            monsterHealth = 18; monsterSpeed = 9; monsterAC = 8; monsterDamage = 7;
            monster = "troll";
        }
        else if (monsterChoose == 2 || monsterChoose == 3) {
            monsterHealth = 13; monsterSpeed = 11; monsterAC = 6; monsterDamage = 6;
            monster = "gnoll";
        }
        else if (monsterChoose >= 4 && monsterChoose >= 6) {
            monsterHealth = 20; monsterSpeed = 15; monsterAC = 10; monsterDamage = 6;
            monster = "minotaur";
        }
        else if (monsterChoose >= 7 && monsterChoose <= 9) {
            monsterHealth = 16; monsterSpeed = 18; monsterAC = 5; monsterDamage = 8;
            monster = "banshee";
        }
        else if (monsterChoose >= 10 && monsterChoose <= 12) {
            monsterHealth = 17; monsterSpeed = 14; monsterAC = 9; monsterDamage = 7;
            monster = "wight";
        }
        else {
            monsterHealth = 25; monsterSpeed = 5; monsterAC = 9; monsterDamage = 3;
            monster = "mimic";
		}
    }

    void generateBoss() {
        int monsterChoose = random(3);
        if (monsterChoose == 0) {
            monsterHealth = 50; monsterSpeed = 10; monsterAC = 10; monsterDamage = 8;
            monster = "skeletonKing";
        }
        else if (monsterChoose == 1) {
            monsterHealth = 35; monsterSpeed = 15; monsterAC = 15; monsterDamage = 10;
            monster = "vampire";
        }
        else {
            monsterHealth = 100; monsterSpeed = 15; monsterAC = 18; monsterDamage = 10;
            monster = "dragon";
		}
    }

    bool processCommand(const std::string& command) {
        if (command == "actions") {
            actions();
            return false;
        }
        else if (command == "stats") {
            stats();
            return false;
        }
        else if (command == "inventory") {
            inventory();
            return false;
        }
        else if (command == "inspect") {
            inspect();
            return false;
        }
        else if (command == "use") {
            use();
            return false;
        }
        else if (command == "advice") {
            advice();
            return false;
        }
        return true;
    }

    void gameOver(bool victory = false) {
        if (!victory) {
            std::cout << "You died!\n";
            points /= 3;
        }

        if (armor == "1") {
            points *= 3;
        }
        else if (armor == "2") {
            points *= 2;
        }

        if (weapon == "1") {
            points *= 3;
        }
        else if (weapon == "2") {
            points *= 2;
        }

        if (victory) {
            std::cout << "You left with " << points << " points!\n";
        }
        else {
            std::cout << "You ended with " << points << " points!\n";
        }
    }

    void combat() {
        std::cout << "As you walk in you see a " << monster << "! Do you fight? y/n\n";

        while (true) {
            fight = getInput();

            if (!processCommand(fight)) continue;

            if (fight == "y") {
                if (speed > monsterSpeed) {
                    std::cout << "You swing...";
                    int hit = random(20);
                    hit += precision;
                    if (hit < monsterAC) {
                        std::cout << " and you miss!\n";
                        std::cout << "The " << monster << " swings at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " and misses!\n";
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                        else if (monsterHit >= AC) {
                            std::cout << " and hits!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            else if (health >= 1) {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else if (hit >= monsterAC) {
                        std::cout << " and you hit!\n";
                        monsterHealth -= damage;
                        if (monsterHealth <= 0) {
                            std::cout << "You killed the " << monster << "!\n";
                            monsterLootTables();
                            inRoom = false;
                            needToAsk = false;
                            std::cout << "You now have " << points << " points!\n";
                            delay(1500);
                            return;
                        }
                        else {
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                }
                else if (speed == monsterSpeed) {
                    int first = random(2);
                    if (first == 0) {
                        std::cout << "You swing...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " and you miss!\n";
                            std::cout << "The " << monster << " swings at you...";
                            int monsterHit = random(20);
                            if (monsterHit < AC) {
                                std::cout << " and misses!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else if (monsterHit >= AC) {
                                std::cout << " and hits!\n";
                                health -= monsterDamage;
                                std::cout << "You now have " << health << " health!\n";
                                if (health <= 0) {
                                    gameOver(false);
                                    exit(0);
                                }
                                else if (health >= 1) {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else if (hit >= monsterAC) {
                            std::cout << " and you hit!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed the " << monster << "!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                std::cout << "You now have " << points << " points!\n";
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else {
                        std::cout << "The " << monster << " swings at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " and misses!\n";
                            std::cout << "You swing and...";
                            int hit = random(20);
                            hit += precision;
                            if (hit < monsterAC) {
                                std::cout << " miss!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else if (hit >= monsterAC) {
                                std::cout << " hit!\n";
                                monsterHealth -= damage;
                                if (monsterHealth <= 0) {
                                    std::cout << "You killed the " << monster << "!\n";
                                    monsterLootTables();
                                    inRoom = false;
                                    needToAsk = false;
                                    std::cout << "You now have " << points << " points!\n";
                                    delay(1500);
                                    return;
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else if (monsterHit >= AC) {
                            std::cout << " and hits!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            else if (health >= 1) {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                }
                else if (speed < monsterSpeed) {
                    std::cout << "The " << monster << " swings at you...";
                    int monsterHit = random(20);
                    if (monsterHit < AC) {
                        std::cout << " and misses!\n";
                        std::cout << "You swing and...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " miss!\n";
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                        else if (hit >= monsterAC) {
                            std::cout << " hit!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed the " << monster << "!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                std::cout << "You now have " << points << " points!\n";
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else if (monsterHit >= AC) {
                        std::cout << " and hits!\n";
                        health -= monsterDamage;
                        std::cout << "You now have " << health << " health!\n";
                        if (health <= 0) {
                            gameOver(false);
                            exit(0);
                        }
                        else if (health >= 1) {
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                }
            }
            else if (fight == "n") {
                std::cout << "You ran away!\n";
                if (points == 0) {
                    std::cout << "Dude you didn't even try.\n";
                }
                else {
                    gameOver(true);
                }
                exit(0);
            }
        }
    }


    void bossCombat() {
        if (monster == "vampire") {
            std::cout << "You see Dale, the vampire warlord!\n";
            vampireCombat();
        }
        else if (monster == "skeletonKing") {
            std::cout << "You see Dreadlord Varak, the skeleton king!\n";
            skeletonKingCombat();
        }
        else if (monster == "dragon") {
            std::cout << "You see Brash the Stonehided, the massive stone dragon!\n";
            dragonCombat();
        }
    }

    void vampireCombat() {
        while (true) {
            std::cout << "Do you fight? y/n\n";
            fight = getInput();

            if (!processCommand(fight)) continue;

            if (fight == "y") {
                if (speed > monsterSpeed) {
                    std::cout << "You swing...";
                    int hit = random(20);
                    hit += precision;
                    if (hit < monsterAC) {
                        std::cout << " and you miss!\n";
                        std::cout << "Dale swings at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " and misses!\n";
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                        else if (monsterHit >= AC) {
                            int lifesteal = random(5) + 3;
                            std::cout << " and hits!\n";
                            monsterHealth += lifesteal;
                            std::cout << "He steals " << lifesteal << " health!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else if (hit >= monsterAC) {
                        std::cout << " and you hit!\n";
                        monsterHealth -= damage;
                        if (monsterHealth <= 0) {
                            std::cout << "You killed Dale the vampire warlord!\n";
                            monsterLootTables();
                            inRoom = false;
                            needToAsk = false;
                            delay(1500);
                            return;
                        }
                        else {
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                }
                else if (speed == monsterSpeed) {
                    int first = random(2);
                    if (first == 0) {
                        std::cout << "You swing...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " and you miss!\n";
                            std::cout << "Dale swings at you...";
                            int monsterHit = random(20);
                            if (monsterHit < AC) {
                                std::cout << " and misses!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else if (monsterHit >= AC) {
                                int lifesteal = random(5) + 3;
                                std::cout << " and hits!\n";
                                monsterHealth += lifesteal;
                                std::cout << "He steals " << lifesteal << " health!\n";
                                health -= monsterDamage;
                                std::cout << "You now have " << health << " health!\n";
                                if (health <= 0) {
                                    gameOver(false);
                                    exit(0);
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else if (hit >= monsterAC) {
                            std::cout << " and you hit!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed Dale the vampire warlord!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else {
                        std::cout << "Dale swings at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " and misses!\n";
                            std::cout << "You swing and...";
                            int hit = random(20);
                            hit += precision;
                            if (hit < monsterAC) {
                                std::cout << " miss!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else if (hit >= monsterAC) {
                                std::cout << " hit!\n";
                                monsterHealth -= damage;
                                if (monsterHealth <= 0) {
                                    std::cout << "You killed Dale the vampire warlord!\n";
                                    monsterLootTables();
                                    inRoom = false;
                                    needToAsk = false;
                                    delay(1500);
                                    return;
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else if (monsterHit >= AC) {
                            int lifesteal = random(5) + 3;
                            std::cout << " and hits!\n";
                            monsterHealth += lifesteal;
                            std::cout << "He steals " << lifesteal << " health!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                }
                else if (speed < monsterSpeed) {
                    std::cout << "Dale swings at you...";
                    int monsterHit = random(20);
                    if (monsterHit < AC) {
                        std::cout << " and misses!\n";
                        std::cout << "You swing and...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " miss!\n";
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                        else if (hit >= monsterAC) {
                            std::cout << " hit!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed Dale the vampire warlord!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else if (monsterHit >= AC) {
                        int lifesteal = random(5) + 3;
                        std::cout << " and hits!\n";
                        monsterHealth += lifesteal;
                        std::cout << "He steals " << lifesteal << " health!\n";
                        health -= monsterDamage;
                        std::cout << "You now have " << health << " health!\n";
                        if (health <= 0) {
                            gameOver(false);
                            exit(0);
                        }
                        else {
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                }
            }
            else if (fight == "n") {
                std::cout << "You can't run away from Dale!\n";
            }
        }
    }

    void skeletonKingCombat() {
        int bossRoundCounter = 6;

        while (true) {
            std::cout << "Do you fight? y/n\n";
            fight = getInput();

            if (!processCommand(fight)) continue;

            if (fight == "y") {
                bossRoundCounter--;

                if (bossRoundCounter == 0) {
                    bossRoundCounter = 5;
                    std::cout << "Dreadlord Varak raises his staff!\n";
                    std::cout << "A skeleton warrior rises from the ground!\n";
                    std::cout << "You must defeat it before continuing the fight with Dreadlord Varak!\n\n";

                    //Gotta save the stats
                    int savedBossHealth = monsterHealth;
                    int savedBossSpeed = monsterSpeed;
                    int savedBossAC = monsterAC;
                    int savedBossDamage = monsterDamage;
                    std::string savedBossName = monster;

                    // New stats
                    monsterHealth = 5;
                    monsterSpeed = 5;
                    monsterAC = 3;
                    monsterDamage = 2;
                    monster = "skeleton";

                    std::cout << "The skeleton gets ready to attack! Do you fight it? y/n\n";

                    while (true) {
                        std::string skeletonFight = getInput();

                        if (!processCommand(skeletonFight)) continue;

                        if (skeletonFight == "y") {
                            if (speed > monsterSpeed) {
                                std::cout << "You swing at the skeleton...";
                                int hit = random(20);
                                hit += precision;
                                if (hit < monsterAC) {
                                    std::cout << " and you miss!\n";
                                    std::cout << "The skeleton swings at you...";
                                    int monsterHit = random(20);
                                    if (monsterHit < AC) {
                                        std::cout << " and misses!\n";
                                        std::cout << "Do you keep fighting the skeleton? y/n\n";
                                    }
                                    else {
                                        std::cout << " and hits!\n";
                                        health -= monsterDamage;
                                        std::cout << "You now have " << health << " health!\n";
                                        if (health <= 0) {
                                            gameOver(false);
                                            exit(0);
                                        }
                                        std::cout << "Do you keep fighting the skeleton? y/n\n";
                                    }
                                }
                                else {
                                    std::cout << " and you hit!\n";
                                    monsterHealth -= damage;
                                    if (monsterHealth <= 0) {
                                        std::cout << "You killed the skeleton minion!\n";
                                        std::cout << "The skeleton crumbles to dust leaving nothing behind!\n";
                                        break;
                                    }
                                    else {
                                        std::cout << "Do you keep fighting the skeleton? y/n\n";
                                    }
                                }
                            }
                            else if (speed < monsterSpeed) {
                                std::cout << "The skeleton swings at you...";
                                int monsterHit = random(20);
                                if (monsterHit < AC) {
                                    std::cout << " and misses!\n";
                                    std::cout << "You swing at the skeleton and... ";
                                    int hit = random(20);
                                    hit += precision;
                                    if (hit < monsterAC) {
                                        std::cout << "miss!\n";
                                        std::cout << "Do you keep fighting the skeleton? y/n\n";
                                    }
                                    else {
                                        std::cout << "hit!\n";
                                        monsterHealth -= damage;
                                        if (monsterHealth <= 0) {
                                            std::cout << "You killed the skeleton minion!\n";
                                            std::cout << "The skeleton crumbles to dust leaving nothing behind!\n";
                                            break;
                                        }
                                        else {
                                            std::cout << "Do you keep fighting the skeleton? y/n\n";
                                        }
                                    }
                                }
                                else if (monsterHit >= AC) {
                                    std::cout << " and hits!\n";
                                    health -= monsterDamage;
                                    std::cout << "You now have " << health << " health!\n";
                                    if (health <= 0) {
                                        gameOver(false);
                                        exit(0);
                                    }
                                    std::cout << "Do you keep fighting the skeleton? y/n\n";
                                }
                            }
                            else if (speed == monsterSpeed) {
                                int first = random(2);
                                if (first == 0) {
                                    std::cout << "You swing at the skeleton...";
                                    int hit = random(20);
                                    hit += precision;
                                    if (hit < monsterAC) {
                                        std::cout << " and you miss!\n";
                                        std::cout << "The skeleton swings at you...";
                                        int monsterHit = random(20);
                                        if (monsterHit < AC) {
                                            std::cout << " and misses!\n";
                                            std::cout << "Do you keep fighting the skeleton? y/n\n";
                                        }
                                        else {
                                            std::cout << " and hits!\n";
                                            health -= monsterDamage;
                                            std::cout << "You now have " << health << " health!\n";
                                            if (health <= 0) {
                                                gameOver(false);
                                                exit(0);
                                            }
                                            std::cout << "Do you keep fighting the skeleton? y/n\n";
                                        }
                                    }
                                    else {
                                        std::cout << " and you hit!\n";
                                        monsterHealth -= damage;
                                        if (monsterHealth <= 0) {
                                            std::cout << "You killed the skeleton minion!\n";
                                            std::cout << "The skeleton crumbles to dust leaving nothing behind!\n";
                                            break;
                                        }
                                        else {
                                            std::cout << "Do you keep fighting the skeleton? y/n\n";
                                        }
                                    }
                                }
                                else {
                                    std::cout << "The skeleton swings at you...";
                                    int monsterHit = random(20);
                                    if (monsterHit < AC) {
                                        std::cout << " and misses!\n";
                                        std::cout << "You swing at the skeleton and... ";
                                        int hit = random(20);
                                        hit += precision;
                                        if (hit < monsterAC) {
                                            std::cout << "miss!\n";
                                            std::cout << "Do you keep fighting the skeleton? y/n\n";
                                        }
                                        else {
                                            std::cout << "hit!\n";
                                            monsterHealth -= damage;
                                            if (monsterHealth <= 0) {
                                                std::cout << "You killed the skeleton minion!\n";
                                                std::cout << "The skeleton crumbles to dust leaving nothing behind!\n";
                                                break;
                                            }
                                            else {
                                                std::cout << "Do you keep fighting the skeleton? y/n\n";
                                            }
                                        }
                                    }
                                    else if (monsterHit >= AC) {
                                        std::cout << " and hits!\n";
                                        health -= monsterDamage;
                                        std::cout << "You now have " << health << " health!\n";
                                        if (health <= 0) {
                                            gameOver(false);
                                            exit(0);
                                        }
                                        std::cout << "Do you keep fighting the skeleton? y/n\n";
                                    }
                                }
                            }
                        }
                        else if (skeletonFight == "n") {
                            std::cout << "You can't run away from a boss battle!\n";
                            std::cout << "Do you fight the skeleton? y/n\n";
                        }
                    }

                    monsterHealth = savedBossHealth;
                    monsterSpeed = savedBossSpeed;
                    monsterAC = savedBossAC;
                    monsterDamage = savedBossDamage;
                    monster = savedBossName;

                    std::cout << "You turn back to face Dreadlord Varak!\n";
                    std::cout << "The skeleton king awaits your next move!\n";
                    std::cout << "Do you fight? y/n\n";
                }
                else {
                    if (speed > monsterSpeed) {
                        std::cout << "You swing...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " and you miss!\n";
                            std::cout << "Dreadlord Varak swings at you...";
                            int monsterHit = random(20);
                            if (monsterHit < AC) {
                                std::cout << " and misses!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else if (monsterHit >= AC) {
                                std::cout << " and hits!\n";
                                health -= monsterDamage;
                                std::cout << "You now have " << health << " health!\n";
                                if (health <= 0) {
                                    gameOver(false);
                                    exit(0);
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else if (hit >= monsterAC) {
                            std::cout << " and you hit!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed Dreadlord Varak, the skeleton king!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else if (speed == monsterSpeed) {
                        int first = random(2);
                        if (first == 0) {
                            std::cout << "You swing...";
                            int hit = random(20);
                            hit += precision;
                            if (hit < monsterAC) {
                                std::cout << " and you miss!\n";
                                std::cout << "Dreadlord Varak swings at you...";
                                int monsterHit = random(20);
                                if (monsterHit < AC) {
                                    std::cout << " and misses!\n";
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                                else if (monsterHit >= AC) {
                                    std::cout << " and hits!\n";
                                    health -= monsterDamage;
                                    std::cout << "You now have " << health << " health!\n";
                                    if (health <= 0) {
                                        gameOver(false);
                                        exit(0);
                                    }
                                    else {
                                        std::cout << "Do you keep fighting? y/n\n";
                                    }
                                }
                            }
                            else if (hit >= monsterAC) {
                                std::cout << " and you hit!\n";
                                monsterHealth -= damage;
                                if (monsterHealth <= 0) {
                                    std::cout << "You killed Dreadlord Varak, the skeleton king!\n";
                                    monsterLootTables();
                                    inRoom = false;
                                    needToAsk = false;
                                    delay(1500);
                                    return;
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else {
                            std::cout << "Dreadlord Varak swings at you...";
                            int monsterHit = random(20);
                            if (monsterHit < AC) {
                                std::cout << " and misses!\n";
                                std::cout << "You swing and...";
                                int hit = random(20);
                                hit += precision;
                                if (hit < monsterAC) {
                                    std::cout << " miss!\n";
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                                else if (hit >= monsterAC) {
                                    std::cout << " hit!\n";
                                    monsterHealth -= damage;
                                    if (monsterHealth <= 0) {
                                        std::cout << "You killed Dreadlord Varak, the skeleton king!\n";
                                        monsterLootTables();
                                        inRoom = false;
                                        needToAsk = false;
                                        delay(1500);
                                        return;
                                    }
                                    else {
                                        std::cout << "Do you keep fighting? y/n\n";
                                    }
                                }
                            }
                            else if (monsterHit >= AC) {
                                std::cout << " and hits!\n";
                                health -= monsterDamage;
                                std::cout << "You now have " << health << " health!\n";
                                if (health <= 0) {
                                    gameOver(false);
                                    exit(0);
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                    }
                    else if (speed < monsterSpeed) {
                        std::cout << "Dreadlord Varak swings at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " and misses!\n";
                            std::cout << "You swing and...";
                            int hit = random(20);
                            hit += precision;
                            if (hit < monsterAC) {
                                std::cout << " miss!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else if (hit >= monsterAC) {
                                std::cout << " hit!\n";
                                monsterHealth -= damage;
                                if (monsterHealth <= 0) {
                                    std::cout << "You killed Dreadlord Varak, the skeleton king!\n";
                                    monsterLootTables();
                                    inRoom = false;
                                    needToAsk = false;
                                    delay(1500);
                                    return;
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else if (monsterHit >= AC) {
                            std::cout << " and hits!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                }
            }
            else if (fight == "n") {
                std::cout << "You can't run away from the skeleton king!\n";
            }
        }
    }

    void dragonCombat() {
        while (true) {
            std::cout << "Do you fight? y/n\n";
            fight = getInput();

            if (!processCommand(fight)) continue;

            if (fight == "y") {
                if (speed > monsterSpeed) {
                    std::cout << "You swing at the stone dragon...";
                    int hit = random(20);
                    hit += precision;
                    if (hit < monsterAC) {
                        std::cout << " but your weapon bounces off its stone hide!\n";
                        std::cout << "Brash the Stonehided swats at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " but you dodge the deadly attack!\n";
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                        else {
                            std::cout << " and slaps you aside!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                    else {
                        std::cout << " and you find a weak spot in the stone armor!\n";
                        monsterHealth -= damage;
                        if (monsterHealth <= 0) {
                            std::cout << "You killed Brash the Stonehided!\n";
                            monsterLootTables();
                            inRoom = false;
                            needToAsk = false;
                            delay(1500);
                            return;
                        }
                        else {
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                }
                else if (speed == monsterSpeed) {
                    int first = random(2);
                    if (first == 0) {
                        std::cout << "You swing at the stone dragon...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " but your weapon bounces off its stone hide!\n";
                            std::cout << "Brash the Stonehided swats at you...";
                            int monsterHit = random(20);
                            if (monsterHit < AC) {
                                std::cout << " but you dodge the deadly attack!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else {
                                std::cout << " and slaps you aside!\n";
                                health -= monsterDamage;
                                std::cout << "You now have " << health << " health!\n";
                                if (health <= 0) {
                                    gameOver(false);
                                    exit(0);
                                }
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                        else {
                            std::cout << " and you find a weak spot in the stone armor!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed Brash the Stonehided!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else {
                        std::cout << "Brash the Stonehided swats at you...";
                        int monsterHit = random(20);
                        if (monsterHit < AC) {
                            std::cout << " but you dodge the deadly attack!\n";
                            std::cout << "You swing at the stone dragon and...";
                            int hit = random(20);
                            hit += precision;
                            if (hit < monsterAC) {
                                std::cout << " your weapon bounces off its stone hide!\n";
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                            else {
                                std::cout << " you find a weak spot in the stone armor!\n";
                                monsterHealth -= damage;
                                if (monsterHealth <= 0) {
                                    std::cout << "You killed Brash the Stonehided!\n";
                                    monsterLootTables();
                                    inRoom = false;
                                    needToAsk = false;
                                    delay(1500);
                                    return;
                                }
                                else {
                                    std::cout << "Do you keep fighting? y/n\n";
                                }
                            }
                        }
                        else {
                            std::cout << " and slaps you aside!\n";
                            health -= monsterDamage;
                            std::cout << "You now have " << health << " health!\n";
                            if (health <= 0) {
                                gameOver(false);
                                exit(0);
                            }
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                    }
                }
                else if (speed < monsterSpeed) {
                    std::cout << "Brash the Stonehided swats at you...";
                    int monsterHit = random(20);
                    if (monsterHit < AC) {
                        std::cout << " but you dodge the deadly attack!\n";
                        std::cout << "You swing at the stone dragon and...";
                        int hit = random(20);
                        hit += precision;
                        if (hit < monsterAC) {
                            std::cout << " your weapon bounces off its stone hide!\n";
                            std::cout << "Do you keep fighting? y/n\n";
                        }
                        else {
                            std::cout << " you find a weak spot in the stone armor!\n";
                            monsterHealth -= damage;
                            if (monsterHealth <= 0) {
                                std::cout << "You killed Brash the Stonehided!\n";
                                monsterLootTables();
                                inRoom = false;
                                needToAsk = false;
                                delay(1500);
                                return;
                            }
                            else {
                                std::cout << "Do you keep fighting? y/n\n";
                            }
                        }
                    }
                    else {
                        std::cout << " and slaps you aside!\n";
                        health -= monsterDamage;
                        std::cout << "You now have " << health << " health!\n";
                        if (health <= 0) {
                            gameOver(false);
                            exit(0);
                        }
                        std::cout << "Do you keep fighting? y/n\n";
                    }
                }
            }
            else if (fight == "n") {
                std::cout << "You can't run away from the dragon!\n";
            }
        }
    }

public:
    void run() {
        std::cout << "Welcome to the Dungeon explorer!\n";
        std::cout << "In this game you will be collecting potions and loot.\n";
        std::cout << "Do your best to not run away too early.\n";
        std::cout << "Use 'actions' to check what you can do.\n";
        delay(6500);
        std::cout << "First you have to pick your armor!\n";
        std::cout << "1.T-shirt 2.chainmail 3.metal plate\n";

        while (!armorChosen) {
            armor = getInput();
            if (!processCommand(armor)) continue;

            if (armor == "1") {
                std::cout << "You chose the T-shirt!\n";
                armorChosen = true;
                delay(500);
            }
            else if (armor == "2") {
                std::cout << "You chose chainmail!\n";
                speed -= 5;
                AC += 5;
                armorChosen = true;
                delay(500);
            }
            else if (armor == "3") {
                std::cout << "You chose metal plate!\n";
                speed -= 10;
                AC += 10;
                armorChosen = true;
                delay(500);
            }
            else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }

        if (!weaponAsk) {
            std::cout << "Now pick your weapon!\n";
            std::cout << "1. fists 2. dagger 3. sword\n";
            weaponAsk = true;
        }

        while (!weaponChosen) {
            weapon = getInput();
            if (!processCommand(weapon)) continue;

            if (weapon == "1") {
                std::cout << "You chose your own fists!\n";
                weaponChosen = true;
                delay(500);
            }
            else if (weapon == "2") {
                std::cout << "You chose the daggers!\n";
                damage += 2;
                speed -= 1;
                weaponChosen = true;
                delay(500);
            }
            else if (weapon == "3") {
                std::cout << "You chose the sword!\n";
                damage += 5;
                speed -= 2;
                weaponChosen = true;
                delay(500);
            }
            else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }

        while (true) {
            if (!inRoom) {
                doorPick();
                doorPickTwo();

                int direction = random(7);
                if (direction == 0) {
                    std::cout << "You can only go straight down the hall, so that's where you go.\n";
                }
                else if (direction == 1) {
                    std::cout << "There's only a left turn in the hall, so that's where you go.\n";
                }
                else if (direction == 2) {
                    std::cout << "There's only a right turn in the hall, so that's where you go.\n";
                }
                else if (direction == 3) {
                    std::cout << "You can go left or straight. Where do you go? left/straight\n";
                    whichWay = getInput();
                    if (!processCommand(whichWay)) continue;
                    if (whichWay == "left") {
                        std::cout << "You go left!\n";
                    }
                    else if (whichWay == "straight") {
                        std::cout << "You go straight!\n";
                    }
                    else {
                        std::cout << "Invalid answer. You go straight.\n";
                    }
                }
                else if (direction == 4) {
                    std::cout << "You can go left or right. Where do you go? left/right\n";
                    whichWay = getInput();
                    if (!processCommand(whichWay)) continue;
                    if (whichWay == "left") {
                        std::cout << "You go left!\n";
                    }
                    else if (whichWay == "right") {
                        std::cout << "You go right!\n";
                    }
                    else {
                        std::cout << "Invalid answer. You go left.\n";
                    }
                }
                else if (direction == 5) {
                    std::cout << "You can go straight or right. Where do you go? straight/right\n";
                    whichWay = getInput();
                    if (!processCommand(whichWay)) continue;
                    if (whichWay == "straight") {
                        std::cout << "You go straight!\n";
                    }
                    else if (whichWay == "right") {
                        std::cout << "You go right!\n";
                    }
                    else {
                        std::cout << "Invalid answer. You go straight.\n";
                    }
                }
                else if (direction == 6) {
                    std::cout << "You can go left, straight, or right. Where do you go? left/straight/right\n";
                    whichWay = getInput();
                    if (!processCommand(whichWay)) continue;
                    if (whichWay == "left") {
                        std::cout << "You go left!\n";
                    }
                    else if (whichWay == "straight") {
                        std::cout << "You go straight!\n";
                    }
                    else if (whichWay == "right") {
                        std::cout << "You go right!\n";
                    }
                    else {
                        std::cout << "Invalid answer. You go right.\n";
                    }
                }

                int doors = random(4);
                if (doors == 0) {
                    std::cout << "There are no doors, so you continue onward.\n";
                }
                else if (doors == 1) {
                    std::cout << "There is only one door to your left. It is a " << door << " door. Do you go in? y/n\n";
                    doorAnswer = getInput();
                    if (!processCommand(doorAnswer)) continue;
                    if (doorAnswer == "y") {
                        inRoom = true;
                        std::cout << "You enter the room.\n";
                        inside();
                    }
                    else if (doorAnswer == "n") {
                        std::cout << "You continue onward.\n";
                    }
                }
                else if (doors == 2) {
                    std::cout << "There is only one door to your right. It is a " << doorTwo << " door. Do you go in? y/n\n";
                    doorAnswer = getInput();
                    if (!processCommand(doorAnswer)) continue;
                    if (doorAnswer == "y") {
                        inRoom = true;
                        std::cout << "You enter the room.\n";
                        insideTwo();
                    }
                    else if (doorAnswer == "n") {
                        std::cout << "You continue onward.\n";
                    }
                }
                else if (doors == 3) {
                    std::cout << "There is a " << door << " door to your left, and a " << doorTwo << " door to your right. Do you go in? left/right/n\n";
                    doorAnswer = getInput();
                    if (!processCommand(doorAnswer)) continue;
                    if (doorAnswer == "left") {
                        inRoom = true;
                        std::cout << "You enter the room.\n";
                        inside();
                    }
                    else if (doorAnswer == "right") {
                        inRoom = true;
                        std::cout << "You enter the room.\n";
                        insideTwo();
                    }
                    else if (doorAnswer == "n") {
                        std::cout << "You continue onward.\n";
                    }
                }
            }

            updateTimers();
        }
    }
};

int main() {
    DungeonGame game;
    game.run();
    return 0;
}