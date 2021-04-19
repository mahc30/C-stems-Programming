//uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize)

fn arrayCommon(arr1: &mut [i32], arr2: &mut [i32], arrRes: &mut [i32]){
    for i in 0 .. arr1.len(){
        if(arr1[i] == arr2[i]){
            arrRes[i] = arr1[i];
        }
    }
}

fn main() {
    let mut arr1 = [1,2,3,4,5,6];
    let mut arr2 = [9,8,7,6,5,4];
    let mut arr_res = [0; 6]; //Inicializar las primeras 6 posiciones en 0

    arrayCommon(&mut arr1, &mut arr2, &mut arr_res);

    printArray(&mut arr_res);
    println!("Hello, world!");
}

fn printArray(arr: &mut [i32]){
    for i in 0 .. arr.len(){
            println!("arr[{}] = {}", i, arr[i]);
    }
}