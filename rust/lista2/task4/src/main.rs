fn main() {}

fn count_bits(n: i64) -> u32 {
    format!("{:b}", n)
        .chars()
        .filter(|x| *x == '1')
        .count()
        .try_into() // tries to convert usize to inferred u32
        .unwrap()
}

#[test]
fn test_count_bits() {
    assert_eq!(count_bits(0), 0);
}

#[test]
fn test2() {
    assert_eq!(count_bits(4), 1);
}

#[test]
fn test3() {
    assert_eq!(count_bits(7), 3);
}

#[test]
fn test4() {
    assert_eq!(count_bits(9), 2);
}

#[test]
fn test5() {
    assert_eq!(count_bits(10), 2);
}
