fn main() {
    println!("Hello, world!");
}

fn descending_order(x: u64) -> u64 {
    let mut digits: Vec<u64> = x
        .to_string()
        .chars()
        .map(|c| c.to_digit(10).unwrap() as u64)
        .collect();

    digits.sort_by(|a, b| b.cmp(a));

    digits.iter().fold(0, |acc, &digit| acc * 10 + digit)
}

#[test]
fn test1() {
    assert_eq!(descending_order(0), 0);
}
#[test]
fn test2() {
    assert_eq!(descending_order(1), 1);
}
#[test]
fn test3() {
    assert_eq!(descending_order(15), 51);
}
#[test]
fn test4() {
    assert_eq!(descending_order(1021), 2110);
}
#[test]
fn test5() {
    assert_eq!(descending_order(123456789), 987654321);
}
