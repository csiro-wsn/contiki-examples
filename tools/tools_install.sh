#install script for Contiki for SensorTag
sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
sudo apt-get update
sudo apt-get install -y gcc-arm-none-eabi	#Install ARM GCC EABI compiler
sudo apt-get install -y libnewlib-arm-none-eabi	#Install ARM new library
sudo apt-get install -y srecord 					#Install srec cat
sudo apt-get install -y ckermit		#Install Serial Terminal
sudo apt-get install -y libglib2.0 autoconf libtool libsdl-console libsdl-console-dev zlib1g-dev flex bison #dependencies for QEMU
sudo apt-get install -y gitg		#Git management
sudo apt-get install -y libncurses5-dev libncursesw5-dev
sudo apt-get remove -y modemmanager brltty	#Remove serial terminal interference
sudo adduser $USER dialout		#Add user permissions for dialout
git clone https://github.com/magicmonty/bash-git-prompt.git ~/.bash-git-prompt
git clone https://github.com/contiki-os/contiki.git ~/contiki-git --recursive	#Add contiki install script
cd ~/contiki-git
git submodule sync && git submodule update --init

#Adding environment variables
sudo echo source ~/contiki-examples/tools/tools_env.sh >> ~/.bashrc

#python tools
sudo apt-get install -y python-pip
sudo apt-get install -y python-wxgtk3.0
sudo pip install  pyserial
sudo pip install  readchar

#network tools
sudo apt-get install -y netcat6

