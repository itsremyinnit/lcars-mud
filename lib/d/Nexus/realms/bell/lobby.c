// /d/Nexus/realms/bell/lobby.c
// PLACEHOLDER: replace the long description with the real lobby.
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Lobby");
    set("long", @EndText
You stand in the lobby of a school, though the details have not quite
settled yet, like a memory waiting for a photograph. The echo of the arch
still hums behind you, to the west.
EndText
    );
    set("exits", ([
        "west" : "/d/Nexus/rooms/concourse_of_arches",
    ]));
}
