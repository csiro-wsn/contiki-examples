#install script for Contiki for SensorTag
sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi	#Install ARM GCC EABI compiler
sudo apt-get install ckermit		#Install Serial Terminal
sudo apt-get install libglib2.0 autoconf libtool libsdl-console libsdl-console-dev zlib1g-dev flex bison #dependencies for QEMU
sudo apt-get install gitg		#Git management
sudo apt-get remove modemmanager brltty	#Remove serial terminal interference
sudo adduser $USER dialout		#Add user permissions for dialout
git clone https://github.com/magicmonty/bash-git-prompt.git ~/.bash-git-prompt
git clone https://github.com/contiki-os/contiki.git ~/contiki-git --recursive	#Add contiki install script
cd ~/contiki-git
git submodule sync && git submodule update --init
