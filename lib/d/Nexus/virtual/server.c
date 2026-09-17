// /d/Nexus/virtual/server.c: builds Inn wing segments and wizard quarters on demand.
#define QUARTERS_D "/d/Nexus/adm/quarters_d"

void create() { seteuid(getuid()); }

object compile_object(string file) {
    string wing, name;
    int k;
    object ob;

    if (!file || file == "") return 0;
    if (file[0] == '/') file = file[1..];
    if (strlen(file) > 2 && file[<2..] == ".c") file = file[0..<3];

    if (sscanf(file, "d/Nexus/wings/%s_%d", wing, k) == 2) {
        if ((wing != "west" && wing != "east") || !(name = (string)QUARTERS_D->owner_at(wing, k)))
            return 0;
        ob = new("/d/Nexus/std/wing_segment");
        ob->setup_segment(wing, k, name);
        return ob;
    }
    if (sscanf(file, "d/Nexus/quarters/%s", name) == 1) {
        if (strsrch(name, "/") != -1 || !QUARTERS_D->query_index(name)) return 0;
        ob = new("/d/Nexus/std/quarters_room");
        ob->setup_quarters(lower_case(name));
        return ob;
    }
    return 0;
}
