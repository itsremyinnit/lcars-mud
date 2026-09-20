// /d/Avakuma/framsburg/npc/injured_soldier.c
// Three of these stand in the hospital and share one chat set, which the
// original did too: identical NPCs draw from a common pool.
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("soldier");
    set("short", "An injured soldier");
    set("long", @EndText
    One of the valiant men who helped push the orcs back. A lucky blow
during the battle put him here.
EndText
    );
    set("id", ({ "soldier", "injured soldier", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 7000);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "say", "murmurs", "I can't believe I was injured by that Orc." }),
        ({ "say", "yells",   "Ouch! That hurt!" }),
    }));
}
