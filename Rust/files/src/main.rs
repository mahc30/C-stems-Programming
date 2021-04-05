use std::fs;

fn main() {

    let filename = String::from("input.txt");
    println!("In file {}", filename);

    let contents = fs::read_to_string(filename)
        .expect("Something went wrong reading the file");

    println!("With text:\n{}", contents);

    let target_filename = String::from("output.txt");
    fs::write(target_filename, contents)
        .expect("Something went wrong writing the file");
}


