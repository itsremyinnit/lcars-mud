// /d/Avakuma/guild/entrance_hall.c
// North is the jail in the original, reached by the guild guard seizing
// you rather than by walking. Deferred: the north exit is deliberately
// absent until that mechanic exists. exit_order keeps its slot so the
// captured order is preserved when it returns.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The guild entrance hall");
    set("long", @EndText
PLACEHOLDER. The entrance hall of the Sheriff's Guild, watched by a
guard of the Rim-Ainacam.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/guild/hallway_1",
        "south" : "/d/Avakuma/guild/guild_bar",
        "west"  : "/d/Avakuma/guild/outside",
    ]));
    set("exit_order", ({ "north", "east", "south", "west" }));
}
