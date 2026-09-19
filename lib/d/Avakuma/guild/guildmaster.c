// /d/Avakuma/guild/guildmaster.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The Guildmaster's office");
    set("long", @EndText
PLACEHOLDER. The Guildmaster's office. A roughly-dressed sheriff is
here.
EndText
    );
    set("exits", ([
        "south" : "/d/Avakuma/guild/hallway_2",
    ]));
    set("exit_order", ({ "south" }));
}
