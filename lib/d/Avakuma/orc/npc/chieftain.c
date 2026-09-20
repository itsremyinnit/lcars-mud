// /d/Avakuma/orc/npc/chieftain.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("chieftain");
    set("short", "The orc chieftain");
    set("long", @EndText
    The orc leader. Extremely large, for an orc, and no less ugly or
foul-smelling for it. He wears light armour, and you would expect him to
have a weapon somewhere within reach.
EndText
    );
    set("id", ({ "chieftain", "orc chieftain", "orc", "leader" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 12000);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N looks you over the way a butcher looks over stock." }),
    }));
}
