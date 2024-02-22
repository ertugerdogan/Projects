#!/bin/sh

log_file="/var/volatile/log/agentlogs.log"
touch "${log_file}"

get_latest_software_version_number() {
  local data
  data=$(curl -s "http://192.168.1.102:8080/getLatestVersionNumber")
  echo "${data}" | jq -r '.latestVersion'
}

get_latest_software() {
  curl -o latest_software "http://192.168.1.102:8080/getLatestSoftware"
}

read_current_version() {
  local data
  data=$(cat software_info.json)
  echo "${data}" | jq -r '.currentVersion'
}

latest_version=$(get_latest_software_version_number)
current_version=$(read_current_version)

if [[ "${latest_version}" -gt "${current_version}" ]]; then
  get_latest_software
  echo "Successfully updated software to latest version" >> "$log_file"
else
  echo "Software is already up to date" >> "$log_file"  
fi
