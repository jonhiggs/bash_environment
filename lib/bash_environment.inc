_be_type() {
  # returns type of "getter" or "setter" with input string
  if echo "$1" | grep -E "s/^.+=.+$/" &> /dev/null; then
    echo "setter"
  else
    echo "getter"
  fi
}


bash_environment() {
  env_file="${HOME}/.bash_environment"
  [[ -f "${env_file}" ]] || touch "${env_file}"

  # verify that they are all setters or getters
  for arg in $@; do
    this_type=$(_be_type ${arg})
    return
    type=$(_be_type ${arg})
  done



  for arg in $@; do
    echo ${arg} | grep '=' &> /dev/null
    [[ $? -eq 0 ]] && action="setter" || action="getter"

  case $# in
    0) source ${env_file} ;;
    *)
      local k=$(echo "$1" | cut -d= -f1)
      local v=$(echo "$1" | cut -d= -f2)

      if [[ ! -z "$k" ]] && [[ ! -z "$v" ]]
        action="setter"
      else
        action="getter"
      fi
  esac

  else
    echo "Usage: bash_environment [key[=value]]"
    return 1
  fi

  case "${action}" in
    "sourcer") source ${env_file} ;;
    "getter")  grep "^$k=" ${env_file}; true ;;
    "setter")
      if grep "^$k=.*" &> /dev/null; then
        sed -i "s/^$k=.*/$k=$v/" ${env_file}
      else
        echo "$k=$v" >> ${env_file}
      fi
      ;;
  esac
}

#! vim: ft=sh
