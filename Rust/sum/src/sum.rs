pub fn suma(a: i32, b: i32) -> i32 {
    a + b
}

pub fn sumatoria(numeros: &mut [i32], cantidad: i32) -> i32 {
    let mut acumulado : i32 = 0;
    
    for i in 0..numeros.len(){
        acumulado = suma(acumulado,numeros[i]);
    }

    return acumulado
}