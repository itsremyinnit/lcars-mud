// /d/Avakuma/framsburg/kitchen.c
// A working tavern in the original: the menu prices beer, whiskey and
// stew. "read menu" carries the list; the shop itself is deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined house that has a smell of stew all about it");
    set("long", @EndText
    Someone has made this place habitable out of sheer stubbornness.
The walls and windows are as ruined as anywhere else in Framsburg, but
there are curtains up, and a rug thrown down so that nobody has to sit
in the dirt. A pot hangs over a cooking fire, and there is a menu on the
wall.
EndText
    );
    set("item_desc", ([
        "curtains" : @EndText
    Ragged strips of faded cloth. They should not make as much
difference as they do.
EndText
        ,
        "rug" : @EndText
    Five feet by eight, and worked with designs worth stooping to look
at properly.
EndText
        ,
        "pot" : @EndText
    A big iron pot, with a hearty stew going in it.
EndText
        ,
        "fire" : @EndText
    A good cooking fire, throwing out a great deal of heat.
EndText
        ,
        "menu" : @EndText
    A list of what the house serves, and what it charges. Worth reading.
EndText
        ,
        "walls" : "    Falling apart, like every other wall in this town.\n",
        "windows" : @EndText
    Only the south wall has any, the others having become windows on
their own account.
EndText
        ,
        "floor" : @EndText
    Dirt, with the rug covering as much of it as a rug that size can.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/corner_house",
        "north" : "/d/Avakuma/framsburg/hospital",
        "west"  : "/d/Avakuma/framsburg/leaders_house",
    ]));
    set("exit_order", ({ "east", "north", "west" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/father" : 1,
        "/d/Avakuma/framsburg/npc/meryne" : 1,
    ]));
    spawn_objects();
}

void init() {
    add_action("do_read", "read");
}

int do_read(string str) {
    if (str != "menu") {
        notify_fail("Read what?\n");
        return 0;
    }
    write(
"I serve the following food and drinks:\n"
"beer            2\n"
"whiskey         10\n"
"stew            13\n");
    return 1;
}
