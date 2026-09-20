#include <mudlib.h>
inherit ARMOR;
void create() {
    set("id", ({ "shield", "large shield" }));
    set("short", "a large shield");
    set("long", @EndText
    This is a large shield that covers a lot of the body. It
is made of some tough hide. It seems it would hold up rather
well in battle.
EndText
    );
    set("bulk", 90); set("mass", 700);
    set("value", ({ 46, "gold" }));
    set("type", "shield"); set("armor", 5);
}
