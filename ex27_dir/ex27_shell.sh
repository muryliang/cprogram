#!/bin/sh

set -e
# if commands don't eixt normally   , exit immediatelly

#go somewhere safe
cd /tmp

#get the source to base ARP 1.5.2
#curl -L -O http://archive.apache.org/dist/apr/apr-1.5.2.tar.gz

#signify it
#curl -L -O http://archive.apache.org/dist/apr/apr-1.5.2.tar.gz.asc
#curl -L -O http://archive.apache.org/dist/apr/KEYS
#gpg --import KEYS
#gpg --verify apr-1.5.2.tar.gz.asc


#extract it and go into the source
#tar -zxv -f apr-1.5.2.tar.gz
#cd apr-1.5.2

#configure, make , make install
#./configure
#make
#sudo make install

#reset and cleanup
cd /tmp
#rm -rf apr-1.5.2 apr-1.5.2.tar.gz

#do the same with apr-util
#curl -L -O http://archive.apache.org/dist/apr/apr-util-1.5.4.tar.gz

#signify it
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.5.4.tar.gz.asc
gpg --verify apr-util-1.5.4.tar.gz.asc

#extract
tar -zxv -f apr-util-1.5.4.tar.gz
cd apr-util-1.5.4

#configuire ,make , make install
./configure --with-apr=/usr/local/apr
#you need that extra parameter to configure because
#apr-util can't really find it bacause ... who knows

make
sudo make install

#cleanup
cd /tmp
rm -rf apr-util-1.5.4* apr-1.5.4*
