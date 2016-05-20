#!/usr/bin/env bash

_usage() {
  echo "$0 [name[=value] ...]"
}

_check_argument_type_consistency() {
  consistency=1;
  for arg in $@; do
    if [[ "$consistency" = 1 ]] && [[ $(_get_augument_type $1) != $(_get_augument_type ${arg}) ]]; then
      consistency=0
    fi
  done
  echo "$consistency"
}

_get_action() {
  [[ -z ${input} ]]           && echo "sourcer" && return 0
  [[ ${input} =~ /^[^=]+$/ ]] && echo "getter"  && return 0
  [[ ${input} =~ /^.+=.+$/ ]] && echo "setter"  && return 0
  return 1
}


readonly ENV_FILE="${HOME}/.bash_environment"
[[ -f "${ENV_FILE}" ]] || touch "${ENV_FILE}"

_actions $@ 

case $(_get_action $*) in
  "sourcer")
    cat ${ENV_FILE}
    ;;
  "getter")
    for key in $@; do
      echo cat ${ENV_FILE} | grep -E "^$key=.+$" ${ENV_FILE}
    done
    ;;
  "setter")
    for arg in $@; do
      key=$(echo "$arg" | grep -Eo "^.+=")
      if cat ${ENV_FILE} | grep -E "^$key.+$" &> /dev/null; then
        sed -i "s/^$key.*$/$arg/g" ${ENV_FILE}
      else
        echo "$arg" >> ${ENV_FILE}
      fi
    done
    ;;
esac

#! vim: ft=sh
