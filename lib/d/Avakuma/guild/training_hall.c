// /d/Avakuma/guild/training_hall.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The training hall");
    set("long", @EndText
    This was the old eating hall, until the sheriffs began taking their
meals at the new bar and making the guild a little extra money by it. An
old master of the guild decided the room would serve better for study,
found that Tarlyn was the best trainer to be had, requisitioned some mats
and a desk and left him to arrange the rest. The result is plain enough:
sparring mats on the left, Tarlyn's desk on the right.
EndText
    );
    set("item_desc", ([
        "mats" : "    Simple sparring mats covering the left side of the room.\n",
        "desk" : @EndText
    A very simple desk for Tarlyn to write on. It has not even got
drawers, only a flat surface.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/guild/hallway_1",
    ]));
    set("exit_order", ({ "north" }));

    set("objects", ([
        "/d/Avakuma/guild/npc/tarlyn" : 1,
    ]));
    spawn_objects();
}
