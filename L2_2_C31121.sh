#!/bin/bash

NOMBRE_ARCHIVO=""
read -p "Ingrese el nombre del documento log (al final del nombre escriba .log):"  nombre_archivo

touch "$NOMBRE_ARCHIVO"

process=$1

# Ejecutar proceso
$process &

# Obtener PID
pid=$!


# Añadir header 
echo "Tiempo | %CPU | %Memoria" > "$NOMBRE_ARCHIVO"

# Loop para registrar 
while true; do
    if ps -p "$pid" > /dev/null; then
        echo "$(ps -p "$pid" -o time,%cpu,%mem --no-headers)" >> "$NOMBRE_ARCHIVO"
        sleep 1
    else
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