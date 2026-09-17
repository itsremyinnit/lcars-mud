// /d/Nexus/adm/quarters_d.c: registry of wizard quarters, grants, and invites.
// A removed wizard's slot becomes vacant (""), and the next promotion reuses it.
#include <mudlib.h>
inherit DAEMON;

#define SAVE_FILE "/d/Nexus/data/quarters"
#define INN       "/d/Nexus/rooms/inn"
#define VACANT    ""

string *roster;
mapping grants;
nosave mapping invites;

void create() {
    seteuid(getuid());
    roster = ({ });
    grants = ([ ]);
    restore_object(SAVE_FILE);
    if (!roster) roster = ({ });
    if (!grants) grants = ([ ]);
    invites = ([ ]);
}

void clean_up() { }  // stay loaded so invites survive

private int trusted_caller() {
    object po = previous_object();
    string f;
    if (!po) return 0;
    f = file_name(po);
    return strsrch(f, "/cmds/adm/_makewiz") == 0 ||
           strsrch(f, "/cmds/adm/_unwiz") == 0 ||
           strsrch(f, "/cmds/adm/_banish") == 0;
}

private int from_quarters(string owner) {
    object po = previous_object();
    return po && (string)po->query("owner") == owner &&
           strsrch(file_name(po), "/d/Nexus/quarters/") == 0;
}

private int slot_index(string wing, int k) {
    if (k < 1) return 0;
    if (wing == "west") return 2 * k - 1;
    if (wing == "east") return 2 * k;
    return 0;
}

int query_index(string name) {
    if (!name || name == VACANT) return 0;
    return member_array(lower_case(name), roster) + 1;
}
string query_wing(string name) { int i = query_index(name); return i ? ((i % 2) ? "west" : "east") : 0; }
int query_segment(string name) { int i = query_index(name); return i ? (i + 1) / 2 : 0; }
string segment_path(string name) { return "/d/Nexus/wings/" + query_wing(name) + "_" + query_segment(name); }
string *query_roster() { return copy(roster); }

int slot_exists(string wing, int k) {
    int i = slot_index(wing, k);
    return i && i <= sizeof(roster);
}

string owner_at(string wing, int k) {
    int i = slot_index(wing, k);
    if (!i || i > sizeof(roster) || roster[i - 1] == VACANT) return 0;
    return roster[i - 1];
}

private void refresh_slot(string wing, int k) {
    object ob;
    if (ob = find_object(INN)) ob->refresh_wings();
    if (k > 1 && (ob = find_object("/d/Nexus/wings/" + wing + "_" + (k - 1))))
        ob->setup_segment(wing, k - 1, owner_at(wing, k - 1));
    if (ob = find_object("/d/Nexus/wings/" + wing + "_" + k))
        ob->setup_segment(wing, k, owner_at(wing, k));
}

int register_wizard(string name) {
    int i;
    if (!trusted_caller() || !name) return 0;
    name = lower_case(name);
    if (member_array(name, roster) != -1) return 1;
    i = member_array(VACANT, roster);
    if (i == -1) roster += ({ name });
    else roster[i] = name;
    save_object(SAVE_FILE);
    refresh_slot(query_wing(name), query_segment(name));
    return 1;
}

int vacate(string name) {
    string wing, *keys_list;
    int k, i;
    object q, *inv;

    if (!trusted_caller() || !name) return 0;
    name = lower_case(name);
    if (!query_index(name)) return 0;
    wing = query_wing(name);
    k = query_segment(name);

    if (q = find_object("/d/Nexus/quarters/" + name)) {
        inv = all_inventory(q);
        for (i = 0; i < sizeof(inv); i++)
            if (interactive(inv[i])) {
                tell_object(inv[i], "The quarters around you fade gently away, and you find yourself on the Inn landing.\n");
                inv[i]->move_player(INN, (string)inv[i]->query("cap_name") + " steps out onto the landing.");
            }
        destruct(q);
    }

    roster[query_index(name) - 1] = VACANT;
    map_delete(grants, name);
    keys_list = keys(grants);
    for (i = 0; i < sizeof(keys_list); i++) grants[keys_list[i]] -= ({ name });
    map_delete(invites, name);
    keys_list = keys(invites);
    for (i = 0; i < sizeof(keys_list); i++) invites[keys_list[i]] -= ({ name });

    save_object(SAVE_FILE);
    refresh_slot(wing, k);
    return 1;
}

int may_enter(string owner, string who) {
    if (!owner || !who) return 0;
    owner = lower_case(owner);
    who = lower_case(who);
    if (who == owner || adminp(who)) return 1;
    if (member_array(who, grants[owner] || ({ })) != -1) return 1;
    if (member_array(who, invites[owner] || ({ })) != -1 && find_player(owner)) return 1;
    return 0;
}

int add_invite(string owner, string who) {
    if (!from_quarters(owner)) return 0;
    invites[owner] = (invites[owner] || ({ })) - ({ who }) + ({ who });
    return 1;
}

int add_grant(string owner, string who) {
    if (!from_quarters(owner)) return 0;
    grants[owner] = (grants[owner] || ({ })) - ({ who }) + ({ who });
    save_object(SAVE_FILE);
    return 1;
}

int remove_guest(string owner, string who) {
    int found;
    if (!from_quarters(owner)) return 0;
    found = member_array(who, (grants[owner] || ({ })) + (invites[owner] || ({ }))) != -1;
    if (grants[owner]) grants[owner] -= ({ who });
    if (invites[owner]) invites[owner] -= ({ who });
    save_object(SAVE_FILE);
    return found;
}

void clear_invite(string owner, string who) {
    if (from_quarters(owner) && invites[owner]) invites[owner] -= ({ who });
}

mapping query_guests(string owner) {
    return ([ "invited" : copy(invites[owner] || ({ })), "granted" : copy(grants[owner] || ({ })) ]);
}
