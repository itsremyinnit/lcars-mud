// /d/Nexus/rooms/between.c: where new wizards travel on their first wearing.
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "Between");
    set("long", "There is no floor here, no sky, no here at all. Only green fire, and motion.\n");
    set("exits", ([ ]));
}
