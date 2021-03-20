fn main() {
    let s1 = String::from("¿Había mencionado que en Rust los emojis son caracteres válidos 👁️ 👄👁️ ?");
    print_string(s1);

    println!("s1 = {}", s1);
}

fn print_string(my_string: String){
    println!("my string: {}", my_string);
}