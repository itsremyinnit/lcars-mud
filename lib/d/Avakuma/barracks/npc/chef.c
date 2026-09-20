// /d/Avakuma/barracks/npc/chef.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("chef");
    set("short", "An angry chef");
    set("long", @EndText
    A heavy, overweight chef in white, sweat running off his face, and he
smells like an orc. His trousers are covered in animal blood. His arms are
large and dark with hair and he looks very strong and close to a
heart attack. His forehead is wrinkled and his eyebrows have grown
together.
EndText
    );
    set("id", ({ "chef", "angry chef", "cook", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 11000);
    set("bulk", 250);
    enable_commands();
    set_chat(5, ({
        ({ "emote", "$N brings the cleaver down harder than the vegetables warrant." }),
        ({ "say", "snarls", "Out. Out of my kitchen." }),
    }));
}
