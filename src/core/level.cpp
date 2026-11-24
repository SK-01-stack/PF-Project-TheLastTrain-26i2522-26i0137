#include "level.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;
bool getchar(char sym){
    switch(sym){
        case ENT_NONE:             
        case ENT_MASTER_KEY:      // Master Key
        case ENT_ENERGY_PACK:      // Energy Pack
        case ENT_EMERGENCY_TOOLKIT: // Emergency Toolkit
        case ENT_CLUE_4:          // Clue Digit 4
        case ENT_FUSE:              // Fuse
        case ENT_CAT:              // Stranded Cat
        case ENT_CONTROL_PANEL:     // Control Panel Terminal
        case ENT_LIFT_PASS:         // Lift Pass
        case ENT_PASSENGER:         // Stranded Passenger
        case ENT_MEDICAL_KIT:       // Medical Kit
        case ENT_EMERGENCY_CARD:    // Emergency Access Card
        case ENT_CLUE_2:            // Clue Digit 2
        case ENT_CLUE_7:            // Clue Digit 7
        case ENT_CABINET_TRAIN_KEY: // Cabinet / Train Key
        case ENT_CAT_CARRIER:       // Cat Carrier
        case ENT_OBSERVATION_TOKEN:
            return true;
        default:
            return false;
    }
}
bool installR_entity(char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], char sym, int f_indx, int r_indx, int e_indx){
    if(f_indx < 0 || f_indx >= NUM_FLOORS || r_indx < 0 || r_indx > ROOMS_PER_FLOOR || e_indx < 0 || e_indx > MAX_ENTITIES_PER_ROOM){
        return false;
    }
    
    roomEntities[f_indx][r_indx][e_indx] = sym;
    return true;

}

bool addEntity_count(int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR], int f_indx, int r_indx){
    if(f_indx < 0 || f_indx >= NUM_FLOORS || r_indx < 0 || r_indx > ROOMS_PER_FLOOR ){
        return false;
    }
    if(entityCounts[f_indx][r_indx] < MAX_ENTITIES_PER_ROOM){
    entityCounts[f_indx][r_indx]++;
    return true;
    }
    return false;

}

string Entityname(char sym){
    switch(sym){
         case ENT_MASTER_KEY:
            return "Master Key";

        case ENT_ENERGY_PACK:
            return "Energy Pack";

        case ENT_EMERGENCY_TOOLKIT:
            return "Emergency Toolkit";

        case ENT_CLUE_4:
            return "Clue Digit 4";

        case ENT_FUSE:
            return "Fuse";

        case ENT_CAT:
            return "Stranded Cat";

        case ENT_CONTROL_PANEL:
            return "Control Panel";

        case ENT_LIFT_PASS:
            return "Lift Pass";

        case ENT_PASSENGER:
            return "Injured Passenger";

        case ENT_MEDICAL_KIT:
            return "Medical Kit";

        case ENT_EMERGENCY_CARD:
            return "Emergency Access Card";

        case ENT_CLUE_2:
            return "Clue Digit 2";

        case ENT_CLUE_7:
            return "Clue Digit 7";

        case ENT_CABINET_TRAIN_KEY:
            return "Cabinet and Train Key";

        case ENT_CAT_CARRIER:
            return "Cat Carrier";

        case ENT_OBSERVATION_TOKEN:
            return "Observation Token";

        default:
            return "None";

    }


}


bool valid_room(int initial_room, int initial_floor, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
    if (initial_floor >= 1 && initial_floor <= NUM_FLOORS &&
    initial_room >= 1 && initial_room <= ROOMS_PER_FLOOR){
    int f_indx = initial_floor - 1;
    int r_indx = initial_room - 1;
        // checking both sides of room
        if ((r_indx > 0 && horizontalConn[f_indx][r_indx - 1] == CONN_NONE ||
            horizontalConn[f_indx][r_indx - 1] == CONN_SOLID_WALL ) || (r_indx < (ROOMS_PER_FLOOR - 1) && horizontalConn[f_indx][r_indx] == CONN_NONE ||
            horizontalConn[f_indx][r_indx] == CONN_SOLID_WALL)){
                return false;
            }
        
        else{
                return true;
        }

        
    }
    else{
        return false;
    }

}

bool loading(const char* f_name, int &energy, int &time , int &score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                bool objectives[NUM_OBJECTIVES], int &emergencyTripsLeft){
                if(f_name == nullptr){
                    return false;
                }
                ifstream file(f_name);
                if(!file.is_open()){
                    return false;
                }
 energy=INITIAL_ENERGY;
 time=INITIAL_TIME;
 score=INITIAL_SCORE;
 inventoryCount=0;
 emergencyTripsLeft=2;
 for (int i = 0; i < NUM_OBJECTIVES; i++)
    {
        objectives[i] = false;
    }
 string line;
    while (getline(file, line))
    {
        int sep = line.find(':');

        if (sep == -1)
        {
            continue;
        }
   string key = line.substr(0, sep);
   string value = line.substr(sep + 1);
       if (key == "INITIAL_ENERGY")
        {
            energy = atoi(value.c_str());
        }

        else if (key == "INITIAL_TIME")
        {
            time = atoi(value.c_str());
        }

        else if (key == "INITIAL_SCORE")
        {
            score = atoi(value.c_str());
        }
         else if(key=="INITIAL_INVENTORY"){
         if(value!="NONE")
         {  
             int len = 0;

             for (int i = 0; value[i] != '\0'; i++)
            {
               len++;
}
            for(int i=0;i<len&&inventoryCount<=MAX_INVENTORY_CAPACITY;i++)
            {
                char sym = value[i];
                if (getchar(sym))
            {
                inventory[inventoryCount] = sym;
                inventoryCount++;
            }
        }
    }
}
        else if (key == "PASSENGER_RESCUED")
        {
            if (value == "YES")
            {
                objectives[OBJ_PASSENGER_RESCUED] = true;
            }
        }
        else if (key == "CAT_RESCUED")
        {
            if (value == "YES")
            {
                objectives[OBJ_CAT_SECURED] = true;
            }
        }
        else if(key=="CLUES COLLECTED"){
             for (int i = 0; value[i] != '\0'; i++){
                 if(value[i]=='2'){
                 objectives[OBJ_CLUE_2 ]=true;
                }
                 else if(value[i]=='7')
                 {
                    objectives[OBJ_CLUE_7 ]=true;
                 }
                 else if(value[i]=='4'){
                   objectives[OBJ_CLUE_4 ]=true;
                 }
                
        }
    }
           else if(key=="CABINET_UNLOCKED"){
                if(value=="YES")
                {
                    objectives[OBJ_CABINET_UNLOCKED ]=true;
                }
        }
           else if(key=="TRAIN_KEY_COLLECTED")
           {
            if(value=="YES")
            {
                objectives[OBJ_TRAIN_KEY ]=true;
            }
           }
           else if(key=="FUSE_INSTALLED")
           {
            if(value=="YES")
            {
                objectives[OBJ_FUSE_INSTALLED ]=true;
            }
           }
            else if(key=="LIFT_PASS_COLLECTED")
           {
            if(value=="YES")
            {
                objectives[ OBJ_LIFT_PASS  ]=true;
            }
           }
            else if(key=="TRAIN_PREPARED")
           {
            if(value=="YES")
            {
                objectives[ OBJ_TRAIN_PREPARED]=true;
            }
           }
            else if(key=="TRAIN_PREPARED")
           {
            if(value=="YES")
            {
                objectives[ OBJ_TRAIN_PREPARED]=true;
            }
           }
           else if(key=="GAME_STATUS")
           {
            if(value=="WON")
            {
                objectives[OBJ_MISSION_WON]=true;
            }
            else if(value=="FAILED")
            {
                 objectives[OBJ_MISSION_FAILED]=true;
            }
           }
    }

    file.close();

    return true;
}

bool loadBuildingMap(
    const char* filename,
    char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
    char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
    int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){

    if (filename == nullptr)
    {
        return false;
    }

    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    for (int i = 0; i < NUM_FLOORS; i++)
    {
        for (int j = 0; j < ROOMS_PER_FLOOR - 1; j++)
        {
            horizontalConn[i][j] = CONN_NONE;
        }
    }

    for (int i = 0; i < NUM_FLOORS; i++)
    {
        for (int j = 0; j < ROOMS_PER_FLOOR; j++)
        {
            entityCounts[i][j] = 0;

            for (int k = 0; k < MAX_ENTITIES_PER_ROOM; k++)
            {
                roomEntities[i][j][k] = ENT_NONE;
            }
        }
    }
string line;
string obj_entity;
int len = 0;
int len_e = 0;

    for (int i = 0; line[i] != '\0'; i++){
        len++;
        }
    for (int i = 0; obj_entity[i] != '\0'; i++){
        len_e ++;
        }

for(int i = 0; i+4 < len ; i++){
    if(line[i] == 'F' && line[i+1] >= '1' && line[i+1] <= '5' && 
    line[i+2] == '-' && line[i+3] == 'R' && line[i+4] >= '1' && line[i+4] <= '5' ){
        int cr_floor = line[i+1] -'1';
        int cr_room = line[i+4] - '1';
        if(cr_room < ROOMS_PER_FLOOR - 1){
            int j = i+5;
            while(j < len && line[i] == ' '){
                j++;
                char sym = line[j];
                if(sym == 'D' || sym == '#' || sym == 'W' || sym == '#'){
                    horizontalConn[cr_floor][cr_room] = sym;
                }

                }
            }
        for(int k = 0; k < len_e ; k++){
            char sym = obj_entity[k];
            if((sym == ';' || sym == ')' || sym == '\\' ||
            sym == '4' || sym == '~' || sym == '*' ||
            sym == '<' || sym == '2' || sym == '!' ||
            sym == '%' || sym == '$' || sym == '(' ||
            sym == '7' || sym == '&' || sym == '@' ||
            sym == '^')){
                if(entityCounts[cr_floor][cr_room] < MAX_ENTITIES_PER_ROOM){
                    roomEntities[cr_floor][cr_room][entityCounts[cr_floor][cr_room]] = sym;
                    entityCounts[cr_floor][cr_room]++;
                }
            } 
        }
        }


    }
    file.close();

    return true;
} // ADD START PLAYER SELECT CONDITIOM