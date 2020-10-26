/*
 Adaptación de:
 https://blog.knoldus.com/linux-system-call-fork-in-rust/

 Recordar agregar la dependencia
 nix = "0.18.0"
*/

use nix::sys::wait::wait;
use nix::unistd::ForkResult::{Child, Parent};
use nix::unistd::{fork, getpid, getppid};

fn main() {

    println!("Este proceso va a crear otro proceso\n\n");
    println!("El pid de este programa es: {}\n", getpid());
    let pid = fork();

    match pid.expect("No se pudo crear proceso hijo") {
        Child => println!(
            "PROCESO HIJO:\nSoy el hijo, mi pid es: {}\ny el pid de mi proceso padre es:{}\n",
            getpid(),
            getppid()
        ),
        Parent { child } => {
            match wait(){
                _ => println!("Error en proceso hijo")
            };
            println!(
                "PROCESO PADRE:\nProceso hijo con pid {} creado\n",
                child
            );
        }
    }
}