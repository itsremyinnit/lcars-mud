// /d/Nexus/rooms/proving_ground.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Proving Ground");
    set("long", @EndText
Sand the color of old bone covers the floor of this broad, open hall, raked
smooth and waiting. Racks of practice weapons line the walls, wooden blades
and blunted spears worn pale at the grip, and a ring of stone posts marks
out a sparring circle in the center. It smells of leather, dust, and honest
effort. Something about the place feels expectant, as if its first real
challenger has yet to arrive. The Hall of Banners lies to the west.
EndText
    );
    set("item_desc", ([
        "sand" : "Freshly raked, without a single footprint.\n",
        "racks" : "Practice weapons of every sort, all well used and well cared for.\n",
        "posts" : "A ring of stone posts marking the sparring circle. The center is empty, for now.\n",
        "circle" : "An empty sparring circle, waiting for someone worth testing.\n",
    ]));
    set("exits", ([
        "west" : "/d/Nexus/rooms/hall_of_banners",
    ]));
}
