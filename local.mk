GAMEDIR = /opt/nethack/chroot/notnotdnethack-2025.05.16
CFLAGS = -g3 -O0 -Wno-format-overflow
CPPFLAGS = -DWIZARD=\"build\" -DCOMPRESS=\"/bin/gzip\" -DCOMPRESS_EXTENSION=\".gz\"
CPPFLAGS += -DHACKDIR=\"/notnotdnethack-2025.05.16\" -DDUMPMSGS=100
CPPFLAGS += -DDUMP_FN=\"/dgldir/userdata/%N/%n/notnotdnethack/dumplog/%t.nndnh.txt\"
CPPFLAGS += -DHUPLIST_FN=\"/dgldir/userdata/%N/%n/notnotdnethack/hanguplist.txt\"
CPPFLAGS += -DEXTRAINFO_FN=\"/dgldir/extrainfo-nndnh/%n.extrainfo\"
