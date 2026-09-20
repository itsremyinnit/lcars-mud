// /d/Avakuma/barracks/office.c
// Three lamps, two descriptions: the hanging one over the desk, and a
// green-glass one that answers to both "desk lamp" and "table lamp".
// Bare "lamp" gives the disambiguation hint.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The barracks office");
    set("long", @EndText
    Simple paintings hang around the walls and take some of the hardness
out of the room. A large desk stands in the centre under a suspended
lamp, and everything on it has been squared to everything else by a man
who likes to know where things are. A fire burns in the corner. In the
far west corner a leather sofa faces a small table.
EndText
    );
    set("item_desc", ([
        "paintings" : @EndText
    Various, and none of them grand. They show the men and women who
organised the building of the barracks.
EndText
        ,
        "desk" : @EndText
    Wood, in fair condition, with a lamp standing on it and another
hanging above. A few papers lie there, squared to the edge.
EndText
        ,
        "lamp" : @EndText
    There are three of them: one hung above the desk, one standing on
it, and one on the small table by the sofa.
EndText
        ,
        "hanging lamp" : @EndText
    A good lamp hung from the roof over the desk, throwing its light
straight down onto the papers where it is wanted.
EndText
        ,
        "desk lamp" : @EndText
    Green glass over the shade, and handsome with it. It gives out less
light than it looks as though it should. Mostly it is here to be looked
at.
EndText
        ,
        "table lamp" : @EndText
    Green glass over the shade, and handsome with it. It gives out less
light than it looks as though it should. Mostly it is here to be looked
at.
EndText
        ,
        "fireplace" : @EndText
    Burning pleasantly, and keeping the room warm. One of several lights
in here.
EndText
        ,
        "sofa" : @EndText
    Leather, and by the look of it comfortable. A small table sits in
front of it. This is where the office puts its visitors.
EndText
        ,
        "table" : @EndText
    Clean, wooden, and orderly, with a lamp and some papers on it.
EndText
        ,
        "papers" : @EndText
    Stacked square and in order. Whoever keeps this office keeps track.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/barracks/lounge",
    ]));
    set("exit_order", ({ "north" }));

    set("objects", ([
        "/d/Avakuma/barracks/npc/officer" : 1,
    ]));
    spawn_objects();
    create_door("north", "south", "A plain door", "closed");
}
