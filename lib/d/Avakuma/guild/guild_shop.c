// /d/Avakuma/guild/guild_shop.c
// Plain room for now. Shop mechanics deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The guild shop");
    set("long", @EndText
PLACEHOLDER. The guild's shop. Belinda the shop mistress keeps it.
Not yet a working shop.
EndText
    );
    set("exits", ([
        "south" : "/d/Avakuma/guild/hallway_1",
    ]));
    set("exit_order", ({ "south" }));
}
