#!/bin/zsh
if [[ $HOST == "linux1" ]] || [[ $HOST == "linux4" ]] || [[ $HOST == "linux6" ]]; then
  PFAD=/DATA/down/autofax
elif [[ $HOST == "linux2" ]]; then
  PFAD=/DATA/down/autofax
fi
cd "$PFAD"
# faxsql.cpp 
vi autofax.cpp autofax.h vorgaben.cpp DB.cpp DB.h konsole.cpp konsole.h -p
cd -

