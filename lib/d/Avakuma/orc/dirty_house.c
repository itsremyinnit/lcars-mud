// /d/Avakuma/orc/dirty_house.c
// The orc counterpart to Framsburg's hospital: injured orcs and a medic.
// walls/roof/smell were not implemented in the original; written fresh.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A dirty house");
    set("long", @EndText
    This house is in better repair than the others. The walls are very
nearly gone, but the roof over them is sound. For reasons not worth
dwelling on, the smell in here is worse than anywhere else in the camp,
which would not have seemed possible before you walked in.
EndText
    );
    set("item_desc", ([
        "walls" : @EndText
    Nearly gone, and holding up a roof anyway out of what looks like
spite.
EndText
        ,
        "roof" : @EndText
    Sound, and the reason the wounded were put under it.
EndText
        ,
        "smell" : @EndText
    Worse than the rest of the camp, and the rest of the camp set a
considerable standard.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/orc/end_of_road",
        "west"  : "/d/Avakuma/orc/dirty_room",
        "south" : "/d/Avakuma/orc/filthy_road_north",
    ]));
    set("exit_order", ({ "east", "west", "south" }));
}
