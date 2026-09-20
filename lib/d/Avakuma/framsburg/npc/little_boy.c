// /d/Avakuma/framsburg/npc/little_boy.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("boy");
    set("short", "A little boy");
    set("long", @EndText
    A hyper little kid, constantly running and climbing on things. He
gives his parents their full share of headaches.
EndText
    );
    set("id", ({ "boy", "little boy", "kid", "child" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 3000);
    set("bulk", 250);
    enable_commands();
    set_chat(6, ({
        ({ "emote", "$N climbs onto something he should not be on." }),
        ({ "emote", "$N tears past you without slowing down." }),
    }));
    set_range(45, ({
        "/d/Avakuma/framsburg/road_north",
        "/d/Avakuma/framsburg/road_south",
        "/d/Avakuma/framsburg/armoury_house",
        "/d/Avakuma/framsburg/hospital",
        "/d/Avakuma/framsburg/kitchen",
        "/d/Avakuma/framsburg/corner_house",
    }));

}
