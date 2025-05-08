#!/bin/bash

# Solicitar nombre de archivo
read -p "Ingrese el nombre del documento log (al final del nombre escriba .log): " nombre_archivo

# Validar que el archivo tenga extensión .log
if [[ "$nombre_archivo" != *.log ]]; then
    echo "El nombre del archivo debe terminar con '.log'"
    exit 1
fi

NOMBRE_ARCHIVO="$nombre_archivo"

# Verificar que se haya proporcionado el proceso
if [ -z "$1" ]; then
    echo "Debe especificar el nombre del proceso a monitorear."
    exit 1
fi

process=$1

# Ejecutar proceso
$process &

# Obtener PID
pid=$!

# Añadir encabezado
echo "Tiempo | %CPU | %Memoria" > "$NOMBRE_ARCHIVO"

# Loop para registrar
while true; do
    if ps -p "$pid" > /dev/null; then
        echo "$(ps -p "$pid" -o time,%cpu,%mem --no-headers)" >> "$NOMBRE_ARCHIVO"
        sleep 1
    else
        # Crear gráfico de memoria
        gnuplot <<EOF 
        set terminal png
        set output 'grafico_memoria.png'
        set title "Memoria vs Tiempo"
        set xlabel "Tiempo"
        set ylabel "Uso de Memoria"
        set xdata time
        set timefmt "%H:%M:%S"
        set format x "%H:%M:%S"
        plot "$NOMBRE_ARCHIVO" using 1:3 with lines title "Uso de Memoria"
EOF

        # Crear gráfico de CPU
        gnuplot <<EOF 
        set terminal png
        set output 'grafico_cpu.png'
        set title "CPU vs Tiempo"
        set xlabel "Tiempo"
        set ylabel "Uso de CPU"
        set xdata time
        set timefmt "%H:%M:%S"
        set format x "%H:%M:%S"
        plot "$NOMBRE_ARCHIVO" using 1:2 with lines title "Uso de CPU"
EOF

        echo "Terminado exitosamente!"
        break
    fi
done