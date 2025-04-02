fn main() {}

fn summy(strng: &str) -> i32 {
    strng
        .split_whitespace()
        .map(|str| str.parse::<i32>().unwrap())
        .sum()
}

#[test]
fn test_summy() {
    assert_eq!(summy("1 2 3 4"), 10);
}

#[test]
fn test2() {
    assert_eq!(summy(""), 0);
}

#[test]
fn test3() {
    assert_eq!(summy("1 -1 2 -2 3"), 3);
}

#[test]
fn test4() {
    assert_eq!(summy("25"), 25);
}

#[test]
fn test5() {
    assert_eq!(summy("-0 1 4 5"), 10);
}
