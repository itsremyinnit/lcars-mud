// /d/Nexus/rooms/grand_concourse.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Grand Concourse");
    set("long", @EndText
The light of the Threshold settles here into stone: a hall so vast its
ceiling is lost in a soft golden haze, borne up by pillars as broad as
ancient trees. The floor is a single sweep of pale marble, worn smooth by
feet that have not yet walked it. To the west a doorway breathes a steady
green glow, and to the east the warmth of firelight and the murmur of
voices spill out into the hall. The concourse runs on to the north, and
the Threshold lies behind you to the south.
EndText
    );
    set("item_desc", ([
        "pillars" : "Each pillar is carved from a single stone, and none of them cast a shadow.\n",
        "haze" : "Golden and unhurried. Somewhere above it, you suspect, is a sky.\n",
        "marble" : "Pale, veined with faint gold, and warm underfoot.\n",
        "glow" : "A green light pulses gently beyond the western door, like a slow heartbeat.\n",
        "firelight" : "It flickers invitingly through the eastern doorway.\n",
    ]));
    set("exits", ([
        "south" : THRESHOLD,
        "north" : "/d/Nexus/rooms/commons",
        "west"  : "/d/Nexus/rooms/lamplit_hall",
        "east"  : "/d/Nexus/rooms/kindled_hearth",
    ]));
}
