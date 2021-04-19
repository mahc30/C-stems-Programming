use std::io;

	fn read_user_input(buffer: &mut String) {
 	   buffer.clear();
 	   io::stdin().read_line(buffer).expect("Failed to read_user_input");
	}

	fn print_array(arr: &mut Vec<i32>){
   	 for i in 0..arr.len(){
  	      println!("data[{}] = {}", i, arr[i]);
  	  }
	}

	fn main() {
    
   	 let mut buffer = String::new();
    
    	println!("Escriba el tamaño del arreglo");
    	read_user_input(&mut buffer);
    
   	 let n : usize = buffer.trim().parse().unwrap();
   	 let mut data : Vec<i32> = Vec::with_capacity(n);
    
   	 for i in 0..n {
    
      	  println!("Escriba el elemento {}", i);
      	  read_user_input(&mut buffer);
        
    	    let elem : i32 = buffer.trim().parse().unwrap();
    	    data.push(elem);
   	 }
        print_array(&mut data);
    
  	 println!("Ingrese la posición donde quiere insertar");
  	 read_user_input(&mut buffer);
 	 let mut position : usize = buffer.trim().parse().unwrap();
 	 position = position - 1;
    
      data.push(0); //El vector necesita un nuevo espacio para mover los dato antes de la inserción
  
 	 for i in (position..data.len() - 1).rev() {
  	    data[i+1] = data[i];
  	}
  
 	 println!("Ingrese el valor a insertar");
 	 read_user_input(&mut buffer);

 	 data[position] = buffer.trim().parse().unwrap();

	 print_array(&mut data);
	}