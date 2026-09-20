// /d/Avakuma/framsburg/npc/leader.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("leader");
    set("short", "The men's leader");
    set("long", @EndText
    A noble looking man, tall and well built, with a bearing that leaves
no doubt why these people chose him to lead them.
EndText
    );
    set("id", ({ "leader", "mens leader", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9500);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
}
