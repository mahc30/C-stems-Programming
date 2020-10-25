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

fn es_mayor(a: i32, b: i32) -> bool {
    a > b
}

fn sort(arr: &mut Vec<i32>, len: usize){ 
    for i in 0..len {
        for j in 0..len{
            if es_mayor(arr[j] , arr[i]){
                let temp: i32 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

fn main() {
    let buffer: String = String::from("1 9 3 4 8 5 7 40 3 2");

    let mut numbers: Vec<i32> = buffer
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    let numbers_size : usize = numbers.len();
    let mut max: i32 = numbers[0];
    let mut min: i32 = numbers[0];
    let mut avg: f32 = 0.0;
    
    sort(&mut numbers, numbers_size);

    for i in numbers {
        if es_mayor(i, max) {
            max = i;
        }

        if es_mayor(min, i){
            min = i;
        }

        avg += i as f32;
        print!("{} ", i);
    }

    println!("\nNúmero Mayor: {}\nNúmero Menor: {}\nPromedio: {}\n", max, min, avg / numbers_size as f32);
}
