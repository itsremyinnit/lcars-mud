// /d/Avakuma/framsburg/npc/malcolm.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("malcolm");
    set("short", "Malcolm, the shopkeeper");
    set("long", @EndText
    A tall black-haired man, going slightly round in the middle, and well
versed in weapons. He is an expert at running a business and has learned
through many years how to deal with thieves.
EndText
    );
    set("id", ({ "malcolm", "shopkeeper", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9000);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
    set_inquiry(([
        "wagon"         : "Everything in it is for sale. Read the sign first.",
        "shop"          : "Everything in it is for sale. Read the sign first.",
        "weapons"       : "I know weapons. Tell me what you need and I will tell you what it costs.",
        "armour"        : "Primitive work, most of it. It will still keep more off you than your shirt.",
        "thieves"       : "I have dealt with a great many. It stopped being interesting years ago.",
        "framsburg"     : "It was a town. Now it is a place people are camped in.",
    ]), "Not something I trade in.");

}
