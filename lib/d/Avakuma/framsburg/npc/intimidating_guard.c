// /d/Avakuma/framsburg/npc/intimidating_guard.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("guard");
    set("short", "An intimidating guard");
    set("long", @EndText
    A large, broad-shouldered man. He was sent here to use what he knows
about fighting to keep other people alive.
EndText
    );
    set("id", ({ "guard", "intimidating guard", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9000);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
    set_range(70, ({
        "/d/Avakuma/framsburg/road_north",
        "/d/Avakuma/framsburg/road_south",
        "/d/Avakuma/framsburg/armoury_house",
        "/d/Avakuma/framsburg/store",
        "/d/Avakuma/framsburg/entrance",
    }));

}
