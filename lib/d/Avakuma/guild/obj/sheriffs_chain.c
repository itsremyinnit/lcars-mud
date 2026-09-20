// /d/Avakuma/guild/obj/sheriffs_chain.c
#include <mudlib.h>
inherit ARMOR;

void create() {
    set("id", ({ "chain", "sheriff's chain", "sheriffs chain", "mail" }));
    set("short", "sheriff's chain");
    set("long", @EndText
    A shirt of fine mail, close-linked and lighter than it looks. The
Rim-Ainacam issued these to sheriffs who expected trouble, which in the
end was all of them.
EndText
    );
    set("bulk", 100);
    set("mass", 1100);
    set("value", ({ 176, "gold" }));
    set("type", "suit");
    set("armor", 7);
}
