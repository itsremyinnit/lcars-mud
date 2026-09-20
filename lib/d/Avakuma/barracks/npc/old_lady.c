// /d/Avakuma/barracks/npc/old_lady.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("lady");
    set("short", "An old lady");
    set("long", @EndText
    She must be past seventy, and she looks healthy on it. She has the
manner of a woman who has kept house most of her life.
EndText
    );
    set("id", ({ "lady", "old lady", "housekeeper", "woman" }));
    set("gender", "female");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 5000);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N runs a cloth over something that was already clean." }),
    }));
}
