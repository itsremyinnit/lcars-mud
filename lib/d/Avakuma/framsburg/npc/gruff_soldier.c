// /d/Avakuma/framsburg/npc/gruff_soldier.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("soldier");
    set("short", "A gruff soldier");
    set("long", @EndText
    A rather gruff looking person standing about five foot eight. He has
let his eating habits get away from him and is not in the best of shape.
EndText
    );
    set("id", ({ "soldier", "gruff soldier", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 8000);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
}
