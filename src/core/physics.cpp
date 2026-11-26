#include "physics.h"
#include "util.h"

// Movement validation and resource adjustments without structures
bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol){
    for(int i=0;i<inventoryCount;i++)
    {
        if(inventory[i]==itemSymbol)
        {
            return 1;
        }
    }
    return 0;
}
bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    for(int j=0;j<MAX_INVENTORY_CAPACITY;j++)
    {
        if(inventory[j]==ENT_NONE){
            inventory[j]=itemSymbol;
            inventoryCount++;
            return 1;

        }
    }
    return 0;
}
bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    for(int i=MAX_INVENTORY_CAPACITY-1;i>0;i--)
    {
        if(inventory[i]==itemSymbol)
        {
            inventory[i]==ENT_NONE;
          for(int j=i;j<inventoryCount-1;j++)
          {
            inventory[j]==inventory[j+1];

        }
        inventoryCount--;
        inventory[inventoryCount]=ENT_NONE;
        return 1;
    }
    }
    return 0;
}

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime){
    energy+=deltaEnergy;
    time+=deltaTime;
}
void applyScoreDelta(int& score, int deltaScore){
    score+=deltaScore;
}
bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational){
                    if (connType=='D'|| connType=='W')
                    {
                        return true;
                    }
                    if (connType=='L')
                    {
                        if(hasItem(inventory,inventoryCount,ENT_MASTER_KEY))
                        {
                            return true;
                        }
                        return false;
                    }
                    if (connType=='#')
                    {
                        return false;
                    }

                 }
                 bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,
                         const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                         char& outConnType){
                            if (fromF!=toF)
                            {
                                return false;
                            }
                            int diffrence=toR-fromR;
                            if(diffrence==1 || diffrence==-1)
                            {
                                int R_connection;
                                if(toR>fromR)
                                {
                                    R_connection=fromR;
                                }
                                else
                                {
                                    R_connection=toR;
                                }
                                int F_connection=fromF-1;
                                outConnType=horizontalConn[F_connection][R_connection-1];
                                return true;
                            }
                            return false;
                         }

// Movement validation and resource adjustments without structures



