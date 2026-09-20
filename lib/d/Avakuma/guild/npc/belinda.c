// /d/Avakuma/guild/npc/belinda.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("belinda");
    set("short", "Belinda the shop mistress");
    set("long", @EndText
    An incredibly beautiful blonde edain woman, tall and slender and
curved, who looks as though she knows perfectly well how to take care of
herself. She seems pleasant and smiles often. The glint in her eye makes
you wonder whether the lovely veneer is not simply a way of suckering
her customers. She wears a tight blue dress that leaves little of her
figure to speculation.
EndText
    );
    set("id", ({ "belinda", "shop mistress", "shopkeeper", "woman" }));
    set("gender", "female");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 6000);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N smiles at you in a way that is worth being careful about." }),
    }));
    set_inquiry(([
        "goods"         : "Ask me for a list and I will show you what I have.",
        "list"          : "Ask me for a list and I will show you what I have.",
        "shop"          : "Everything a sheriff heading out might need, and a few things he only wants.",
        "weapons"       : "The finest make I can get. Have a look at the walls.",
        "armour"        : "On the walls and on the shelves. Handle anything you like.",
        "guild"         : "They keep me busy. Or they did.",
    ]), "Not my department, love.");

}
