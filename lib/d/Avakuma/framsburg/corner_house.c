// /d/Avakuma/framsburg/corner_house.c
// Outdoors: ruined enough that weather prints here.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A residential district");
    set("long", @EndText
    Four stone corners are all that is left of a house that was a fine
one once. They have held up well, which is more than can be said for the
walls and the roof between them, and a good storm would likely finish
both. It is still better shelter than standing in the open.
EndText
    );
    set("item_desc", ([
        "corners" : @EndText
    Stone, and square, and all that remains of the walls that stood
between them.
EndText
        ,
        "walls" : @EndText
    Not much left. They have crumbled away a little at a time over a
great many years.
EndText
        ,
        "roof" : @EndText
    Barely the word for it. The framing is all that is left.
EndText
        ,
        "home" : @EndText
    It was one, and a good one. The corners still standing were cut by
someone who expected the house to outlast him.
EndText
        ,
    ]));
    set("exits", ([
        "east" : "/d/Avakuma/framsburg/road_south",
        "west" : "/d/Avakuma/framsburg/kitchen",
    ]));
    set("exit_order", ({ "east", "west" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/large_soldier" : 1,
        "/d/Avakuma/framsburg/npc/gruff_soldier" : 1,
    ]));
    spawn_objects();
}
