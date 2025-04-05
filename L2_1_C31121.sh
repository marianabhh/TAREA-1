#!/bin/bash

# Verificaciones iniciales
[[ $(id -u) -ne 0 ]] && { echo "Error: Ejecutar comandos como root."; exit 1; }
[[ $# -ne 3 ]] && { echo "Error. Ejemplo de uso: $0 usuario grupo ruta del archivo"; exit 1; }
[[ ! -e "$3" ]] && { echo "Error: Archivo $3 no existe"; exit 1; }

usuario=$1; grupo=$2; archivo=$3

# Manejo de grupo
getent group "$grupo" >/dev/null || { groupadd "$grupo"; echo "Grupo '$grupo' fue creado exitosamente";  }

# Manejo de usuario
if id "$usuario" &>/dev/null; then
    if ! groups "$usuario" | grep -qw "$grupo"; then
        usermod -aG "$grupo" "$usuario" && echo "Usuario '$usuario' agregado exitosamente al grupo '$grupo'."
    else
        echo "El usuario '$usuario' ya pertenece al grupo '$grupo'."
    fi
else
    useradd -m -g "$grupo" "$usuario" && echo "Usuario '$usuario' creado y asignado al grupo '$grupo'."
fi

# Cambio de permisos
chown "$usuario:$grupo" "$archivo" && chmod 740 "$archivo" || { echo "Error"; exit 1; }

[[ $(stat -c %U:%G:%a "$archivo") == "$usuario:$grupo:740" ]] && echo "Configuración de permisos aplicada exitosamente." || { echo "Error"; exit 1; }