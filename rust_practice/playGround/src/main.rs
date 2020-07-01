fn main() {
    playGound::main();
}

mod playGound {
    pub fn main() {
        let mut s1 = String::from("hello");
        let len = calculate_length(&mut s1);
        println!("The length of '{}' is {}.", s1, len);
    }
    fn calculate_length(s: &mut String) -> usize {
        let t = calculate_length(s);
        s.len()
    }
    fn first_word(s: &String) -> usize {
        let bytes = s.as_bytes();

        for (i, &item) in bytes.iter().enumerate() {
            if item == b' ' {
                return i;
            }
        }

        s.len()
    }
}
