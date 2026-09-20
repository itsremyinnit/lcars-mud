// /d/Avakuma/guild/obj/sheriffs_chain.c
#include <mudlib.h>
inherit ARMOR;

void create() {
    set("id", ({ "chain", "sheriff's chain", "sheriffs chain", "mail" }));
    set("short", "sheriff's chain");
    set("long", @EndText
    This is a shirt of white chain mail armour. Emblazoned on
the chest of the mail is the crest of the Rim-Ainacam. The
emblem features a large black shield with a white longsword
lying across it with black highlights. The hilt is in the 
bottom left corner and its tip in the top right. On the left 
side above the sword scales of balance have been added using 
a metallic silver color. The right side has a dark blue 
gauntlet just below the sword's tip.
EndText
    );
    set("bulk", 100);
    set("mass", 1100);
    set("value", ({ 176, "gold" }));
    set("type", "suit");
    set("armor", 7);
}
