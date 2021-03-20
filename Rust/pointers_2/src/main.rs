fn main() {
    let (d1, mut d2, mut d3) = (3,1,4);

    println!("d1={} d2={} d3={}",d1,d2,d3);

    f1(--d1, &mut d2, &mut d3);
    println!("d1={} d2={} d3={}",d1,d2,d3);
}

fn f1(mut x : i32, y: &mut i32, z: &mut i32){
    *y = x + *z;
    *z = --(*y);
    x = *y - *z;
}

