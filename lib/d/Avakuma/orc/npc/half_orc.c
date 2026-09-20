// /d/Avakuma/orc/npc/half_orc.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("half-orc");
    set("short", "An ugly half-orc");
    set("long", @EndText
    One of the foot soldiers of the orc militia. Larger than most orcs
and certainly not one of the toughest. He seems to be resting from the
battle.
EndText
    );
    set("id", ({ "orc", "half-orc", "half orc", "ugly half-orc" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9000);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N scratches at something and does not look at you." }),
    }));
}
