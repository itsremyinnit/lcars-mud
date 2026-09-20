// /d/Avakuma/guild/npc/tarlyn.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("tarlyn");
    set("short", "Tarlyn, the guild trainer");
    set("long", @EndText
    Tarlyn, member trainer of the Rim-Ainacam. He has been with the guild
many years, until a raid some years ago left his leg injured and gave him
the limp. Up to then he was by far the best sheriff the guild had ever
had. Now the limp keeps him from running criminals down, so he trains the
members instead, and they could not possibly have a better teacher.

    Type 'cost' to see what he can train you in, and 'train' to be
trained.
EndText
    );
    set("id", ({ "tarlyn", "trainer", "guild trainer", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9000);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N shifts his weight off his bad leg without noticing he did." }),
    }));
}
