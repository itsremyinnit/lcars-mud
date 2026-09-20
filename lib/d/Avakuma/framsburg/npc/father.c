// /d/Avakuma/framsburg/npc/father.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("father");
    set("short", "The father");
    set("long", @EndText
    A large man with a barrel chest, about six feet and all of two
hundred and twenty pounds. He looks every inch the protector of the
family.
EndText
    );
    set("id", ({ "father", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 10000);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N helps out with the whiskey, a worried look on his face." }),
    }));
}
