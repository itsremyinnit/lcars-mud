// /d/Avakuma/guild/npc/trainee.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("sheriff");
    set("short", "A sheriff in training");
    set("long", @EndText
    A young sheriff trying to improve his skills. Watching him, you form
the opinion that he has a long way to go before he can work safely on his
own.
EndText
    );
    set("id", ({ "sheriff", "sheriff in training", "trainee", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 7500);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N runs the same form again, and gets it wrong again." }),
    }));
}
