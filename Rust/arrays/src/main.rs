fn main() {
    let vec : [i32; 4] = [1,2,3,4];
    let pvec = vec.as_ptr();

    unsafe{
        let a = *pvec.offset(1); // En C sería pvec + 1
        let b = *pvec.add(1) + 1;

        println!("a {} b {}", a, b);
    }

    let mut arr: [i32; 6] = [2,3,1,0,9,6];

    unsafe{

    let mut ptr1 : *mut i32;
    
    let ptr2 : *mut i32 = arr.as_mut_ptr().add(5);

    ptr1 = arr.as_ptr() as *mut i32; //Casteo explícito para indicar que el apuntador es variable
    
    ptr1 = ptr1.add(2);
    
    *ptr1 = 5;
    
    *ptr2.sub(1) = *ptr2.sub(1) - 1;

    *(ptr2) = *ptr1 + *(ptr2.offset(-1))
    
    }


    let nombres : [[char; 10]; 3] = [['F','u','l','a','n','o', '\0', '\0', '\0', '\0'], ['M','e','n','g','a','n','o', '\0', '\0', '\0'], ['P','e','r','a','n','o', '\0', '\0', '\0', '\0']];

    for nombre in &nombres{
        
        for caracter in nombre{
            print!("{}", caracter);
        }

        println!();
    }
}

/*
...
int A[6]={2,3,1,0,9,6};
int *ptr1;
int *ptr2 = &A[5];
ptr1 = A;
ptr1+=2;
*ptr1=5;
ptr2--;
*(ptr2)=*ptr1+*(ptr2-1)+*(ptr2+1);
...
*/