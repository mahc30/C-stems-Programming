use std::fs;
use std::io::{stdin, stdout, Write};
use std::fs::OpenOptions;

fn main() {

   
    let mut command = String::new();

    println!("Enter in_file out_file function\n");
    read(&mut command);

    let instructions : Vec<String> = command.split(" ").map(|s| s.to_string()).collect();
    
    let in_file  = String::from(instructions[0].clone().trim());
    let out_file = String::from(instructions[1].clone().trim());
    let function = String::from(instructions[2].clone().trim());

    let path: String = format!("./{}.txt", in_file.trim());

    let in_file_buffer = fs::read_to_string(path).expect("Error leyendo el archivo");

    // Abrir archivo de salida
    let mut out = OpenOptions::new()
    .write(true)
    .append(true)
    .create(true)
    .open(out_file)
    .unwrap();

    for mut character in in_file_buffer.chars() {
        match function.as_str() {
            "xor" => character = enc_xor_function(character as u8) as char,
            _ => character = character,
        }
        
        if let Err(e) = write!(out, "{}", character as char) {
            eprintln!("Couldn't write to file: {}", e);
        }
    }    
}

fn enc_xor_function(data : u8) ->  u8{
    data ^ 0xFF
}

fn read(input: &mut String) {
    stdout().flush().expect("Couldn't flush in_file_buffer");
    stdin().read_line(input).expect("Failed to read");
}