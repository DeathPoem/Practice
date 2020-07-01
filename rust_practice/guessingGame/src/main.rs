use rand::Rng;
use std::cmp::Ordering;
use std::io;

// https://doc.rust-lang.org/book/ch02-00-guessing-game-tutorial.html
fn main() {
    println!("Guess the number!");
    let security_num: u32 = rand::thread_rng().gen_range(1, 101);
    loop {
        println!("Please input your guess.");

        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(v) => v,
            Err(_) => continue,
        };

        println!("You guessed : {}", guess);

        match guess.cmp(&security_num) {
            Ordering::Less => println!("too small"),
            Ordering::Greater => println!("too big"),
            Ordering::Equal => {
                println!("you win");
                return;
            }
        }
    }
}
