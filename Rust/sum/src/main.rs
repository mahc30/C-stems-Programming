fn main() {
    let a = 1;
    let b = -5;
    
    let suma = sum(a, b);
    
    println!("El resultado es {}", suma);
}

fn sum(a: i32, b: i32) -> i32 {
    a + b
}
