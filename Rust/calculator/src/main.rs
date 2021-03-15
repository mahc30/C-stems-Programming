extern crate ferris_says;

use ferris_says::say;
use std::io::{stdin, stdout, Write};

fn read_user_input(input: &mut String) {
    stdout().flush().expect("Couldn't flush buffer");
    stdin().read_line(input).expect("Failed to read_user_input");
}

fn read_num(num: &mut f32) -> bool{
    stdout().flush().expect("Couldn't flush buffer");
    let mut buffer: String = String::new();
    read_user_input(&mut buffer);

    match buffer.trim().parse::<f32>() {
        Ok(res) => {
            *num = res;
        },
        Err(err) => {
            println!("Error leyendo numero\nError: {}", err);
            return false;
        } 
    };

    return true;
}

fn main() {
    
    let mut stdout = stdout();
    let welcome_message : String = String::from("Bienvenid@ a mi Calculadora");
    let width : usize = welcome_message.chars().count();
    say(welcome_message.as_bytes(), width, &mut stdout).unwrap();

    let mut status : bool = true;
    while status {
        let mut buffer = String::new();
        let mut num1 : f32 = 0.0;
        let mut num2 : f32 = 0.0; 

        print!("\nEscribe el primer Número: ");
        if !read_num(&mut num1) {continue;}

        print!("Escribe el segundo Número: ");
        if !read_num(&mut num2) {continue;}

        print!("Escribe la operación que quieres realizar (+ - * /): ");
        read_user_input(&mut buffer);
        let mut op: char = buffer.trim().chars().next().unwrap();

        // Validamos que la operación sea válida
        let operators = String::from("+-/*");

        if !operators.contains(op) {
            println!("Operación no reconocida");
            continue;
        }

        //  Switch-Case
        let result = match op {
            '+' => num1 + num2,
            '-' => num1 - num2,
            '/' => num1 / num2,
            '*' => num1 * num2,
            _ => panic!("Error de operación"),
        };
        println!("Resultado: {} {} {} = {}", num1, op, num2, result);

        println!("¿Continuar? (S/N)");
        buffer = String::new(); // Limpiamos el buffer
        read_user_input(&mut buffer);
        op = buffer.trim().to_lowercase().chars().next().unwrap();
        status = op != 'n';
    }
    
}
