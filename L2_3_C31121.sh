#!/bin/bash

# Directorio a monitorear
DIR_MONITOREADO="$HOME/IE0117/monitoreado"
LOG_FILE="$HOME/IE0117/monitor_log.txt"

# Asegurar que el directorio existe
mkdir -p "$DIR_MONITOREADO"

echo "$(date '+%Y-%m-%d %H:%M:%S') - Servicio iniciado, monitoreando $DIR_MONITOREADO" >> "$LOG_FILE"

# Monitorear continuamente cambios en el directorio
inotifywait -m -r -e create,modify,delete "$DIR_MONITOREADO" --format '%T - %w%f - %e' --timefmt '%Y-%m-%d %H:%M:%S' |
while read event; do
    echo "$event" >> "$LOG_FILE"
done