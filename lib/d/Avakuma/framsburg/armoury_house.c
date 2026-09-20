// /d/Avakuma/framsburg/armoury_house.c
// Note: "wagon" is an exit, so "look wagon" renders the wagon room's
// description rather than describing the wagon from outside.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A residential area");
    set("long", @EndText
    A house that stood proud once, and now barely holds its own roof up.
The boards in the trusses creak at the least wind, and the frame they
hang from is going. Mortar drops from between the stones a little at a
time, and the stones that have already come loose lie where they fell.
An armoury wagon stands among them.
EndText
    );
    set("item_desc", ([
        "trusses" : @EndText
    They run down from the center beam to the edge of the roof, and
every one of them is carrying more than it was built for.
EndText
        ,
        "boards" : @EndText
    Old and rotten through. Several have given up on the frame
altogether and hang from a single nail.
EndText
        ,
        "mortar" : @EndText
    A primitive sort of concrete, and it has done what it was made to
do for longer than anyone intended.
EndText
        ,
        "stones" : @EndText
    Well laid, and squared by someone who knew the work. A good number
of them are on the floor now.
EndText
        ,
        "walls" : @EndText
    Stone, and standing considerably longer than they have any right to.
EndText
        ,
        "roof" : @EndText
    Like the rest of it, there is not much left.
EndText
        ,
        "beam" : @EndText
    The ridge of the roof, running the length of the house. Everything
else hangs off it, and it has not given yet.
EndText
        ,
        "frame" : @EndText
    The beam, the trusses and the boards, holding each other up out of
long habit.
EndText
        ,
        "floor" : @EndText
    Plain dirt, with fallen stones scattered across it.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/road_north",
        "west"  : "/d/Avakuma/framsburg/hospital",
        "wagon" : "/d/Avakuma/framsburg/armoury_wagon",
    ]));
    set("exit_order", ({ "east", "west", "wagon" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/intimidating_guard" : 1,
        "/d/Avakuma/framsburg/npc/gruff_soldier" : 1,
        "/d/Avakuma/framsburg/npc/large_soldier" : 1,
    ]));
    spawn_objects();
}
