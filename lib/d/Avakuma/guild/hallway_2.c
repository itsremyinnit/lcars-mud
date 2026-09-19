// /d/Avakuma/guild/hallway_2.c
// The conference room east is behind a real door, closed by default.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A hallway");
    set("long", @EndText
    A hallway east of the Grand Entrance Hall. Not so grand as the
entranceway, but the ceiling is vaulted all the same and marble columns
carry it. The conference room lies east, the Guildmaster's office north,
and the supply room south.
EndText
    );
    set("item_desc", ([
        "ceiling" : @EndText
    Vaulted in the manner of the Grand Entrance Hall, though neither so
high nor so grandiose.
EndText
        ,
        "columns" : @EndText
    Tall and cylindrical, standing off to either side and holding up the
vault. Polished to a bright sheen.
EndText
        ,
        "walls" : @EndText
    Quality granite blocks set in that same ivory-speckled mortar. North
and south they carry tapestries.
EndText
        ,
        "tapestries" : @EndText
    There are tapestries on both the north and south walls. To make out
what either depicts you would have to look at the wall it hangs on.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/guild/guildmaster",
        "east"  : "/d/Avakuma/guild/conference",
        "south" : "/d/Avakuma/guild/supply_room",
        "west"  : "/d/Avakuma/guild/hallway_1",
    ]));
    set("exit_order", ({ "north", "east", "south", "west" }));
    create_door("east", "west", "A heavy door", "closed");
}
