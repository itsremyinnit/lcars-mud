// /d/Avakuma/framsburg/hospital.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A residential area");
    set("long", @EndText
    This house has fared better than its neighbours. The roof is whole,
without a hole in it, and it would turn rain as well as it ever did.
The walls are another matter: enough of them have come down to leave
the place open east, north and south. The men have made it their
hospital, for want of anything better.
EndText
    );
    set("item_desc", ([
        "roof" : @EndText
    In very good shape, with no hole worth the name. It does not even
creak when the wind comes up.
EndText
        ,
        "walls" : @EndText
    The southern and eastern walls have fallen. What is left of the
others stands square and shows no sign of following them.
EndText
        ,
        "rain" : @EndText
    Not falling at the moment. When it does, this is the driest room in
Framsburg.
EndText
        ,
        "ruin" : @EndText
    A house, once. It keeps the weather off the wounded, which is more
than most of the town manages.
EndText
        ,
        "hospital" : @EndText
    Not a hospital so much as the soundest roof the men could find, with
the hurt laid out beneath it.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/armoury_house",
        "north" : "/d/Avakuma/framsburg/barracks",
        "south" : "/d/Avakuma/framsburg/kitchen",
    ]));
    set("exit_order", ({ "east", "north", "south" }));

    // /std/room.c's reset() clones these up to the given count at load,
    // counting what is already present by the NPC's first "id". It runs
    // from create(), so these appear whenever the room loads.
    set("objects", ([
        "/d/Avakuma/framsburg/npc/injured_soldier" : 3,
        "/d/Avakuma/framsburg/npc/nurse"           : 1,
    ]));
}
