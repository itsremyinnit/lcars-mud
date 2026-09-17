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
    add_arch("east", "/d/Nexus/rooms/far_concourse", "the eastern arch",
        "The arch is empty stone. Whatever it will open onto has not yet been imagined.");
    add_arch("west", "/d/Nexus/rooms/far_concourse", "the western arch",
        "The arch is empty stone. Whatever it will open onto has not yet been imagined.");
    add_arch("north", "/d/Nexus/rooms/far_concourse", "the mist",
        "You walk into the mist, and it walks you gently back. The Nexus has not dreamed this far yet.");
}
