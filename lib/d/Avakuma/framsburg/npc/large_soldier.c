// /d/Avakuma/framsburg/npc/large_soldier.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("soldier");
    set("short", "A large soldier");
    set("long", @EndText
    Slightly larger than the others, and in rather good shape, without
much around the waist. He has the start of a good build on him, and you
would not care to see what he could do with it in a few years.
EndText
    );
    set("id", ({ "soldier", "large soldier", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 8500);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "say", "says", "It seems they have strength in numbers." }),
        ({ "say", "says", "If only this battle took place when I was in my prime." }),
    }));
}
