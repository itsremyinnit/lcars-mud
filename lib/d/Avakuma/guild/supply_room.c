// /d/Avakuma/guild/supply_room.c
// The chest and the badges are takeable objects in the original, not
// scenery. Described here; the objects themselves are deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The Guild's supply room");
    set("long", @EndText
    The Guild's supply room. It held weapons of every kind once, but the
sheriffs carry their own gear now, and all that is left in here are the
badges of the fallen of the Rim-Ainacam. There is a large chest against
the wall.
EndText
    );
    set("item_desc", ([
        "chest" : @EndText
    An old wooden chest with "Sheriff's Club" painted across the top.
EndText
        ,
        "badges" : @EndText
    Scattered in a sad pile near the chest. This is where they came to
rest after being taken off the bodies of sheriffs killed defending
Framsburg.
EndText
        ,
        "weapons" : @EndText
    All taken. The sheriffs carried them out to make a last stand
against the forces of Sauron.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/guild/hallway_2",
    ]));
    set("exit_order", ({ "north" }));

    set("objects", ([
        "/d/Avakuma/guild/npc/eomon" : 1,
        "/d/Avakuma/guild/npc/trainee" : 1,
    ]));
    spawn_objects();
}
