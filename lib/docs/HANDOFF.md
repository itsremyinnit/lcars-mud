# Nexus-96: Shattered Sector — Project Handoff

A living orientation doc for anyone (human or AI) picking up this project. It is the **map and the traps**, not a code dump. Read the actual repo files for detail.

---

## 1. What this is

A private, self-hosted MUD recreating the feel of **The Two Towers** (t2tmud.org), the LPMUD that Jeremy and his friend **Jarrod** played years ago. It runs the **TMI-2 mudlib** on the modern **FluffOS** driver. It's a **shared sandbox** for the two of them to build in and goof off together, reached through a themed hub called the **Nexus** (branded "Nexus-96: Shattered Sector"). One of the first worlds they'll build together is a walkthrough of their old high school.

Admin character: **Trelane**. GitHub: **itsremyinnit/lcars-mud** (private).

---

## 2. Infrastructure map

**The VM (`LCARS-MUD`)** — Ubuntu Server, hostname `lcars-mud`, `192.168.4.33` (static DHCP reservation, `lcars.local` A/PTR records). Runs on Hyper-V host **LCARS-SRV** (`192.168.4.41`).

- Isolated by Hyper-V ACLs: can reach the internet and LCARS-SRV/router, but **not** the rest of the LAN. IPv6 disabled.
- SSH only from LCARS-SRV (key-only). To connect: from LCARS-SRV PowerShell, `ssh lcars_admin@lcars-mud.lcars.local`.

**Ports (public via Eero forward + ufw `limit`):**
- `5555` — plain telnet, **local only** (blocked at the firewall from outside; used for testing from LCARS-SRV)
- `5556` — telnet + TLS (Mudlet: host `mud.mettech.org`, port 5556, "secure")
- `5557` — TLS websocket, the **browser web client** at `https://mud.mettech.org:5557/`

**Service accounts on the VM:**
- `mud` — owns and runs the driver (systemd service `lcars-mud`). Sandboxed (noexec, ProtectSystem, etc.). **All lib files should be owned by `mud`; create/edit them with `sudo -u mud`.**
- `mudgit` — holds a single-repo GitHub **deploy key**; runs the 10-minute Git auto-sync. In the `mud` group.
- `mudbackup` — forced-command SSH key; LCARS-SRV pulls the nightly data archive through it.
- `mudcert` — forced-command SSH key; LCARS-SRV pushes renewed TLS certs through it.

**LCARS-SRV side (Windows, scheduled tasks as Administrator):**
- `LCARS-MUD-Backup-Pull` (1:30 AM) — pulls the VM's nightly data archive into `D:\Backup\LCARS-MUD`, which Rclone mirrors to OneDrive at 2:00 AM.
- `LCARS-MUD-Cert-Renew` (3:00 AM) — Posh-ACME renews the Let's Encrypt cert (GoDaddy DNS validation, credentials reused from the existing `GoDaddyDDNS.ps1`) and deploys it to the VM.
- `LCARS-GoDaddy-DDNS` — keeps `vpn.mettech.org` (and via CNAME, `mud.mettech.org`) pointed at home.

**On the VM:**
- Driver binary: `/opt/mud/bin/driver` (root-owned, `mud`-group, mode 750)
- Mudlib: **git work tree is `/opt/mud`** (NOT `/opt/mud/lib`); the lib itself lives at `/opt/mud/lib`. The git database is a **bare repo** at `/var/lib/mudgit/lcars-mud.git`, reachable only as the `mudgit` user. There is no `.git` dir inside `/opt/mud`, so `git rev-parse` from inside the tree returns nothing. Always drive git with the explicit form:
  `sudo -u mudgit git --git-dir=/var/lib/mudgit/lcars-mud.git --work-tree=/opt/mud <cmd>`
- Config: `/opt/mud/etc/config.tmi2` (root-owned; the running MUD can read, not write)
- TLS certs: `/opt/mud/etc/tls/` (locked down; only `mud` can read the key, via ACL)
- FluffOS source (for rebuilds): `~/src/fluffos` under `lcars_admin`
- Build recipe: `~/src/fluffos-build-notes.txt`
- Weekly maintenance restart: Sundays 4:00 AM Pacific (systemd timer) — this is how renewed certs get loaded.

---

## 3. How to work on it

- **Two shells:** PowerShell on LCARS-SRV (Windows/Hyper-V/backup/cert tasks) and a bash SSH session on the VM. Always check the prompt before pasting; mixing them up is the #1 time-waster.
- **Run as `mud` for lib files:** `sudo -u mud tee/sed/perl/python3 ...`. Files created as `lcars_admin` end up unreadable/unwritable in the wrong ways. Wildcards like `*.c` expand as `lcars_admin` **before** sudo runs, and `lcars_admin` can't read into `/opt/mud/lib`, so name files explicitly or run the whole command under `sudo`.
- **Editing LPC:** change the file on disk, then `update /path/to/file` **in-game** (as Trelane) to recompile it live. Warnings are fine; `error:` is not. Errors get written to `/u/t/trelane/log` too.
- **Git auto-sync:** a systemd timer commits in-game `ed` edits and pushes every 10 minutes. The repo uses the split git-dir/work-tree layout described in section 2: bare repo at `/var/lib/mudgit/lcars-mud.git`, work tree `/opt/mud`, run as `mudgit`. To push a change with a real message immediately: `(cd / && sudo -u mudgit git --git-dir=/var/lib/mudgit/lcars-mud.git --work-tree=/opt/mud add <paths> && ... commit -m "..." && ... push origin main)`. Never run bare `git` from inside `/opt/mud` expecting it to find a `.git`; there isn't one.
- **Private repo caveat:** a fresh chat/session CANNOT read the GitHub repo (it's private, no connector). Keep `HANDOFF.md` in the claude.ai Project's knowledge, and hand a new session a **tarball of the relevant lib subtree** (code + config, never `.o` saves or logs) rather than a repo URL.
- **Restart vs update:** most changes load with `update`. Things read only at boot need a service restart: **the master's groups/access files, the config file, and the preload list.** A restart saves players cleanly.
- **Player saves survive restarts.** Runtime data (`.o` files, logs) is **not** in Git — it's covered by the nightly backup. Only code and config are tracked.
- **Colors:** the mudlib uses `%^COLOR%^` codes (valid names in `/adm/daemons/terminal.c`), translated per-client on output to a **logged-in player**. Pre-login text (the welcome screen) has no player to translate, so it must use **raw ANSI escapes** instead.

---

## 4. FluffOS-vs-1990s-mudlib gotchas (the expensive ones)

These are modern-driver incompatibilities that cost real time to find. If something old-mudlib breaks, check here first.

- **`static` is gone.** Modern FluffOS always has `SENSIBLE_MODIFIERS`. Old `static` on a variable → `nosave`; on a function → `protected`. But watch the combos: `private static` → just `private` (not `private protected`, which is illegal); `static` across a line break before the function name is easy to miss.
- **`export_uid()` is a no-op if the target already has an euid.** With `AUTO_SETEUID`, freshly-cloned objects get an euid immediately, so `export_uid` silently fails. Fix: have the object call `seteuid(0)` on itself first (see `connection.c`'s `logon()` / `clear_euid()` pattern) before `export_uid`. This bit us in finger, makewiz, and unwiz for offline players.
- **Variable declarations must be at the top of a function**, not partway through a nested block. Declaring mid-block throws confusing `Left argument of -> is not a class` errors.
- **`RNAME` etc. are macros**, not properties. `RNAME` expands to `query("real_name")`, so `link->RNAME` works but only as a bare top-level expression; don't wrap it in a larger expression or cast it.
- **Virtual objects:** TMI-2's `virtual_d` routing was written for paths **without** a leading slash; FluffOS passes them **with** one. Strip a leading `/` before the `sscanf` route-matching or every virtual room silently fails to load.
- **`external_start` / FFI are security risks.** FFI is denied via `master::valid_ffi()` (returns 0). The `external` package was compiled **out** entirely (`-DPACKAGE_EXTERNAL=OFF`). The service also runs with a noexec sandbox allowing only the driver's own shared libs.
- **`PACKAGE_PCRE=OFF`** — the old PCRE1 lib is gone from Ubuntu; TMI-2 doesn't need it.
- **The prompt is NOT set via the driver.** `set_prompt()` is a stub in this build. The driver draws the prompt by calling the interactive's **`write_prompt()`** (because `HAS_WRITE_PROMPT` is flagged). Our live prompt works by having `write_prompt()` in `/std/user/tsh.c` call `update_prompt()` in `/std/user.c`, which reads the template from the **`myprompt`** env var (not `prompt` — the driver's own `prompt` is kept empty so it never double-draws), substitutes `$hp/$HP/$sp/$SP/$me`, and sends via `message("prompt", ...)`. `set prompt` is intercepted in `/cmds/std/_set.c` to write `myprompt`.
- **`%^RESET%^` gets appended** to some env vars by `_set.c`; strip it when reading them back.
- **`ed`/editor temp files:** players can't write arbitrary paths. Use a writable temp path (e.g. `/tmp/...`), not a bare filename. `unique_name()` is not a global efun here.
- **A domain needs a `d_master.c`** (at `/d/<Domain>/adm/d_master.c`, inheriting `/adm/obj/master/d_master`) for its own objects to write in its data dir. The base grants the domain's own uid write access to `data/` and read to all. **Do not** add a `[Domain]` entry to `/adm/etc/groups` unless that domain master exists first, or the groups parse fails and **the master shuts the MUD down at boot.**

---

## 5. What's built (the Nexus)

All under `/d/Nexus/`. Wizards arrive at the **Threshold** on login; players still start in the TMI-2 quad.

- **Rooms:** a north-south spine (Threshold → Grand Concourse → Commons → Crafthall → Hall of Banners → Concourse of Arches → Far Concourse) with side rooms off it (Lamplit Hall, Kindled Hearth + Inn above, Hall of Records, Rookery, Workshop, Artificer's Stall, Proving Ground). Shared base: `/d/Nexus/std/nexus_room.c`.
- **Arches:** ring-gated exits. Only a wizard wearing their own **Calenmîr** may pass. The **Bell Arch** (east from the Concourse of Arches) leads to a placeholder **Lobby** — this is where the **high school** will be built. Other arches are sealed ("not yet").
- **Calenmîr, the focus ring** (`/d/Nexus/obj/calenmir.c`): bound to its bearer (can't drop/give/steal/put), keyed with a per-owner rune, has a voice (`ask ring about ...`). **Does not autoload** — the login re-forge is the single source (autoload caused rings to stack). Wearing it enables wizard commands; without it, "your will scatters."
- **Willpower gate:** in `cmd_hook` (`/std/user.c`), wizard-folder commands require the worn ring. Admins exempt.
- **Ring ceremony** (`/d/Nexus/adm/ceremony_d.c`): on `makewiz`, the ring appears; first wearing carries the wizard through "the Between" (paced narration) to the Threshold. Plays at next login if promoted offline.
- **Quarters:** virtual Inn wings + private rooms per wizard (`/d/Nexus/adm/quarters_d.c` + `/d/Nexus/virtual/server.c`). Slots go **vacant** on removal and are reused, so nobody's door moves. `invite`/`grant`/`revoke`/`guests` manage access.
- **Promotion/demotion/banishment:** `makewiz`, `unwiz` (demote; ring departs; quarters vacated), `banish [days] <name>` (parks the character 90 days by default; login refused; finger shows it; name reserved; archived on expiry via `/d/Nexus/adm/banish_d.c`; ASCII "phantom zone" broadcast), `unbanish`. Stock permanent name-ban is now `banishname`.
- **Legend system** (`/d/Nexus/adm/legend_d.c`): T2T-style `finger`/`legend` card with tiers (player/wizard/admin see progressively more), settable `TITLE` (wizards need `$N`; players get "Name the <race>") and `INFO`, life **stories** (`story` to write, `story <name>` to read, 200-line cap), and `register` in the Rookery to set a mail home. Offline lookups use a saved snapshot.
- **Live prompt:** default `HP:$hp EP:$sp>`; players `set prompt <template>` with `$hp $HP $sp $SP $me`. (See the prompt gotcha above.)
- **Welcome screen** (`/adm/news/welcome`): raw-ANSI "Nexus-96: Shattered Sector" fractured triptych (Seattle / alien world / fantasy keep).

**Test characters:** `testwiz`, `testguy` exist for testing promotion/quarters/etc. Clean them up once Jarrod is onboarded and the flows are proven.

---

## 6. In flight / next up

1. **Room exits, T2T-style (two formats, keyed to brief/verbose mode)** — in `/cmds/std/_look.c`, add a `roomexits` player setting.
   - **Brief mode:** exits appended to the room name line, abbreviated, in parens, **no space before the paren**: `The main street(n, e, s and w)`.
   - **Verbose mode:** exits flow into the description as a full sentence, spelled out: `The only obvious exits are north, east, south and west.` (Current stock code already does a sentence form but tab-indented and worded slightly differently; match the T2T wording.)
   - So it is NOT parens-vs-sentence; it is brief-gets-parens, verbose-gets-sentence. Jeremy confirmed this against a live T2T session. The exact switch block in `_look.c` is known.
2. **The Lobby description** — the placeholder room beyond the Bell Arch, to be replaced with the real high school lobby once Jeremy has photos.
3. **Bring Jarrod in as co-wizard/builder** — `mailreg jarrod` to register his name, deliver a starter password separately, and a short "how to connect" note (Mudlet on 5556, or the web client on 5557). Then `makewiz jarrod` for the full ring ceremony, and add `jarrod` to the Nexus `builders` group so he can build alongside Jeremy.
4. **Optional later:** working shop/inn systems, the Proving Ground training construct, the recharge ceremony for the ring (original oath, not the GL/One-Ring text), IPv6, the FTP-vs-Git decision revisited.

---

## 7. Checkpoints & safety

Hyper-V checkpoints mark milestones (`Phase1-Baseline` … `Legend-Complete`, etc.). Everything is committed to GitHub, backed up nightly to OneDrive, and runs as a self-restarting service. It is always safe to stop.

**Morning health check** (VM): `systemctl is-active lcars-mud lcars-mud-sync.timer lcars-mud-backup.timer`. (LCARS-SRV): confirm the backup-pull and cert-renew tasks last ran with result 0.
