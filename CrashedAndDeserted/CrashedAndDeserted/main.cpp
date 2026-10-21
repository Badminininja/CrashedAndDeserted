//
//  main.cpp
//  CrashedAndDeserted
//
//

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include "characterRace.hpp"
#include "animalRace.hpp"
#include "humanRace.hpp"
#include "ExiledMember.hpp"
#include "Boss.hpp"
#include "Goblin.hpp"
#include "Dice20App.hpp"

using namespace std;

// Reads an integer from the user. If they type something that isn't a number,
// cin would otherwise enter a fail state and any validation loop would spin
// forever, so we clear the error, discard the bad input, and ask again.
int readInt() {
    int value;
    while (!(cin >> value)) {
        if (cin.eof()) { exit(0); }   // input closed (piped end / Ctrl+D): quit cleanly
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number: ";
    }
    return value;
}

Character* openingScene(CharacterRace* typeCharacter, Character* userCharacter);
int firstScene(Character* userCharacter, vector<string>& progress);
string beachScene(Character* userCharacter, vector<string> progress);
string BeachDialogue(Character* userCharacter, vector<string> progress);
string forestScene(Character* userCharacter, vector<string> progress);
string investigateStructureScene(Character* userCharacter, vector<string> progress);
string waterfallScene(Character* userCharacter, vector<string> progress);
string beach2Scene(Character* userCharacter, vector<string> progress);
string bossSceneFront(Character* userCharacter, vector<string> progress);
string bossSceneBack(Character* userCharacter, vector<string> progress);
string deathRoute(Character* userCharacter, vector<string> progress);
string secretEnding(Character* userCharacter, vector<string> progress);
void GoblinBattle(Character* player, vector<string> progress);
void ExiledMemberBattle(Character* player, vector<string> progress);
void BossBattle(Character* player, vector<string> progress);
void printProgress(vector<string> progress);


int main() {
	srand(time(NULL));
    CharacterRace* typeCharacter;
    Character* userCharacter;
    int sceneNum;
    vector<string> progress;
    progress.push_back("Exiled from the Kingdom");
    //Will have to make a Character class that inherits the Mage and Warrior classes
    userCharacter = openingScene(typeCharacter,userCharacter);
    sceneNum = firstScene(userCharacter, progress);
    string tempSecondScene;
    string tempThirdScene;
    string endingScene;
    
    if(sceneNum == 1){
        tempSecondScene = forestScene(userCharacter, progress);
    }
    else if (sceneNum == 2){
        tempSecondScene  = beachScene(userCharacter, progress);
    }
    progress.push_back(tempSecondScene);
    
    if(tempSecondScene == "Investigate Structure Scene"){
        tempThirdScene = investigateStructureScene(userCharacter, progress);
    }
    else if (tempSecondScene == "Waterfall Scene"){
    	tempThirdScene = waterfallScene(userCharacter, progress);
    }
    else if (tempSecondScene == "Beach 2 Scene"){
    	tempThirdScene = beach2Scene(userCharacter, progress);
    }
    progress.push_back(tempThirdScene);

    if(tempThirdScene == "Boss Scene Front"){
        endingScene = bossSceneFront(userCharacter, progress);
    }
    else if (tempThirdScene == "Boss Scene Back"){
        endingScene = bossSceneBack(userCharacter, progress);
    }
    else if (tempThirdScene == "Death Route"){
        endingScene = deathRoute(userCharacter, progress);
    }
    else if (tempThirdScene == "Secret Ending"){
        cout << "CONGRATULATIONS, SECRET ENDING ACHIEVED"<<endl;
        endingScene = secretEnding(userCharacter, progress);
    }
    progress.push_back(endingScene);

	if(endingScene == "THE END"){
		cout << "After defeating the boss of this island, you triumphantly climb the tower and ride his helicopter. Of course you, don't actually have any keys so you make your way to search his room and bring some jewellery while you were there. Once you get in the coptor, you fly high and start to search for where civilization is again."<<endl;
		cout << "Congrats, you won the game"<<endl;
	}else if(endingScene == "Death End Route"){
		cout << "Unfortunately you got the bad end"<<endl;
	}else if(endingScene == "Secret Route End"){
		cout << "Congrats, you found the secret route"<<endl;
	}
	printProgress(progress);
	return 0;
}
void printProgress(vector<string> progress){
	cout << endl << "Your Decisions" <<endl;
    for(int i = 0; i < progress.size(); i++){
		cout << "Scene #" << i + 1 << ": ";
		cout << progress.at(i)<<endl;
	}
    cout << endl;
}
Character* openingScene(CharacterRace* typeCharacter, Character* userCharacter) {
    string name;
    Character* character;
    int response = 0;
    bool human = false;
    bool mage = false;
    cout << "SCENE: Court Room" << endl;
    cout << "Judge: Who is the next person up for judgment?" << endl;
    cout << "Deputy: State your name to the judge." << endl;
    getline(cin, name);
    cout << "Judge: Ok " << name << ", is your race an animal or human?" << endl;
    cout << "(Enter 1 for animal or 2 for human)" << endl;
    while ((response != 1) && (response != 2)) {
        response = readInt();
        if (response == 1) {
            typeCharacter = new AnimalRace();
        } else if (response == 2) {
            human = true;
            typeCharacter = new HumanRace();
        } else {
            cout << "Judge: No funny business, please tell me your race." << endl;
            cout << "(Enter 1 for animal or 2 for human)" << endl;
        }
    }
    cout << "Judge: So " << name << ", what is your profession?" << endl;
    cout << "(Enter 1 for warrior or 2 for mage)" << endl;
    response = 0;
    while ((response != 1) && (response != 2)) {
        response = readInt();
        if (response == 1) {
            character = typeCharacter->createWarrior(name);
        } else if (response == 2) {
            mage = true;
            character = typeCharacter->createMage(name);
        } else {
            cout << "Judge: No funny business, please tell me your profession." << endl;
            cout << "(Enter 1 for warrior or 2 for mage)" << endl;
        }
    }
    // tests the character selection menu
    if (human) {
        if (mage) {
            cout << "* You have selected a Human Mage as your character. *" << endl;
        }
        else {
            cout << "* You have selected a Human Warrior as your character. *" << endl;
        }
    }
    else {
        if (mage) {
            cout << "* You have selected an Animal Mage as your character. *" << endl;
        }
        else {
            cout << "* You have selected an Animal Warrior as your character. *" << endl;
        }
    }
    
    cout << "Judge: For the betrayal of your team and murder for your partner, you are sentenced to death by hanging" << endl;
    cout << name << ": Your honor please, my reasons are valid; I should not have my life taken away." << endl;
    cout << "Judge: Valid or invalid, your crimes are still clear, but if you still believe your life should not be taken, then you shall be exiled on the abandoned island." << endl;
    cout << name << ": But your honor-" << endl;
    cout << "Judge: Silence, your sentence is final. Guards, take him away." << endl << endl;
    return character;
}

int firstScene(Character* userCharacter, vector<string>& progress) {
    int response = 0;
    int scene = 0;
    cout << "SCENE: Stranded Beach" << endl;
    cout << "You wake up from being unconcious on the unknown beach." << endl;
    cout << "You look left and right and do not see a single man made object in sight." << endl;
    cout << "Behind you is an unclimbable mountain." << endl;
    cout << "To the right is the ocean." << endl;
    cout << "To the left is the forest." << endl;
    cout << "Up ahead is the rest of the beach." << endl;
    cout << "You can't climb the mountain or swim in the ocean" << endl;
    cout << "Which route do you take?" << endl;
    cout << "(Enter 1 to venture into the forest)" << endl;
    cout << "(Enter 2 to trek along the beach)" << endl;
    cout << "(Enter 3 to view your stats)" << endl;
    while ((response != 1) && (response != 2)) {
        response = readInt();
        if (response == 1) {
            cout << "You decided to brave the dark forest." << endl;
            progress.push_back("You decided to brave the dark forest.");
            scene = 1;
        } else if (response == 2) {
            cout << "You decided to walk along the beach." << endl;
            progress.push_back("You decided to walk along the beach.");
            scene = 2;
        } else if (response == 3) {
            userCharacter->stats();
            cout << endl;
            cout << "(Enter 1 to venture into the forest)" << endl;
            cout << "(Enter 2 to trek along the beach)" << endl;
            cout << "(Enter 3 to view your stats)" << endl;
        } else {
            cout << "Idly standing here won't keep you alive (Wrong Input)." << endl;
            cout << "(Enter 1 to venture into the forest)" << endl;
            cout << "(Enter 2 to trek along the beach)" << endl;
            cout << "(Enter 3 to view your stats)" << endl;
        }
    }
    return scene;
}
string beachScene(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout<< "As you go down the beach, you notice how clear it is. Just sand and rocks. You don’t spot any pollution around or littered on the beach; until you come across what seems to be some near a rock cluster. You move to the side to get a better view of what might be behind the rock and you see someone who is sleeping there, understandably so as the sun has just risen."<<endl;
	cout << "What do you do?"<<endl;
	cout << "(Enter 1) Call out to him from afar to wake him up and talk to him?"<<endl;
	cout << "(Enter 2) Go up to him and shake him to make sure he wakes up? You gotta be sure he wakes up else you will continue to be clueless of this situation."<<endl;
	cout << "(Enter 3) Ignore him and keep walking along the beach? Who knows who or what he is, it's best to just leave him be. Plus, he is sleeping so might as well let him sleep." <<endl;
	cout << "(Enter 4 for stats)"<<endl;
	while((response !=1) && (response !=2) && (response !=3)){
		response = readInt();
		if(response ==1){
			cout << "The guy sleeping woke up and noticed you. He does an inviting gesture and you walk up a bit closer so you can talk to him." <<endl;//DIALOGUE
			return BeachDialogue(userCharacter, progress);
		}
		else if(response == 2){
			cout << "As you shake him vigorously to wake him up, the guy gets startled and wakes up; however, as a defensive reaction to his sudden awakening he hit you with a rock that he was holding while sleeping. (Player takes damage) “Oh man, sorry, I didn’t mean to hit you, it's just that I thought you might have been like a bear or something, it was just a reflex” the stranger says. He then sits up and asks if you want to know anything as it was the least he could do." <<endl; //DIALOGUE
			return BeachDialogue(userCharacter, progress);	
		}
		else if (response == 3){
			cout << "As you walk past him you start to notice how run down his area was, but it’s none of your business. As you walk a few paces past what you could only assume was his area, you start to hear a waterfall nearby and that's when you get stabbed in the back from the guy that was supposedly sleeping. (Player takes damage). The guy was never actually sleeping and you simply showed your back to a potential enemy. You were an exiled on this beach, if he’s there then he must be one too. He loads up a second strike but he you parry it and you guys fight." <<endl;
			ExiledMemberBattle(userCharacter, progress);
			return "Waterfall Scene";
			//call Battle Function
		}
		else if (response == 4) {
			userCharacter->stats();
			cout << "(Enter 1) Call out to him from afar to wake him up and talk to him?"<<endl;
			cout << "(Enter 2) Go up to him and shake him to make sure he wakes up? You gotta be sure he wakes up else you will continue to be clueless of this situation."<<endl;
			cout << "(Enter 3) Ignore him and keep walking along the beach? Who knows who or what he is, it's best to just leave him be. Plus, he is sleeping so might as well let him sleep." <<endl;
			cout << "(Enter 4 for stats)"<<endl;
		}
		else{
			cout << "(Enter 1) Call out to him from afar to wake him up and talk to him?"<<endl;
			cout << "(Enter 2) Go up to him and shake him to make sure he wakes up? You gotta be sure he wakes up else you will continue to be clueless of this situation."<<endl;
			cout << "(Enter 3) Ignore him and keep walking along the beach? Who knows who or what he is, it's best to just leave him be. Plus, he is sleeping so might as well let him sleep." <<endl;
			cout << "(Enter 4 for stats)"<<endl;
		}
	}
	return "BEACH OUT OF LOOP";


}
string BeachDialogue(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout << "Hey, my name is Octavius, Tane Octavius, I’ve been here for a short while now, is there anything you wanted to know? I don’t have much better things to do right now and I don’t mind the company." <<endl;
	cout << "What do you want to know?" <<endl;
	cout << "(Enter 1) Ask about the area" <<endl;
	cout << "(Enter 2) Ask how he got here" <<endl;
	cout << "(Enter 3) Ask if he knows if there is anyone else around" <<endl;
        cout << "(Enter 4) Ask why is he here on this island (Enter 4)" << endl;
        cout << "(Enter 5) You know all that you need to know, say a farewell and continue along the beach" << endl;
	cout << "(Enter 6) view stats" <<endl;
	while((response !=4) && (response !=5)){
		response = readInt();
		if (response == 1){
			cout << "So far as I know, this place is a small island, located who knows where. The forest covers most of the area, there’s plenty of food in there so it's pretty easy to continue living here." <<endl;
			cout << "Anything else you want to know? (1 area, 2 how, 3 anyone, 4 why, 5 leave, 6 stats)" <<endl;
		}
		else if (response == 2){
			cout << "I’m not entirely sure how I got here, at one point I got knocked out and then I woke up on this Island, I don’t know how I was put here nor the people who did it. Though that was a long time ago so that matters little now." <<endl;
                        cout << "Anything else you want to know? (1 area, 2 how, 3 anyone, 4 why, 5 leave, 6 stats)" <<endl;
		}	
		else if (response == 3){
			cout << "I haven’t actually seen anyone around but I do hear noises that I can only assume are other people. Or maybe even mystical creatures, who knows. I don’t know their business whether they are hostile or friendly so I haven’t confronted them." <<endl;
                        cout << "Anything else you want to know? (1 area, 2 how, 3 anyone, 4 why, 5 leave, 6 stats)" <<endl;

		}
		else if (response == 4){
			cout << "How about before I answer that we go into the forest? It's morning and I haven’t had anything to eat and I’m sure you haven’t either. There is a lot of food in the forest as it seems there has been little human intervention." <<endl;
			//BATTLE TRIGGER
			cout << "You both start walking into the forest with Tane leading to a place with some good fruit. “You know I remembered the reason why I’m here, before I was knocked out and landed on this beach, I remember a court scene. Heh, yea I was exiled. But you know, that also means you’ve been exiled, and that means you’ve got blood on your hands” As we finish his sentence an arrow shoots, hidden in some bushes and pierces your shoulder, just nearly missing your head. “Tsk, You’re a criminal like me, I can’t trust you” He pulls out his sword and gets ready to fight you." <<endl;
			ExiledMemberBattle(userCharacter, progress);
			return "Waterfall Scene";
		}
		else if (response == 5){
			cout << "All good, I’m gonna go get some fruit in the forest for something to eat, see ya around I guess" <<endl;
			return "Beach 2 Scene";
		}else if (response == 6){
			userCharacter->stats();
			cout << "Anything else you want to know? (1 area, 2 how, 3 anyone, 4 why, 5 leave, 6 stats)" <<endl;
		}
		else{
			cout << "What do you want to know?" <<endl;
		        cout << "(Enter 1) Ask about the area" <<endl;
		        cout << "(Enter 2) Ask how he got here" <<endl;
		        cout << "(Enter 3) Ask if he knows if there is anyone else around" <<endl;
		        cout << "(Enter 4) Ask why is he here on this island (Enter 4)" << endl;
		        cout << "(Enter 5) You know all that you need to know, say a farewell and continue along the beach" << endl;
			cout << "(Enter 6) view stats" <<endl;
	
		
		}
	}
}
string forestScene(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout << "As the player treks into the forest, it is filled with large vegetation, not only bushes plentiful of all shapes and sorts but trees tall enough to reach a second story building while their leaves creates a roof over the entire forest leaving only small holes for the sunlight to penetrate and illuminate the darkness beneath the treeline. Alas, even as beautiful as the forest felt and untouched by the hands of human intervention, you spot signs of a trail lined with rocks. As you spot this trail you immediately hear the unnatural sounds of the clanging of metal. Its clangs sounded off in a rhythmic pattern reminding you of the sound of one of your previous party members' armor as they moved around. What should you do now?" <<endl;
	cout << "CHOICES What do you do?"<<endl;
	cout << "(Enter 1) Keep moving forward toward the trail and try to see where the sound is coming from? Maybe there’s actually other people on this island who could help you." <<endl;
	cout << "(Enter 2) Hide in the bushes and stalk and follow the noise. With the amount of vegetation it should be enough to conceal your presence. "<<endl;
	cout << "(Enter 3) Climb up a nearby tree close to the trail in order to get a better view of the situation and in hope that said noise won't notice you." << endl;
	cout << "(Enter 4) view stats" <<endl;
	while((response !=1) && (response !=2) && (response !=3)){
		response = readInt();
		if(response == 1){
			cout << "You decide to confront the sound coming from the trail. You believe this is the best choice, I mean you have no clue about where you’re at nor anything about this area or what’s going on. As you get closer to the noise you could see a humanoid figure to your delight; however, upon closer inspection you see that the figure is actually a Goblin suited with light metal armor across his whole body. What was worse is that you can see that he has a badge indicating servitude toward the court which means people still monitor this area, but that does mean there is a mode of transportation available." <<endl;
			cout << "CHOICES With him close enough for both of you to see each other what do you do."<<endl;
			cout << "(Enter 1) Try to make a break for it along the trail" <<endl; 
			cout << "(Enter 2) Try to talk your way out" <<endl;
			cout << "(Enter 3) view stats" <<endl;
			response = 0;
			while((response !=1) && (response !=2) && (response !=3)){	
				response = readInt();
				if(response == 1){
					cout << "The Goblin throws a small knife hitting your leg and slowing you down enough for him to get to you" <<endl;
					//PLAYER FREE HIT
					//BATTLE
					GoblinBattle(userCharacter, progress);
				}
				else if (response == 2){ 
					cout << "You tell the Goblin you were lost and would much appreciate it if he could lead you back to civilization. He responds in a deep and dirty voice, “Well that’s fine, it's just down this trail. But you know, the only people here that can be wandering around outside needs a badge right?” You awkwardly smile and nod your head “of course, of course I knew that, I just so happened to have lost my badge.” He responds “Ah, then that’s good, because then that means you should also know that if you don’t have a badge outside then we can only assume that you are an exile to which we may kill on the spot” He sports a dark grin as he unsheathed his sword and points it at you. “Hope you’re ready to die exile, cus I’m ready for a promotion”" <<endl;
					//BATTLE
					GoblinBattle(userCharacter, progress);
				}else if (response == 3){
					userCharacter->stats();
					cout << "This is no time to look at your stats. The Goblin throws a knife at you while you're distracted then prepares for battle" <<endl;
					GoblinBattle(userCharacter, progress);
					//PLAYER FREE HIT
					//BATTLE	
				}
			}
 						
			cout << "With the Goblin gone, you could path toward where the trail continues, or you can trek into the forest where you hear crashing waters which could potentiall give you a place to rest" <<endl;
			cout << "CHOICE "<<endl;
			cout << "(Enter 1) toward the trail"<<endl;
			cout << "(Enter 2) toward the water"<<endl;
			cout << "(Enter 3) view stats" <<endl;
			response = 0;
			while((response !=1) && (response !=2)){
				response = readInt();
				if(response ==1){
					return "Investigate Structure Scene";
				}
				else if (response == 2) {
					return "Waterfall Scene";
				}
				else if (response == 3) {
					userCharacter->stats();
					cout << "(Enter 1) toward the trail"<<endl;
					cout << "(Enter 2) toward the water"<<endl;
					cout << "(Enter 3) view stats" <<endl;
				}
				else{
				 	cout << "CHOICE "<<endl;
                      		 	cout << "(Enter 1) toward the trail"<<endl;
                		       cout << "(Enter 2) toward the water"<<endl;
 		                       cout << "(Enter 3) view stats" <<endl;
				} 
			}	
			
			
		}else if(response ==2){
			cout << "As you wait in the bushes you see a humanoid figure to your delight; however, upon closer inspection you see that the figure is actually a Goblin suited with light metal armor across his whole body. What was worse is that you can see that he has a badge indicating servitude toward the court which means people still monitor this area, but that does mean there is a mode of transportation available. " <<endl; 
			cout << "CHOICES: With him still unaware of your presence what do you do?" <<endl;
			cout << "(Enter 1) Stab him in the back and get a free hit before fighting him? "<<endl;
			cout << "(Enter 2) Continue to stalk him from the bushes" <<endl;
			cout << "(Enter 3) View Stats" <<endl;
			response = 0;
			while((response !=1) && (response !=2)){
				response = readInt();
				if(response == 1){
					cout << "Goblin grunts in pain “haah, an exile stabbing me in the back, how typical”" <<endl;
					//Goblin Takes free hit
					//GOBLINE BATTLE
					GoblinBattle(userCharacter, progress);
					cout << "after a successful victory against the Goblin, you come accross the structure that the path lead to "<<endl;
					return "Investigate Structure Scene";
				}else if (response ==2){
					cout << "The trail he walks on leads to a medieval structure, similar to something like a castle but not as majestic or beautiful, more run down if anything. The Goblin goes through the front door with it not seeming to be locked as they probably think no one unapproved would be here on this island. After a bit of time the Goblin leaves the structure in pursuit of something that is off road and deeper in the forest." <<endl;
					return "Investigate Structure Scene";
				}else if (response == 3){
					userCharacter->stats();
					cout << "CHOICES: With him still unaware of your presence what do you do?" <<endl;
        		                cout << "(Enter 1) Stab him in the back and get a free hit before fighting him? "<<endl;
        		                cout << "(Enter 2) Continue to stalk him from the bushes" <<endl;
		                        cout << "(Enter 3) View Stats" <<endl;	
				}else {		
					cout << "Don't just do nothing" <<endl;
		                        cout << "(Enter 1) Stab him in the back and get a free hit before fighting him? "<<endl;
		                        cout << "(Enter 2) Continue to stalk him from the bushes" <<endl;
		                        cout << "(Enter 3) View Stats" <<endl;
		
				}
			}	
		}else if(response == 3) {
			cout << "From on top of the tree you  get a vantage point of the whole island. You can see the whole island cus well . . . it's quite small. Regardless, you see a couple points of interest rather than just more vegetation. Following the trail you see that it leads to a medieval structure, similar to something like a castle but not as majestic or beautiful, more run down if anything. There is also a waterfall deeper in the forest and away from the structure. It seems to be like a good place to rest up and maybe even hide if the situation needs it as the waterfall’s sound could conceal your presence. After you surveyed the island the metal noise was directly below you and you realize that it was a Goblin suited with light metal armor across his whole body. What was worse is that you can see that he has a badge indicating servitude toward the court which means people still monitor this area, but that does mean there is a mode of transportation available. " <<endl;
			cout << "CHOICES: with a decent understanding of the land, what do you do? " <<endl;
			cout << "(Enter 1) Follow the trail that the Goblin is on that leads to the medieval structure to investigate? "<<endl;
			cout << "(Enter 2) Go toward the waterfall to see if there is a place you can set up shop or at least to familiarize yourself with the land to give you the option to run to it and hide if need be." <<endl;
			cout << "(Enter 3) view stats" <<endl;
			response = 0;
                        while((response !=1) && (response !=2)){
				response = readInt();
				if(response == 1){
					return "Investigate Structure Scene";
				}else if(response ==2){
					return "Waterfall Scene";
				}else if(response == 3){
					userCharacter->stats();
					cout << "(Enter 1) Follow the trail that the Goblin is on that leads to the medieval structure to investigate? "<<endl;
                        		cout << "(Enter 2) Go toward the waterfall to see if there is a place you can set up shop or at least to familiarize yourself with the land to give you the option to run to it and hide if need be." <<endl;
                        		cout << "(Enter 3) view stats" <<endl;	
				}else{
					 cout << "CHOICES: with a decent understanding of the land, what do you do? " <<endl;
                        		cout << "(Enter 1) Follow the trail that the Goblin is on that leads to the medieval structure to investigate? "<<endl;
                        		cout << "(Enter 2) Go toward the waterfall to see if there is a place you can set up shop or at least to familiarize yourself with the land to give you the option to run to it and hide if need be." <<endl;
                        		cout << "(Enter 3) view stats" <<endl;
				}
			}									
		}else if(response == 4) {
			userCharacter->stats();
			cout << "CHOICES What do you do?"<<endl;
		        cout << "(Enter 1) Keep moving forward toward the trail and try to see where the sound is coming from? Maybe there’s actually other people on this island who could help you." <<endl;
		        cout << "(Enter 2) Hide in the bushes and stalk and follow the noise. With the amount of vegetation it should be enough to conceal your presence. "<<endl;
		        cout << "(Enter 3) Climb up a nearby tree close to the trail in order to get a better view of the situation and in hope that said noise won't notice you." << endl;
		        cout << "(Enter 4) view stats" <<endl;

		}else{
			cout << "CHOICES What do you do?"<<endl;
		        cout << "(Enter 1) Keep moving forward toward the trail and try to see where the sound is coming from? Maybe there’s actually other people on this island who could help you." <<endl;
		       	cout << "(Enter 2) Hide in the bushes and stalk and follow the noise. With the amount of vegetation it should be enough to conceal your presence. "<<endl;
		        cout << "(Enter 3) Climb up a nearby tree close to the trail in order to get a better view of the situation and in hope that said noise won't notice you." << endl;
		        cout << "(Enter 4) view stats" <<endl;
	
		}

	}
}
string investigateStructureScene(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout << "As you approach the structure, you can tell that there couldn’t be that many people that could reside in said structure as it is quite small. It seems to be more like a small outpost than a giant base of operations. Through investigation you find that there is only one main door at the front with all other normal entrances blocked off with crumbled rocks and wood. You also notice that there seems to be a helicopter at the top of the structure, but it's situated on the top of a tower inside the structure's walls. You might be able to find some way to climb the outside walls, but the tower is much too tall to be able to climb on your own." << endl;
	cout << "CHOICES "<<endl;
	cout << "(Enter 1) Go through the front door? Surely with how run down the place looks, they wouldn’t have that much security" <<endl;
	cout << "(Enter 2) Look around to see if it's possible to climb over the walls and get into the structure without having to use the front door." <<endl;
	cout << "(Enter 3) view Stats" <<endl;
	while((response !=1) && (response !=2)){
		response = readInt();
		if(response == 1){
			cout << "You were right. It was pretty much empty in the building save for some amenities and foodstuffs. It seemed like it was only really meant to accommodate one or a few people." <<endl;
			return "Boss Scene Front";
		}else if (response == 2){
			cout << "You circle around the castle to delight that part of the forest touches the top of the wall. This allowed you to be able to climb one of the trees and jump onto the wall and get inside from the backside. You believe it would have been too obvious if you had gone through the front door since you are technically a criminal so people might not be the friendliest toward you. You think highly of yourself for this task and enter a balcony opening inside the structure." <<endl;
			return "Boss Scene Back";
		}else if (response == 3){
			userCharacter->stats();
			cout << "(Enter 1) front door" <<endl;
        		cout << "(Enter 2) Look around" <<endl;
        		cout << "(Enter 3) view Stats" <<endl;	
		}else {
			cout << "Don't delay, you wont find a better time to get in" <<endl;
			cout << "(Enter 1) front door" <<endl;
                        cout << "(Enter 2) Look around" <<endl;
                        cout << "(Enter 3) view Stats" <<endl;
		}
	}
    
}


string waterfallScene(Character* userCharacter, vector<string> progress){
	int response = 0;

	cout << "As you make your way toward the waterfall you start to feel woozy, you try your best to shake it off until you get to the waterfall. Successfully making it there you take a break and sit down. Everything feels so calming, you start to hear high pitched giggles around you that pierce the sound of the crashing waterfall; however, it doesn’t startle you. You feel amazing and as you try to look in the direction of the giggles you don’t see anything and you hear the giggles from the opposite side from where you looked. As you become even more delirious you slowly more and more start to see something sparkling. Then a pixie appears before you. They tell you that as a strong individual it is your duty to take down those which are tyrannus and kill the tyrant of the island in the castle in the middle of the island." <<endl;
	cout << "CHOICES" <<endl;
	cout << "(Enter 1) Accept Quest" <<endl;
	cout << "(Enter 2) Decline Quest" <<endl;
	cout << "(Enter 3) view Stats" <<endl;
		response = readInt();
		if(response == 1){
			cout << "you start to hear joyful glees from the pixie and then another and then another. Then you start to hear them giggle again as you start to become more and more delirious. Before knocking out you hear one of them say “Good luck, our saviour” When you awake you are nowhere near the waterfall as its sound cannot be heard anymore, and you seem to not feel the ground. As you look down, you see that you are indeed flying, but as you realize this you once again hear a giggle from one pixie then she says “times up” then you start to feel gravity kick in and you feel as though you are now going to fall to your death; however, your fall is broken and it seems you landed on a balcony and looking around you see that your in something like a medieval structure similar to a castle" <<endl;
			return "Boss Scene Back";
		}else if (response == 2) {
			cout << "you start to hear gumbles from the pixie and then another and then another. Then you start to hear them giggle again as you start to become more and more delirious. Before knocking out you hear one of them say “Your loss”" <<endl;
			return "Death Route";
		}else if (response == 3) {
			cout << "as you try to look at your stats, you can't make out what they say, before you know it you knock out" <<endl;
			return "Death Route";
		}else {
			cout << "As you take too much time to decide the magic from the pixie make you even more delirious making it so you can't even utter a word anymore. You knock out with the last thing you hear is the giggles of multiple pixies" <<endl;
			return "Death Route";		
		}
}

string beach2Scene(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout << "As you continue on the beach after meeting Tane, you didn’t expect to find much, but after walking the sand for a while you overhear someone yelling “Get that exile” as well as muffled screaming with multiple hastened footsteps. You see two people chase what you can only assume is another exile into the forest, you also see a boat to which you can assume they came from here." <<endl;
	cout << "CHOICES: What do you do?" <<endl;
	cout << "(Enter 1) Steal the boat?" <<endl;
	cout << "(Enter 2) Stalk and follow the pursuers" <<endl;
	cout << "(Enter 3) view Stats" <<endl;
	while((response !=1) && (response !=2)){	
		response = readInt();
		if(response == 1){
			cout << "You hurry toward the boat while the two pursuers are distracted by the exile. As you enter the boat you hear a single high pitched beep. You look to try to start up the boat and get off this forsaken island but you can’t find a key anywhere. After searching for the key for a bit, you hear the beeping get increasingly louder and faster. At one point the beeping stops. You take a deep sigh of relief. And then you get electrified by the boat so much so you lose consciousness. When you wake up you’re next to a door on what looks like a medieval structure." <<endl;
			return "Boss Scene Front";
		}else if(response == 2){
			cout << "After stalking the pursuers for a bit you spot something shiny that they dropped, it seemed to be the key to the boat. While it’s understandable to want to help that other exile, they may not be framed like you were, so you take the key and run back to the boat quickly as the 2 pursuers are still busy. When you get on the boat you hear a single high pitched beep. After inserting the key you found on the floor the boat beeps again but in a deep tone and then turns on. You drive out of the island and look for where civilization is. The boat has enough rations and fuel if you even got slightly lost." <<endl;
			return "Secret Ending";
		}else if(response == 3){
			userCharacter->stats();
			cout << "CHOICES: What do you do?" <<endl;
		        cout << "(Enter 1) Steal the boat?" <<endl;
		        cout << "(Enter 2) Stalk and follow the pursuers" <<endl;
		        cout << "(Enter 3) view Stats" <<endl;	
		}else{
			cout << "CHOICES: What do you do?" <<endl;
		        cout << "(Enter 1) Steal the boat?" <<endl;
		        cout << "(Enter 2) Stalk and follow the pursuers" <<endl;
		        cout << "(Enter 3) view Stats" <<endl;
		}
		
		
	}




}
string bossSceneFront(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout << "As you look around in the structure you approach an isolated pedestal that contains an amulet that seemed familiar. As you walk up to and begin to inspect the amulet you realize where exactly that amulet wa-\n“Well, well, well, it seems a rat has crawled onto one of my most prized achievements'' Someone at the other end of the room spots you and starts walking toward you. “This achievement was one of the best ones I’ve had in awhile. Originally I was just following a kill order; assassinate a person in a squad while they’re on a mission, but I was also able to frame one of their party members to be the one who did it. Such offense leads to a death sentence. Killing one person, framing and killing another while leaving the whole squad in pieces. To top it off, I was able to be rewarded for capturing the ‘so-called’ culprit and got this wonderful job one this deser-” By now he was close enough to see who exactly he was talking to. “OH, well ain’t that a surprise.” He crafted a grin with his mouth “Hello there so-called-culprit rat”"<<endl;
	cout << "CHOICE"<<endl;
	cout << "(Enter 1) yell: “YOU DIRTY ASSASSIN I’LL F**KING KILL YOU”"<<endl;
	cout << "(Enter 2) yell: “B*TCH, THOSE WERE MY FRIENDS, I'LL KILL YOU”"<<endl;
	cout << "(Enter 3) view stats" <<endl;
	response = readInt();
	if((response == 1)||(response == 2) ){
		cout << "Boss: Heh, now thats more like it"<<endl;
		BossBattle(userCharacter, progress);
		//BOSS BATTLE
	}
	else if(response == 3){
		userCharacter->stats();
		cout << "While you were busy trying to checkout your well being, thinking back to your past actions or whatever you were trying to do, the boss got a free hit on you while you were distracted"<<endl;
		BossBattle(userCharacter, progress);
		//BOSS BATTLE
	}
	return "THE END";
}
string bossSceneBack(Character* userCharacter, vector<string> progress){
	int response = 0;
	cout << " Coming into the structure from a high balcony you look around to find a lavish bedroom, decorated with high quality linens and materials all around. A place, where anyone would want to stay. But you know that this means someone resides here and it’s not safe. You keep an ear out as you open the door to survey the surrounding and find closeby a pedestal containing a familiar pendant. Upon closer inspection you realize that that pendant was the pendant your deceased team member kept on them and cherished. . . There’s even a bloodstain still left on it. . . . You quickly snatch the pendant and hide within an area in the ceiling as you hear footsteps coming closer to your area. You piece together that this person walking closer is probably the person who killed your teammate and framed you for murder. Knowing this you know he or she won’t let you just waltz out of here and get to the top of the tower to the helicopter. You’re gonna have to kill him for it. With this in mind you prepare a pre-emptive strike." <<endl;
	cout << "CHOICE" <<endl;
	cout << "(Enter 1) Lay a trap for him" <<endl;
	cout << "(Enter 2) Ambush him when he enters the room" <<endl;
	cout << "(Enter 3 view Stats" <<endl;
	response = readInt();
	if(response == 1){
		cout << "The man enters the room, to immediately notice his prized achievement of a pendant gone. He looks shaken, but before he can’t even call out “who goes there” an arrow shoots from the side of the room and hits him around his waist (Boss takes a free hit) Afterwards you jump in to try to get another hit but he parries by unsheathing his sword." <<endl;
		BossBattle(userCharacter, progress);
		//BOSS BATTLE

	}else if(response ==2){
		cout << "The man enters the room and even before he lets go of the door handle you jump on him attempting to give a clean cut on his head, but he moves his hand to block the blade, taking a stab through his hand but avoiding fatality. (Boss takes a free hit) He pushes you off of him and takes out his sword." <<endl;
		BossBattle(userCharacter, progress);
		//BOSS BATTLE
	}else if (response ==3) {
		userCharacter->stats();
		cout << "you took your time look at your stats and lost the element of surprise. The boss sees you and draws his sword" <<endl;
		BossBattle(userCharacter, progress);
		//BOSS BATTLE
	}else{
		cout <<"you took your time doing who knows what (not setting up a surprise attack thats for sure), and lost the element of surprise. The boss sees you and draws his sword" <<endl;
 		BossBattle(userCharacter, progress);
		//BOSS BATTLE
	}

	
	return "THE END";
}
string deathRoute(Character* userCharacter, vector<string> progress){
	cout << "You wake up from a sudden thud that caused the ground to shake, you still hear the waterfall so you know you are close by where you fell asleep from but it seems you were dragged into a cave and is tied up. Fortunately it seems that whoever tied you up did an extremely poor job and with little effort you were able to cut your bindings off, but then you felt the ground shake again. As you turn around you hear in a deep voice from behind you “NOW WE CAN'T HAVE YOU GOING ANYWHERE NOW” you couldn’t see exactly what said that in a booming voice since the cave was dark but you back up in fear as you see a shrouded figure 2 to 3 times your size in front of you. As the figure got closer to the entrance of the cave toward the light you realize it was a Troll, but before you could react he grabbed a club and hit you with full force" <<endl;

	return "Death Route End";
}
string secretEnding(Character* userCharacter, vector<string> progress){
	cout << "you survived without fighting anyone and still managed to get off the island. Congratz" <<endl;
	return "Secret Route End";

}

void GoblinBattle(Character* player, vector<string> progress) {
	Goblin* goblinObj = new Goblin();
	double bias = player->getIQ() - goblinObj->getHealth();
	Dice20App* GobDice = new Dice20App(11, 0);
		GobDice->SetRollFunction();
	Dice20App* SpecialDice = new Dice20App(0, 1);
		SpecialDice->SetRollFunction();
	Dice20App* RunDice = new Dice20App(10, bias);
		RunDice->SetRollFunction();
	bool reaction = false;
	while((player->getHealth() > 0) && goblinObj->getHealth() > 0) {
		cout << "Battle Scene: " << player->getName() << " vs Goblin" << endl;
		cout << "Player health: " << player->getHealth() << endl;
		cout << "Goblin health: " << goblinObj->getHealth() << endl; 
		cout << "Enter one of the numbers displayed below as one of your options: " << endl;
		cout << "Enter 1 to use regular attack" << endl;
		cout << "Enter 2 to use a special attack" << endl;
		cout << "Enter 3 to use a health item" << endl;
		cout << "Enter 4 to run away" << endl;
		int userInput = -1;
		
		while ((userInput != 1) && (userInput != 2) && (userInput != 3) && (userInput != 4)) {
		userInput = readInt();
			if (userInput == 1) {
				
				GobDice->roll();
				if (GobDice->succeed()) {
					 double getDamage = player->attack();
					goblinObj->deflect_damage(getDamage, player);
					reaction = true;
				}
				else {
					 double getDamage = player->attack();
					reaction = false;			
					goblinObj->loseHealth(getDamage);
				}
			}
			else if (userInput == 2) {

				 SpecialDice->roll();
				if (SpecialDice->succeed()) {
					SpecialDice->setNumberToBeat(SpecialDice->getNumberToBeat()+3);
					GobDice->roll();
					if (GobDice->succeed()) {
						 double getDamage = player->specialAttack();

						goblinObj->deflect_damage(getDamage, player);
						reaction = true;
					}
					else {
						 double getDamage = player->specialAttack();
						reaction = false;
						goblinObj->loseHealth(getDamage);
					}
				}
				else {
					cout << "You missed your special attack" << endl;
					reaction = false;
				}
 			}
			else if (userInput == 3) {
				bool checker = player->getHealthItem();
					if (checker) {
						player->increaseHealth(2.0);
					}
					else {
						cout << "You don't have a health item." << endl;
            					cout << "Enter another option: " << endl;
						cout << "Battle Scene: " << player->getName() << " vs Goblin" << endl;
						cout << "Player health: " << player->getHealth() << endl;
						cout << "Goblin health: " << goblinObj->getHealth() << endl;
						cout << "Enter one of the numbers below as one of your options: " << endl;
						cout << "Enter 1 to use regualar attack" << endl;
						cout << "Enter 2 to use a special attack" << endl;
						cout << "Enter 3 to use a health item" << endl;
						cout << "Enter 4 to run away" << endl;
					}	
			}
			else if (userInput == 4) {
				bias = player->getIQ() - goblinObj->getHealth();	
				RunDice->setBias(bias);
				RunDice->SetRollFunction();
				RunDice->roll();
				if (RunDice->succeed()) {
					cout << "You've successfully run away from battle" << endl;
					return;
				}
				else {
					cout << "You failed to run away" << endl;
				}	
			}
			else {
				cout << "Error: Invalid input" << endl;
				cout << "Battle Scene: " << player->getName() << " vs Goblin" << endl;
				cout << "Player health: " << player->getHealth() << endl;
				cout << "Goblin health: " << goblinObj->getHealth() << endl;
				cout << "Enter one of the numbers displayed below as one of your options: " << endl;
				cout << "Enter 1 to use regualar attack" << endl;
				cout << "Enter 2 to use a special attack" << endl;
				cout << "Enter 3 to use a health item"<< endl;
				cout << "Enter 4 to run away" << endl;
			}
		}
		 if (goblinObj->getHealth() <= 0) {
             cout << "The Goblin has died" <<endl;
			 cout << "=========BATTLE OVER=========="<<endl;
             return;
         }
	
		if (!reaction) {
			GobDice->setBias(2);
			GobDice->SetRollFunction();
			GobDice->roll();
			if (GobDice->succeed()) {
				goblinObj->attack_power_indicator(player);
			}
			else {
				cout << "The Goblin missed his attack" << endl;
			}
            GobDice->setBias(0);
			GobDice->SetRollFunction();
		}
	}
	cout << "=========BATTLE OVER=========="<<endl; 
	if (player->getHealth() <= 0) {
		cout << "You Have Died"<<endl;
		cout << "GAME OVER" <<endl;
        printProgress(progress);
		exit(0);
	}
	else {
		return;
	}
}

void ExiledMemberBattle(Character* player, vector<string> progress) {
    ExiledMember* exiledObj = new ExiledMember();
    double bias = player->getIQ() - exiledObj->getHealth();
    Dice20App* exiledDice = new Dice20App(11, 0);
	exiledDice->SetRollFunction();
    Dice20App* SpecialDice = new Dice20App(0, 1);
	SpecialDice->SetRollFunction();
	SpecialDice->roll();
    Dice20App* RunDice = new Dice20App(10, bias);
	RunDice->SetRollFunction();
    while((player->getHealth() > 0) && exiledObj->getHealth() > 0) {
        cout << "Battle Scene: " << player->getName() << " vs Exiled Member" << endl;
        cout << "Player health: " << player->getHealth() << endl;
        cout << "Exiled Member: " << exiledObj->getHealth() << endl;
        cout << "Enter one of the numbers displayed below as one of your options: " << endl;
        cout << "Enter 1 to use regular attack" << endl;
        cout << "Enter 2 to use a special attack" << endl;
        cout << "Enter 3 to use a health item" << endl;
        cout << "Enter 4 to run away" << endl;
        int userInput = -1;
        
	
        while ((userInput != 1) && (userInput != 2) && (userInput != 3) && (userInput != 4)) {
            userInput = readInt();
		
	    if (userInput == 1) {
                
		double getDamage = player->attack();
		exiledObj->loseHealth(getDamage);
		
            }
            else if (userInput == 2) {
                 
		 SpecialDice->roll();
		
                 if (SpecialDice->succeed()) {
                     double getDamage = player->specialAttack();
			SpecialDice->setNumberToBeat(SpecialDice->getNumberToBeat()+3);
                     exiledObj->loseHealth(getDamage);
                 }
		else{
			cout << "You missed your attack"<<endl;
		}
             }
            else if (userInput == 3) {
                bool checker = player->getHealthItem();
                    if (checker) {
                        player->increaseHealth(2.0);
                    }
                    else {
                        cout << "You don't have a health item." << endl;
                        cout << "Enter another option: " << endl;
                        cout << "Battle Scene: " << player->getName() << " vs Exiled Member" << endl;
                        cout << "Player health: " << player->getHealth() << endl;
                        cout << "Exiled Member health: " << exiledObj->getHealth() << endl;
                        cout << "Enter one of the numbers displayed below as one of your options: " << endl;
                        cout << "Enter 1 to use regualar attack" << endl;
                        cout << "Enter 2 to use a special attack" << endl;
                        cout << "Enter 3 to use a health item" << endl;
                        cout << "Enter 4 to run away" << endl;
                    }
            }
            else if (userInput == 4) {
                bias = player->getIQ() - exiledObj->getHealth();
                RunDice->setBias(bias);
                RunDice->SetRollFunction();
		RunDice->roll();
		if (RunDice->succeed()) {
			cout << "You've successfully run away from battle" << endl;
			return;
		}
		else {
			cout << "You failed to run away" << endl;
		} 
            }
            else {
                cout << "Error: Invalid input" << endl;
                cout << "Battle Scene: " << player->getName() << " vs Exiled Member" << endl;
                cout << "Player health: " << player->getHealth() << endl;
                cout << "Exiled Member health: " << exiledObj->getHealth() << endl;
                cout << "Enter one of the numbers displayed below as one of your options: " << endl;
                cout << "Enter 1 to use regualar attack" << endl;
                cout << "Enter 2 to use a special attack" << endl;
                cout << "Enter 3 to use a health item" << endl;
                cout << "Enter 4 to run away" << endl;
            }
        }
	if (exiledObj->getHealth() <= 0) {
            cout << "The Exile has died" <<endl;
            cout << "=========BATTLE OVER=========="<<endl;
            return;
        }

	if (exiledObj->getHealth() <= 12) {
		exiledDice->roll();
		if(exiledDice->succeed()) {
			exiledObj->boost_health();
		}
		else {
			exiledDice->setBias(2);
			exiledDice->SetRollFunction();
			exiledDice->roll();
			if (exiledDice->succeed()) {
                exiledObj->special_attack(player);
            }
			else {
                cout << "The Exiled Member missed his attack" << endl;
			} 
                exiledDice->setBias(0);
		exiledDice->SetRollFunction();
        }
	}
	else {
		
            exiledDice->setBias(2);
            exiledDice->SetRollFunction();
	    exiledDice->roll();
            if (exiledDice->succeed()) {
                exiledObj->special_attack(player);
            }
            else {
                cout << "The Exiled Member missed his attack" << endl;
            }
            exiledDice->setBias(0);
	    exiledDice->SetRollFunction();
        }
    }
	cout << "===============BATTLE OVER============="<<endl;
	if (player->getHealth() <= 0) {
		cout << "You Have Died"<<endl;
        cout << "GAME OVER" <<endl;
        printProgress(progress);
		exit(0);
	}
	else {
		return;
	}
}

void BossBattle(Character* player, vector<string> progress) {
    Boss* bossObj = new Boss();
    double bias = player->getIQ() - bossObj->getHealth();
    Dice20App* bossDice = new Dice20App(11, 0);
	bossDice->SetRollFunction();
    Dice20App* SpecialDice = new Dice20App(0, 1);
	SpecialDice->SetRollFunction();
    Dice20App* RunDice = new Dice20App(10, bias);
	RunDice->SetRollFunction();
    bool reaction = false;
    while((player->getHealth() > 0) && bossObj->getHealth() > 0) {
        cout << "Battle Scene: " << player->getName() << " vs Boss" << endl;
        cout << "Player health: " << player->getHealth() << endl;
        cout << "Boss health: " << bossObj->getHealth() << endl;
        cout << "Enter one of the numbers displayed below as one of your options: " << endl;
        cout << "Enter 1 to use regular attack" << endl;
        cout << "Enter 2 to use a special attack" << endl;
        cout << "Enter 3 to use a health item" << endl;
        cout << "Enter 4 to run away" << endl;
        int userInput = -1;
        
        while ((userInput != 1) && (userInput != 2) && (userInput != 3) && (userInput != 4)) {
		userInput = readInt();
            if (userInput == 1) {

                bossDice->roll();
                if (bossDice->succeed()) {
			 double getDamage = player->attack();

                    bossObj->reflectDamage(getDamage, player);
                    reaction = true;
                }
                else {
                    reaction = false;
			 double getDamage = player->attack();

                    bossObj->loseHealth(getDamage);
                }
            }
            else if (userInput == 2) {
 
                 SpecialDice->roll();
                 if (SpecialDice->succeed()) {
                     SpecialDice->setNumberToBeat(SpecialDice->getNumberToBeat()+3);
                     bossDice->roll();
                     if (bossDice->succeed()) {
			 double getDamage = player->specialAttack();

                         bossObj->reflectDamage(getDamage, player);
                         reaction = true;
                     }
                     else {
                         double getDamage = player->specialAttack();
 			reaction = false;
                         bossObj->loseHealth(getDamage);
                     }
                 }
                 else {
                     cout << "You missed your special attack" << endl;
                     reaction = false;
                 }
             }
            else if (userInput == 3) {
                bool checker = player->getHealthItem();
                    if (checker) {
                        player->increaseHealth(2.0);
                    }
                    else {
                        cout << "You don't have a health item." << endl;
                        cout << "Enter another option: " << endl;
                        cout << "Battle Scene: " << player->getName() << " vs Boss" << endl;
                        cout << "Player health: " << player->getHealth() << endl;
                        cout << "Boss health: " << bossObj->getHealth() << endl;
                        cout << "Enter one of the numbers displayed below as one of your options: " << endl;
                        cout << "Enter 1 to use regualar attack" << endl;
                        cout << "Enter 2 to use a special attack" << endl;
                        cout << "Enter 3 to use a health item" << endl;
                        cout << "Enter 4 to run away" << endl;

                    }
            }
            else if (userInput == 4) {
                bias = player->getIQ() - bossObj->getHealth();
                RunDice->setBias(bias);
		    RunDice->SetRollFunction();
                RunDice->roll();
                if (RunDice->succeed()) {
                    cout << "You've successfully run away from battle" << endl;
                    return;
                }
                else {
                    cout << "You failed to run away" << endl;
                }
            }
            else {
                cout << "Error: Invalid input" << endl;
                cout << "Battle Scene: " << player->getName() << " vs Boss" << endl;
                cout << "Player health: " << player->getHealth() << endl;
                cout << "Boss health: " << bossObj->getHealth() << endl;
                cout << "Enter one of the numbers displayed below as one of your options: " << endl;
                cout << "Enter 1 to use regualar attack" << endl;
                cout << "Enter 2 to use a special attack" << endl;
                cout << "Enter 3 to use a health item" << endl;
                cout << "Enter 4 to run away" << endl;
            }
        }
        if (bossObj->getHealth() <= 0) {
       		 cout << "The Boss has died" <<endl;
             cout << "=========BATTLE OVER=========="<<endl;
            return;
        }

        if (!reaction) {
            bossDice->setBias(2);
		bossDice->SetRollFunction();
            bossDice->roll();
            if (bossDice->succeed()) {
                bossObj->attackDamage(player);
            }
            else {
                cout << "The Boss missed his attack" << endl;
            }
            bossDice->setBias(0);
		bossDice->SetRollFunction();
        }
    }
	cout << "=====================Battle Over======================" <<endl;
    if (player->getHealth() <= 0) {
        cout << "You Have Died"<<endl;
        cout << "GAME OVER" <<endl;
        printProgress(progress);
        exit(0);
    }
    else {
        return;
    }
}


