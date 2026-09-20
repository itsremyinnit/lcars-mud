// /d/Avakuma/guild/npc/eomon.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("eomon");
    set("short", "Eomon");
    set("long", @EndText
    Eomon was the Sheriff of Edoras. He spends his days now keeping the
streets of Framsburg safe for its citizens, or for the few of them left.
He is a large, burly man who looks as though he could put fear into the
heart of many an orc.
EndText
    );
    set("id", ({ "eomon", "sheriff", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 10500);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
}
