// /d/Avakuma/guild/obj/sheriffs_breastplate.c
#include <mudlib.h>
inherit ARMOR;

void create() {
    set("id", ({ "breastplate", "sheriff's breastplate", "sheriffs breastplate", "plate" }));
    set("short", "a sheriff's breastplate");
    set("long", @EndText
    This piece of finely-crafted armour is enameled white and has the
black symbol of a guild painted across the chest. The symbol is of a 
shield with a long sword going diagonally downward from left to right.
In the top right-hand corner is a balance, and in the lower left-hand 
corner is the executioner's hood. The breastplate does look a little
battered around the edges, though.
EndText
    );
    set("bulk", 140);
    set("mass", 2200);
    set("value", ({ 260, "gold" }));
    set("type", "suit");
    set("armor", 10);
}
