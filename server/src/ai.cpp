#include "../include/ai.h"
#include <unistd.h>

// threads
void * gameAIfn(void * p){
	Player * player = (Player*)p;	
}

void * roomAIfn(void * v){

	while(1){
		Player * player = NULL;
		for (list <Player*>::iterator it = allPlayers.begin(); it != allPlayers.end(); ++it){
			player = *it;
			for (list<Entity*>::iterator j = player->currentPos->monsters.begin(); j != player->currentPos->monsters.end(); ++j){
				Entity * mon = *j;
				int i = attack(mon, player);
				if ( i == 0) {
//					msgAll(encodeColorInfo("#b" + player->displayName + " lands a killing blow!#w\n"), player->currentPos);
//					msgAll(encodeColorInfo("#y" + mon->gName + " drops Dead before you!#w\n"), player->currentPos);
					break;	////// MSG DOESNT WORK!!!
				}
			}
		}
		for (list <Entity*>::iterator i = respawnList.begin(); i != respawnList.end(); ++i){
			int n = ((Monster*)*i)->respawn();
			if (n==0) i = respawnList.erase(i);
		}
		sleep(2);
	}
}


// functions
inline void updateTime(void * p){
 return;
}

inline int attack(Entity * &monster, Player * p){
	Monster * mon = (Monster*)monster;
	if ( (Player*)(*(findPlayer(p, mon->enemies))) == p){
		cout << mon->life << '\n';
		if (mon->life <= 0){
			mon->die(p);
			return 0;	// monster dead
		}
		else {
			p->life -= 4;
			mon->updateStatus();
			p->actions.push(colors['R'] + mon->gName + "attacks you!\n" + colors['w']);
			return 1;
		}
	}
	return 1;
}

