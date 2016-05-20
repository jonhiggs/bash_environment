#!/bin/sh
_get_augument_type() {
  # returns type of "getter" or "setter" with input string
  if echo "$1" | grep -E "^.+=.+$" &> /dev/null; then
    echo "setter"
  else
    echo "getter"
  fi
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

_get_auguments_type() {
  if [[ $(_check_argument_type_consistency $*) = 1 ]]; then
    echo $(_get_augument_type $1)
  fi
}

_get_action(){
  if [[ $# -eq 0 ]]; then
    echo "sourcer"
  else
    echo $(_get_auguments_type $*)
  fi
}

readonly ENV_FILE="${HOME}/.bash_environment"
[[ -f "${ENV_FILE}" ]] || touch "${ENV_FILE}"


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
