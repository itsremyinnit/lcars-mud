// /d/Avakuma/guild/guild_bar.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The Guild's Bar");
    set("long", @EndText
PLACEHOLDER. The guild's own bar, and a working one, unlike the ruin
above. Dano the sheriff drinks here. Dalin the stoor tends it.
EndText
    );
    set("exits", ([
        "north" : "/d/Avakuma/guild/entrance_hall",
    ]));
    set("exit_order", ({ "north" }));
}
