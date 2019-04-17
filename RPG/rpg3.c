#include <stdio.h>
#include <stdlib.h>

typedef enum ClassEnum {
    WARRIOR,
    DRAGON,
    MAGE,
    PHD_STUDENT
}class;

char* classN[4]={"Warrior","DRAGON","MAGE","PHD_STUDENT"};

// The player Structure
typedef struct playerStructure {
 char name[1000];
 class na;
 int hp;
 int mp;
 int attack;
 int defense;
 int poi;
 struct playerStructure *next;
 int gold;
 int x, y, z;
}player;

struct playerStructure *head = NULL;
struct playerStructure *current = NULL;
struct playerStructure *prev = NULL;

void create_player(player* pp);
void pickBag(player* pp);
void insert_bag(int poi);
void use_item(int poi);
void change(int poi, player* pp);
void Print_Plater_Stats(struct playerStructure pp);
void create_NPC(player* p2);
void Print_NPC_Stats(struct playerStructure p2);
void War(player* pp, player* p2,int count);
int cool_name(char name[64]);


void pickBag(player* pp){
		printf("What set of items group would you like to have in your backpack?\n");
		printf("1.Normal(lame)(1 HP potion, 1 Mana potion, gold: 15)\n2.Invigoration Pack( 2 HP potion, gold: 20)\n3.Wizard's Pack (3 Mana potion, gold:10)\n4.Wood Elf's pack(2 Elf Bread, gold: 10)\n");
		int choice=0;
		scanf("%d", &choice);

		if(choice == 1){
			pp->gold=15;
			pp->x=1;
			pp->y=1;
			insert_bag(1);
			insert_bag(2);
			insert_bag(0);
		}
		else if(choice == 2){
			pp->gold=20;
			pp->x=2;
			insert_bag(1);
			insert_bag(1);
			insert_bag(0);
		}
		else if(choice == 3){
			pp->gold=10;
			pp->y=3;
			insert_bag(2);
			insert_bag(2);
			insert_bag(2);
			insert_bag(0);
		}
		else if(choice == 4){
			pp->gold=10;
			pp->z=3;
			insert_bag(3);
			insert_bag(3);
			insert_bag(3);
			insert_bag(0);
		}
};
void show_bag(player* pp){
    struct playerStructure *bag = head;
    printf("Your Inventory: |");
    while(bag != NULL){
        printf(" %d |", bag->poi);
        bag = bag->next;
    };
    printf("Your Gold: %d\n", pp->gold);
};



int main()
{
	struct playerStructure pp;
	struct playerStructure p2;
	int worth1, worth2;
	printf("Welcome to the Land of Mordor weary traveller!\nPlayer 1, how do you want your name to be: ");
	scanf("%s", pp.name);

	create_player(&pp);
	pickBag(&pp);

	worth1 = cool_name(pp.name);

	printf("Welcome to the Land of Mordor!\nPlayer 2, how do you want your name to be: ");
	scanf("%s", p2.name);

	create_player(&p2);
	pickBag(&p2);

	worth2=cool_name(p2.name);

	Print_Plater_Stats(pp);

	Print_Plater_Stats(p2);
	int count=0;

	if(worth1>worth2)
	{
		printf("%s is the cooler name than the other! You commence first\n", pp.name);
	War(&pp, &p2,count);
}
else
{
	printf("%s is the cooler name than the other! you start first\n", p2.name);
	War(&p2, &pp,count);
}
}

void insert_bag(int poi){
    struct playerStructure *bag = (struct playerStructure*) malloc(sizeof(struct playerStructure));

    bag->poi = poi;

    bag->next = head;

    head = bag;
};

void change(int poi, player* pp){

    if (poi == 1){
        use_item(1);

    	}
    	else if (poi== 2){
    	    use_item(2);

    	}
        else if (poi== 3){
            use_item(3);

    	}
};

void use_item(int poi){
    poi = 0;
    player* pp = malloc(sizeof(player));

   if(head==NULL) {
      printf("Your bag seems to be drained empty\n");
      return;
   }

   if(head->poi == poi) {
      if(head->next != NULL) {
         head = head->next;
      } else {
         head = NULL;
         printf("Bag is seemingly empty now\n");
      }
   } else if(head->poi != poi && head->next == NULL) {
      printf("Item has not been found in your backpack\n");
   }

   current = head;

   while(current->next != NULL && current->poi != poi) {
      prev = current;
      current = current->next;
   }

   if(current->poi == poi) {
      prev->next = prev->next->next;
      pp->hp+=20;
      free(current);
   } else{
      printf("The item has not been found in the list.\n");
   }
   free(pp);
}

void War(player* pp, player* p2, int count){

	int choice=0;
	printf("==================\n");
	printf("%s Health point: %d\n", pp->name, pp->hp);
	printf("%s Mana point:   %d\n", pp->name, pp->mp);
	printf("==================\n");

	printf("\n                                                 =====================\n");
	printf("						  %s Health point: %d\n", p2->name, p2->hp);
	printf("						  %s Mana point:   %d\n", p2->name, p2->mp);
	printf("                                                  =====================\n");

	if (pp->hp <= 0){
		printf("You have no health left! Your have fallen to the depths of Mount Doom! War is lost!\n");
		exit(0);
	}
	else if(p2->hp <=0){
		printf("You Won! You single handedly took down the other player! You have been named the new hero of Middle-Earth!!\n");
		exit(0);
	};

	if(count%3==0)
	{
		int store=0;
		printf("Would you like to buy an HP potion for 10 gold? Press 1 for yes 2 for no: \n");
		scanf("%d", &store);
		if (store==1 && pp->gold >=10){
			pp->x+=1;
			pp->gold-=10;
			insert_bag(1);
		}
		else if (store==1 && pp->gold < 10){
			printf("You are poor Sir or Madam! You shall not afford it..\n");
		}
		else if (store==1 && pp->x >= 10){
			printf("\n");
		}
		else {
			printf("As you wish Master!\n");
		}
}

	printf("What is your current move %s\n", pp->name);
	printf("  1.Slash\n  2.Spells of Doom\n  3.Items\n  4.Quit\n");
	scanf("%d", &choice);

	if (choice == 1){
		printf("You chose to slash the enemy, relying on your super epic strength.\n");
		p2->hp-=(pp->attack - p2->defense);
	}
	else if (choice == 2){

		if (pp->mp < 5){
			printf("You don't have enough Mana to even cast one spell.\n  Please use your super strong hands to slash?: ");
			scanf("%d", &choice);
			War(pp, p2,count);
		}
		else{

			printf("Which spell would you like to cast?\n");
			printf("  1.Heart of Demon (+5 dmg, -5 Mana)\n  2.Shatterer of Earth (+10 dmg, -15 Mana)\n  3.LifeDrainer (Drains opponent's health to yours, +10 HP, -25 Mana)\n");
			int spell=0;
			scanf("%d", &spell);

			if (spell == 1 && pp->mp >=5){
				printf("You cast a firey ball of Hell towards your foe, you make it go down to Hell where it came from!\n");
				p2->hp-=(pp->attack+5 - p2->defense);
				pp->mp-=5;
			}
			else if(spell == 2 && pp->mp >=15){
				printf("You throw a big chunk of earth to your enemy, that has got to hurt!\n");
				p2->hp-=(pp->attack+15 - p2->defense);
				pp->mp-=15;
			}
			else if(spell == 3 && pp->mp >=25){
				printf("You use the Force and drain your foe's health to heal yourself\n");
				p2->hp-=10;
				pp->hp+=10;
				pp->mp-=25;
			}
		}
	}
	else if (choice == 3){

	    if (head->next != NULL || head != NULL){
    	    printf("What item would you like to use?\n");
    	    printf("  1.Health Potion(+20 HP)\n  2.Mana Potion(+20 MP)\n  3.Wood Elf's Bread(+10 HP, +10 MP)\n");
    	    int potion=0;
    	    scanf("%d", &potion);
    	    if (potion == 1){
    	    	if (pp->x <=0){
    	    		printf("You don't have enough in your inventory to use in the heat of battle!\n");
				}
				else{
    	        use_item(1);
				pp->hp+=20;
				pp->x-=1;
			}

    	    }
    	    else if (potion == 2){
    	    	if (pp->y <=0){
    	    		printf("You don't have enough in your inventory to use in the heat of battle!\n");
				}
				else{
    	        use_item(2);
    	        pp->mp+=20;
    	        pp->y-=1;
    	    }
    	    }
    	    else if (potion == 3){
    	    	if (pp->z <=0){
    	    		printf("You don't have enough in your inventory to use in the heat of battle!\n");
				}
				else{
    	        use_item(3);
    	        pp->hp+=10;
				pp->mp+=10;
				pp->z-=1;
			}
    	    }

        show_bag(pp);
    	}
    	else {
    	    printf("You don't have any items in your backpack!\n");
    	}
	}

	else if (choice == 4){

	    printf("You have forfeited, hence lost the battle to the enemy, it's all over!\n");
	    exit(0);
	}
	count = count + 1;
		if(count%3==0)
	{
		int store=0;
		printf("Would you like to buy an HP potion for 10 gold? Press 1 for yes 2 for no: \n");
		scanf("%d", &store);
		if (store==1 && p2->gold >=10){
			p2->x+=1;
			p2->gold-=10;
			insert_bag(1);
		}
		else if (store==1 && p2->gold < 10){
			printf("You are poor Sir or Madam! You shall not afford it..\n");
		}
		else if (store==1 && p2->x >= 10){
			printf("That's enough right there! You drain my stock!\n");
		}
		else {
			printf("As you wish!\n");
		}
}
	printf("  1.Slash\n  2.Spells\n  3.Items\n  4.Quit\n");
	printf("What is your current move %s\n", p2->name);
	int cho;
	scanf("%d", &cho);

	if (cho == 1){
		printf("You chose to slash the enemy, relying on your super epic strength.\n");
		pp->hp-=(p2->attack - pp->defense);
	}
	else if (cho == 2){

		if (p2->mp < 5){
			printf("You don't have enough Mana to even cast one spell.\n  Please use your strong hands to slash?: ");
			scanf("%d", &choice);
			War(pp, p2,count);
		}
		else{

			printf("Which spell would you like to cast?\n");
			printf("  1.Heart of Demon (+5 dmg, -5 Mana)\n  2.Shatterer of Earth (+10 dmg, -15 Mana)\n  3.LifeDrainer (Drains your opponent's health to yours, +10 HP, -25 Mana)\n");
			int spell=0;
			scanf("%d", &spell);

			if (spell == 1 && p2->mp >=5){
				printf("You cast a firey ball of Hell towards your foe, you make it go down to Hell where it came from!\n");
				pp->hp-=(p2->attack+5 - pp->defense);
				p2->mp-=5;
			}
			else if(spell == 2 && p2->mp >=15){
				printf("You throw a big chunk of earth to your enemy, that has got to hurt!\n");
				pp->hp-=(p2->attack+15 - pp->defense);
				p2->mp-=15;
			}
			else if(spell == 3 && p2->mp >=25){
				printf("You use the Force and drain your foe's health to heal yourself\n");
				pp->hp-=10;
				p2->hp+=10;
				p2->mp-=25;
			}
		}
	}
	else if (cho == 3){

	    if (head->next != NULL || head != NULL){
    	    printf("What item would you like to use?\n");
    	    printf("  1.Health Potion(+20 HP)\n  2.Mana Potion(+20 MP)\n  3.Wood Elf's Bread(+10 HP, +10 MP)\n");
    	    int potion=0;
    	    scanf("%d", &potion);
    	    if (potion == 1){
    	    	if (p2->x <=0){
    	    		printf("You don't have enough in your inventory to use in the heat of battle!\n");
				}
				else{
    	        use_item(1);
				p2->hp+=20;
				p2->x-=1;
			}

    	    }
    	    else if (potion == 2){
    	    	if (p2->y <=0){
    	    		printf("You don't have enough in your inventory to use in the heat of battle!\n");
				}
				else{
    	        use_item(2);
    	        p2->mp+=20;
    	        p2->y-=1;
    	    }
    	    }
    	    else if (potion == 3){
    	    	if (p2->z <=0){
    	    		printf("You don't have enough in your inventory to use in the heat of battle!\n");
				}
				else{
    	        use_item(3);
    	        p2->hp+=10;
				p2->mp+=10;
				p2->z-=1;
			}
    	    }

        show_bag(p2);
    	    War(pp, p2,count);
    	}
	}

	else if (cho == 4){

	    printf("You have forfeited, hence lost the battle to the enemy, it's all over!\n");
	    exit(0);
	}
	count = count + 1;
	War(pp, p2,count);

};


void Print_Plater_Stats(struct playerStructure pp){
	printf("-----------------------\n");
	printf(" Name: %s \n Class: %s \n", pp.name, classN[pp.na]);
	printf("  Health: %d\n", pp.hp);
	printf("  Mana:   %d\n", pp.mp);
	printf("	Attack:  %d\n", pp.attack);
	printf("	Defense: %d\n", pp.defense);
}

void create_player(player* pp){
	int choice=0;
	printf("\nNow choose your class of choice traveller of Minas Tirith!\n");
	printf("  1.Warrior\n  2.Dragon\n  3.Mage\n  4.PHD_STUDENT\n");
	scanf("%d", &choice);

	if (choice == 1){
		printf("You have opted to be the Warrior! Worthy of being folklore legend! But little to no magical ability!\n");
		pp->hp=50;
		pp->mp=0;
		pp->attack=25;
		pp->defense=10;
		pp->na=0;
	}
	else if(choice == 3){
	    printf("You've chosen to be the Mage, strong in the sense of magic but not physically.\n");
		pp->hp=25;
		pp->mp=50;
		pp->attack=10;
		pp->defense=3;
		pp->na=2;
	}
	else if(choice == 2){
	    printf("You've chosen to be the mighty Dragon! A host of Magic and Strength, perfectly balanced as all things should be..\n");
		pp->hp=30;
		pp->mp=35;
		pp->attack=15;
		pp->defense=5;
		pp->na=1;
	}
	else if(choice == 4){
	    printf("You've chosen to be the PHD_STUDENT, relying on Magic and intelligence than Strength\n");
		pp->hp=30;
		pp->mp=45;
		pp->attack=15;
		pp->defense=5;
		pp->na=3;
	}
	else {
	    exit(0);
	}

}



void Print_NPC_Stats(struct playerStructure p2){
	printf("			-----------------------\n");
	printf("			Enemy's Stats: \n");
	printf("		    Class: %s \n", classN[p2.na]);
	printf("			Health: %d\n", p2.hp);
	printf("			Mana:   %d\n", p2.mp);
	printf("			Attack:  %d\n", p2.attack);
	printf("			Defense: %d\n", p2.defense);
	printf("			-----------------------\n");
}
int cool_name(char name[64]){
    int val=0;
    int i,j;
    char alpha[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(j=0; name[j] != '\0'; j++)
    {
     for (i=0;i<26;i++)
	 {
        if (name[j]==alpha[i])
		{
            val = val + i+1;
        }
    }
}
    printf("The Magic hat decides that your name is worth: %d\n", val);
    return val;
};

void store(player* cc){
    if (cc->gold <= 10){
        printf("You don't have enough gold to purchase anything from the merchandise\n");
    }
    else{
        printf("Welcome! Welcome to the store weary traveller! What would you like to purchase?\n  Press 1 for Health potion(-10 gold)\n  2 for Mana Potion(-15 gold)\n 3 to exit\n");
        int sto = 0;
        scanf("%d", &sto);
        if (sto == 1 && cc->gold >= 10){
            cc->gold-=10;
            insert_bag(1);
        }
        else if (sto == 2 && cc->gold >= 15){
            cc->gold-=10;
            insert_bag(2);
        }
    }
}
