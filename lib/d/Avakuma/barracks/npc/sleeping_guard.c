// /d/Avakuma/barracks/npc/sleeping_guard.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("guard");
    set("short", "A sleeping guard");
    set("long", @EndText
    Off duty, and sleeping heavily. He has been working hard and is
catching up on it, and takes no notice of you at all. He is large. You
would be better off letting him sleep.
EndText
    );
    set("id", ({ "guard", "sleeping guard", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9500);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N shifts in his sleep and mutters something." }),
    }));
}
