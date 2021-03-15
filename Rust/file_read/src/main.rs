/*
En un archivo se almacenará una secuencia de números enteros positivos, por ejemplo, considere este archivo:
12 23 43 55 67 765 213 12 1 4 90 34

El programa deberá leer el archivo y generar uno nuevo. El archivo nuevo tendrá las siguientes líneas:

    En la primera línea, los número ordenados de menor a mayor.
    En la segunda línea, el mayor número.
    En la tercer línea el menor número.
    En la cuarta línea el promedio.
    Tendrá una quinta línea pero estará vacía.
*/

use std::env;
use std::fs;
use std::io::{stdin, stdout, Write};

fn read(input: &mut String) {
    stdout().flush().expect("Couldn't flush buffer");
    stdin().read_line(input).expect("Failed to read");
}

fn es_mayor(a: i32, b: i32) -> bool {
    return a > b;
}

fn sort(arr: &mut Vec<i32>, len: usize) {
    for i in 0..len {
        for j in 0..len {
            if es_mayor(arr[j], arr[i]) {
                let temp: i32 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

fn main() {

    let args: Vec<String> = env::args().collect();
    let mut name : String = String::new();

    // Diferente comportamiento dependiendo de la cantidad de argumentos
    if args.capacity() > 1 { //Si hay argumentos...
        name = args[1].clone();
    } else {
        println!("Escriba el nombre del archivo a buscar: ");
        read(&mut name);
    }

    // Formatear ruta del archivo
    let path: String = format!("./{}.txt", name.trim());
    // Leer archivo
    let buffer: String = match fs::read_to_string(path.trim()) {
        Ok(buffer) => buffer,
        _ => {
            println!("Error leyendo el archivo");
            return;
        }
    };

    //Convertir String en un arreglo de enteros
    let mut numbers: Vec<i32> = buffer
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    let numbers_size: usize = numbers.len();
    sort(&mut numbers, numbers_size);

    //Arreglo ordenado de menor a mayor
    let min: i32 = numbers[0];
    let max: i32 = numbers[numbers_size - 1];

    let mut avg: f32 = 0.0;

    //Sumar posiciones del arreglo
    for i in numbers {
        avg += i as f32;
        print!("{} ", i);
    }

    println!(
        "\nNúmero Mayor: {}\nNúmero Menor: {}\nPromedio: {}\n",
        max,
        min,
        avg / numbers_size as f32
    ); //Podemos poner operaciones dentro de los argumentos de print
}
