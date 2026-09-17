// /d/Nexus/rooms/threshold.c: where wizards arrive
#include "/d/Nexus/nexus.h"

inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Threshold");
    set("long", @EndText
Here the world thins to light. No wall bounds this place and no ceiling
closes it; there is only a pale, unending radiance, and a stillness older
than the stars. Your footsteps make no sound, yet you never doubt the
ground beneath you. To the north the light gathers into the shape of a
great hall, as though the Nexus itself had drawn breath to greet you.
EndText
    );
    set("item_desc", ([
        "light" : "It has no source. It simply is, the way morning is.\n",
        "radiance" : "It has no source. It simply is, the way morning is.\n",
        "hall" : "Far to the north, pillars of light settle into columns of pale stone.\n",
    ]));
    set("exits", ([
        "north" : "/d/Nexus/rooms/grand_concourse",
    ]));
}
