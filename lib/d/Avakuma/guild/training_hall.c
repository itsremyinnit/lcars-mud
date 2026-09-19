// /d/Avakuma/guild/training_hall.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The training hall");
    set("long", @EndText
PLACEHOLDER. Where the guild trains its sheriffs. Tarlyn the guild
trainer works here. Training mechanics deferred.
EndText
    );
    set("exits", ([
        "north" : "/d/Avakuma/guild/hallway_1",
    ]));
    set("exit_order", ({ "north" }));
}
