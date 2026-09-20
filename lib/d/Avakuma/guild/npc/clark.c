// /d/Avakuma/guild/npc/clark.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("clark");
    set("short", "A roughly-dressed sheriff");
    set("long", @EndText
    This weathered-looking elf has the appearance of an old and
experienced officer. His shrewd eyes move over a great many reports and
you are certain they miss nothing. He is plainly tackling something very
dire. You have no doubt this former sheriff always got his man, but the
lines on his face say there is a deep worry in him now.
EndText
    );
    set("id", ({ "clark", "sheriff", "roughly-dressed sheriff", "elf" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9000);
    set("bulk", 250);
    enable_commands();
    set_chat(6, ({
        ({ "say", "says", "I KNOW there's got to be a way..." }),
        ({ "say", "says", "Get out of my way. Can't you see I'm trying to save a town here?" }),
        ({ "emote", "$N sneers at you." }),
        ({ "emote", "$N ponders something." }),
        ({ "emote", "$N prods a pile with his quill, as if thinking idly." }),
        ({ "emote", "$N leans over and examines some battle reports." }),
        ({ "emote", "$N tilts his head as if listening." }),
    }));
}
