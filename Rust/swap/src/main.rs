fn main() {

    let mut x = 1;
    let mut y = 2;
    println!("El valor de x es: {}\n El valor de y es: {}\n", x, y);

    swap(&mut x, &mut y);

    println!("El valor de x es: {}\n El valor de y es: {}\n", x, y);
}

fn swap(a: &mut i32, b: &mut i32){
      let temp : i32;
      temp = *a;
      *a = *b;
      *b = temp;
}



