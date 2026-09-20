// /d/Avakuma/framsburg/npc/meryne.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("meryne");
    set("short", "A tired mother");
    set("long", @EndText
    Meryne, keeping a handle on her children and making a little extra
money selling food and drink at the same time. Look at the menu to see
what is for sale.
EndText
    );
    set("id", ({ "meryne", "mother", "tired mother", "woman" }));
    set("gender", "female");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 6000);
    set("bulk", 250);
    enable_commands();
    set_chat(5, ({
        ({ "say", "says", "Would you like some good homemade whiskey?" }),
        ({ "say", "says", "Would you care for some stew?" }),
    }));
}
