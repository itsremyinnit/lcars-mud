// /d/Avakuma/framsburg/npc/little_girl.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("girl");
    set("short", "A cute little girl");
    set("long", @EndText
    Is this not the cutest little girl you have ever seen? Strawberry
blonde hair, about six years old, rosy cheeks and hands filthy to the
wrist. What a tomboy.
EndText
    );
    set("id", ({ "girl", "cute little girl", "kid", "child" }));
    set("gender", "female");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 2800);
    set("bulk", 250);
    enable_commands();
    set_chat(6, ({
        ({ "emote", "$N wipes her hands on her dress, making it worse." }),
        ({ "emote", "$N watches you with frank curiosity." }),
    }));
    set_range(50, ({
        "/d/Avakuma/framsburg/road_north",
        "/d/Avakuma/framsburg/road_south",
        "/d/Avakuma/framsburg/corner_house",
        "/d/Avakuma/framsburg/entrance",
        "/d/Avakuma/framsburg/store",
        "/d/Avakuma/orc/battlefield",
    }));

}
