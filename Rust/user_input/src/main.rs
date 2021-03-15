use std::io;

fn main() {
    
    println!("Escriba algo: ");
    let mut input : String = String::new();

    io::stdin().read_line(&mut input).expect("Failed to read");

    println!("Usted escribió: {}", input);
}