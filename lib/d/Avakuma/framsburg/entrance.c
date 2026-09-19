// /d/Avakuma/framsburg/entrance.c
// East and west lead out of Framsburg and are deliberately omitted.
// South is sealed as a future expansion. The Anduin and the ford (the
// bracketed water exits in the original) are described but not modelled.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "Entrance to Framsburg");
    set("long", @EndText
    Before you lie the ruins of Framsburg, a town of men long before the
war with Sauron. It is a gloomy place and it is coming apart. The road at
your feet is barely visible through the dying grass, and the buildings
that line it are in shambles. The ford lies south, and the Great River
Anduin runs away southwest and southeast.
EndText
    );
    set("item_desc", ([
        "ruins" : @EndText
    A whole town of them. Men lived here for a long time, and then they
did not.
EndText
        ,
        "road" : @EndText
    Barely a road at all now, and losing what is left of itself to the
grass.
EndText
        ,
        "grass" : @EndText
    Dying back, and still winning against the road.
EndText
        ,
        "buildings" : @EndText
    In shambles, every one. From here the whole town can be taken in at
a glance, which is not a kindness to it.
EndText
        ,
        "ford" : @EndText
    South of here, where the river runs shallow enough to cross. It is
the reason a town stood in this place.
EndText
        ,
        "river" : @EndText
    The Great River Anduin, running away southwest and southeast.
EndText
        ,
        "anduin" : @EndText
    The Great River Anduin, running away southwest and southeast.
EndText
        ,
        "water" : @EndText
    The Anduin, to the southwest and southeast, and the ford to the
south.
EndText
        ,
        "post" : @EndText
    A hitching post, still standing. Somebody keeps horses, or did.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/framsburg/road_south",
    ]));
    set("exit_order", ({ "north", "south" }));
    add_sealed("south",
        "The road runs on south to the ford, but not yet.\n");
}
