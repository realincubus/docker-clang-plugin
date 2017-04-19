#fetch
fetch(){
  cd ~/ClanPlugin
  git pull
  cd ~/pet
  git pull
  cd ~/pluto
  git pull
  cd ~/pluto/pluto_codegen_cxx
  git pull https://github.com/realincubus/pluto_codegen_cxx.git
  cd ~/clang_plugin_tests 
  git pull
}

# build
build(){
  cd ~/pluto/pluto_codegen_cxx
  make install
  cd ~/pet 
  make install
  cd ~/ClanPlugin
  ninja
}


#fetch
build
