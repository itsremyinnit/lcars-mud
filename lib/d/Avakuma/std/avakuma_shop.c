// /d/Avakuma/std/avakuma_shop.c
// Base for Avakuma's shops.
//
// NOTE: this inherits /std/shop ONLY, not AVAKUMA_ROOM. Both inherit ROOM,
// and FluffOS does not share the duplicate: the second copy tries to
// redefine ROOM's nomask property functions and the compile fails. Shop
// rooms therefore do without the Avakuma room extras (weather relay,
// set_outdoors, add_sealed, spawn_objects); spawn_here() below covers the
// only one that mattered.
//
// buy(), sell(), value() and list() are all replaced rather than
// inherited, for two reasons:
//
//   1. Stock /std/shop.c sells from storeroom + CENTSTORE, the central
//      warehouse shared by every shop on the MUD. That is why "buy axe"
//      in Belinda's shop handed over /obj/axe from Fooland. Avakuma shops
//      sell what is in their own storeroom and nothing else.
//   2. The stock messages are TMI-2's. These match T2T's.
//
// Prices are quoted in gold. Sale price is SHOP_SALES_FRAC of value.

#include <mudlib.h>
#include <money.h>
#include <move.h>

inherit "/std/shop";

// Resale is 14/25 of value, which matches T2T (a 34 gold backpack
// fetched 19). Payout is capped: the shop has a budget and says so when
// an item exceeds it, which is what stops a shop being a money printer.
#define SELL_FRAC   14
#define SELL_DIV    25
#define MAX_PAYOUT  100

void set_shopkeeper(string who) {
    set("shopkeeper", who);
}

private string keeper() {
    string who;
    who = (string)query("shopkeeper");
    return who ? who : "The shopkeeper";
}

// Clone something into this room at load, without stacking duplicates
// when the room is reloaded while copies are still standing here.
void spawn_here(string path) {
    object *inv;
    object ob;
    int i;

    inv = all_inventory(this_object());
    for (i = 0; i < sizeof(inv); i++)
        if (base_name(inv[i]) == path) return;
    ob = clone_object(path);
    if (ob) ob->move(this_object());
}

// Value of an object in gold, rounded down.
private int gold_value(object ob) {
    mixed *v;
    int copper;

    v = (mixed *)ob->query("value");
    if (!v || sizeof(v) != 2) return 0;
    copper = v[0] * coinvalue(v[1]);
    return copper / coinvalue("gold");
}

int list() {
    object *stock;
    string *shorts;
    int *prices;
    string short_desc;
    int i, j, found, price;

    stock = storeroom ? all_inventory(storeroom) : ({ });
    shorts = ({ });
    prices = ({ });

    for (i = 0; i < sizeof(stock); i++) {
        price = gold_value(stock[i]);
        if (!price) continue;
        short_desc = (string)stock[i]->query("short");
        if (!short_desc) continue;

        found = -1;
        for (j = 0; j < sizeof(shorts); j++)
            if (shorts[j] == short_desc && prices[j] == price) found = j;
        if (found != -1) continue;

        shorts += ({ short_desc });
        prices += ({ price });
    }

    if (!sizeof(shorts)) {
        write(keeper() + " tells you: I have nothing for sale just now.\n");
        return 1;
    }

    write(keeper() + " tells you: I have the following for sale:\n");
    for (i = 0; i < sizeof(shorts); i++)
        write(sprintf("  %3d - %s\n", prices[i], shorts[i]));
    return 1;
}

int buy(string str) {
    object ob, who;
    int price;

    who = this_player();
    if (!str) {
        notify_fail(keeper() + " tells you: Buy what?\n");
        return 0;
    }
    if (!storeroom) {
        notify_fail(keeper() + " tells you: I have nothing to sell.\n");
        return 0;
    }

    ob = present(str, storeroom);
    if (!ob) {
        notify_fail(keeper() + " tells you: I do not carry that.\n");
        return 0;
    }

    price = gold_value(ob);
    if ((int)who->query("wealth/gold") < price) {
        notify_fail(keeper() + " tells you: You cannot afford that.\n");
        return 0;
    }

    if (ob->move(who) != MOVE_OK) {
        notify_fail(keeper() + " tells you: You cannot carry that.\n");
        return 0;
    }

    who->debit("gold", price);
    write(keeper() + " tells you: Would you like anything else today?\n");
    say((string)who->query("cap_name") + " buys " +
        (string)ob->query("short") + ".\n", who);
    return 1;
}

int value(string str) {
    object ob;
    int price;

    if (!str) {
        notify_fail(keeper() + " tells you: Value what?\n");
        return 0;
    }
    ob = present(str, this_player());
    if (!ob) {
        notify_fail("You do not have that.\n");
        return 0;
    }
    price = gold_value(ob) * SELL_FRAC / SELL_DIV;
    if (!price) {
        write(sprintf(" %s :   %s would not give you anything for that.\n",
              (string)ob->query("short"), keeper()));
        return 1;
    }
    if (price > MAX_PAYOUT) {
        write(sprintf(" %s :   That exceeds my budget.  Worth %d gold.\n",
              (string)ob->query("short"), MAX_PAYOUT));
        return 1;
    }
    write(sprintf(" %s :   Worth %d gold.\n",
          (string)ob->query("short"), price));
    return 1;
}

int sell(string str) {
    object ob, who;
    string short_desc;
    int price;

    who = this_player();
    if (!str) {
        notify_fail(keeper() + " tells you: Sell what?\n");
        return 0;
    }
    ob = present(str, who);
    if (!ob) {
        notify_fail("You do not have that.\n");
        return 0;
    }
    if (ob->query("prevent_drop")) {
        notify_fail("You cannot part with that.\n");
        return 0;
    }

    short_desc = (string)ob->query("short");
    price = gold_value(ob) * SELL_FRAC / SELL_DIV;
    if (!price) {
        notify_fail(keeper() + " tells you: That is worth nothing to me.\n");
        return 0;
    }

    if (!storeroom || ob->move(storeroom) != MOVE_OK) {
        notify_fail(keeper() + " tells you: I have no room for that.\n");
        return 0;
    }

    if (price > MAX_PAYOUT) {
        price = MAX_PAYOUT;
        who->credit("gold", price);
        write(sprintf("%s : That exceeds my budget.  You get %d gold.\n",
              short_desc, price));
        write(keeper() +
              " tells you: Thanks for your business!  Please come again.\n");
        return 1;
    }

    who->credit("gold", price);
    write(sprintf("%s : You get %d gold.\n", short_desc, price));
    write(keeper() + " tells you: Thanks for your business!  Please come again.\n");
    return 1;
}
