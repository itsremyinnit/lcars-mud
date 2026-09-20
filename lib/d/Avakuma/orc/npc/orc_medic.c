// /d/Avakuma/orc/npc/orc_medic.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("medic");
    set("short", "An orc medic");
    set("long", @EndText
    A poorly trained orc medic trying to help heal his injured fellows.
He seems to be helping very little and may be actively hindering the
process. It is surprising he is not out on the battlefield. He looks as
though he could push his weight around.
EndText
    );
    set("id", ({ "medic", "orc medic", "orc" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9500);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N does something to a patient that cannot possibly help." }),
    }));
}
