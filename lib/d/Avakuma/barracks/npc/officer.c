// /d/Avakuma/barracks/npc/officer.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("officer");
    set("short", "A burly Officer");
    set("long", @EndText
    A large, burly officer, old and genuinely tough with it. His face is
tanned and his hair has gone grey, and he is in very good shape for his
age, his arms large and firmly made, the veins standing out on them and
on his forehead. His eyes are blue with red lines spreading from the
centres. He looks angry. He looks hungover. A life spent in constant
battle has left its tracks on him.
EndText
    );
    set("id", ({ "officer", "burly officer", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 10500);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N counts another stack and writes the number down." }),
    }));
}
