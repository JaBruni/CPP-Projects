// March 17. 2021
// This program is game where 4 different types of creatures with 
// unique attributes can battle one another. The program uses class
// inheritance to eliminate a "type" variable. 

#include <iostream>
#include <ctime>
using namespace std;


class Creature
{
private:
	int strength; // How much damage we can inflict
	int hitpoints; // How much damage we can sustain
public:
	// Default Constructor
	Creature() : strength(10), hitpoints(10) {}

	// Overloaded Constructor
	Creature(int newStrength, int newHit) : strength(newStrength), hitpoints(newHit) {}

	//Sets the strength of the creature
	void setStrength(int newStrength) {
		strength = newStrength;
	}

	//Returns the strength of the creature
	int getStrength() const {
		return strength;
	}

	// Sets the hit points of the creature
	void setHitPoints(int newHit) {
		hitpoints = newHit;
	}

	// Returns the hit points of the creature
	int getHitPoints() const {
		return hitpoints;
	}

	// Returns the damage a creature can inflict in one round of combat.
	// This function is overidden so each child class of creature is able 
	// to return damage modifiers specific to their species,
	// while also generating their inital damage (a random number up to 
	// their strength).
	virtual int getDamage() {
		int damage;
		damage = (rand() % strength) + 1;
		cout << getSpecies() << " attacks for " <<
			damage << " points!" << endl;
		return damage;
	}

	// Returns the species of the creature. This is a pure virtual function
	// which eliminates the need for a type variable. 
	virtual string getSpecies() const = 0;
};


class Demon : public Creature {
public:
	Demon() {}
	Demon(int newStrength, int newHit) : Creature(newStrength, newHit){}
	string getSpecies() const {
		return "Demon";
	}
	int getDamage() {
		int demonDamage = Creature::getDamage();
		if ((rand() % 100) < 5) {
			demonDamage = demonDamage + 50;
			cout << "Demonic attack inflicts 50 "
				<< " additional damage points!" << endl;
		}
		return demonDamage;
	}
};

class Elf : public Creature {
public:
	Elf() {}
	Elf(int newStrength, int newHit) : Creature(newStrength, newHit) {}
	string getSpecies() const {
		return "Elf";
	}
	int getDamage() {
		int elfDamage = Creature::getDamage();
		// All creatures inflict damage which is a
		// random number up to their strength
		int value = (rand() % 10) + 1;
		if (value == 1) {
			cout << "Magical attack inflicts " << elfDamage 
				<< " additional damage!" << endl;
			elfDamage = elfDamage * 2;
		}
		return elfDamage;
	}
};

class Human : public Creature {
public:
	Human() {}
	Human(int newStrength, int newHit) : Creature(newStrength, newHit) {}
	string getSpecies() const {
		return "Human";
	}
};

class Cyberdemon : public Demon {
public:
	Cyberdemon() {}
	Cyberdemon(int newStrength, int newHit) : Demon(newStrength, newHit) {}
	string getSpecies() const {
		return "Cyberdemon";
	}
};

class Balrog : public Demon {
public:
	Balrog() {}
	Balrog(int newStrength, int newHit) : Demon(newStrength, newHit) {}
	string getSpecies() const {
		return "Balrog";
	}
	int getDamage() {
		int balrogDamage = Demon::getDamage();
		int value = ((rand() % getStrength()) + 1);
		cout << "Balrog speed attack inflicts " << value
			<< " additional damage points!" << endl;
		balrogDamage = balrogDamage + value;
		return balrogDamage;
	}
};

void battleArena(Creature& creature1, Creature& creature2);

int main() {
	srand(static_cast<int>(time(NULL)));
	Human human1(30, 10);
	human1.getDamage();
	cout << endl;
	Elf elf1;
	elf1.getDamage();
	cout << endl;
	Balrog balrog1(50, 50);;
	balrog1.getDamage();
	cout << endl;
	Cyberdemon cdemon(30, 40);
	cdemon.getDamage();
	cout << endl;
	Cyberdemon cyberdemon2(50, 50);
	Balrog balrog2(50, 50);
	cout << endl;
	battleArena(cyberdemon2, balrog2);
}

// The battleArena function receives two Creature objects. It calculates the 
// the damage done by creature1, subtracts that amount from creature2, and vice 
// versa. If one creature has postive hitpoints and the other has less than 0, 
// the creature with positive hitpoints wins. If both creatures end up with less 
// than 0 points, the result is a tie game.
void battleArena(Creature& creature1, Creature& creature2) {
	bool gameisOver;
	int newHit1 = 0;
	int newHit2 = 0;
	gameisOver = false;
	cout << "The Battle Begins!" << endl;
	cout << "------------------" << endl;
	while (gameisOver == false) {
		// Creature 1 turn
		int damage1 = creature1.getDamage();
		newHit1 = creature1.getHitPoints() - damage1;
		cout << "Creature 2 has " << newHit1  << " hit points." << endl;
		creature2.setHitPoints(newHit1);
		// Creature 2 turn
		int damage2 = creature2.getDamage();
		newHit2 = creature1.getHitPoints() - damage2;
		cout << "Creature 1 has " << newHit2 << " hit points." << endl;
		creature1.setHitPoints(newHit2);
		if (newHit1 < 0 && newHit2 > 0) {
			cout << endl;
			cout << "Creature 1 wins!" << endl;
			gameisOver = true;
		}
		else if (newHit1 > 0 && newHit2 < 0) {
			cout << endl;
			cout << "Creature 2 wins!" << endl;
			gameisOver = true;
		}
		else if (newHit1 < 0 && newHit2 < 0) {
			cout << endl;
			cout << "Tie game!" << endl;
			gameisOver = true;
		}
	}
}

/* 
 SAMPLE RUN:
 Human attacks for 10 points!

 Elf attacks for 2 points!

 Balrog attacks for 9 points!
 Balrog speed attack inflicts 3 additional damage points!

 Cyberdemon attacks for 5 points!


 The Battle Begins!
 ------------------
 Cyberdemon attacks for 12 points!
 Creature 2 has 38 hit points.
 Balrog attacks for 11 points!
 Balrog speed attack inflicts 48 additional damage points!
 Creature 1 has -9 hit points.

 Creature 2 wins!
*/