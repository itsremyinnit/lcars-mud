// /d/Nexus/rooms/far_concourse.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Far Concourse");
    set("long", @EndText
The concourse grows quieter here, as if it has not quite finished becoming.
Two arches stand to the east and west, their keystones smooth and uncarved,
and through them there is only a still, silver haze. To the north the hall
does not end so much as fade, dissolving into a bright mist where the
pillars grow faint and then are gone. The way back lies south.
EndText
    );
    set("item_desc", ([
        "arches" : "Their keystones are blank, waiting for sigils no one has carved yet.\n",
        "mist" : "Bright and soft. It looks less like an ending than a sentence not yet written.\n",
    ]));
    set("exits", ([
        "south" : "/d/Nexus/rooms/concourse_of_arches",
    ]));
    // Opens onto Ten-Forward. One-way, like the Towers Arch: you arrive
    // as a guest and the ring is the way home.
    add_arch("east", "/d/FinalFrontier/deck10/ten_forward", "the eastern arch", 0,
        "The arch does not so much open as resolve, the way a word you have been\n"
        "trying to remember resolves. Beyond it there is carpet, and low light, and\n"
        "the particular hum of something enormous being very careful. You step\n"
        "through into warmth and the smell of coffee.\n\n"
        "Behind you the arch is a bulkhead, and has always been a bulkhead.\n\n");
    add_arch("west", "/d/Nexus/rooms/far_concourse", "the western arch",
        "The arch is empty stone. Whatever it will open onto has not yet been imagined.");
    add_arch("north", "/d/Nexus/rooms/far_concourse", "the mist",
        "You walk into the mist, and it walks you gently back. The Nexus has not dreamed this far yet.");
}
