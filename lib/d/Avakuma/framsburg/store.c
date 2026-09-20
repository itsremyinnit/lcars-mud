// /d/Avakuma/framsburg/store.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined store");
    set("long", @EndText
    A store of some kind, once. Shelves line the walls, most of them
broken and hanging off their brackets, and an old counter stands in very
poor repair. The roof has come through better than most in Framsburg,
with only small holes in it. Whatever stock there was went with the
people who left. What is left is the dust on the floor.
EndText
    );
    set("item_desc", ([
        "shelves" : @EndText
    Most are broken, and a good number hang by one end from the wall.
EndText
        ,
        "counter" : @EndText
    In really bad shape. Somebody stood behind this and sold things,
which is difficult to picture now.
EndText
        ,
        "roof" : @EndText
    Rather well preserved, all things considered. Only minor holes in it.
EndText
        ,
        "dust" : @EndText
    Thick on the floor, and undisturbed. Nobody comes in here.
EndText
        ,
        "floor" : "    Under the dust, floorboards. Above it, more dust.\n",
    ]));
    set("exits", ([
        "west" : "/d/Avakuma/framsburg/road_south",
    ]));
    set("exit_order", ({ "west" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/intimidating_guard" : 1,
    ]));
    spawn_objects();
}
