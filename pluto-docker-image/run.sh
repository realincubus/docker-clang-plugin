cd ~
cd pluto
git pull
if [ $? -ne 0 ]; then
  echo "no changes found" 
  exit
fi
git submodule update
make
make install
