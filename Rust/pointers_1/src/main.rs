fn main() {
    let var1: i32 = 11;
    let _var2: i32 = 12;

    let _pvar1 : *const i32 = &var1;
    let _pvar2 : *mut i32;


    let mut x = 1;
    let mut y = 2;
    let px;

    println!("x {} y {}", x, y);

    px = &mut x;
    *px = 0;
    
    y = *px;

    println!("y {} *px {}",y, *px);

    let (mut a, mut b, mut c, mut d) = (0, 3, 8, 0); //Es lo mismo que:  int a=0, b=3, c=8, d=0;
    let (mut p1, mut p3) = (&mut a, &mut c);
    let p2;
    *p1 = 2;
    p2 = p3;
    *p2 = *p1 - b;
    d = (*p2)*(*p1);
    p3 = &mut d;
    b = a + b + c;

    println!("a: {} b: {} c: {} d: {}", a, b, c, d);

}
