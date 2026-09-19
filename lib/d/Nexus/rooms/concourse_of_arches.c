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
    add_arch("east", "/d/Nexus/realms/bell/lobby", "the Bell Arch");
    // Opens onto Framsburg, in the Avakuma domain. One-way by design: the
    // pub has no arch on its side, and the ring's recall is the way back.
    add_arch("west", "/d/Avakuma/framsburg/pub", "the Two Towers Arch", 0,
        "The cold wind rises to meet you, and the stone under the two carved towers\n" +
        "turns to ink. It does not reflect you. You step into it and it closes over\n" +
        "your head like water, thick and lightless and utterly silent, and for a\n" +
        "long moment there is nothing at all.\n\n" +
        "Then air. Cold, and smelling of wet ash and old rain.\n\n");
}
