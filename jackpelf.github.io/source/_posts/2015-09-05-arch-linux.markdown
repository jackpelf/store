---  
layout: post  
title: "arch-linux"  
date: 2015-09-05 12:37:07 +0800  
comments: true  
categories:   
---  
  
###0x00  openvpn  
vim vars    

	export KEY_COUNTRY="US"  
	export KEY_PROVINCE="CA"  
	export KEY_CITY="SanFrancisco"  
	export KEY_ORG="Fort-Funston"  
	export KEY_EMAIL="me@myhost.mydomain"  
	export KEY_EMAIL=mail@host.domain  
	export KEY_CN=changeme  
	export KEY_NAME=changeme  
	export KEY_OU=changeme  
	export PKCS11_MODULE_PATH=changeme  
	export PKCS11_PIN=1234  

./vars  
./clean-all  
./build-ca    
./build-key-server server  
./build-key client1  
./build-dh  
cp ca.crt /etc/openvpn/  
cp server.crt /etc/openvpn/  
cp dh1024.pem /etc/openvpn/  
cp server.key /etc/openvpn/  
vi /etc/openvpn/server.conf   

	port 1194  
	proto udp  
	dev tun  
	ca ca.crt  
	cert server.crt  
	key server.key  # This file should be kept secret  
	dh dh1024.pem  
	server 10.8.0.0 255.255.255.0  
	ifconfig-pool-persist ipp.txt  
	client-config-dir ccd  
	route 10.1.0.0 255.255.0.0  
	push "redirect-gateway def1"  
	keepalive 10 120  
	# Select a cryptographic cipher.  
	# This config item must be copied to  
	# the client config file as well.  
	;cipher BF-CBC        # Blowfish (default)  
	;cipher AES-128-CBC   # AES  
	;cipher DES-EDE3-CBC  # Triple-DES  
	comp-lzo  
	user nobody  
	group nobody  
	persist-key  
	persist-tun  
	status openvpn-status.log  
	verb 3  
	mute 20  
  
vi /etc/openvpn/server.conf   
	http://www.vpngate.net/cn/  
openvpn /etc/openvpn/server.conf  
openvpn /etc/openvpn/client.conf  
  
###0x01 octpress  
  
bundle command not found  
export PATH=$PATH:/root/.gem/ruby/2.2.0/bin  
gem sources --remove https://rubygems.org/  
gem sources -a https://ruby.taobao.org/  
gem install jekyll-gist    
bundle update celluloid  
bundle install  
  
###0x02 gdb  
pacman -S gdb  
git clone https://github.com/longld/peda.git ~/peda  
echo "source ~/peda/peda.py" >> ~/.gdbinit  
  
###0x03 qira  
cd ~/  
git clone https://github.com/BinaryAnalysisPlatform/qira.git  
cd qira/  
./install.sh  
  
###0x04 vim  
git clone git://github.com/altercation/solarized.git  
.vimrc  

	syntax enable  
	syntax on  
	set nu  
	set background=dark  
	colorscheme solarized  
  
###0x05 bash  
vi /etc/bash.bashrc  
  
	# ~/.bashrc  
	#  
	# If not running interactively, don't do anything  
	[[ $- != *i* ]] && return  

	alias ls='ls --color=auto'  
	alias ll='ls -al'  
	alias m='sudo mentohust'  
	alias vi='sudo vim'  
	alias x='startxfce4'  
	alias s='sudo shutdown -h 0'  


	#PS1='[\u@\h \W]\$ '  
	PS1='${arch_chroot:+($arch_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$'  

	export LANG=en_US.UTF-8  
	#force_color_prompt=yes  

	set bell-style none  
	setterm -blength 0  
	xset -b  
  
  
  
###0x06 pwntools  
pip install pwntools  
  
###0x07 arch32  
fdisk /dev/sda  
mkfs.ext4 /dev/sda1  
mount /dev/sda1 /mnt   
vi /etc/pacman.d/mirrorlist  
pacman -Syy  
pacstrap -i /mnt base  
生成分区表  
genfstab -U -p /mnt >> /mnt/etc/fstab   
arch-chroot /mnt /bin/bash  
vi /etc/locale.gen  
locale-gen  
echo LANG=en_US.UTF-8 > /etc/locale.conf  
ln -s /usr/share/zoneinfo/Asia/Shanghai /etc/localtime  
echo 主机名 > /etc/hostname   
passwd  
pacman -S grub    
grub-install --target=i386-pc --recheck /dev/sda  
grub-mkconfig -o /boot/grub/grub.cfg  
exit  
reboot  
ip link  
ip link set enp0s3 up  
dhcpcd enp0s3  
systemctl enable dhcpcd@enp0s3.service  
ip link set enp0s8 up  
dhcpcd enp0s8  
systemctl enable dhcpcd@enp0s8.service  
pacman -S net-tools  
pacman -S openssh  
vi /etc/ssh/sshd_config  
systemctl enable sshd  
pacman -S vim  
pacman -S git  
  
  
  
  
###0xxx  
环境变量  
/etc/profile  
ssh自动断开  
/etc/ssh/sshd_config  --ClientAliveCountMax  
  
