// /d/Avakuma/barracks/messhall.c
// The sign by the kitchen doorway carries an ASCII notice under "read".
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The barracks messhall");
    set("long", @EndText
    Long tables run the length of the messhall with plain benches drawn
up alongside them. Candles pick out the packed dirt floor and throw their
light across the mural on the west wall, beside the way back to the main
hall. An entrance to the sleeping quarters opens north. South is a doorway
with a sign next to it, and past it whatever is cooking, which smells a
good deal like burning flesh.
EndText
    );
    set("item_desc", ([
        "tables" : @EndText
    Wood, and in fair condition. Candles stand along them, giving each
man light enough to identify what is on his plate.
EndText
        ,
        "benches" : @EndText
    Wooden, and built with no thought at all for the men sitting on them.
EndText
        ,
        "floor" : @EndText
    Packed dirt, worn down hard. Too poor a floor for a dining room, and
the least attended part of a well attended building.
EndText
        ,
        "candles" : @EndText
    Most of them burned out long before you got here. One or two go on
struggling, to very little effect.
EndText
        ,
        "mural" : @EndText
    Painted across the west wall: a battlefield in the hour after the
men won it. Slain orcs lie everywhere, and a tall warrior stands in the
middle of the field with his sword raised over his head. It was put
there to remind the men what they fight for. The text along the bottom
reads: "Great men stand up for their equals and their trust in their
sword to maintain peace."
EndText
        ,
        "doorway" : @EndText
    There are two, one north and one south. Pick one to look at.
EndText
        ,
        "sign" : @EndText
    Wood, with the letters carved into it by knife.
EndText
        ,
        "smell" : @EndText
    It comes up out of the kitchen and gets into everything. Meat, and
badly handled.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/barracks/sleeping_east",
        "west"  : "/d/Avakuma/barracks/main_hall",
        "south" : "/d/Avakuma/barracks/kitchen",
    ]));
    set("exit_order", ({ "north", "west", "south" }));
}

void init() {
    add_action("do_read", "read");
}

int do_read(string str) {
    if (str != "sign") {
        notify_fail("Read what?\n");
        return 0;
    }
    write(
"\n"
"                   |-------------------------|\n"
"                   |        Kitchen,         |\n"
"                   |                         |\n"
"                   |        NO ENTRY!        |\n"
"                   |-------------------------|\n"
"\n");
    return 1;
}
