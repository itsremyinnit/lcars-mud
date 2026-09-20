// /d/Avakuma/guild/npc/dano.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("dano");
    set("short", "Dano the sheriff");
    set("long", @EndText
    Dano, former sheriff of Bucklebury. He does what he can now to keep
the streets of Framsburg safe for the citizens who remain. He is a large
hobbit and looks as though he could hold his own well enough.
EndText
    );
    set("id", ({ "dano", "sheriff", "hobbit" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 5500);
    set("bulk", 250);
    enable_commands();
    set_chat(5, ({
        ({ "say", "says", "If you want to become a shiriff, I'm sorry." }),
        ({ "say", "says", "The streets are filled with orcs. We can help you cope." }),
        ({ "emote", "$N rubs quietly near his eye." }),
        ({ "emote", "$N nurses his drink sullenly." }),
        ({ "emote", "$N subconsciously fingers his badge." }),
        ({ "emote", "$N glances toward the entrance hall nervously." }),
    }));
}
