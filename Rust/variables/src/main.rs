fn main() {
    let a: i8 = -127;
    let b: u16 = 65535;
    let c: f32 = 50.23167581519675;
    let d: bool = true;
    let e: char = 'e';
    let array: [i32; 6] = [1,2,3,4,5,6];
    let tupla: (i8, u16, char) = (a, b, e);

    println!("a: {} b: {} c: {} d: {} e: {}",
        a,b,c,d,e);

    println!("Tupla.1 = {}", tupla.1);
    
    for i in 0.. array.len() {
        print!("array[{}] = {}\n", i, array[i]);
    }
}