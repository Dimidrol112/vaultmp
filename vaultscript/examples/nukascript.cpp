#include "../vaultscript.h"
#include <map>
#include <cstdio>

using namespace std;
using namespace vaultmp;

Base nuka = (Base) 0x0001519E;
Value area[] = {-12630.32, -15715.93, -12728.72, -15834.46};
map<ID, State> player_nuka;

Result VAULTSCRIPT NukaArea()
{
	for (pair<const ID, State>& player : player_nuka)
	{
		if (!player.second && GetActorSneaking(player.first))
		{
			Value X, Y, Z;
			GetPos(player.first, X, Y, Z);

			if (X < area[0] && X > area[2] && Y < area[1] && Y > area[3])
			{
				UIMessage(player.first, "You found a hidden nuka cola!");
				AddItem(player.first, nuka, 1, 100.0, False);
				player.second = True;
			}
		}
	}

    return (Result) 0;
}

Void VAULTSCRIPT exec()
{
	if (GetGameCode() != Index::FALLOUT3)
	{
		printf("NukaScript is for Fallout 3 only!\n");
		terminate();
	}

	CreateTimer(&NukaArea, (Interval) 500);

	printf("NukaScript for Fallout 3 loaded\n");
}

Void VAULTSCRIPT OnPlayerDisconnect(ID player, Reason reason)
{
	player_nuka.erase(player);
}

Void VAULTSCRIPT OnSpawn(ID object)
{
	if (IsPlayer(object))
	{
		player_nuka.erase(object);
		player_nuka.insert(pair<ID, State>(object, False));
	}
}