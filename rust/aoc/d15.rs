use std::fs;

fn calc_hash(input: &str) -> u32 {
    input
        .chars()
        .fold(0 as u32, |acc, x| ((acc + x as u32) * 17) % 256)
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let strs = input.split(",").collect::<Vec<&str>>();
    let mut total = 0;
    for s in strs {
        let hash = calc_hash(s);
        total += hash;
    }
    println!("Total: {}", total);
}
