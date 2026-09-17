// /d/Nexus/adm/quarters_d.c: registry of wizard quarters, grants, and invites.
#include <mudlib.h>
inherit DAEMON;

#define SAVE_FILE "/d/Nexus/data/quarters"
#define INN       "/d/Nexus/rooms/inn"

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

int clean_up() { return 0; }  // keep invites in memory

private int trusted_caller() {
    object po = previous_object();
    if (this_player() && adminp(this_player())) return 1;
    if (po && strsrch(file_name(po), "/cmds/adm/_makewiz") == 0) return 1;
    return 0;
}

private int from_quarters(string owner) {
    object po = previous_object();
    return po && (string)po->query("owner") == owner &&
           strsrch(file_name(po), "/d/Nexus/quarters/") == 0;
}

int query_index(string name) { return name ? member_array(lower_case(name), roster) + 1 : 0; }
string query_wing(string name) { int i = query_index(name); return i ? ((i % 2) ? "west" : "east") : 0; }
int query_segment(string name) { int i = query_index(name); return i ? (i + 1) / 2 : 0; }
string segment_path(string name) { return "/d/Nexus/wings/" + query_wing(name) + "_" + query_segment(name); }
string *query_roster() { return copy(roster); }

string owner_at(string wing, int k) {
    int i;
    if (k < 1) return 0;
    if (wing == "west") i = 2 * k - 1;
    else if (wing == "east") i = 2 * k;
    else return 0;
    return (i <= sizeof(roster)) ? roster[i - 1] : 0;
}

private void refresh_rooms(string name) {
    object ob;
    string wing = query_wing(name);
    int k = query_segment(name);
    if (k == 1) {
        if (ob = find_object(INN)) ob->refresh_wings();
    } else if (ob = find_object("/d/Nexus/wings/" + wing + "_" + (k - 1))) {
        ob->setup_segment(wing, k - 1, owner_at(wing, k - 1));
    }
}

int register_wizard(string name) {
    if (!trusted_caller() || !name) return 0;
    name = lower_case(name);
    if (member_array(name, roster) != -1) return 1;
    roster += ({ name });
    save_object(SAVE_FILE);
    refresh_rooms(name);
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
