// /d/Avakuma/orc/battlefield.c
// The seam between Framsburg and the orc camp, and the reason the town
// has a hospital full of wounded and a newly built barracks.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A battlefield");
    set("long", @EndText
    This stretch of the road was fought over, and not long ago. The
stones underfoot are stained a deep crimson, and there was nothing
half-hearted about whatever happened here. Pieces of weapons and armour
lie where they fell. South the road runs down toward the entrance of the
village. From the northeast come voices, and they are strange ones.
EndText
    );
    set("item_desc", ([
        "stones" : @EndText
    Stained through with what can only be blood, and a great deal of it.
EndText
        ,
        "weapons" : @EndText
    No whole weapon among them. Only pieces.
EndText
        ,
        "armour" : @EndText
    Nothing here can be called armour any longer. Worthless scraps of
metal, and some of them still buckled.
EndText
        ,
        "road" : @EndText
    Hundreds of stones, laid close and laid well. It has outlasted the
men who fought over it.
EndText
        ,
        "voices" : @EndText
    Northeast, and carrying. Not a language spoken in Framsburg.
EndText
        ,
    ]));
    set("exits", ([
        "northeast" : "/d/Avakuma/orc/filthy_road_south",
        "south"     : "/d/Avakuma/framsburg/road_north",
    ]));
    set("exit_order", ({ "northeast", "south" }));
}
