#!/bin/bash

# Make sure we have 'y/n' for mkfs et al.
LANG=C

if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <core image>.tar.gz" 1>&2
	exit 1
fi
core="$1"
base=`dirname "$core"`/`basename "$core" .tar.gz`

case "$core" in
/*) ;;
*)  core="`pwd`/$core" ;;
esac

echo "*** initialising empty disk image ..."
dd if=/dev/zero of="$base.img" bs=1M count=8192
echo "y" | mkfs -t ext4 "$base.img" >/dev/null
mkdir mnt
sudo mount -o loop "$base.img" mnt

echo "*** adding contents of core tarball ..."
(cd mnt && sudo tar zxf "$core")

echo "*** adding ttyAMA0 ..."
{
	cat - <<EOM
# ttyAMA0 - getty
#
# This service maintains a getty on ttyAMA0 from the point the system is
# started until it is shut down again.
#start on stopped rc RUNLEVEL=[2345] and (
#            not-container or
#            container CONTAINER=lxc or
#            container CONTAINER=lxc-libvirt)
start on started

stop on runlevel [!2345]

respawn
exec /sbin/getty -L ttyAMA0 115200
EOM
} | sudo tee mnt/etc/init/ttyAMA0.conf >/dev/null

echo "*** adding NTP date and time synchronization ..."
{
	cat - <<EOM
#
# This task is run on startup to set the system date and time via NTP

description     "set the date and time via NTP"

start on startup

task
exec ntpdate -u ntp.ubuntu.com
EOM
} | sudo tee mnt/etc/init/ntpdate.conf >/dev/null

echo "*** adding networking for qemu ..."
{
	cat - <<EOM

auto lo
iface lo inet loopback

auto eth0
iface eth0 inet dhcp
EOM
} | sudo tee -a mnt/etc/network/interfaces >/dev/null


echo 'Acquire::CompressionTypes::Order { "gz"; "bz2"; }' | sudo tee mnt/etc/apt/apt.conf.d/99gzip >/dev/null

echo "*** fixing root password to root/root ..."
sudo sed -in -e 's@root:\*:@root:$6$pDWQLJGt$813e.4.vXznRlkCpxRtBdUZmHf6DnYg.XM58h6SGLF0Q2tCh5kTF2hCi7fm9NeaSSHeGBaUfpKQ9/wA54mcb51:@' mnt/etc/shadow

echo "*** unmounting ..."
sudo umount mnt
rmdir mnt

echo "*** done."
