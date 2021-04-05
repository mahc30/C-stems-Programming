use std::io;

fn main() {
    
    let mut input : String;
    let num: i64;
    let key: char;
    let mut num_bytes: usize;

    println!("Ingrese el numero 325 y presione ENTER:\n");

    loop {
        
        input = String::new();
        num_bytes = io::stdin().read_line(&mut input).expect("Failed to read");
        num = match input.trim().parse(){
            Ok(result) => result,
            Err(err) => {
                println!("El texto ingresado no es un número {:?}", err);
                continue;
            },
        };

        println!("Se leyeron: {} bytes\nnum: {}\nnum to Hex {:#X}", num_bytes, num, num);
        
        let buffer: Vec<u8> = input.as_bytes().to_vec();
        
        for i in 0..buffer.capacity(){
            println!("{:#04X}", buffer[i]);
        }

        break;
    }
    
    print!("Ingrese cualquier tecla para terminar y presione ENTER:\n");
    input = String::new();
    
    num_bytes = io::stdin().read_line(&mut input).expect("Failed to read");
    key = input.chars().next().expect("No se pudo leer el caracter");
    println!("num_bytes: {}\nkey: {}", num_bytes, key);


    let key_to_hex = key as u32; //Casteo Explícito
    
   
    println!("{} Key to Hex {:#04X}", key, key_to_hex); 
}
