// /d/Avakuma/orc/npc/injured_orc.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("orc");
    set("short", "An injured orc");
    set("long", @EndText
    This one was injured in the battle. It is surprising that the orcs
would bother to try and heal him at all. He is barely conscious and looks
to be in a good deal of pain.
EndText
    );
    set("id", ({ "orc", "injured orc" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 8000);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "say", "groans", "Nnnh." }),
        ({ "emote", "$N stirs, and stops when it hurts." }),
    }));
}
