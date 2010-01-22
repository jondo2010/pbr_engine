file Debug/pbr_engine.elf
dir ../libusart
dir ../libxbee
dir ../libspi
dir ../libadc

set remoteaddresssize 32
set remote Z-packet enable
set remote hardware-breakpoint-limit 3
set remote hardware-watchpoint-limit 2

target extended-remote localhost:4242
set radix 16
