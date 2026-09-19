// /d/Avakuma/guild/hallway_2.c
// The conference room east is behind a real door, closed by default,
// which the movement code opens and closes as you pass.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A hallway");
    set("long", @EndText
PLACEHOLDER. The eastern hallway of the guild. The Guildmaster's office
lies north, the supply room south, a conference room behind the east
door.
EndText
    );
    set("exits", ([
        "north" : "/d/Avakuma/guild/guildmaster",
        "east"  : "/d/Avakuma/guild/conference",
        "south" : "/d/Avakuma/guild/supply_room",
        "west"  : "/d/Avakuma/guild/hallway_1",
    ]));
    set("exit_order", ({ "north", "east", "south", "west" }));
    create_door("east", "west", "A heavy door", "closed");
}
