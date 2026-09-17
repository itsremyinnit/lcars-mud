// /d/Nexus/rooms/concourse_of_arches.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Concourse of Arches");
    set("long", @EndText
Here the hall opens wide, and on either side stands a great arch of grey
stone, each framing not a room but a glimpse of somewhere else. The eastern
arch bears a bell carved in its keystone, and from beyond it drifts the far
echo of voices in a crowded corridor. The western arch is crowned by two
slender towers, and a cold wind sighs through it, smelling of old campaigns.
The concourse runs on to the north and back to the south.
EndText
    );
    set("item_desc", ([
        "bell arch" : "A bell is carved in the keystone, its clapper caught mid-swing.\n",
        "towers arch" : "Two slender towers stand carved side by side above the arch.\n",
        "keystone" : "Each arch has one, and each keystone bears its own sigil.\n",
    ]));
    set("exits", ([
        "south" : "/d/Nexus/rooms/hall_of_banners",
        "north" : "/d/Nexus/rooms/far_concourse",
    ]));
    add_arch("east", "/d/Nexus/realms/bell/landing", "the Bell Arch",
        "Somewhere beyond the arch a bell rings, far and faint, and the way does not open. Not yet.");
    add_arch("west", "/d/Nexus/realms/towers/landing", "the Two Towers Arch",
        "The cold wind rises to meet you, and for a moment you glimpse two towers against\n" +
        "a darkening sky. Then the arch is only stone again. Not yet.");
}
