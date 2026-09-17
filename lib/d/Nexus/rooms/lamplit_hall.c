// /d/Nexus/rooms/lamplit_hall.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Lamplit Hall");
    set("long", @EndText
A round hall of dark stone rises here into shadow, and at its heart stands
the Wellspring Lamp: a great lantern of green crystal set upon a pedestal
of carved rock, burning with a light that seems less to shine than to
listen. Its glow moves slowly across the walls, where rings of names are
cut into the stone, circling upward past the reach of sight. Here rings
are given, and here, in time, they will be kindled anew. The Grand
Concourse lies to the east.
EndText
    );
    set("item_desc", ([
        "lamp" : "The Wellspring Lamp. Its green flame does not flicker, and standing near it, you feel steadier, as if the Lamp were quietly lending you its patience.\n",
        "wellspring lamp" : "The Wellspring Lamp. Its green flame does not flicker, and standing near it, you feel steadier, as if the Lamp were quietly lending you its patience.\n",
        "pedestal" : "Rough rock below, polished smooth where countless hands have rested.\n",
        "names" : "Most of the rings of names are blank. A few near the base have begun to fill.\n",
    ]));
    set("exits", ([
        "east" : "/d/Nexus/rooms/grand_concourse",
    ]));
}
