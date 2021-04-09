fn main() {
    let vec : [i32; 4] = [1,2,3,4];
    let pvec = vec.as_ptr();

    unsafe{
        let a = *pvec.offset(1); // En C sería pvec + 1
        let b = *pvec.add(1) + 1;

        println!("a {} b {}", a, b);
    }


    /*
        int A[6]={2,3,1,0,9,6};
        int *ptr1;
        int *ptr2 = &A[5];
        ptr1 = A;
        ptr1+=2;
        *ptr1=5;
        ptr2--;
        *(ptr2)=*ptr1+*(ptr2-1)+*(ptr2+1);
    */

    

    unsafe{
    
        let mut arr: [i32; 6] = [2,3,1,0,9,6];
        print_array(arr.as_mut_ptr(), arr.len() as isize);
        let mut ptr1 : *mut i32;
        
        let ptr2 : *mut i32 = arr.as_mut_ptr().add(5);

        ptr1 = arr.as_ptr() as *mut i32; //Casteo explícito para indicar que el apuntador es variable
        
        //println!("arr.as_ptr() = {:p}\narr.as_mut_ptr().add(5); = {:p}", ptr1, ptr2);
        ptr1 = ptr1.add(2);
        //println!("ptr1.add(2) = {:p}", ptr1);

        *ptr1 = 5;
        
        *ptr2 = *ptr2.sub(1) - 1;

        *(ptr2) = *ptr1 + (*(ptr2.offset(-1)) + *ptr2);
        
        println!("ptr1: {:p}\n *ptr1: {}\nptr2: {:p}\n*ptr2: {}", ptr1, *ptr1, ptr2, *ptr2);
        print_array(arr.as_mut_ptr(), arr.len() as isize);
    }

    /*
    #include<stdio.h> 

    int main() 
    { 
        int *p;  
        int (*ptr)[5];  
        int arr[5]; 
        
        p = arr; 
        ptr = &arr;  
        printf("p = %p, ptr = %p\n", p, ptr); 
        p++;  
        ptr++; 
        printf("p = %p, ptr = %p\n", p, ptr); 
        return 0; 
    }

    */

    unsafe {
        let mut arr: [i32; 5] = [0;5];
        let mut p: *mut i32;
        let mut ptr : *mut [i32;5];

        p = arr.as_mut_ptr();
        ptr = &mut arr;

        println!("p = {:p}, ptr = {:p}", p, ptr);

        p = p.add(1);
        ptr = ptr.add(1);
        println!("p = {:p}, ptr = {:p}", p, ptr);
    }

    /*

    #include <stdio.h>

    int arr[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} };

    int main(void) {
        int (*p)[3][4] = &arr;
        printf("%d\n", ( (*p)[2] )[3] );
        printf("%d\n", *( *(*p + 2) + 3 ) );
        return 0;
    }

    */

    unsafe{
        let arr: [[i32;4];3] = [ [1,2,3,4], [5,6,7,8], [9,10,11,12]];

        let p: *const [[i32;4];3] = &arr;

        println!("{}", ((*p)[2])[3]);
        println!("{}",  *(*(*p).as_ptr().offset(2)).as_ptr().offset(3));
    }

    let nombres : [[char; 10]; 3] = [['F','u','l','a','n','o', '\0', '\0', '\0', '\0'], ['M','e','n','g','a','n','o', '\0', '\0', '\0'], ['P','e','r','a','n','o', '\0', '\0', '\0', '\0']];

    for nombre in &nombres{
        
        for caracter in nombre{
            print!("{}", caracter);
        }

        println!();
    }
}

fn print_array(arr: *mut i32, n: isize){

    println!("Printing array");
    unsafe{
    for i in 0..n {
        println!("array[{}] = {}",i, *arr.offset(i));
    }
}
}